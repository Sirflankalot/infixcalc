#pragma once

#include <iosfwd>
#include <vector>
#include <string>

enum ErrorType : char {
	UNMATCHED_PAREN, UNEXPECTED_OPERATOR, NOT_SUPPORTED
};

class Error {
private:
	std::string symbol;
	ErrorType et;
	int location;
	bool error;
public:
	Error(ErrorType e, std::string& nm, int loc, bool err=true);
	bool is_error();
	void print(std::ostream& out = std::cout);
};