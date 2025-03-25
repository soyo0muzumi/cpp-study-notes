#pragma once
#include <utility>
#include <iostream>

using namespace std;


template<class K, class V>
struct AVLTreeNode {
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf; // balence factory 平衡因子

	pair<K, V> _kv;

	// 构造函数
	AVLTreeNode(const pair<K, V>& kv) 
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		, _kv(kv)
	{}
};

template<class K, class V> 
class AVLTree {
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<K, V>& kv) {
		// 1. 先按搜索树的规则进行插入
		// 2. 更新平衡因子
		// 3. 如果更新完了，没有出现违反规则，则插入结束，有，则旋转处理
		if (_root == nullptr) {
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first) {
			parent->_right = cur;
			cur->_parent = parent;
		}
		else {
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 更新平衡因子
		// 1. cur是parent的左，parent->_bf--, cur是parent的右，parent->_bf++;
		// 2. 更新完如果parent->_bf == 0，说明parent的高度不变，更新结束，插入完成（即把parent矮的那一边填上了，高度不变，对上层没有影响）
		// 3. 更新完如果parent->_bf == 1 or -1, 说明parent的高度变了，继续往上更新（即更新前，parent的_bf是0，现在变了，说明变高了，对上层有影响）
		// 4. 更新完如果parent->_bf == 2 or -2, 说明parent所在的子树出现了不平衡，需要旋转处理

		while (parent) {
			if (cur == parent->_right) {
				parent->_bf++;
			}
			else {
				parent->_bf--;
			}
			if (parent->_bf == 0) {
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) {
				// parent所在的子树不平衡了，需要进行旋转处理
				// 1. 旋转完成后，还是搜索树
				// 2. 旋转后变平衡树

				if (parent->_bf == 2) {
					if (cur->_bf == 1) {
						RotateL(parent);
					}
					else if (cur->_bf == -1) {
						RotateRL(parent);
					}
				}
				else {
					if (cur->_bf == -1) {
						RotateR(parent);
					}
					else if (cur->_bf == 1) {
						RotateLR(parent);
					}
				}

				// 旋转完成之后，parent所在的树的高度恢复到了插入节点前的高度
				// 如果是子树，对上层无影响，更新结束

				break;
			}
		}

		return true;
	}

	// 左单旋
	// 把 subR 的左边给到 parent 的右边
	// parent 变成 subR 的左边
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		
		// 1、原来parent是这棵树的根，现在subR是根
		if (_root == parent) {
			_root = subR;
			subR->_parent = nullptr;
		}
		// 2、原来parent不是这棵树的根，上面还有节点，那么subR要顶替parent
		else {
			if (ppNode->_left == parent) {
				ppNode->_left = subR;
			}
			else {
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}

		parent->_bf = subR->_bf = 0;
	}


	// 右单旋	
	// 把 subR 的右边给到 parent 的左边
	// parent 变成 subR 的右边
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		parent->_left = subLR;
		if (subLR) {
			subLR->_parent = parent;
		}

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			if (ppNode->_left == parent) {
				ppNode->_left = subL;
			}
			else {
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}

		parent->_bf = subL->_bf = 0;
	}

	void RotateRL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		// 对应图理解
		if (bf == -1) {
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1) {
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == 0) {
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void RotateLR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1) {
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1) {
			parent->_bf = -1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 0) {
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}

	int Height(Node* root) {
		if (root == nullptr)
			return 0;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _IsBalence(Node* root) {
		if (root == nullptr)
			return true;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return abs(leftHeight - rightHeight) < 2
			&& _IsBalence(root->_left)
			&& _IsBalence(root->_right);
	}

	bool IsBalence() {
		return _IsBalence(_root);
	}

	// 关于删除
	// 1、右边删除，父亲的平衡因子--。左边删除，父亲平衡因子++
	// 2、删除后，父亲的平衡因子变成0，说明父亲所在的树高度变了，继续往上更新
	// 3、删除后，父亲的平衡因子变成1/-1，说明父亲所在的树高度不变，更新结束

	// 查/改
	// 1、搜索树中key是不允许修改的，因为如果修改了整棵树可能就被破坏了。key/value的场景下可以修改value
	// 2、查与搜索树一致

private:
	Node* _root;
};

void TestAVLTree() {
	int a[] = { 6,3,7,11,9,26,18,14,15 };
	AVLTree<int, int> t;
	for (auto e : a) {
		t.Insert(make_pair(e, e));
	}

	cout << t.IsBalence() << endl;
}

