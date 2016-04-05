#pragma once

#include <string>
#include <vector>
#include <memory>

enum NodeType : char {
	END, LITERAL, VAR, FUNC, ADD, SUB, MUL, DIV, EXP, LPAR, RPAR
};

class ASTNode {
protected:
	int pos_start = 0;
	int pos_end = 0;
public:
	void set_info(int s);
	void set_info(int s, int e);
	virtual double compute () = 0;
	virtual NodeType get_type() = 0;
	virtual long get_precedence() = 0;
	virtual bool get_associativity() = 0;
	virtual bool is_literal() = 0;
	virtual bool is_op() = 0;
	virtual bool is_par() = 0;
	virtual bool set (std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR) = 0;
};

class ASTNode_Literal : public ASTNode {
private:
	double value;
public:
	ASTNode_Literal(double in);
	double compute ();
	bool is_par()             { return false; };
	bool is_op()              { return false; };
	bool is_literal()         { return true; };
	NodeType get_type()       { return LITERAL; };

	long get_precedence()     { throw "Precedence on a literal"; };
	bool get_associativity()  { throw "Associativity on a literal"; };
	bool set(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR)
	                          { throw "Set on a literal"; (void) inL; (void) inR; };
};

class ASTNode_Operator : public ASTNode {
protected:
	std::shared_ptr<ASTNode> left, right;
public:
	ASTNode_Operator();
	ASTNode_Operator(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR);
	bool set (std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR);
	bool is_par()             { return false; };
	bool is_op()              { return true; };
	bool is_literal()         { return false; };
};

class ASTNode_Add : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()     { return 2; };
	bool get_associativity()  { return false; };
	NodeType get_type()       { return ADD; };
};

class ASTNode_Sub : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()     { return 2; };
	bool get_associativity()  { return false; };
	NodeType get_type()       { return SUB; };
};

class ASTNode_Mul : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()     { return 3; };
	bool get_associativity()  { return false; };
	NodeType get_type()       { return MUL; };
};

class ASTNode_Div : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()     { return 3; };
	bool get_associativity()  { return false; };
	NodeType get_type()       { return DIV; };
};

class ASTNode_Exp : public ASTNode_Operator {
public:
	double compute ();
	long get_precedence()     { return 4; };
	bool get_associativity()  { return true; };
	NodeType get_type()       { return EXP; };
};

class ASTNode_Par : public ASTNode {
private:
	NodeType pt = END;
public:
	ASTNode_Par(NodeType t);
	long get_precedence() 	  { return -1; };
	bool get_associativity()  { return false; };
	NodeType get_type()       { return pt; };
	bool is_par()             { return true; };
	bool is_op()              { return false; };
	bool is_literal()         { return false; };

	double compute()          { throw "Compute on a parenthesis"; };
	bool set(std::shared_ptr<ASTNode> inL, std::shared_ptr<ASTNode> inR)
	                          { throw "Set on a parenthesis"; (void) inL; (void) inR; };
};