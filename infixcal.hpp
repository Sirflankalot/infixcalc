#pragma once

#include <string>
#include <vector>

enum Tok_type : char {
	END, LITERAL, TOK_ADD, TOK_SUB, TOK_MUL, TOK_DIV, TOK_EXP, TOK_LPAR, TOK_RPAR
};
struct Token {
	Tok_type type;
	int value=0;
};

std::string rpn(std::vector<Token> inex);
std::vector<Token> tokenizer(std::string& in);
bool inline isDigit(char& x);
bool inline isLetter(char& x);
std::string inline toktostr (Token tk);
void inline printToks (std::vector<Token> tokList);