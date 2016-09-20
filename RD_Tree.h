/*
 * RD_Tree.h
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#ifndef RD_TREE_H_
#define RD_TREE_H_

#include <iostream>
#include <stdint.h>

enum Color {
	RED = 0,
	BLACK
};

class RDTree {
public:
	RDTree() : root_(nullptr) {}
	RDTree(uint32_t value) : root_(new RDTreeNode(value)) {}
	~RDTree() {
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
	struct RDTreeNode {
		RDTreeNode() : RDTreeNode(0){}
		RDTreeNode(uint32_t value) : left_(nullptr), right_(nullptr), parent_(nullptr), value_(value),
				color_(RED), count_(1){}
		~RDTreeNode() {
			if (left_ != nullptr) {
				delete left_;
				left_ = nullptr;
			}
			if (right_ != nullptr) {
				delete right_;
				right_ = nullptr;
			}
		}
		RDTreeNode * left_;
		RDTreeNode * right_;
		RDTreeNode * parent_;
		uint32_t value_;
		Color color_;
		uint32_t count_;
	};

private:
	Color GetColor(RDTreeNode *node) { //得到color
		if (node == nullptr) {
			return BLACK;
		}
		return node->color_;
	}
	void Dlr(RDTreeNode *node); //前序遍历，递归实现
	void Ldr(RDTreeNode *node); //中序遍历，递归实现
	void Lrd(RDTreeNode *node); //后序遍历，递归实现
	void RDInsertFixup(RDTreeNode *node); //插入修复
	void RightRotato(RDTreeNode *node);   //右旋
	void LeftRotato(RDTreeNode *node);    //左旋
private:
	RDTreeNode * root_;
};


#endif /* RD_TREE_H_ */
