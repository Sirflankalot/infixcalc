#include "lexer.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<Token> lexer(string in_str) {
	vector<Token> output;
	for (int i = 0; i < in_str.size(); i++) {
		Token tk;

		if (isDigit(in_str[i])) {
			tk.posbeg = i;
			tk.type = LITERAL;
			while (isDigit(in_str[i]) && i < in_str.size()) {
				tk.value *= 10;
				tk.value += in_str[i] - '0';
				i++;
			}
			tk.src = in_str.substr(tk.posbeg, i-tk.posbeg);
			tk.posend = i--;
		}

		else if (isLetter(in_str[i])) {
			tk.posbeg = i;
			tk.type = NAME;
			while (isLetter(in_str[i]) && i < in_str.size()) {
				i++;
			}
			tk.src = in_str.substr(tk.posbeg, i-tk.posbeg);
			tk.posend = i+1;
			i--;
		}

		else {
			auto control_setup = [&tk, &i, &in_str](Tok_type type){
				tk.type = type;
				tk.posbeg = i;
				tk.posend = i+1;
				tk.src = in_str.substr(tk.posbeg, 1);
			};

			switch(in_str[i]) {
				case '(':
					control_setup(TOK_LPAR);
					break;
				case ')':
					control_setup(TOK_RPAR);
					break;
				case '+':
					control_setup(TOK_ADD);
					break;
				case '-':
					control_setup(TOK_SUB);
					break;
				case '*':
					control_setup(TOK_MUL);
					break;
				case '/':
					control_setup(TOK_DIV);
					break;
				case '^':
					control_setup(TOK_EXP);
					break;
			}
		}

		output.push_back(tk);

	}

	output.push_back({END});

	return output;
}