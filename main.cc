/*
 * main.cc
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#include <iostream>

#include "Avl_Tree.h"
#include "RD_Tree.h"
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

	RDTree tree = RDTree();
	for (uint32_t i = 0; i < 100; i++) {
		uint32_t temp_value = rand() % 100;
		cout << temp_value << " " << endl;
		tree.Insert(temp_value);
	}
	cout << endl << "==============================" << endl;
    tree.Ldr();
	return 0;
}


