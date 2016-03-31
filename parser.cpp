#include <vector>
#include <memory>
#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"

using namespace std;

ShuntingYardParser::ShuntingYardParser (vector<Token> in_tokens) {
	this->add_tokens(in_tokens);
}

bool ShuntingYardParser::add_tokens(vector<Token> in_tokens) {
	operator_stack.reserve(operator_stack.size() + in_tokens.size());
	final_stack.reserve(final_stack.size() + in_tokens.size());
	input_tokens.reserve(input_tokens.size() + in_tokens.size());

	for (auto tk : in_tokens) {
		shared_ptr<ASTNode> node;
		switch (tk.type) {
			case END:
				finished = true;
				return true;
				break;
			case LITERAL:
				node = make_shared<ASTNode_Literal>(tk.value);
				break;
			case TOK_ADD:
				node = make_shared<ASTNode_Add>();
				break;
			case TOK_SUB:
				node = make_shared<ASTNode_Sub>();
				break;
			case TOK_MUL:
				node = make_shared<ASTNode_Mul>();
				break;
			case TOK_DIV:
				node = make_shared<ASTNode_Div>();
				break;
			case TOK_EXP:
				node = make_shared<ASTNode_Exp>();
				break;
			default:
				continue;
		}

		cout << toktostr(tk);

		node->set_info(tk.posbeg, tk.posend);
		input_tokens.push_back(node);
	}

	return true;
}

bool ShuntingYardParser::compute_ast() {
	for (auto in_node : input_tokens){
		if (in_node->is_literal()) {

		}
	}
	
	return true;
}