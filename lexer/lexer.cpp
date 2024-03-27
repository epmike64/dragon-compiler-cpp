//
// Created by mike on 1/17/24.
//

#include "../include/lexer.h"
#include <ctype.h>

namespace d_lex {

	 int Lexer::line = 1;

	 void Lexer::reserve(const std::shared_ptr<Word> &w) {
		 words.insert(std::pair<const std::string, std::shared_ptr<Token>>(w->lexeme, w));
	 }

	 void Lexer::readCh() {
		 if(textIndex >= text.size()) {
			 throw std::runtime_error("End of file reached.");
		 }
		 currCh = text.at(textIndex++);
	 }

	 bool Lexer::readCh(char c) {
		 readCh();
		 if (currCh != c) {
			 return false;
		 }
		 currCh = ' ';
		 return true;
	 }

	 std::shared_ptr<Token> Lexer::scan() {
		 for (;; readCh()) {
			 if (currCh == ' ' || currCh == '\t')
				 continue;
			 else if (currCh == '\n')
				 line = line + 1;
			 else
				 break;
		 }

		 switch (currCh) {
			 case '&':
				 if (readCh('&'))
					 return Word::And;
				 else
					 return std::make_shared<Token>('&');
			 case '|':
				 if (readCh('|'))
					 return Word::Or;
				 else
					 return std::make_shared<Token>('|');
			 case '=':
				 if (readCh('='))
					 return Word::Eq;
				 else
					 return std::make_shared<Token>('=');
			 case '!':
				 if (readCh('='))
					 return Word::Ne;
				 else
					 return std::make_shared<Token>('!');
			 case '<':
				 if (readCh('='))
					 return Word::Le;
				 else
					 return std::make_shared<Token>('<');
			 case '>':
				 if (readCh('='))
					 return Word::Ge;
				 else
					 return std::make_shared<Token>('>');
		 }

		 if (isdigit(currCh)) {

			 int v = 0;
			 do {
				 v = 10 * v + (currCh - '0');
				 readCh();
			 } while (isdigit(currCh));

			 if (currCh != '.')
				 return std::make_shared<Token>(Num(v));

			 float x = v;
			 float d = 10;
			 for (;;) {
				 readCh();
				 if (!isdigit(currCh))
					 break;
				 x = x + (currCh - '0') / d;
				 d = d * 10;
			 }
			 return std::make_shared<Token>(Real(x));
		 }


		 if (isalpha(currCh)) {

			 std::stringstream ss;
			 do {
				 ss << currCh;
				 readCh();
			 } while (isalpha(currCh) || isdigit(currCh));

			 std::string s = ss.str();
			 if (words.count(s)) {
				 std::shared_ptr<Token> w = words[s];
				 return w;
			 }

			 std::shared_ptr<Token> w = std::make_shared<Token>(Word(s, TagId::ID));
			 words.insert(std::pair<const std::string, std::shared_ptr<Token>>(s, w));
			 return w;
		 }

		 Token tok(currCh);
		 currCh = ' ';
		 return std::make_shared<Token>(tok);
	 }
}