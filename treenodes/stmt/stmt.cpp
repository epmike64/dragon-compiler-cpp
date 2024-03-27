//
// Created by mike on 1/11/24.
//
#include "../../include/stmt.h"
namespace d_treenode {

	 const std::shared_ptr<Stmt> Stmt::Null = std::make_shared<Stmt>(Stmt());
	 std::shared_ptr<Stmt> Stmt::Enclosing = Stmt::Null;

	 }