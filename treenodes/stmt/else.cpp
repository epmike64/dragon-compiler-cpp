//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 void Else::gen(int begin, int after) {
		 int label1 = newLabel();   // label1 for stmt1
		 int label2 = newLabel();   // label2 for stmt2
		 expr->jumping(0, label2);    // fall through to stmt1 on true
		 emitLabel(label1);
		 stmt1->gen(label1, after);
		 emit("goto L" + after);
		 emitLabel(label2);
		 stmt2->gen(label2, after);
	 }
}