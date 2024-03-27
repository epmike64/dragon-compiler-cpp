
//
// Created by mike on 1/6/24.
//

#include "../../include/node.h"
namespace d_treenode {

	 int Node::labels = 0;

//Node::~Node() noexcept {}

	 void Node::error(const std::string &s) {
		 throw DragonException("Dragon exception near line " + std::to_string(lexLine) + ": " + s);
	 }

	 void Node::emitLabel(int i) {
		 std::cout << "L" << i << ":";
	 }

	 void Node::emit(const std::string &s) {
		 std::cout << "\t" << s << std::endl;
	 }

}