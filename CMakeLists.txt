cmake_minimum_required(VERSION 3.25)
project(java_dragon_comp)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71.0 COMPONENTS filesystem regex)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(java_dragon_comp main.cpp treenodes/expr/node.cpp include/node.h lexer/token.cpp include/token.h types/types.cpp include/types.h treenodes/expr/expr.cpp treenodes/expr/logical.cpp treenodes/expr/access.cpp treenodes/expr/op.cpp treenodes/expr/and.cpp treenodes/expr/constant.cpp treenodes/stmt/do.cpp treenodes/stmt/else.cpp treenodes/stmt/if.cpp treenodes/expr/rel.cpp treenodes/stmt/set.cpp treenodes/stmt/set-elem.cpp treenodes/stmt/stmt.cpp treenodes/stmt/while.cpp treenodes/expr/temp.cpp include/stmt.h parser/parser.cpp include/parser.h lexer/lexer.cpp include/lexer.h include/common.h treenodes/stmt/seq.cpp)
target_link_libraries(java_dragon_comp ${Boost_LIBRARIES})