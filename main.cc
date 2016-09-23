/*
 * main.cc
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#include <iostream>

#include "avl_tree.h"
#include "rb_tree.h"
using namespace std;

int main() {
	srand(time(NULL));
//	AvlTree tree = AvlTree();
//	for (uint32_t i = 0; i < 100; i++) {
//		uint32_t temp_value = rand() % 10;
//		cout << temp_value << " ";
//		tree.Insert(temp_value);
//	}
//
////	cout << endl << "==============================" << endl;
////    tree.Dlr();
//    cout << endl << "==============================" << endl;
//    tree.Ldr();
//    tree.Delete(3);
//    cout << endl << "==============================" << endl;
//    tree.Ldr();
////    cout << endl << "==============================" << endl;
////    tree.Lrd();

	RBTree tree = RBTree();
	for (uint32_t i = 0; i < 100; i++) {
		uint32_t temp_value = rand() % 100;
		cout << temp_value << " ";
		tree.Insert(temp_value);
	}
	tree.PrintBlackSum();

////	cout << endl << "==============================" << endl;
////    tree.Ldr();
//    cout << endl << "==============================" << endl;
//    tree.Dlr();
//    cout << endl << "==============================" << endl;
//    tree.Lrd();
//
    for (uint32_t i = 0; i < 200; i++) {
		uint32_t temp_value = rand() % 100;
		cout << temp_value << " ";
		tree.Delete(temp_value);
	}
    tree.PrintBlackSum();
//
////    cout << endl << "==============================" << endl;
////    tree.Ldr();
//    cout << endl << "==============================" << endl;
//    tree.Dlr();
//    cout << endl << "==============================" << endl;
//    tree.Lrd();
	return 0;
}


