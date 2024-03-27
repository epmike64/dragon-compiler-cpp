//
// Created by mike on 1/12/24.
//

#include "../include/parser.h"

using namespace d_treenode;
using namespace d_lex;

namespace d_parser {


	 void Parser::move() {
		 lexTok = lex.scan();
	 }

	 void Parser::error(const std::string &s) {
		 throw DragonException("");
	 }

	 void Parser::matchCurrTokAndMove(int t) {
		 if (lexTok->token == t) {
			 move();
		 } else {
			 error("syntax error");
		 }
	 }

	 void Parser::program() {
		 std::shared_ptr<Stmt> s = block();
		 int begin = s->newLabel();
		 int after = s->newLabel();
		 s->emitLabel(begin);
		 s->gen(begin, after);
		 s->emitLabel(after);
	 }

	 std::shared_ptr<Stmt> Parser::block() {
		 matchCurrTokAndMove('{');
		 std::shared_ptr<Env> savedEnv = top;
		 top = std::make_shared<Env>(Env(top));
		 decls();
		 std::shared_ptr<Stmt> s = stmts();
		 matchCurrTokAndMove('}');
		 top = savedEnv;
		 return s;
	 }

	 void Parser::decls() {
		 while (lexTok->token == TagId::BASIC) {   // D -> type ID ;
			 std::shared_ptr<Type> pType = type();
			 std::shared_ptr<Token> pTok = lexTok;
			 matchCurrTokAndMove(TagId::ID);
			 matchCurrTokAndMove(';');
			 std::shared_ptr<Id> id = std::make_shared<Id>(pTok, pType, used);
			 top->putValue(pTok, id);
			 used = used + pType->width;
		 }
	 }

	 std::shared_ptr<Type> Parser::type() {

		 std::shared_ptr<Type> pType = std::dynamic_pointer_cast<Type>(lexTok);            // expect look.tag == Tag.BASIC
		 matchCurrTokAndMove(TagId::BASIC);
		 if (lexTok->token != '[')
			 return pType; // T -> basic
		 else
			 return dims(pType);            // return array type
	 }

	 std::shared_ptr<Type> Parser::dims(const std::shared_ptr<Type> &p) {
		 std::shared_ptr<Type> _p(p);
		 matchCurrTokAndMove('[');
		 std::shared_ptr<Token> tok = lexTok;
		 matchCurrTokAndMove(TagId::NUM);
		 matchCurrTokAndMove(']');
		 if (lexTok->token == '[')
			 std::shared_ptr<Type> _p = dims(p);
		 int num = std::dynamic_pointer_cast<Num>(tok)->numValue;
		 return std::make_shared<Array>(Array(num, _p));
	 }

	 std::shared_ptr<Stmt> Parser::stmts() {
		 if (lexTok->token == '}')
			 return Stmt::Null;
		 else {
			 std::shared_ptr<Stmt> s = stmt();
			 std::shared_ptr<Stmt> ss = stmts();
			 return std::make_shared<Stmt>(Seq(s, ss));
		 }
	 }

	 std::shared_ptr<Stmt> Parser::stmt() {
		 std::shared_ptr<Expr> x;
		 std::shared_ptr<Stmt> s, s1, s2;
		 std::shared_ptr<Stmt> savedStmt;         // save enclosing loop for breaks

		 switch (lexTok->token) {

			 case ';':
				 move();
				 return Stmt::Null;

			 case TagId::IF:
				 matchCurrTokAndMove(TagId::IF);
				 matchCurrTokAndMove('(');
				 x = boolean();
				 matchCurrTokAndMove(')');
				 s1 = stmt();
				 if (lexTok->token != TagId::ELSE)
					 return std::make_shared<If>(If(x, s1));
				 matchCurrTokAndMove(TagId::ELSE);
				 s2 = stmt();
				 return std::make_shared<Else>(Else(x, s1, s2));


			 case TagId::WHILE: {
				 std::shared_ptr<While> whilenode = std::make_shared<While>(While());
				 savedStmt = Stmt::Enclosing;
				 Stmt::Enclosing = whilenode;
				 matchCurrTokAndMove(TagId::WHILE);
				 matchCurrTokAndMove('(');
				 x = boolean();
				 matchCurrTokAndMove(')');
				 s1 = stmt();
				 whilenode->init(x, s1);
				 Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
				 return whilenode;
			 }

			 case TagId::DO: {
				 std::shared_ptr<Do> donode = std::make_shared<Do>(Do());
				 savedStmt = Stmt::Enclosing;
				 Stmt::Enclosing = donode;
				 matchCurrTokAndMove(TagId::DO);
				 s1 = stmt();
				 matchCurrTokAndMove(TagId::WHILE);
				 matchCurrTokAndMove('(');
				 x = boolean();
				 matchCurrTokAndMove(')');
				 matchCurrTokAndMove(';');
				 donode->init(s1, x);
				 Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
				 return donode;
			 }

			 case TagId::BREAK:
				 matchCurrTokAndMove(TagId::BREAK);
				 matchCurrTokAndMove(';');
				 return std::make_shared<Break>(Break());

			 case '{':
				 return block();

			 default:
				 return assign();
		 }

	 }

