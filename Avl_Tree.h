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

struct TreeNode {
	TreeNode() : TreeNode(0){}
	TreeNode(int32_t value) : left_(nullptr), right_(nullptr), value_(value), height_(1), count_(1){};
	~TreeNode() {
		if (left_ != nullptr) {
			delete left_;
			left_ = nullptr;
		}
		if (right_ != nullptr) {
			delete right_;
			right_ = nullptr;
		}
	}
	TreeNode * left_;
	TreeNode * right_;
	int32_t value_;
	uint32_t height_;   //结点高度
	uint32_t count_;    //结点数量统计
};

class AvlTree {
public:
	AvlTree() : root_(nullptr){}
	AvlTree(int32_t value) : root_(new TreeNode(value)){}
	~AvlTree() {
		if (root_) {
			delete root_;
			root_ = nullptr;
		}
	}
	void Insert(int32_t value); //插入
	bool Delete(int32_t value); //删除
	void Dlr();  //前序遍历，非递归实现
	void Ldr();  //中序遍历
	void Lrd();  //后序遍历
private:
	TreeNode * LeftRotate(TreeNode * node);
	TreeNode * RightRotate(TreeNode * node);
	uint32_t Height(TreeNode * node) {
		if (node == nullptr) {
			return 0;
		}
		return node->height_;
	}
	TreeNode * Insert(int32_t value, TreeNode *node); //插入
	TreeNode * Delete(int32_t value, TreeNode *node); //删除
	TreeNode * Find(int32_t value); //查找
	void Dlr(TreeNode *node); //前序遍历，递归实现
	void Ldr(TreeNode *node); //中序遍历，递归实现
	void Lrd(TreeNode *node); //后序遍历，递归实现
private:
	TreeNode * root_;
};


#endif /* AVL_TREE_H_ */
