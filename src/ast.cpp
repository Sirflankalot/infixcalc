#include "ast.hpp"
#include <cmath>
#include <memory>

void ASTNode::set_info(int s, int e) {
	pos_start = s;
	pos_end = e;
}

void ASTNode::set_info(int s) {
	pos_start = s;
	pos_end = s + 1;
}

ASTNode_Literal::ASTNode_Literal (double in) {
	value = in;
}

double ASTNode_Literal::compute () {
	return value;
}

ASTNode_Operator::ASTNode_Operator(){

}

ASTNode_Operator::ASTNode_Operator(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR) {
	left = inL;
	right = inR;
}

bool ASTNode_Operator::set(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR) {
	left = inL;
	right = inR;
	return true;
}

ASTNode_Par::ASTNode_Par(NodeType t) {
	pt = t;
}

double ASTNode_Add::compute () {
	return left->compute() + right->compute();
}

double ASTNode_Sub::compute () {
	return left->compute() - right->compute();
}

double ASTNode_Mul::compute () {
	return left->compute() * right->compute();
}

double ASTNode_Div::compute () {
	return left->compute() / right->compute();
}

double ASTNode_Exp::compute () {
	return std::pow(left->compute(), right->compute());
}