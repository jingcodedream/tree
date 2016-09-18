/*
 * avl_tree.h
 *
 *  Created on: 2016年9月12日
 *      Author: joe
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>
#include <stdint.h>

class AvlTree {
public:
	AvlTree() : root_(nullptr){}
	AvlTree(uint32_t value) : root_(new AvlTreeNode(value)){}
	~AvlTree() {
		if (root_) {
			delete root_;
			root_ = nullptr;
		}
	}
	bool Insert(uint32_t value); //插入
	bool Delete(uint32_t value); //删除
	int64_t Find(uint32_t value); //查找
	void Dlr();  //前序遍历
	void Ldr();  //中序遍历
	void Lrd();  //后序遍历
private:
	struct AvlTreeNode {
		AvlTreeNode() : AvlTreeNode(0){}
		AvlTreeNode(uint32_t value) : left_(nullptr), right_(nullptr), value_(value), height_(1), count_(1){};
		~AvlTreeNode() {
			if (left_ != nullptr) {
				delete left_;
				left_ = nullptr;
			}
			if (right_ != nullptr) {
				delete right_;
				right_ = nullptr;
			}
		}
		AvlTreeNode * left_;
		AvlTreeNode * right_;
		uint32_t value_;
		uint32_t height_;   //结点高度
		uint32_t count_;    //结点数量统计
	};
private:
	AvlTreeNode * LeftRotate(AvlTreeNode * node);
	AvlTreeNode * RightRotate(AvlTreeNode * node);
	uint32_t Height(AvlTreeNode * node) {
		if (node == nullptr) {
			return 0;
		}
		return node->height_;
	}
	//height_change执行操作后结点的高度有没有改变
	AvlTreeNode * Insert(uint32_t value, AvlTreeNode *node, bool &height_change); //插入
	AvlTreeNode * Delete(uint32_t value, AvlTreeNode *node, bool &height_change); //删除
	AvlTreeNode * NodeHandle(AvlTreeNode *node); //结点或其子树修改后的处理
	void Dlr(AvlTreeNode *node); //前序遍历，递归实现
	void Ldr(AvlTreeNode *node); //中序遍历，递归实现
	void Lrd(AvlTreeNode *node); //后序遍历，递归实现
private:
	AvlTreeNode * root_;
};


#endif /* AVL_TREE_H_ */
