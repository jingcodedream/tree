/*
 * RD_Tree.cc
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#include "RD_Tree.h"

void RDTree::Dlr() {
	Dlr(root_);
}

void RDTree::Dlr(RDTreeNode *node) {
	if (node != nullptr) {
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
		if (node->left_ != nullptr) {
			Dlr(node->left_);
		}
		if (node->right_ != nullptr) {
			Dlr(node->right_);
		}
	}
}

void RDTree::Ldr() {
	Ldr(root_);
}

void RDTree::Ldr(RDTreeNode *node) {
	if (node != nullptr) {
		if (node->left_ != nullptr) {
			Ldr(node->left_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
		if (node->right_ != nullptr) {
			Ldr(node->right_);
		}
	}
}

void RDTree::Lrd() {
	Lrd(root_);
}

void RDTree::Lrd(RDTreeNode *node) {
	if (node != nullptr) {
		if (node->left_ != nullptr) {
			Lrd(node->left_);
		}
		if (node->right_ != nullptr) {
			Lrd(node->right_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
	}
}


