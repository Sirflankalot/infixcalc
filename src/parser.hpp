#pragma once

#include <vector>
#include <memory>
#include "ast.hpp"
#include "lexer.hpp"

class ShuntingYardParser {
private:
	std::vector<std::shared_ptr<ASTNode>> operator_stack;
	std::vector<std::shared_ptr<ASTNode>> final_stack;
	std::vector<std::shared_ptr<ASTNode>> input_tokens;
	bool finished = false;
public:
	ShuntingYardParser(std::vector<Token> in_tokens);
	bool add_tokens(std::vector<Token> in_tokens);
	bool compute_ast();
	std::vector<Token> get_rpn();
	std::shared_ptr<ASTNode> get_ast();
};