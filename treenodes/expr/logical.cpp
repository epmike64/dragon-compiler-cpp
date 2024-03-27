//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {

	 std::shared_ptr<Type> Logical::check(const Type &p1, const Type &p2) {
		 if (p1 == *Type::Bool.get() && p2 == *Type::Bool.get())
			 return Type::Bool;
		 else
			 return Type::Null;
	 }


	 std::shared_ptr<Expr> Logical::gen() {
		 int f = newLabel();
		 int a = newLabel();
		 Temp temp(type);
		 jumping(0, f);
		 emit(temp.toString() + " = true");
		 emit("goto L" + a);
		 emitLabel(f);
		 emit(temp.toString() + " = false");
		 emitLabel(a);
		 return std::make_shared<Expr>(temp);
	 }
}