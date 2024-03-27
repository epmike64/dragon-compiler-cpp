//
// Created by mike on 1/7/24.
//

#ifndef JAVA_DRAGON_COMP_TYPES_H
#define JAVA_DRAGON_COMP_TYPES_H

#include <memory>
#include <unordered_map>
#include "token.h"

namespace d_lex {

	 class Type : public Word {
	 public:
		  const int width;

		  Type(const std::string &lexeme, int tagId, int width) : Word(lexeme, tagId), width(width) {}

		  Type(const Type &o) : Word(o), width(o.width) {}

		  virtual ~Type() {}

		  static const std::shared_ptr<Type> Null;
		  static const std::shared_ptr<Type> Int;
		  static const std::shared_ptr<Type> Float;
		  static const std::shared_ptr<Type> Char;
		  static const std::shared_ptr<Type> Bool;

		  static bool numeric(const Type &t);

		  static std::shared_ptr<Type> max(const Type &p1, const Type &p2);

		  bool operator==(const Type &rhs) const {
			  return static_cast<const d_lex::Word &>(*this) == static_cast<const d_lex::Word &>(rhs) &&
			         width == rhs.width;
		  }

		  bool operator!=(const Type &rhs) const {
			  return !(rhs == *this);
		  }
//		  friend bool operator==(const Type &c1, const Type &c2) ;
//		  friend bool operator!=(const Type &c1, const Type &c2);

	 };

	 class Array : public Type {
	 public:
		  std::shared_ptr<Type> of;
		  int size = 1;

		  Array(int sz, std::shared_ptr<Type> &p) : Type("[]", TagId::INDEX, sz * p->width), size(sz), of(p) {}

		  Array(const Array &a) : Type(a), size(a.size), of(a.of) {}

		  ~Array() {}

		  std::string toString() {
			  return "[" + std::to_string(size) + "]" + of->toString();
		  }
	 };

//	 class Env {
//		  //map<Word, Id>
//		  std::unordered_map<Word, Id> table;
//	 };
}

#endif //JAVA_DRAGON_COMP_TYPES_H
