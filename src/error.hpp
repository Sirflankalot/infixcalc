#pragma once

#include <iosfwd>
#include <vector>
#include <string>

class Error {
private:
	std::string symbol;
	int location;
	bool error;
public:
	Error(std::string& nm, int loc, bool err);
	void print(std::ostream& out = std::cout);
};

class ErrorServer {
private:
	std::vector<Error> errors;
	std::ostream& os;
public:
	ErrorServer(std::ostream& o = std::cout);
	void add_error(Error e);
	void add_error(std::string nm, int loc, bool err);
	void print();
};