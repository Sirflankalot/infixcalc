#include <iostream>
#include <vector>
#include <string>
#include "error.hpp"

using namespace std;

Error::Error (ErrorType e, string& nm, int loc, bool err) {
	et = e;
	symbol = nm;
	location = loc;
	error = err;
}

bool Error::is_error () {
	return error;
}

void Error::print(std::ostream& out) {
	if (error) {
		out << "\033[1;31mError\033[0m at Char ";
	}
	else {
		out << "\033[1;35mWarning\033[0m at Char ";
	}
	switch (et) {
		case UNMATCHED_PAREN:
			out << location << ": Unmatched parethsis \"" << symbol << "\"\n";
			break;

		case UNEXPECTED_OPERATOR:
			out << location << ": Unexpected operator \"" << symbol << "\"\n";
			break;
	}
}