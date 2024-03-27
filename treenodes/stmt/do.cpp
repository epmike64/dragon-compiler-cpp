//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 void Do::init(const std::shared_ptr<Stmt> &s, const std::shared_ptr<Expr> &x) {
		 expr = x;
		 stmt = s;
		 if (expr->type != Type::Bool)
			 expr->error("boolean required in do");
	 }

	 void Do::gen(int begin, int after) {
		 this->after = after;
		 int label = newLabel();   // label for expr
		 stmt->gen(begin, label);
		 emitLabel(label);
		 expr->jumping(begin, 0);
	 }
}