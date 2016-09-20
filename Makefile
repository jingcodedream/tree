all:avl_tree.cc avl_tree.h main.cc rd_tree.h rd_tree.cc
	g++ -std=c++11 -g avl_tree.cc avl_tree.h main.cc rd_tree.h rd_tree.cc -o test
