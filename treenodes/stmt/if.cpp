//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 void If::gen(int begin, int after) {
		 int label = newLabel(); // label for the code for stmt
		 expr->jumping(0, after);     // fall through on true, goto after on false
		 emitLabel(label);
		 stmt->gen(label, after);
	 }
}