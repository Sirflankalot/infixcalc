#pragma once

#include <vector>
#include <memory>
#include <string>
#include "ast.hpp"

class ShuntingYardParser {
private:
	std::vector<std::shared_ptr<ASTNode>> final_stack;
	std::vector<std::shared_ptr<ASTNode>> operator_stack;
	std::vector<std::shared_ptr<ASTNode>> input_nodes;
	bool lexer(std::string& in_str);
public:
	ShuntingYardParser(std::string& in_str);
	bool add_tokens(std::string& in_str);
	void print_input();
	bool compute_ast();
	std::string get_rpn();
	std::shared_ptr<ASTNode> get_ast();
};