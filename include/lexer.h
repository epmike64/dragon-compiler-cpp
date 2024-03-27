//
// Created by mike on 1/17/24.
//

#ifndef JAVA_DRAGON_COMP_LEXER_H
#define JAVA_DRAGON_COMP_LEXER_H

#include <unordered_map>
#include "types.h"
#include "token.h"
#include "common.h"

using namespace d_common;

namespace d_lex {

	 class Lexer {
		  char currCh = ' ';
		  int textIndex;
		  std::vector<char> text;
		  std::unordered_map<std::string, std::shared_ptr<Token>> words;

	 public:
		  static int line;

		  Lexer(const std::vector<char>& text): text(text){
			  reserve(std::make_shared<Word>(Word("if", TagId::IF)));
			  reserve(std::make_shared<Word>(Word("else", TagId::ELSE)));
			  reserve(std::make_shared<Word>(Word("while", TagId::WHILE)));
			  reserve(std::make_shared<Word>(Word("do", TagId::DO)));
			  reserve(std::make_shared<Word>(Word("break", TagId::BREAK)));

			  reserve(Word::True);
			  reserve(Word::False);

			  reserve(Type::Int);
			  reserve(Type::Char);
			  reserve(Type::Bool);
			  reserve(Type::Float);
		  }

			void readCh() ;
		   void reserve(const std::shared_ptr<Word>& w);
			bool readCh(char c);
		  std::shared_ptr<Token> scan();

	 };
}
#endif //JAVA_DRAGON_COMP_LEXER_H
