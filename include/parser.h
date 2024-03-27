//
// Created by mike on 1/12/24.
//

#ifndef JAVA_DRAGON_COMP_PARSER_H
#define JAVA_DRAGON_COMP_PARSER_H

#include "node.h"
#include "lexer.h"
#include "stmt.h"
#include "common.h"

using namespace d_treenode;
using namespace d_lex;
using namespace d_common;

namespace d_parser {

	 class Env {
		   std::shared_ptr<Env> prev;
			std::unordered_map<std::shared_ptr<Token>, std::shared_ptr<Id>, SharedPtrHashFun<Token>, SharedPtrEqualFun<Token>> map;
	 public:
		  Env(const std::shared_ptr<Env>& prev): prev(prev){}

		  void putValue(const  std::shared_ptr<Token>& t,  std::shared_ptr<Id>& id){
			  map.insert(std::pair<std::shared_ptr<Token>, std::shared_ptr<Id>>(t, id));
		  }

		  std::shared_ptr<Id> getValue(const std::shared_ptr<Token> t){
			   const auto it = map.find(t);
				if(it != map.cend()){
					return it->second;
				}
			  return std::shared_ptr<Id>();
		  }
	 };

	 class Parser {
		  Lexer lex;    // lexical analyzer for this parser

		  std::shared_ptr<Token> lexTok;   // lookahead tagen
		  std::shared_ptr<Env> top;     // current or top symbol table
		  int used = 0;         // storage used for declarations

	 public:

		  Parser(const std::vector<char> &text) : lex(text) {
			  move();
		  }

		  void move();

		  void error(const std::string &s);

		  void matchCurrTokAndMove(int t);

		  void program();

		  std::shared_ptr<Stmt> block();

		  void decls();

		  std::shared_ptr<Type> type();

		  std::shared_ptr<Type> dims(const std::shared_ptr<Type> &p);

		  std::shared_ptr<Stmt> stmts();

		  std::shared_ptr<Stmt> stmt();

		  std::shared_ptr<Stmt> assign();

		  /*
			  p.966 - Source code,  p.212 - Left recursion elimination @ Dragon book
			*/
		  std::shared_ptr<Expr> boolean();

		  std::shared_ptr<Expr> join();

		  std::shared_ptr<Expr> equality();

		  std::shared_ptr<Expr> rel();

		  std::shared_ptr<Expr> expr();

		  std::shared_ptr<Expr> term();

		  std::shared_ptr<Expr> unary();

		  std::shared_ptr<Expr> factor();

		  /*
				Dragon Book
				p. 966 Grammar
				p. 212 Left Recursion Elimination
			*/
		  std::shared_ptr<Access> offset(const std::shared_ptr<Id>& a);

	 };
}

#endif //JAVA_DRAGON_COMP_PARSER_H
