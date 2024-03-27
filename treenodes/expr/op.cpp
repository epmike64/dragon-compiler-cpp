//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {

	 std::shared_ptr<Expr> Op::reduce() {
		 std::shared_ptr<Expr> x = gen();
		 Temp t(this->type);
		 emit(t.toString() + " = " + x->toString());
		 return std::make_shared<Expr>(t);
	 }
}