//
// Created by mike on 1/12/24.
//

#ifndef JAVA_DRAGON_COMP_STMT_H
#define JAVA_DRAGON_COMP_STMT_H


#include "node.h"
namespace d_treenode {

	 class Stmt : public Node {
	 public:
		  const static std::shared_ptr<Stmt> Null;
		  static std::shared_ptr<Stmt> Enclosing;
		  int after = 0;

		  Stmt(){}
		  virtual void gen(int begin, int after) {}

		  bool operator==(const Stmt &rhs) const {
			  return static_cast<const d_treenode::Node &>(*this) == static_cast<const d_treenode::Node &>(rhs) &&
			         after == rhs.after;
		  }
	 };

	 class Break : public Stmt {
	 public:
		  std::shared_ptr<Stmt> stmt;

		  Break() {
			  if (Stmt::Enclosing == Stmt::Null)
				  error("unenclosed break");
			  stmt = Stmt::Enclosing;
		  }

		  void gen(int begin, int after) {
			  emit("goto L" + stmt->after);
		  }

		  bool operator==(const Break &rhs) const {
			  return static_cast<const d_treenode::Stmt &>(*this) == static_cast<const d_treenode::Stmt &>(rhs) &&
			         stmt == rhs.stmt;
		  }
	 };


	 class Do : public Stmt {
	 public:
		  std::shared_ptr<Expr> expr = Expr::Null;
		  std::shared_ptr<Stmt> stmt = Stmt::Null;

		  void init(const std::shared_ptr<Stmt> &s, const std::shared_ptr<Expr> &x);

		  void gen(int begin, int after) override;

		  bool operator==(const Do &rhs) const {
			  return static_cast<const d_treenode::Stmt &>(*this) == static_cast<const d_treenode::Stmt &>(rhs) &&
			         expr == rhs.expr &&
			         stmt == rhs.stmt;
		  }
	 };

	 class Else : public Stmt {
	 public:
		  std::shared_ptr<Expr> expr;
		  std::shared_ptr<Stmt> stmt1, stmt2;

		  Else(const std::shared_ptr<Expr> &x, const std::shared_ptr<Stmt> &s1, const std::shared_ptr<Stmt> &s2) : expr(
				  x), stmt1(s1), stmt2(s2) {
			  if (expr->type != Type::Bool)
				  expr->error("boolean required in if");
		  }

		  void gen(int begin, int after) override;

		  bool operator==(const Else &rhs) const {
			  return static_cast<const d_treenode::Stmt &>(*this) == static_cast<const d_treenode::Stmt &>(rhs) &&
			         expr == rhs.expr &&
			         stmt1 == rhs.stmt1 &&
			         stmt2 == rhs.stmt2;
		  }
	 };

	 class If : public Stmt {
	 public:
		  std::shared_ptr<Expr> expr;
		  std::shared_ptr<Stmt> stmt;

		  If(const std::shared_ptr<Expr> &x, const std::shared_ptr<Stmt> &s) : expr(x), stmt(s) {
			  if (expr->type != Type::Bool)
				  expr->error("boolean required in if");
		  }

		  void gen(int begin, int after) override;

		  bool operator==(const If &rhs) const {
			  return static_cast<const d_treenode::Stmt &>(*this) == static_cast<const d_treenode::Stmt &>(rhs) &&
			         expr == rhs.expr &&
			         stmt == rhs.stmt;
		  }
	 };

	 class Seq : public Stmt {
	 public:
		  std::shared_ptr<Stmt> stmt1;
		  std::shared_ptr<Stmt> stmt2;

		  Seq(const std::shared_ptr<Stmt> &s1, const std::shared_ptr<Stmt> &s2) : stmt1(std::move(s1)), stmt2(std::move(s2)) {}

		  void gen(int begin, int after) override;

		  bool operator==(const Seq &rhs) const {
			  return static_cast<const d_treenode::Stmt &>(*this) == static_cast<const d_treenode::Stmt &>(rhs) &&
			         stmt1 == rhs.stmt1 &&
			         stmt2 == rhs.stmt2;
		  }
	 };

	 class Set : public Stmt {
	 public:
		  std::shared_ptr<Id> id;
		  std::shared_ptr<Expr> expr;

		  Set(const std::shared_ptr<Id> &i, const std::shared_ptr<Expr> &x) : id(i), expr(x) {
			  if (check(*id->type.get(), *expr->type.get()) == Type::Null)
				  error("type error");
		  }

		  std::shared_ptr<Type> check(const Type &p1, const Type &p2);

		  void gen(int begin, int after) override;


	 };

	 class SetElem : public Stmt {
	 public:

		  std::shared_ptr<Id> array;
		  std::shared_ptr<Expr> index;
		  std::shared_ptr<Expr> expr;

		  SetElem(const std::shared_ptr<Access> &x, const std::shared_ptr<Expr> &y) : array(x->array), index(x->index),
		                                                                              expr(y) {
			  if (check(*x->type.get(), *expr->type.get()) == Type::Null)
				  error("type error");
		  }

		  std::shared_ptr<Type> check(const Type &p1, const Type &p2);

		  void gen(int begin, int after) override;

	 };

	 class While : public Stmt {
	 public:

		  std::shared_ptr<Expr> expr = Expr::Null;
		  std::shared_ptr<Stmt> stmt = Stmt::Null;

		  void gen(int begin, int after) override;

		  void init(const std::shared_ptr<Expr> &x, const std::shared_ptr<Stmt> &s);

	 };
}
#endif //JAVA_DRAGON_COMP_STMT_H
