cmake_minimum_required(VERSION 3.19.7)

project(MAIN VERSION 3.19.7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -ggdb)
#add_compile_options(-Wall -Ofast)

#folders

set(HDR headers)
set(SRC sources)

set(NOD nodes)
set(ITE iterators)
set(CON containers)

#directories

include_directories(${HDR}/${NOD})
include_directories(${HDR}/${ITE})
include_directories(${HDR}/${CON})

#libs

set(NODE ${HDR}/${NOD}/node.hpp ${SRC}/${NOD}/node.cpp)
set(ITER ${HDR}/${ITE}/iterator.hpp ${SRC}/${ITE}/iterator.cpp)
set(CTNR ${HDR}/${CON}/container.hpp ${SRC}/${CON}/container.cpp)

set(FNODE ${HDR}/${NOD}/forward_node.hpp ${SRC}/${NOD}/forward_node.cpp)
set(FITER ${HDR}/${ITE}/forward_iterator.hpp ${SRC}/${ITE}/forward_iterator.cpp)
set(FCTNR ${HDR}/${CON}/forward_list.hpp ${SRC}/${CON}/forward_list.cpp)

set(BNODE ${HDR}/${NOD}/bidirectional_node.hpp ${SRC}/${NOD}/bidirectional_node.cpp)
set(BITER ${HDR}/${ITE}/bidirectional_iterator.hpp ${SRC}/${ITE}/bidirectional_iterator.cpp)
set(BCTNR ${HDR}/${CON}/bidirectional_list.hpp ${SRC}/${CON}/bidirectional_list.cpp)

add_library(_node STATIC ${NODE})
add_library(_iter STATIC ${ITER})
add_library(_ctnr STATIC ${CTNR})

add_library(_fnode STATIC ${FNODE})
add_library(_fiter STATIC ${FITER})
add_library(_fctnr STATIC ${FCTNR})

add_library(_bnode STATIC ${BNODE})
add_library(_biter STATIC ${BITER})
add_library(_bctnr STATIC ${BCTNR})

#main file

add_executable(launcher main.cpp)

#link

target_link_libraries(_fnode _node)
target_link_libraries(_bnode _node)

target_link_libraries(_iter _node)
target_link_libraries(_fiter _iter _fnode)
target_link_libraries(_biter _iter _bnode)

target_link_libraries(_fctnr _ctnr _fiter)
target_link_libraries(_bctnr _ctnr _biter)
