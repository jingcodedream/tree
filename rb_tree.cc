/*
 * RD_Tree.cc
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#include "rb_tree.h"

bool RBTree::Insert(uint32_t value) {
	if (root_ == nullptr) { //如果根节点为空，直接创建根节点，并将节点颜色设置为黑色
		root_ = new RBTreeNode(value);
		root_->color_ = BLACK;
		return true;
	}
	RBTreeNode * temp_node = root_;
	RBTreeNode * parent_temp_node = temp_node;
	while (true) {
		parent_temp_node = temp_node;
		if (value > temp_node->value_) {
			temp_node = temp_node->right_;
			if (temp_node == nullptr) {
				temp_node = new RBTreeNode(value);
				temp_node->parent_ = parent_temp_node;
				parent_temp_node->right_ = temp_node;
				break;
			}
		} else if (value < temp_node->value_) {
			temp_node = temp_node->left_;
			if (temp_node == nullptr) {
				temp_node = new RBTreeNode(value);
				temp_node->parent_ = parent_temp_node;
				parent_temp_node->left_ = temp_node;
				break;
			}
		} else {
			++temp_node->count_;
			return false;
		}
	}
	if (GetColor(parent_temp_node) == BLACK) {  //如果插入节点的父节点颜色为黑色，不需要管
		return true;
	} else { //否者需要对插入节点进行处理
		RDInsertFixup(temp_node);
	}
	return true;
}

void RBTree::RDInsertFixup(RBTreeNode * node) {
	while (GetColor(node->parent_) == RED) {
		if (node->parent_ == node->parent_->parent_->left_) { //node->parent_->parent_一定存在，否则，就不满足红黑树的性质
			if (GetColor(node->parent_->parent_->right_) == RED) { //如果父节点的兄弟节点是红色，直接将父节点和其兄弟节点颜色设置为黑色，将祖父节点设置为红色，处理祖父节点
				node->parent_->color_ = BLACK;
				node->parent_->parent_->right_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			} else { //如果父节点的兄弟节点是黑色
				if (node->parent_ == node->parent_->right_) { //如果节点是父节点的右子节点，父节点左旋变为下一种请款
					LeftRotato(node->parent_);
					node = node->left_;
				}
				//如果是父节点的左节点，将父节点颜色设置为黑色，祖父节点设置红色，祖父节点右旋
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				RightRotato(node->parent_->parent_);
				break;
			}
		} else {
			if (GetColor(node->parent_->parent_->left_) == RED) { //如果父节点的兄弟节点是红色，直接将父节点和其兄弟节点颜色设置为黑色，将祖父节点设置为红色，处理祖父节点
				node->parent_->color_ = BLACK;
				node->parent_->parent_->left_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			} else { //如果父节点的兄弟节点是黑色
				if (node->parent_ == node->parent_->left_) { //如果节点是父节点的右子节点，父节点左旋变为下一种请款
					RightRotato(node->parent_);
					node = node->right_;
				}
				//如果是父节点的左节点，将父节点颜色设置为黑色，祖父节点设置红色，祖父节点右旋
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				LeftRotato(node->parent_->parent_);
				break;
			}
		}
	}
	root_->color_ = BLACK;
}

bool RBTree::Delete(uint32_t value) {
	RBTreeNode * temp_node = root_;
	while (temp_node != nullptr) {
		if (value > temp_node->value_) {
			temp_node = temp_node->right_;
		} else if (value < temp_node->value_) {
			temp_node = temp_node->left_;
		} else {
			if (temp_node->left_ == nullptr) {
				if (temp_node->parent_ == nullptr) {
					root_ == temp_node->right_;
				} else {
					if (temp_node == temp_node->parent_->right_) {
						temp_node->parent_->right_ = temp_node->right_;
					} else {
						temp_node->parent_->left_ = temp_node->right_;
					}
				}
				if (temp_node->right_ != nullptr) {
					temp_node->right_->parent_ = temp_node->parent_;
				}
				break;
			} else if (temp_node->right_ == nullptr) {
				if (temp_node->parent_ == nullptr) {  //如果当前节点不存在，表示删除的是根节点
					root_ == temp_node->left_;
				} else {
					if (temp_node == temp_node->parent_->right_) { //否则，将当前节点的后继节点指向相对应的后继节点
						temp_node->parent_->right_ = temp_node->left_;
					} else {
						temp_node->parent_->left_ = temp_node->left_;
					}
				}
				if (temp_node->left_ != nullptr) {
					temp_node->left_->parent_ = temp_node->parent_;
				}
				break;
			} else {  //如果被删除节点的左右子树都不为空，找到节点的前驱节点，将前驱节点的值赋给被删除节点，删除前驱节点
				RBTreeNode * temp_node_pre = temp_node->left_;
				while (temp_node_pre->right_ != nullptr) {
					temp_node_pre = temp_node_pre->right_;
				}
				temp_node->value_ = temp_node_pre->value_;
				value = temp_node_pre->value_;
				temp_node = temp_node->left_;
			}
		}
	}
	Color temp_color = RED;
	if (temp_node != nullptr) {
		temp_color = temp_node->color_;
		temp_node->right_ = nullptr;
		temp_node->left_ = nullptr;
		temp_node->parent_ = nullptr;
		delete temp_node;
	} else {
		return false;  //如果没找到，返回删除失败
	}
	if (temp_color == BLACK) { //被删除节点是颜色是黑色才会对红黑树有影响，才需要修复
		RDDeleteFixup(temp_node);
	}
	return true;
}

void RBTree::RDDeleteFixup(RBTreeNode * node) {

}


void RBTree::RightRotato(RBTreeNode * node) {
	if (node->parent_ == nullptr) {
		RBTreeNode * temp_node = node->left_->right_;
		root_ = node->left_;
		root_->right_ = node;
		node->parent_ = root_;
		node->left_ = temp_node;
		if (node->left_ != nullptr) {
			node->left_->parent_ = node;
		}
		root_->parent_ = nullptr;
	} else {
		RBTreeNode * temp_node = node->left_->right_;
		if (node == node->parent_->left_) {
			node->parent_->left_ = node->left_;
		} else {
			node->parent_->right_ = node->left_;
		}
		node->left_->parent_ = node->parent_;
		node->parent_ = node->left_;
		node->left_->right_ = node;
		node->left_ = temp_node;
		if (node->left_ != nullptr) {
			node->left_->parent_ = node;
		}
	}
}

void RBTree::LeftRotato(RBTreeNode * node) {
	if (node->parent_ == nullptr) {
		RBTreeNode * temp_node = node->right_->left_;
		root_ = node->right_;
		root_->left_ = node;
		node->parent_ = root_;
		node->right_ = temp_node;
		if (node->right_ != nullptr) {
			node->right_->parent_ = node;
		}
		root_->parent_ = nullptr;
	} else {
		RBTreeNode * temp_node = node->right_->left_;
		if (node == node->parent_->left_) {
			node->parent_->left_ = node->right_;
		} else {
			node->parent_->right_ = node->right_;
		}
		node->right_->parent_ = node->parent_;
		node->parent_ = node->right_;
		node->right_->left_ = node;
		node->right_ = temp_node;
		if (node->right_ != nullptr) {
			node->right_->parent_ = node;
		}
	}
}


void RBTree::Dlr() {
	Dlr(root_);
}

void RBTree::Dlr(RBTreeNode *node) {
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

void RBTree::Ldr() {
	Ldr(root_);
}

void RBTree::Ldr(RBTreeNode *node) {
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

void RBTree::Lrd() {
	Lrd(root_);
}

void RBTree::Lrd(RBTreeNode *node) {
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


