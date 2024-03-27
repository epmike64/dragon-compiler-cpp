//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 std::shared_ptr<Type> Set::check(const Type &p1, const Type &p2) {
		 if (Type::numeric(p1) && Type::numeric(p2))
			 return std::make_shared<Type>(p2);
		 else if (p1 == *Type::Bool.get() && p2 == *Type::Bool.get())
			 return std::make_shared<Type>(p2);
		 else
			 return Type::Null;
	 }

	 void Set::gen(int begin, int after) {
		 emit(id->toString() + " = " + expr->gen()->toString());
	 }
}