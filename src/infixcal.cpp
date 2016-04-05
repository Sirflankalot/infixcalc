#include <string>
#include <iostream>
#include <vector>
#include "ast.hpp"
#include "parser.hpp"

using namespace std;

int main (int argc, char * argv[]) {
	if (argc != 2) {
		cerr << "Invalid amount of arguments" << endl;
		return 3;
	}

	string input_expression (argv[1]);
	ShuntingYardParser syp (input_expression);
	syp.print_input();

	//Holy shit it works!
	auto leftnode = make_shared<ASTNode_Literal>(25);
	auto rightnode = make_shared<ASTNode_Literal>(25);
	auto middle = make_shared<ASTNode_Add>();
	middle->set(leftnode,rightnode);
	cout << "Test add: " << middle->compute() << ".\n";
}

