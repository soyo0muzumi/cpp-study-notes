#pragma once
#include <iostream>

using namespace std;

template<class K, class V>
struct BSTreeNode {
	BSTreeNode(const K& x = K(), const V& val = V()) 
		: _left(nullptr)
		, _right(nullptr)
		, _key(x)
		, _val(val)
	{}

	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;

	K _key;
	V _val
};


template<class K, class V>
class BSTree {
	typedef BSTreeNode<K, V> Node;
public:

	bool Insert(const K& x, const V& val) {
		if (_root == nullptr) {
			_root = new Node(x, val);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;


		while (cur) {
			if (cur->_key > x) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < x) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		cur = new Node(x);
		if (parent->_key < x) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}

		return true;
	}

	Node* find(const K& x) {
		Node* cur = _root;

		while (cur) {
			if (cur->_key > x) {
				cur = cur->_left;
			}
			else if (cur->_key < x) {
				cur = cur->_right;
			}
			else {
				return cur;
			}
		}

		return nullptr;
	}

	bool Erase(const K& x) {
		Node* parent = nullptr;
		Node* cur = _root;

		while (cur) {
			if (cur->_key < x) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > x) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				break;
			}
		}

		if (cur == nullptr) {
			return false;
		}

		// ×óÎª¿Õ
		if (cur->_left == nullptr) {
			if (cur == _root) {
				_root = cur->_right;
			}
			else {
				if (parent->_right == cur) {
					parent->_right = cur->_right;
				}
				else {
					parent->_left = cur->_right;
				}
			}

			delete cur;
		}
		// ÓÒÎª¿Õ
		else if (cur->_right == nullptr) {
			if (cur == _root) {
				_root = cur->_left;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = cur->_left;
				}
				else {
					parent->_right = cur->_left;
				}
			}
			
			delete cur;
		}
		// ×óÓÒ¶¼²»Îª¿Õ
		else {
			Node* swapnode = cur->_left;
			Node* sparent = cur;
			while (swapnode->_right) {
				sparent = swapnode;
				swapnode = swapnode->_right;
			}
			// Ìæ´úÉ¾³ý
			cur->_key = swapnode->_key;
			// ×ª»»³ÉÉ¾³ýswapnode
			if (swapnode == sparent->_right) {
				sparent->_right = swapnode->_left;
			}
			else {
				sparent->_left = swapnode->_left;
			}

			delete swapnode;
		}
	}

	void _InOrder(Node* root) {
		if (root == nullptr) {
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << ":" << root->_val << " ";
		_InOrder(root->_right);

	}
	void InOrder() {
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};