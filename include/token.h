//
// Created by mike on 1/6/24.
//

#ifndef JAVA_DRAGON_COMP_TOKEN_H
#define JAVA_DRAGON_COMP_TOKEN_H

#include <boost/functional/hash.hpp>
#include <iostream>

namespace d_lex {


	 class Token {
	 public:

		  static const std::shared_ptr<Token> Null;
		  const int token;

		  explicit Token(int t): token(t){}
		  Token(const Token& t): token(t.token){}

		  bool operator==(const Token &rhs) const {
			  return token == rhs.token;
		  }

		  bool operator!=(const Token &rhs) const {
			  return !(rhs == *this);
		  }

		  size_t operator()() const {
				return token;
		  }

		  std::string toString() {
			  return ""+(char)token;
		  }

		  virtual ~Token(){}
	 };


	 /**
	  *
	  */
	 enum TagId: short  {
		  AND = 256, BASIC = 257, BREAK = 258, DO = 259, ELSE = 260, EQ = 261, FALSE = 262, GE = 263, ID = 264, IF = 265, INDEX = 266, LE = 267, MINUS = 268, NE = 269, NUM = 270,
		  OR = 271, REAL = 272, TEMP = 273, TRUE = 274, WHILE = 275, _NULL = 276
	 };

	 /**
	  *
	  */
	 class Word: public Token {
	 public:
		  static const std::shared_ptr<Word> And;
		  static const std::shared_ptr<Word> Or;
		  static const std::shared_ptr<Word> Eq;
		  static const std::shared_ptr<Word> Ne;
		  static const std::shared_ptr<Word> Le;
		  static const std::shared_ptr<Word> Ge;
		  static const std::shared_ptr<Word> Minus;
		  static const std::shared_ptr<Word> True;
		  static const std::shared_ptr<Word> False;
		  static const std::shared_ptr<Word> Temp;

		  const std::string lexeme;

		  Word(const std::string& lexeme, int tagId): Token(tagId), lexeme(lexeme) {}
		  Word(const Word& o): Token(o), lexeme(o.lexeme){}

		  bool operator==(const Word &rhs) const {
			  return static_cast<const d_lex::Token &>(*this) == static_cast<const d_lex::Token &>(rhs) &&
			         lexeme == rhs.lexeme;
		  }

		  bool operator!=(const Word &rhs) const {
			  return !(rhs == *this);
		  }

		  std::size_t operator() () const {
			  std::size_t seed = 0;
				boost::hash_combine(seed, token);
				boost::hash_combine(seed, lexeme);
			  return seed;
		  }

		  std::string toString()
		  {
			  return lexeme;
		  }

		  ~Word(){}
	 };


	 /**
	  *
	  */
	 class Num: public Token {
	 public:
		  const int numValue;

		  explicit Num(int v): Token(TagId::NUM), numValue(v){}
		  bool operator==(const Num& o){
			  return this->token == o.token && this->numValue == o.numValue;
		  }
		  ~Num(){}
	 };

	 /**
	  *
	  */
	 class Real: public Token {
	 public:
		  float value;

		  explicit Real(float v): Token(TagId::NUM), value(v){}
		  ~Real(){}
	 };
}

#endif //JAVA_DRAGON_COMP_TOKEN_H
