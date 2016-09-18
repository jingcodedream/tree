/*
 * avl_tree.cc
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#include "Avl_Tree.h"

#include <algorithm>
#include <iostream>

bool AvlTree::Insert(uint32_t value) {
	bool height_change = false;
	root_ = Insert(value, root_, height_change);
	return height_change;
}

AvlTree::AvlTreeNode * AvlTree::Insert(uint32_t value, AvlTreeNode *node, bool &height_change) {
	if (node == nullptr) {
		node = new AvlTreeNode(value);
		node->count_ = 1;
		node->height_ = 1;
		height_change = true;
		return node;
	} else {
		if (value < node->value_) {
			node->left_ = Insert(value, node->left_, height_change);
		} else if (value > node->value_) {
			node->right_ = Insert(value, node->right_, height_change);
		} else {
			++node->count_;
			height_change = false;
		}

		if (height_change) { //高度变化才需要对结点处理处理
			node = NodeHandle(node);
		}
		return node;
	}
}

bool AvlTree::Delete(uint32_t value) {
	bool height_change = false;
	root_ = Delete(value, root_, height_change);
	return height_change;
}

AvlTree::AvlTreeNode * AvlTree::Delete(uint32_t value, AvlTreeNode *node, bool &height_change) {
	if (node == nullptr) {
		height_change = false;
		return node;
	} else {
		if (value < node->value_) {
			node->left_ = Delete(value, node->left_, height_change);
		} else if (value > node->value_) {
			node->right_ = Delete(value, node->right_, height_change);
		} else {  //如果相等
			AvlTreeNode *temp_node = nullptr;
			if (node->left_ == nullptr) {
				temp_node = node;
				node = node->right_;
				temp_node->left_ = nullptr;
				temp_node->right_ = nullptr;
				delete temp_node;
			} else if (node->right_ == nullptr) {
				temp_node = node;
				node = node->left_;
				temp_node->left_ = nullptr;
				temp_node->right_ = nullptr;
				delete temp_node;
			} else {
				temp_node = node->left_;
				while(temp_node->right_ != nullptr) {
					temp_node = temp_node->right_;
				}
				node->value_ = temp_node->value_;
				node->left_ = Delete(node->value_, node->left_, height_change);
			}
			height_change = true;
		}
		if (height_change) { //高度变化才需要对结点处理处理
			node = NodeHandle(node);
		}
		return node;
	}
}

AvlTree::AvlTreeNode * AvlTree::NodeHandle(AvlTreeNode *node) {
	if (node != nullptr) {
		node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
		if (Height(node->left_) - Height(node->right_) == 2 || Height(node->left_) - Height(node->right_) == -2) {
			if (Height(node->left_) - Height(node->right_) == 2) {
				if (Height(node->left_->left_) >= Height(node->left_->right_)) {
					node = RightRotate(node);
				} else {
					node->left_ = LeftRotate(node->left_);
					node = RightRotate(node);
				}
			} else {
				if (Height(node->right_->left_) <= Height(node->right_->right_)) {
					node = LeftRotate(node);
				} else {
					node->right_ = RightRotate(node->right_);
					node = LeftRotate(node);
				}
			}
		}
	}
	return node;
}

int64_t AvlTree::Find(uint32_t value) {
	AvlTreeNode * temp_node = root_;
	while (temp_node != nullptr && temp_node->value_ != value) {
		if (value > temp_node->value_) {
			temp_node = temp_node->right_;
		} else {
			temp_node = temp_node->left_;
		}
	}
	if (temp_node == nullptr) {
		return -1;
	} else {
		return temp_node->value_;
	}
}

AvlTree::AvlTreeNode * AvlTree::LeftRotate(AvlTreeNode * node) {
	AvlTreeNode * temp_node = node->right_;
	node->right_ = temp_node->left_;
	temp_node->left_ = node;
	node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
	temp_node->height_ = std::max(Height(temp_node->left_), Height(temp_node->right_)) + 1;
	return temp_node;
}

AvlTree::AvlTreeNode * AvlTree::RightRotate(AvlTreeNode * node) {
	AvlTreeNode * temp_node = node->left_;
	node->left_ = temp_node->right_;
	temp_node->right_ = node;
	node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
	temp_node->height_ = std::max(Height(temp_node->left_), Height(temp_node->right_)) + 1;
	return temp_node;
}

void AvlTree::Dlr() {
	Dlr(root_);
}

void AvlTree::Dlr(AvlTreeNode *node) {
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

void AvlTree::Ldr(AvlTreeNode *node) {
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

void AvlTree::Lrd(AvlTreeNode *node) {
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
