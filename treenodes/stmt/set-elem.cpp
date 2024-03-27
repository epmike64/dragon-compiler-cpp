//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 std::shared_ptr<Type> SetElem::check(const Type &p1, const Type &p2) {
		 if (dynamic_cast<const Array *>(&p1) != nullptr
		     || dynamic_cast<const Array *>(&p2) != nullptr) {
			 return Type::Null;
		 } else if (p1 == p2)
			 return std::make_shared<Type>(p2);
		 else if (Type::numeric(p1) && Type::numeric(p2))
			 return std::make_shared<Type>(p2);
		 else
			 return Type::Null;
	 }

	 void SetElem::gen(int begin, int after) {
		 std::string s1 = index->reduce()->toString();
		 std::string s2 = expr->reduce()->toString();
		 emit(array->toString() + " [ " + s1 + " ] = " + s2);
	 }
}