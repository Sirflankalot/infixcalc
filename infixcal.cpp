#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "infixcal.hpp"

using namespace std;

bool inline isDigit(char& x) {
	return ('0' <= x && x <= '9');
}

bool inline isLetter(char& x) {
	return (('A' <= x && x <='Z') || ('a' <= x && x <= 'z'));
}

string inline toktostr (Token tk) {
	string out;
	switch (tk.type) {
		case END:
			out.append("END");
			break;
		case TOK_ADD:
			out.append("+");
			break;
		case TOK_SUB:
			out.append("-");
			break;
		case TOK_MUL:
			out.append("*");
			break;
		case TOK_DIV:
			out.append("/");
			break;
		case TOK_EXP:
			out.append("^");
			break;
		case TOK_LPAR:
			out.append("(");
			break;
		case TOK_RPAR:
			out.append(")");
			break;
		case LITERAL:
			out = to_string(tk.value);
			break;
	}
	out.append("\n");

	return out;
}

void inline printToks (vector<Token> tokList) {
	for (Token& i : tokList) {
		cout << toktostr(i);
	}
}

int main (int argc, char * argv[]) {
	if (argc != 2) {
		cerr << "Invalid amount of arguments" << endl;
		return 3;
	}

	string input_expression (argv[1]);
	vector<Token> tokens = tokenizer(input_expression);
	printToks(tokens);
}

//Basic tokenizer that ignores what it doesn't know
vector<Token> tokenizer(string& in) {
	vector<Token> output;

	for (int i = 0; i < in.length(); i++) {
		Token tk;

		if(in[i] == '+')
			tk.type = TOK_ADD;

		else if(in[i] == '-')
			tk.type = TOK_SUB;

		else if(in[i] == '*')
			tk.type = TOK_MUL;

		else if(in[i] == '/')
			tk.type = TOK_DIV;

		else if(in[i] == '^')
			tk.type = TOK_EXP;

		else if(in[i] == '(')
			tk.type = TOK_LPAR;

		else if(in[i] == ')')
			tk.type = TOK_RPAR;

		else if (isDigit(in[i])) {
			tk.type = LITERAL;
			tk.value = stoll(in.substr(i, in.size()));
			while (isDigit(in[i]) && i < in.size()) i++;
			i--; 
		}

		else {
			cerr << "Unknown symbol \"" << in[i] << "\" at pos " << i << "." << endl;
			exit(EXIT_FAILURE);
		}
		output.push_back(tk);
	}

	output.push_back({END});

	return output;
}

string rpn(vector<Token> inex) {
	vector<Token> stack;
	string result;

	return result;
}