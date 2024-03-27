//
// Created by mike on 1/6/24.
//

#ifndef JAVA_DRAGON_COMP_NODE_H
#define JAVA_DRAGON_COMP_NODE_H

#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include "token.h"
#include "types.h"
#include "lexer.h"

using namespace d_lex;

namespace d_treenode {

	 class DragonException : public std::exception {
	 private:
		  std::string message;

	 public:
		  DragonException(const std::string& m) : message(m) {}
		  char * what () {
			  return const_cast<char *>(message.c_str());
		  }
	 };

	 /**
	  *
	  */
	 class Node {
	 public:
		  static int labels;
		  int lexLine;

		  Node(): lexLine(d_lex::Lexer::line){}
		  Node(const Node& o) { this->lexLine = o.lexLine; }

		  int newLabel() { return ++Node::labels; }
		  void error(const std::string& s);
		  void emitLabel(int i);
		  void emit(const std::string &s);
		  bool operator==(const Node &rhs) const {
			  return lexLine == rhs.lexLine;
		  }
		  bool operator!=(const Node &rhs) const {
			  return !(rhs == *this);
		  }
		  virtual ~Node()  {}
	 };


	 /**
	  *
	  */
	 class Expr: public Node{
	 public:

		  static const std::shared_ptr<Expr> Null;

		  std::shared_ptr<Token> op;
		  std::shared_ptr<Type> type;

		  Expr(const std::shared_ptr<Token>& tok, const std::shared_ptr<Type>& p): op(tok), type(p){}
		  Expr(const Expr& o) {
			  op = o.op;
			  type = o.type;
		  }

		  virtual std::shared_ptr<Expr> gen();
		  virtual std::shared_ptr<Expr> reduce();
		  virtual void jumping(int t, int f);
		  virtual void emitJumps(const std::string& test, int t, int f);

		  bool operator==(const Expr &rhs) const {
			  return op == rhs.op && type == rhs.type;
		  }

		  bool operator!=(const Expr &rhs) const {
			  return !(rhs == *this);
		  }

		  virtual std::string toString(){
				return op->toString();
		  }
	 };

	 /**
	  *
	  */
	 class Logical: public Expr {
	 public:
		  std::shared_ptr<Expr> expr1, expr2;

		  Logical(const std::shared_ptr<Token> tok, std::shared_ptr<Expr> expr1, std::shared_ptr<Expr> expr2): Expr(tok, Type::Null), expr1(expr1), expr2(expr2){
			  type = (check(*expr1->type.get(), *expr2->type.get()));
		  }
		  virtual std::shared_ptr<Type> check(const Type& p1, const Type& p2);
		  std::shared_ptr<Expr> gen() override;

		  std::string toString() override {
				return expr1->toString() + " " + op->toString() + " " + expr2->toString();
		  }
	 };

	 /**
	  *
	  */
	 class Id: public Expr {
	 public:
		  int offset;

			Id(const std::shared_ptr<Token>& w_p, const std::shared_ptr<Type>& t_p, int b): Expr(w_p, t_p), offset(b){}

			std::string toString() override {
				return "" + op->toString() + std::to_string(offset);
			}
	 };

	 /**
	  *
	  */
	 class Constant: public Expr {
	 public:
		  static const std::shared_ptr<Constant> True;
		  static const std::shared_ptr<Constant> False;

		  Constant(const std::shared_ptr<Token>& tok_p, const std::shared_ptr<Type>& type_p): Expr(tok_p, type_p){}
		  Constant(int i): Expr(std::make_shared<Token>(Num(i)), Type::Int){}
		  void jumping(int t, int f) override;
	 };

	 class Op: public Expr {
	 public:
		  Op(const std::shared_ptr<Token>& tok_p, const std::shared_ptr<Type>& op_p): Expr(tok_p, op_p){}
		  std::shared_ptr<Expr> reduce() override;
	 };

	 class Unary: public Op {
	 public:
		  std::shared_ptr<Expr> expr_p;

		  Unary(const std::shared_ptr<Token>& tok_p, const std::shared_ptr<Expr>& x_p): Op(tok_p, Type::Null), expr_p(x_p){
			  this->type = Type::max(*Type::Int.get(), *expr_p->type.get());
			  if(this->type == Type::Null){
				  error("Type error");
			  }
		  }

		  std::shared_ptr<Expr> gen() override { return std::make_shared<Expr>(Unary(op, expr_p->reduce())); }
		  std::string toString() override { return op->toString() + " " + expr_p->toString(); }
	 };

	 class Arith: public Op {
	 public:
		  std::shared_ptr<Expr> expr1, expr2;

		  Arith(const std::shared_ptr<Token>& tok, const std::shared_ptr<Expr>& x1, const std::shared_ptr<Expr>& x2): Op(tok, Type::Null), expr1(x1), expr2(x2){
			  this->type = Type::max(*expr1->type.get(), *expr2->type.get());
			  if(this->type == Type::Null){
				  error("Type error");
			  }
		  }

		  std::shared_ptr<Expr> gen() { return std::make_shared<Expr>(Arith(op, expr1->reduce(), expr2->reduce())); }
		  std::string toString() override { return expr1->toString() + " " + op->toString() + " " + expr2->toString(); }
	 };



	 class Access: public Op {
	 public:
		  std::shared_ptr<Id> array;
		  std::shared_ptr<Expr> index;

		  Access(const std::shared_ptr<Id>& a, const std::shared_ptr<Expr>& i, const std::shared_ptr<Type>& p): Op(std::make_shared<Token>(Word("[]", TagId::INDEX)), p), array(a), index(i){}
		  std::shared_ptr<Expr> gen() override;
		  void jumping(int t, int f) override;
		  std::string toString() override;
	 };

	 class Temp: public Expr {
	 public:
		  static int count;
			int number;

			Temp(const std::shared_ptr<Type>& p): Expr(Word::Temp, p){
				number = ++ Temp::count;
			}
		  std::string toString() override { return "t" + number; }
	 };

	 class Or: public Logical {
	 public:
			Or(const std::shared_ptr<Token>& tok, const std::shared_ptr<Expr> x1, const std::shared_ptr<Expr> x2): Logical(tok, x1, x2){}
		  void jumping(int t, int f) {
			  int label = (t != 0) ? t : newLabel();
			  expr1->jumping(label, 0);
			  expr2->jumping(t, f);
			  if (t == 0)
				  emitLabel(label);
			}
	 };

	 class Rel: public Logical {
	 public:
		  Rel(const std::shared_ptr<Token>& tok, const std::shared_ptr<Expr>& x1, const std::shared_ptr<Expr>& x2): Logical(tok, x1, x2){}
		  void jumping(int t, int f) override;
		  std::shared_ptr<Type> check(const Type& p1, const Type& p2) override;
	 };

	 class Not: public Logical {
	 public:

		  Not(const std::shared_ptr<Token>& tok, const std::shared_ptr<Expr>& x2): Logical(tok, x2, x2){}
		  void jumping(int t, int f) { return expr2->jumping(f, t);}
		  std::string toString() override { return op->toString() + " " + expr2->toString(); }
	 };

	 class And: public Logical {
	 public:

		  And(const std::shared_ptr<Token>& tok, const std::shared_ptr<Expr>& x1, const std::shared_ptr<Expr>& x2): Logical(tok, x1, x2){}
		  void jumping(int t, int f) override;
	 };
}








#endif //JAVA_DRAGON_COMP_NODE_H