	 std::shared_ptr<Stmt> Parser::assign() {
		 std::shared_ptr<Stmt> stmt;
		 std::shared_ptr<Token> t = lexTok;
		 matchCurrTokAndMove(TagId::ID);
		 std::shared_ptr<Id> id = top->getValue(t);
		 if (id.use_count() == 0)
			 error(t->toString() + " undeclared");

		 if (lexTok->token == '=') {       // S -> id = E ;
			 move();
			 stmt = std::make_shared<Stmt>(Set(id, boolean()));
		 } else {                        // S -> L = E ;
			 std::shared_ptr<Access> x = offset(id);
			 matchCurrTokAndMove('=');
			 stmt = std::make_shared<Stmt>(SetElem(x, boolean()));
		 }
		 matchCurrTokAndMove(';');
		 return stmt;
	 }

	 /*
		 p.966 - Source code,  p.212 - Left recursion elimination @ Dragon book
	  */
	 std::shared_ptr<Expr> Parser::boolean() {
		 std::shared_ptr<Expr> x = join();
		 while (lexTok->token == TagId::OR) {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 x = std::make_shared<Expr>(Or(tok, x, join()));
		 }
		 return x;
	 }

	 std::shared_ptr<Expr> Parser::join() {
		 std::shared_ptr<Expr> x = equality();
		 while (lexTok->token == TagId::AND) {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 x = std::make_shared<Expr>(And(tok, x, equality()));
		 }
		 return x;

	 }

	 std::shared_ptr<Expr> Parser::equality() {
		 std::shared_ptr<Expr> x = rel();
		 while (lexTok->token == TagId::EQ || lexTok->token == TagId::NE) {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 x = std::make_shared<Expr>(Rel(tok, x, rel()));
		 }
		 return x;

	 }

	 std::shared_ptr<Expr> Parser::rel() {
		 std::shared_ptr<Expr> x = expr();
		 switch (lexTok->token) {
			 case '<':
			 case TagId::LE:
			 case TagId::GE:
			 case '>': {
				 std::shared_ptr<Token> tok = lexTok;
				 move();
				 return std::make_shared<Expr>(Rel(tok, x, expr()));
			 }
			 default:
				 return x;
		 }

	 }

	 std::shared_ptr<Expr> Parser::expr() {
		 std::shared_ptr<Expr> x = term();
		 while (lexTok->token == '+' || lexTok->token == '-') {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 x = std::make_shared<Expr>(Arith(tok, x, term()));
		 }
		 return x;
	 }

	 std::shared_ptr<Expr> Parser::term() {
		 std::shared_ptr<Expr> x = unary();
		 while (lexTok->token == '*' || lexTok->token == '/') {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 x = std::make_shared<Expr>(Arith(tok, x, unary()));
		 }
		 return x;

	 }

	 std::shared_ptr<Expr> Parser::unary() {
		 if (lexTok->token == '-') {
			 move();
			 return std::make_shared<Expr>(Unary(Word::Minus, unary()));
		 } else if (lexTok->token == '!') {
			 std::shared_ptr<Token> tok = lexTok;
			 move();
			 return std::make_shared<Expr>(Not(tok, unary()));
		 } else
			 return factor();

	 }

	 std::shared_ptr<Expr> Parser::factor() {
		 std::shared_ptr<Expr> x;
		 switch (lexTok->token) {
			 case '(':
				 move();
				 x = boolean();
				 matchCurrTokAndMove(')');
				 return x;
			 case TagId::NUM:
				 x = std::make_shared<Expr>(Constant(lexTok, Type::Int));
				 move();
				 return x;
			 case TagId::REAL:
				 x = std::make_shared<Expr>(Constant(lexTok, Type::Float));
				 move();
				 return x;
			 case TagId::TRUE:
				 x = Constant::True;
				 move();
				 return x;
			 case TagId::FALSE:
				 x = Constant::False;
				 move();
				 return x;
			 default:
				 error("syntax error");
				 return x;
			 case TagId::ID:
				 //String s = lexTok->toString();
				 std::shared_ptr<Id> id = top->getValue(lexTok);
				 if (id.use_count() == 0)
					 error(lexTok->toString() + " undeclared");
				 move();
				 if (lexTok->token != '[')
					 return id;
				 else
					 return offset(id);

		 }
	 }

	 /*
		  Dragon Book
		  p. 966 Grammar
		  p. 212 Left Recursion Elimination
	  */
	 std::shared_ptr<Access> Parser::offset(const std::shared_ptr<Id> &a) {

		 std::shared_ptr<Expr> i;
		 std::shared_ptr<Expr> w;
		 std::shared_ptr<Expr> t1, t2;
		 std::shared_ptr<Expr> loc;  // inherit id

		 std::shared_ptr<Type> type = a->type;
		 matchCurrTokAndMove('[');
		 i = boolean();
		 matchCurrTokAndMove(']');     // first index, I -> [ E ]
		 type = std::dynamic_pointer_cast<Array>(type)->of;
		 w = std::make_shared<Expr>(Constant(type->width));
		 t1 = std::make_shared<Expr>(Arith(std::make_shared<Token>(Token('*')), i, w));
		 loc = t1;
		 while (lexTok->token == '[') {      // multi-dimensional I -> [ E ] I
			 matchCurrTokAndMove('[');
			 i = boolean();
			 matchCurrTokAndMove(']');
			 type = std::dynamic_pointer_cast<Array>(type)->of;
			 w = std::make_shared<Expr>(Constant(type->width));
			 t1 = std::make_shared<Expr>(Arith(std::make_shared<Token>(Token('*')), i, w));
			 t2 = std::make_shared<Expr>(Arith(std::make_shared<Token>(Token('+')), loc, t1));
			 loc = t2;
		 }

		 return std::make_shared<Access>(Access(a, loc, type));
	 }

}
