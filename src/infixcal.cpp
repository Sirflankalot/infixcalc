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
	#ifdef DEBUG
	syp.print_input();
	#endif
	if (syp.compute_ast()) {
		cout << "Answer = " << syp.answer() << endl;
	}
}

