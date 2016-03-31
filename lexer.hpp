#pragma once

#include <string>
#include <vector>
#include <iostream>

enum Tok_type : char {
	END, LITERAL, NAME, TOK_ADD, TOK_SUB, TOK_MUL, TOK_DIV, TOK_EXP, TOK_LPAR, TOK_RPAR
};

struct Token {
	Tok_type type;
	std::string src;
	int posbeg;
	int posend;
	float value=0;
};

inline bool charisin(char num, const char * list) {
	for (int i = 0; list[i]; i++)
		if (num == list[i])
			return true;
	return false;
};

inline bool isDigit(char& x) {
	return (('0' <= x && x <= '9'));
};

inline bool isLetter(char& x) {
	return (('A' <= x && x <='Z') || ('a' <= x && x <= 'z'));
};

inline bool isControl(char& x) {
	return charisin(x, "+-*/^() ");
};

inline std::string toktostr (Token& tk) {
	std::string out;
	switch (tk.type) {
		case END:
			out= "END";
			break;
		case TOK_ADD:
			out= "+";
			break;
		case TOK_SUB:
			out= "-";
			break;
		case TOK_MUL:
			out= "*";
			break;
		case TOK_DIV:
			out= "/";
			break;
		case TOK_EXP:
			out= "^";
			break;
		case TOK_LPAR:
			out= "(";
			break;
		case TOK_RPAR:
			out= ")";
			break;
		case LITERAL:
			out = std::to_string(tk.value);
			break;
		case NAME:
			out = tk.src;
			break;
	}

	return out;
};

inline void printToks (std::vector<Token>& tokList) {
	for (Token& i : tokList) {
		//std::cout << toktostr(i) << "\n";
		std::cout << i.src << "\n";
	}
};

std::vector<Token> lexer(std::string in_str);