//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {


	 std::shared_ptr<Type> Rel::check(const Type &p1, const Type &p2) {
		 if (dynamic_cast<const Array *>(&p1) != nullptr || dynamic_cast<const Array *>(&p2) != nullptr)
			 return Type::Null;
		 else if (p1 == p2)
			 return Type::Bool;
		 else
			 return Type::Null;
	 }

	 void Rel::jumping(int t, int f) {
		 std::shared_ptr<Expr> a = expr1->reduce();
		 std::shared_ptr<Expr> b = expr2->reduce();
		 std::string test = a->toString() + " " + op->toString() + " " + b->toString();
		 emitJumps(test, t, f);
	 }
}