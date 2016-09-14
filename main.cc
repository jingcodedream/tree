/*
 * main.cc
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#include <iostream>

#include "Avl_Tree.h"
using namespace std;

int main() {
	srand(time(NULL));
	AvlTree tree = AvlTree();
	for (uint32_t i = 0; i < 5; i++) {
		uint32_t temp_value = rand() % 10;
		cout << temp_value << " ";
		tree.Insert(temp_value);
	}
	tree.Delete(3);
//	cout << endl << "==============================" << endl;
//    tree.Dlr();
    cout << endl << "==============================" << endl;
    tree.Ldr();
//    cout << endl << "==============================" << endl;
//    tree.Lrd();
	return 0;
}


