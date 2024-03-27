//
// Created by mike on 1/6/24.
//

#include "../include/token.h"

namespace d_lex {

	 const std::shared_ptr<Token> Token::Null = std::make_shared<Token>(0);


	 std::ostream &operator<<(std::ostream &strm, const Token &t) {
		 return strm << (char) t.token;
	 }

	 std::ostream &operator<<(std::ostream &strm, const Num &n) {
		 return strm << n.numValue;
	 }

	 std::ostream &operator<<(std::ostream &strm, const Real &n) {
		 return strm << n.value;
	 }


	 const std::shared_ptr<Word> Word::And = std::make_shared<Word>(Word("&&", TagId::AND));
	 const std::shared_ptr<Word> Word::Or = std::make_shared<Word>(Word("||", TagId::OR));
	 const std::shared_ptr<Word> Word::Eq = std::make_shared<Word>(Word("==", TagId::EQ));
	 const std::shared_ptr<Word> Word::Ne = std::make_shared<Word>(Word("!=", TagId::NE));
	 const std::shared_ptr<Word> Word::Le = std::make_shared<Word>(Word("<=", TagId::LE));
	 const std::shared_ptr<Word> Word::Ge = std::make_shared<Word>(Word(">=", TagId::GE));
	 const std::shared_ptr<Word> Word::Minus = std::make_shared<Word>(Word("minus", TagId::MINUS));
	 const std::shared_ptr<Word> Word::True = std::make_shared<Word>(Word("true", TagId::TRUE));
	 const std::shared_ptr<Word> Word::False = std::make_shared<Word>(Word("false", TagId::FALSE));
	 const std::shared_ptr<Word> Word::Temp = std::make_shared<Word>(Word("t", TagId::TEMP));
}