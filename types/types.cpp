//
// Created by mike on 1/7/24.
//

#include "../include/types.h"

namespace d_lex {


	 const std::shared_ptr<Type> Type::Null = std::make_shared<Type>(Type("null", TagId::_NULL, 1));
	 const std::shared_ptr<Type> Type::Int = std::make_shared<Type>(Type("int", TagId::BASIC, 4));
	 const std::shared_ptr<Type> Type::Float = std::make_shared<Type>(Type("float", TagId::BASIC, 8));
	 const std::shared_ptr<Type> Type::Char = std::make_shared<Type>(Type("char", TagId::BASIC, 1));
	 const std::shared_ptr<Type> Type::Bool = std::make_shared<Type>(Type("bool", TagId::BASIC, 1));

	 std::ostream &operator<<(std::ostream &strm, const Type &t) {
		 return strm << t.lexeme;
	 }


	 bool Type::numeric(const Type &p) {
		 if (p == *Type::Char.get() || p == *Type::Int.get() || p == *Type::Float.get())
			 return true;
		 else
			 return false;
	 }

	 std::shared_ptr<Type> Type::max(const Type &p1, const Type &p2) {
		 if (!numeric(p1) || !numeric(p2))
			 return Null;
		 else if (p1 == static_cast<const Type &>(*Float.get()) || p2 == static_cast<const Type>(*Float.get()))
			 return Float;
		 else if (p1 == *Int.get() || p2 == *Int.get())
			 return Int;
		 else
			 return Char;
	 }

	 std::ostream &operator<<(std::ostream &strm, const Array &a) {
		 return strm << "[" << a.size << "] " << a.of;
	 }

}