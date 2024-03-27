//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 void While::init(const std::shared_ptr<Expr> &x, const std::shared_ptr<Stmt> &s) {
		 expr = x;
		 stmt = s;
		 if (expr->type != Type::Bool)
			 expr->error("boolean required in while");
	 }

	 void While::gen(int begin, int after) {
		 this->after = after;                // save label after
		 expr->jumping(0, after);
		 int label = newLabel();   // label for stmt
		 emitLabel(label);
		 stmt->gen(label, begin);
		 emit("goto L" + begin);
	 }
}