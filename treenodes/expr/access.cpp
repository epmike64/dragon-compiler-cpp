//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {

	 std::shared_ptr<Expr> Access::gen() {
		 return std::make_shared<Expr>(Access(this->array, this->index->reduce(), this->type));
	 }

	 void Access::jumping(int t, int f) {
		 emitJumps(reduce()->toString(), t, f);
	 }

	 std::string Access::toString() {
		 return this->array->toString() + "[" + index->toString() + "]";
	 }
}