/*
 * RD_Tree.h
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <iostream>
#include <stdint.h>

enum Color {
	RED = 0,
	BLACK
};

class RBTree {
public:
	RBTree() : root_(nullptr) {}
	RBTree(uint32_t value) : root_(new RBTreeNode(value)) {}
	~RBTree() {
		if (root_ != nullptr) {
			delete root_;
			root_  = nullptr;
		}
	}
	bool Insert(uint32_t value);
	bool Delete(uint32_t value);
	void Dlr();  //前序遍历
	void Ldr();  //中序遍历
	void Lrd();  //后序遍历
private:
	struct RBTreeNode {
		RBTreeNode() : RBTreeNode(0){}
		RBTreeNode(uint32_t value) : left_(nullptr), right_(nullptr), parent_(nullptr), value_(value),
				color_(RED), count_(1){}
		~RBTreeNode() {
			if (left_ != nullptr) {
				delete left_;
				left_ = nullptr;
			}
			if (right_ != nullptr) {
				delete right_;
				right_ = nullptr;
			}
		}
		RBTreeNode * left_;
		RBTreeNode * right_;
		RBTreeNode * parent_;
		uint32_t value_;
		Color color_;
		uint32_t count_;
	};

private:
	Color GetColor(RBTreeNode *node) { //得到color
		if (node == nullptr) {
			return BLACK;
		}
		return node->color_;
	}
	void Dlr(RBTreeNode *node); //前序遍历，递归实现
	void Ldr(RBTreeNode *node); //中序遍历，递归实现
	void Lrd(RBTreeNode *node); //后序遍历，递归实现
	void RDInsertFixup(RBTreeNode *node); //插入修复
	void RDDeleteFixup(RBTreeNode *node); //删除修复
	void RightRotato(RBTreeNode *node);   //右旋
	void LeftRotato(RBTreeNode *node);    //左旋
private:
	RBTreeNode * root_;
};


#endif /* RB_TREE_H_ */
