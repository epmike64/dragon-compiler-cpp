//
// Created by mike on 1/11/24.
//
#include "../../include/node.h"
namespace d_treenode {

	 const std::shared_ptr<Constant> Constant::True = std::make_shared<Constant>(Constant(Word::True, Type::Bool));
	 const std::shared_ptr<Constant> Constant::False = std::make_shared<Constant>(Constant(Word::False, Type::Bool));

	 void Constant::jumping(int t, int f) {
		 if (*this == *Constant::True.get() && t != 0)
			 emit("goto L" + t);
		 else if (*this == *Constant::False.get() && f != 0)
			 emit("goto L" + f);
	 }
}