/*
 * avl_tree.cc
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#include "Avl_Tree.h"

#include <algorithm>
#include <iostream>

void AvlTree::Insert(int value) {
	root_ = Insert(value, root_);
}

TreeNode * AvlTree::Insert(int value, TreeNode *node) {
	if (node == nullptr) {
		node = new TreeNode(value);
		node->count_ = 1;
		node->height_ = 1;
		return node;
	} else {
		if (value < node->value_) {
			node->left_ = Insert(value, node->left_);
			if (Height(node->left_) - Height(node->right_) == 2) {
				if (value < node->left_->value_) {
					node = RightRotate(node);
				} else {
					node->left_ = LeftRotate(node->left_);
					node = RightRotate(node);
				}
			}
		} else if (value > node->value_) {
			node->right_ = Insert(value, node->right_);
			if (Height(node->right_) - Height(node->left_) == 2) {
				if (value > node->right_->value_) {
					node = LeftRotate(node);
				} else {
					node->right_ = RightRotate(node->right_);
					node = LeftRotate(node);
				}
			}
		} else {
			++node->count_;
		}
		node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
		return node;
	}
}

bool AvlTree::Delete(int32_t value) {
	return Delete(value, root_);
}

TreeNode * AvlTree::Delete(int32_t value, TreeNode *node) {
	if (node == nullptr) {
		return node;
	} else {
		if (value < node->value_) {
			node->left_ = Delete(value, node->left_);
			if (node != nullptr) {
				if (Height(node->left_) - Height(node->right_) == 2) {
					if (value < node->left_->value_) {
						node = RightRotate(node);
					} else {
						node->left_ = LeftRotate(node->left_);
						node = RightRotate(node);
					}
				}
			}
		} else if (value > node->value_) {
			node->right_ = Delete(value, node->right_);
			if (node != nullptr) {
				if (Height(node->right_) - Height(node->left_) == 2) {
					if (value > node->right_->value_) {
						node = LeftRotate(node);
					} else {
						node->right_ = RightRotate(node->right_);
						node = LeftRotate(node);
					}
				}
			}
		} else {  //如果相等
			TreeNode *temp_node = nullptr;
			if (node->left_ == nullptr) {
				temp_node = node;
				node = node->right_;
				temp_node->left_ == nullptr;
				temp_node->right_ == nullptr;
				delete temp_node;
			} else if (node->right_ == nullptr) {
				temp_node = node;
				node = node->left_;
				temp_node->left_ == nullptr;
				temp_node->right_ == nullptr;
				delete temp_node;
			} else {
				temp_node = node->left_;
				while(temp_node->right_ != nullptr) {
					temp_node = temp_node->right_;
				}
				node->value_ = temp_node->value_;
				node->left_ = Delete(node->value_, node->left_);
			}
		}
		//node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
		return node;
	}
}

TreeNode * AvlTree::Find(int32_t value) {
	TreeNode * temp_node = root_;
	while (temp_node != nullptr && temp_node->value_ == value) {
		if (value > temp_node->value_) {
			temp_node = temp_node->right_;
		} else {
			temp_node = temp_node->left_;
		}
	}
	return temp_node;
}

TreeNode * AvlTree::LeftRotate(TreeNode * node) {
	TreeNode * temp_node = node->right_;
	node->right_ = temp_node->left_;
	temp_node->left_ = node;
	node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
	temp_node->height_ = std::max(Height(temp_node->left_), Height(temp_node->right_)) + 1;
	return temp_node;
}

TreeNode * AvlTree::RightRotate(TreeNode * node) {
	TreeNode * temp_node = node->left_;
	node->left_ = temp_node->right_;
	temp_node->right_ = node;
	node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
	temp_node->height_ = std::max(Height(temp_node->left_), Height(temp_node->right_)) + 1;
	return temp_node;
}

void AvlTree::Dlr() {
	Dlr(root_);
}

void AvlTree::Dlr(TreeNode *node) {
	if (node != nullptr) {
		std::cout << node->value_ << ":" << node->count_ << ":" << node->height_ << std::endl;
		if (node->left_ != nullptr) {
			Dlr(node->left_);
		}
		if (node->right_ != nullptr) {
			Dlr(node->right_);
		}
	}
}

void AvlTree::Ldr() {
	Ldr(root_);
}

void AvlTree::Ldr(TreeNode *node) {
	if (node != nullptr) {
		if (node->left_ != nullptr) {
			Ldr(node->left_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->height_ << std::endl;
		if (node->right_ != nullptr) {
			Ldr(node->right_);
		}
	}
}

void AvlTree::Lrd() {
	Lrd(root_);
}

void AvlTree::Lrd(TreeNode *node) {
	if (node != nullptr) {
		if (node->left_ != nullptr) {
			Lrd(node->left_);
		}
		if (node->right_ != nullptr) {
			Lrd(node->right_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->height_ << std::endl;
	}
}
