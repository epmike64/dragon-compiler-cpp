//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {

	 void And::jumping(int t, int f) {
		 int label = f != 0 ? f : newLabel();
		 expr1->jumping(0, label);
		 expr2->jumping(t, f);
		 if (f == 0)
			 emitLabel(label);
	 }
}