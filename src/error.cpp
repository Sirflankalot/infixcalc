#include <iostream>
#include <vector>
#include <string>
#include "error.hpp"

using namespace std;

Error::Error (string& nm, int loc, bool err=true) {
	symbol = nm;
	location = loc;
	error = err;
}

void Error::print(std::ostream& out) {
	out << "Char " << location << " \"" << symbol << "\" ";
}