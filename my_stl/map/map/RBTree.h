#pragma once
#include <utility>
#include <iostream>

using namespace std;

// 红黑树
// 搜索二叉树，节点中加了颜色，不是红色就是黑色，最长的路径不超过最短的路径的两倍
// AVLTree是严格平衡二叉树，红黑树是近似平衡二叉搜索树
// 1、每个节点不是红色就是黑色
// 2、根节点是黑色的
// 3、如果一个节点是红色的，则它的两个孩子节点是黑的
// 4、对于每个节点，从该节点到其所有后代叶节点的简单路径上，均包含相同数目的黑色节点
// 5、每个叶子节点都是黑色的（这里的叶节点指的是空节点）

// 最短的路径：全黑
// 最长的路径：一黑一红

enum Color {
	BLACK,
	RED,
};

template<class T>
struct RBTreeNode {
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	
	T _data;

	Color _col;

	RBTreeNode(const T& x)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(x)
		, _col(RED)
	{ }

};

template<class T>
struct __TreeIterator {
	typedef RBTreeNode<T> Node;
	typedef __TreeIterator<T> Self;
	Node* _node;

	T& operator*() {
		return _node->_data;
	}

	T* operator->() {
		return &(_node->_data);
	}

	Self& operator++() {
		// 1. 右不为空，中序的下一个就是右子树的最左节点
		// 2. 右为空，表示_node所在的子树已经访问完成，下一个节点在他的祖先中找
		//	  怎么找
		//			如果父亲小于孩子，那么父亲一定访问过了，去父亲的祖先中找
		//			如果父亲大于孩子，那么父亲没有访问过，跳出循环
		//    
		if (_node->_right) {
			// 中序的下一个就是右子树的最左节点
			Node* subLeft = _node->_right;
			while (subLeft->_left) {
				subLeft = subLeft->_left;
			}

			_node = subLeft;
		}
		else {
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_right == cur) {
				cur = parent;
				parent = cur->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	Self operator++(int) {
		Self tmp = this;
		++this;
		return tmp;
	}

	Self& operator--() {

	}

	Self operator--(int) {

	}

	bool operator!=(const Self& s) {
		return _node != s._node;
	}

	bool operator==(const Self& s) {
		return _node == s._node;
	}

	__TreeIterator(Node* node)
		: _node(node)
	{ }
};


template<class K, class T, class KOfT>
class RBTree {
	typedef RBTreeNode<T> Node;
public:
	typedef __TreeIterator<T> iterator;

	RBTree()
		: _root(nullptr)
	{}

	iterator begin() {
		Node* cur = _root;
		while (cur && cur->_left) {
			cur = cur->_left;
		}

		return iterator(cur);
	}

	iterator end() {
		return iterator(nullptr);
	}

	pair<iterator, bool> Insert(const T& data) {
		// 1. 按搜索树的规则插入
		if (_root == nullptr) {
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root), true);
		}

		KOfT koft;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (koft(cur->_data) < koft(data)) {
				parent = cur;
				cur = cur->_right;
			}
			else if (koft(cur->_data) > koft(data)) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return make_pair(iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newNode = cur;
		if (koft(parent->_data) < koft(data)) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		cur->_parent = parent;
		
		// 把新插入的节点置为红色，因为其违反的规则3影响更小
		cur->_col = RED;

		// 旋转 + 变色
		while (parent && parent->_col == RED) {
			if (parent == _root) break;
			// 红黑树的调节关键看uncle
			Node* grandparent = parent->_parent;
			Node* uncle = nullptr;
			if (parent == grandparent->_left) {
				uncle = grandparent->_right;
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					// 继续向上处理
					parent = grandparent;
					grandparent = parent->_parent;
				}
				else {
					// 双旋 -> 变为单旋（情况3）
					if (cur == parent->_right) {
						RotateL(parent);
						swap(parent, cur);
					}

					// 第二种情况（可能是第三种变过来的）
					RotateR(grandparent);
					grandparent->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
			else {
				uncle = grandparent->_left;
				if (uncle && uncle->_col == RED) {
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandparent->_col = RED;

					parent = grandparent;
					grandparent = parent->_parent;
				}
				else {
					if (cur == parent->_left) {
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandparent);
					grandparent->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(iterator(newNode), false);

	}

	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (_root == parent) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			subR->_parent = ppNode;
			if (ppNode->_left == parent) {
				ppNode->_left = subR;
			}
			else {
				ppNode->_right = subR;
			}
		}

	}

	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			subL->_parent = ppNode;
			if (ppNode->_left == parent) {
				ppNode->_left = subL;
			}
			else {
				ppNode->_right = subL;
			}
		}

	}

	void _inorder(Node* root) {
		if (root == nullptr) {
			return;
		}

		_inorder(root->_left);
		cout << root->_kv.first << endl;
		_inorder(root->_left);
	}

	void Inorder() {
		_inorder(_root);
	}

	Node* Find(const K& key) {
		KOfT koft;
		Node* cur = _root;
		while (cur) {
			if (koft(cur->_data) < key) {
				cur = cur->_right;
			}
			else if (koft(cur->_data) > key) {
				cur = cur->_left;
			}
			else {
				return cur;
			}
		}

		return false;
	}

private:
	Node* _root;
};