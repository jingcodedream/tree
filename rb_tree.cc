/*
 * RD_Tree.cc
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#include "rb_tree.h"

bool RBTree::Insert(uint32_t value) {
	RBTreeNode * index = root_;
	RBTreeNode * parent_index = index;
	while (index != leaf_node_) {
		parent_index = index;
		if (value > index->value_) {
			index = index->right_;
		} else if (value < index->value_) {
			index = index->left_;
		} else {
			++index->count_;
			return false;
		}
	}
	index = new RBTreeNode(value);
	index->color_ = RED;
	index->left_ = index->right_ = index->parent_ = leaf_node_;
	if (parent_index == leaf_node_) {
		root_ = index;
		index->color_ = BLACK;
		leaf_node_->left_ = leaf_node_->right_ = leaf_node_->parent_ = root_;
		return true;
	}
	if (value < parent_index->value_) {
		parent_index->left_ = index;
	} else {
		parent_index->right_ = index;
	}
	index->parent_ = parent_index;
	if (GetColor(parent_index) == BLACK) {  //如果插入节点的父节点颜色为黑色，不需要管
		return true;
	} else { //否者需要对插入节点进行处理
		RDInsertFixup(index);
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
				if (node == node->parent_->right_) { //如果节点是父节点的右子节点，父节点左旋变为下一种请款
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
				if (node == node->parent_->left_) { //如果节点是父节点的右子节点，父节点左旋变为下一种请款
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
	RBTreeNode * delete_node = root_;
	RBTreeNode * replace_node = delete_node;
	while (delete_node != leaf_node_) {
		if (value > delete_node->value_) {
			delete_node = delete_node->right_;
		} else if (value < delete_node->value_) {
			delete_node = delete_node->left_;
		} else {
			if (delete_node->left_ == leaf_node_) {
				if (delete_node->parent_ == leaf_node_) {
					root_ = delete_node->right_;
					if (root_ != leaf_node_) {
						root_->parent_ = leaf_node_;
					}
				} else {
					if (delete_node == delete_node->parent_->right_) {
						delete_node->parent_->right_ = delete_node->right_;
					} else {
						delete_node->parent_->left_ = delete_node->right_;
					}
				}
				delete_node->right_->parent_ = delete_node->parent_;
				replace_node = delete_node->right_;
				break;
			} else if (delete_node->right_ == leaf_node_) {
				if (delete_node->parent_ == leaf_node_) {  //如果当前节点不存在，表示删除的是根节点
					root_ = delete_node->left_;
					if (root_ != leaf_node_) {
						root_->parent_ = leaf_node_;
					}
				} else {
					if (delete_node == delete_node->parent_->right_) { //否则，将当前节点的后继节点指向相对应的后继节点
						delete_node->parent_->right_ = delete_node->left_;
					} else {
						delete_node->parent_->left_ = delete_node->left_;
					}
				}
				delete_node->left_->parent_ = delete_node->parent_;
				replace_node = delete_node->left_;
				break;
			} else {  //如果被删除节点的左右子树都不为空，找到节点的前驱节点，将前驱节点的值赋给被删除节点，删除前驱节点
				RBTreeNode * delete_node_pre = delete_node->left_;
				while (delete_node_pre->right_ != leaf_node_) {
					delete_node_pre = delete_node_pre->right_;
				}
				delete_node->value_ = delete_node_pre->value_;
				value = delete_node_pre->value_;
				delete_node = delete_node->left_;
			}
		}
	}
	if (delete_node == leaf_node_) {
		return false;  //如果没找到，返回删除失败
	}
	if (GetColor(delete_node) == BLACK) { //被删除节点是颜色是黑色才会对红黑树有影响，才需要修复
		RDDeleteFixup(replace_node);
	}
	delete_node->right_ = nullptr;
	delete_node->left_ = nullptr;
	delete_node->parent_ = nullptr;
	delete delete_node;
	return true;
}

void RBTree::RDDeleteFixup(RBTreeNode * node) {
	while (GetColor(node) == BLACK && node != root_) {
		if (node == node->parent_->left_) { //处理左节点
			if (GetColor(node->parent_->right_) == RED) {
				node->parent_->right_->color_ = BLACK;
				node->parent_->color_ = RED;
				LeftRotato(node->parent_);
			} else {
				if (GetColor(node->parent_->right_->left_) == BLACK && GetColor(node->parent_->right_->right_) == BLACK) {
					node->parent_->right_->color_ = RED;
					node = node->parent_;
				} else {
					if (GetColor(node->parent_->right_->left_) == RED && GetColor(node->parent_->right_->right_) == BLACK) {
						node->parent_->right_->color_ = RED;
						node->parent_->right_->left_->color_ = BLACK;
						RightRotato(node->parent_->right_);
					}
					node->parent_->right_->right_->color_ = BLACK;
					node->parent_->right_->color_ = node->parent_->color_;
					node->parent_->color_ = BLACK;
					LeftRotato(node->parent_);
					break;
				}
			}
		} else { //处理右节点
			if (GetColor(node->parent_->left_) == RED) {
				node->parent_->left_->color_ = BLACK;
				node->parent_->color_ = RED;
				RightRotato(node->parent_);
			} else {
				if (GetColor(node->parent_->left_->left_) == BLACK && GetColor(node->parent_->left_->right_) == BLACK) {
					node->parent_->left_->color_ = RED;
					node = node->parent_;
				} else {
					if (GetColor(node->parent_->left_->right_) == RED && GetColor(node->parent_->left_->left_) == BLACK) {
						node->parent_->left_->color_ = RED;
						node->parent_->left_->right_->color_ = BLACK;
						LeftRotato(node->parent_->left_);
					}
					node->parent_->left_->left_->color_ = BLACK;
					node->parent_->left_->color_ = node->parent_->color_;
					node->parent_->color_ = BLACK;
					RightRotato(node->parent_);
					break;
				}
			}
		}
	}
	node->color_ = BLACK;
}

bool RBTree::RightRotato(RBTreeNode * node) {
	if (node == leaf_node_ || node->left_ == leaf_node_) {
		return false;  //不能右旋
	}
	if (node->parent_ == leaf_node_) {  //根节点右旋
		RBTreeNode * temp_node = node->left_->right_;
		root_ = node->left_;
		root_->right_ = node;
		node->parent_ = root_;
		node->left_ = temp_node;
		if (node->left_ != leaf_node_) {
			node->left_->parent_ = node;
		}
		root_->parent_ = leaf_node_;
	} else { //其他节点的右旋
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
		if (node->left_ != leaf_node_) {
			node->left_->parent_ = node;
		}
	}
	return true;
}

bool RBTree::LeftRotato(RBTreeNode * node) {
	if (node == leaf_node_ || node->right_ == leaf_node_) {
		return false;  //不能左旋
	}
	if (node->parent_ == leaf_node_) {  //根节点的左旋
		RBTreeNode * temp_node = node->right_->left_;
		root_ = node->right_;
		root_->left_ = node;
		node->parent_ = root_;
		node->right_ = temp_node;
		if (node->right_ != leaf_node_) {
			node->right_->parent_ = node;
		}
		root_->parent_ = leaf_node_;
	} else {  //其他节点的左旋
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
		if (node->right_ != leaf_node_) {
			node->right_->parent_ = node;
		}
	}
	return true;
}


void RBTree::Dlr() {
	Dlr(root_);
}

void RBTree::Dlr(RBTreeNode *node) {
	if (node != leaf_node_) {
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
		if (node->left_ != leaf_node_) {
			Dlr(node->left_);
		}
		if (node->right_ != leaf_node_) {
			Dlr(node->right_);
		}
	}
}

void RBTree::Ldr() {
	Ldr(root_);
}

void RBTree::Ldr(RBTreeNode *node) {
	if (node != leaf_node_) {
		if (node->left_ != leaf_node_) {
			Ldr(node->left_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
		if (node->right_ != leaf_node_) {
			Ldr(node->right_);
		}
	}
}

void RBTree::Lrd() {
	Lrd(root_);
}

void RBTree::Lrd(RBTreeNode *node) {
	if (node != leaf_node_) {
		if (node->left_ != leaf_node_) {
			Lrd(node->left_);
		}
		if (node->right_ != leaf_node_) {
			Lrd(node->right_);
		}
		std::cout << node->value_ << ":" << node->count_ << ":" << node->color_ << std::endl;
	}
}

void RBTree::PrintBlackSum() {
    uint32_t sum = 0;
	PrintBlackSum(root_, sum);
}

void RBTree::PrintBlackSum(RBTreeNode * node, uint32_t sum) {
	if (node != leaf_node_) {
		if (GetColor(node) == BLACK) {
			++sum;
		}
		PrintBlackSum(node->left_, sum);
		PrintBlackSum(node->right_, sum);
	} else {
		std::cout << sum << std::endl;
	}
}
