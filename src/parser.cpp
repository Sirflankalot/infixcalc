#include <vector>
#include <memory>
#include <iostream>
#include "ast.hpp"
#include "parser.hpp"
#include "error.hpp"

ShuntingYardParser::ShuntingYardParser (std::string& in) {
	this->add_tokens(in);
}

bool ShuntingYardParser::add_tokens(std::string& in) {
	input_string = in;

	this->lexer(in);

	final_stack.reserve(input_nodes.size());

	return true;
}

bool ShuntingYardParser::lexer(std::string& in) {
	auto isDigit  = [](char v) { return ('0' <= v && v <= '9'); };
	auto isNumber = [](char v) { return ('0' <= v && v <= '9') || v == '-' || v == '.'; };
	auto isLetter = [](char v) { return ('A' <= v && v <= 'Z') || ('a' <= v && v <= 'z'); };

	bool stained = false;

	for (int i = 0; i < in.size();) {
		std::shared_ptr<ASTNode> cur_node;

		if (isNumber(in[i]) && !stained) {
			double   num = 0.0;
			bool     neg = false;
			int    start = i;
			
			if (in[i] == '-') {                             //If it's a dash, the number is negitive
				neg = true;
				if (i+1 < in.size()){                       //Only advance if you can
					i++;
					if ( !isDigit(in[i]) ||                 //If the next number isn't a digit,
					    (input_nodes.size() &&              //(Short circut check for an empty node stack)
					     !input_nodes.back()->is_op() &&    //Or if the last node wasn't an operator
					      !input_nodes.back()->is_par())) { //Or a parenthesis
						i--;                                //it's meant to be a minus sign.
						stained = true;
						continue;
					}
				}
			}
			
			while (i < in.size() && isDigit(in[i])) {
				num *= 10;
				num += in[i] - '0';
				i++;
			}
			
			if (i+1 < in.size() && in[i] == '.') {
				i++;
				long divisor = 10;
				while (i < in.size() && isDigit(in[i])) {
					num += (in[i] - '0') / (double) divisor;
					divisor *= 10;
					i++;
				}
			}
			
			if (neg)
				num *= -1;

			cur_node = std::make_shared<ASTNode_Literal>(num);
			cur_node->set_info(start, i);
			i--;
		}

		else if (isLetter(in[i])) {
			std::string name;
			int start = i;

			while (i < in.size() && isLetter(in[i])) {
				i++;
			}

			name = in.substr(start, i-start);
			i--;

			//When I get around to supporting names
			//cur_node = std::make_shared<ASTNode_Name> (name);
			//cur_node-> set_info(start, i);

		}

		else {
			auto opset = [&cur_node, &i]() { cur_node->set_info(i); };
			switch (in[i]) {
				case '+':
					cur_node = std::make_shared<ASTNode_Add>();
					opset();
					break;
				case '-':
					cur_node = std::make_shared<ASTNode_Sub>();
					opset();
					break;
				case '*':
					cur_node = std::make_shared<ASTNode_Mul>();
					opset();
					break;
				case '/':
					cur_node = std::make_shared<ASTNode_Div>();
					opset();
					break;
				case '^':
					cur_node = std::make_shared<ASTNode_Exp>();
					opset();
					break;
				case '(':
					cur_node = std::make_shared<ASTNode_Par>(LPAR);
					opset();
					break;
				case ')':
					cur_node = std::make_shared<ASTNode_Par>(RPAR);
					opset();
					break;
				default:
					i++;
					continue;
			}
		}

		stained = false;
		input_nodes.push_back(cur_node);
		i++;
	}

	return true;
}

void ShuntingYardParser::print_input() {
	for (auto i : input_nodes) {
		print_node(i);
		std::cout << "\n";
	}
}

void ShuntingYardParser::print_node(std::shared_ptr<ASTNode> n) {
	switch (n->get_type()) {
		case LITERAL:
			std::cout << n->compute();
			break;
		case ADD:
			std::cout << '+';
			break;
		case SUB:
			std::cout << '-';
			break;
		case MUL:
			std::cout << '*';
			break;
		case DIV:
			std::cout << '/';
			break;
		case EXP:
			std::cout << '^';
			break;
		case LPAR:
			std::cout << '(';
			break;
		case RPAR:
			std::cout << ')';
			break;
		default:
			break;
	}

}

bool ShuntingYardParser::compute_ast() {
	auto push_op_to_final = [this](std::shared_ptr<ASTNode> node) {
		if (final_stack.size() >= 2) {
			auto nodeR = final_stack.back();
			final_stack.pop_back();

			auto nodeL = final_stack.back();
			final_stack.pop_back();

			#ifdef DEBUG
			std::cout << "DEBUG: ";
			print_node(nodeL);
			print_node(node);
			print_node(nodeR);
			std::cout << "\n";
			#endif

			node->set(std::move(nodeL), std::move(nodeR));
			final_stack.push_back(std::move(node));
		}
		else {
			std::string s = input_string.substr(node->get_start(),node->get_enddist());
			Error e (UNEXPECTED_OPERATOR, s, node->get_start());
			errors.push_back(e);
		}
	};

	for (auto n : input_nodes) {
		if (n->is_literal()) {
			final_stack.push_back(n);
		}
		else if (n->is_op()) {
			if (operator_stack.size() != 0) {
				auto osnp = operator_stack.back()->get_precedence();
				auto cura = n->get_associativity();
				auto curp = n->get_precedence();
				if ((!cura && curp <= osnp) || (cura && curp < osnp)) {
					push_op_to_final(operator_stack.back());
					operator_stack.pop_back();
				}
			}
			operator_stack.push_back(n);
		}

		else if (n->is_par() && n->get_type() == LPAR) {
			operator_stack.push_back(n);
		}

		else if (n->is_par() && n->get_type() == RPAR) {
			while (operator_stack.size() && operator_stack.back()->get_type() != LPAR) {
				push_op_to_final(operator_stack.back());
				operator_stack.pop_back();
			}

			if (operator_stack.size() == 0) {
				std::string s = input_string.substr(n->get_start(),n->get_enddist());
				Error e (UNMATCHED_PAREN, s, n->get_start());
				errors.push_back(e);
			}

			else if (operator_stack.back()->get_type() == LPAR) {
				operator_stack.pop_back();
			}

		}

		#ifdef DEBUG

		std::cout << "STACK: ";
		for (auto i : operator_stack) {
			print_node(i);
			std::cout << " ";
		}
		std::cout << "\n";

		std::cout << "FINAL: ";
		for (auto i : final_stack) {
			print_node(i);
			std::cout << " ";
		}
		std::cout << "\n\n";

		#endif
	}

	while (operator_stack.size()) {
		auto n = operator_stack.back();
		if (n->get_type() == LPAR) {
			std::string s = input_string.substr(n->get_start(),n->get_enddist());
			Error e (UNMATCHED_PAREN, s, n->get_start(), false);
			errors.push_back(e);

			operator_stack.pop_back();
		}

		else if (n->get_type() == RPAR) {
			std::string s = input_string.substr(n->get_start(),n->get_enddist());
			Error e (UNMATCHED_PAREN, s, n->get_start());
			errors.push_back(e);

			operator_stack.pop_back();
			break;
		}

		else {
			push_op_to_final(operator_stack.back());
			operator_stack.pop_back();
		}
	}

	bool error = false;
	for (Error e : errors) {
		e.print();
		if (e.is_error()) {
			error = true;
		}
	}

	if (error){
		return false;
	}
	else {
		return true;
	}
}

double ShuntingYardParser::answer() {
	return final_stack[0]->compute();
}