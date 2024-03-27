//
// Created by mike on 1/20/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 void Seq::gen(int begin, int after) {
		 if (stmt1 == Stmt::Null)
			 stmt2->gen(begin, after);
		 else if (stmt2 == Stmt::Null)
			 stmt1->gen(begin, after);
		 else {
			 int label = newLabel();
			 stmt1->gen(begin, label);
			 emitLabel(label);
			 stmt2->gen(label, after);
		 }
	 }
}