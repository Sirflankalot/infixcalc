#pragma once

#include <string>
#include <vector>
#include <memory>

class ASTNode {
protected:
	int pos_start = 0;
	int pos_end = 0;
public:
	virtual double compute () = 0;
	virtual bool is_literal () = 0;
	virtual bool is_operator () = 0;
	void set_info(int s);
	void set_info(int s, int e);
};

class ASTNode_Literal : public ASTNode {
private:
	double value;
public:
	ASTNode_Literal(double in);
	double compute ();
	bool is_literal () { return true; };
	bool is_operator () { return false; };
};

class ASTNode_Operator : public ASTNode {
protected:
	std::shared_ptr<ASTNode> left, right;
public:
	ASTNode_Operator();
	ASTNode_Operator(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR);
	bool set_left(std::shared_ptr<ASTNode> in);
	bool set_right(std::shared_ptr<ASTNode> in);
 	virtual long get_precedence() = 0;
 	virtual bool get_associativity() = 0;
 	bool is_literal () { return false; };
	bool is_operator () { return true; };
};

class ASTNode_Add : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()    { return 2; };
	bool get_associativity() { return false; };
};

class ASTNode_Sub : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence() { return 2; };
	bool get_associativity() { return false; };
};

class ASTNode_Mul : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence() { return 3; };
	bool get_associativity() { return false; };
};

class ASTNode_Div : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence() { return 3; };
	bool get_associativity() { return false; };
};

class ASTNode_Exp : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence() { return 4; };
	bool get_associativity() { return true; };
};