//
// Created by mike on 1/11/24.
//

#include "../../include/node.h"
namespace d_treenode {

//std::ostream& operator<<(std::ostream &strm, const Expr &expr) {
//	return strm << (char)expr.op.token;
//}

	 const std::shared_ptr<Expr> Expr::Null = std::make_shared<Expr>(Expr(Token::Null, Type::Null));

	 std::shared_ptr<Expr> Expr::gen() {
		 return std::make_shared<Expr>(*this);
	 }

	 std::shared_ptr<Expr> Expr::reduce() {
		 return std::make_shared<Expr>(*this);
	 }

	 void Expr::jumping(int t, int f) {
		 emitJumps(toString(), t, f);
	 }

	 void Expr::emitJumps(const std::string &test, int t, int f) {
		 if (t != 0 && f != 0) {
			 emit("if " + test + " goto L" + std::to_string(t));
			 emit("goto L" + f);
		 } else if (t != 0) {
			 emit("if " + test + " goto L" + std::to_string(t));
		 } else if (f != 0) {
			 emit("iffalse " + test + " goto L" + std::to_string(f));
		 } else; // nothing since both t and f fall through
	 }

//std::string Expr::toString() {
//	std::stringstream sstm;
//	sstm << this->op.token;
//	return sstm.str();
//}
}