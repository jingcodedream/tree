/*
 * RD_Tree.h
 *
 *  Created on: 2016年9月18日
 *      Author: joe
 */

#ifndef RD_TREE_H_
#define RD_TREE_H_

enum Color {
	RED = 0,
	BALACK
};

class RDTree {
public:
	RDTree() : root_(nullptr) {}
	RDTree(int32_t value) : root_(new RDTreeNode(value)) {}
	~RDTree() {
		if (root_ != nullptr) {
			delete root_;
			root_  = nullptr;
		}
	}
	bool Insert(int32_t value);
	bool Delete(int32_t value);
	void Dlr();  //前序遍历
	void Ldr();  //中序遍历
	void Lrd();  //后序遍历
private:
	struct RDTreeNode {
		RDTreeNode() : RDTreeNode(0){}
		RDTreeNode(int32_t value) : left_(nullptr), right_(nullptr), parent_(nullptr), value_(value),
				color_(BALACK), count_(1){}
		~RDTreeNode() {
			if (left_ != nullptr) {
				delete left_;
				left_ = nullptr;
			}
			if (right_ != nullptr) {
				delete right_;
				right_ = nullptr;
			}
			if (parent_ != nullptr) {
				delete parent_;
				parent_ = nullptr;
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
	void Dlr(RDTreeNode *node); //前序遍历，递归实现
	void Ldr(RDTreeNode *node); //中序遍历，递归实现
	void Lrd(RDTreeNode *node); //后序遍历，递归实现
private:
	RDTreeNode * root_;
};


#endif /* RD_TREE_H_ */
