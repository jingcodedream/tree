all:avl_tree.cc avl_tree.h main.cc
	g++ -std=c++11 -g avl_tree.cc avl_tree.h main.cc -o test
