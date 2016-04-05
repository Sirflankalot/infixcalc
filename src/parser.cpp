#include <vector>
#include <memory>
#include <iostream>
#include "ast.hpp"
#include "parser.hpp"

ShuntingYardParser::ShuntingYardParser (std::string& in) {
	this->add_tokens(in);
}

bool ShuntingYardParser::add_tokens(std::string& in) {
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
		switch (i->get_type()) {
			case LITERAL:
				std::cout << i->compute();
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
		std::cout << "\n";
	}
}

bool ShuntingYardParser::compute_ast() {
	
	
	return true;
}