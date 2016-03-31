#pragma once

#include <string>
#include <vector>
#include "lexer.hpp"

std::string rpn(std::vector<Token> inex);
std::vector<Token> tokenizer(std::string& in);
