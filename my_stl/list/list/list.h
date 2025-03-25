#pragma once
#include <assert.h>

//用一个类型去封装节点的指针构成一个自定义类型
//然后重载*、++等运算符就可以达到我们的目的构建出迭代器

template<class T>
struct __list_node {
	__list_node* _next;
	__list_node* _prev;
	T _data;

	__list_node(const T& x = T()) 
		:_data(x)
		, _next(nullptr)
		, _prev(nullptr)
	{}
};

// 封装后的迭代器
// __list_iterator<T, T&, T*> -> iterator
// __list_iterator<T, const T&, const T*> -> const_iterator

template<class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_node<T> Node;
	typedef __list_iterator<T, Ref, Ptr> Self;
	Node* _node;

	__list_iterator(Node* node)
		:_node(node)
	{}

	Ref operator*() {
		return _node->_data;
	}

	Ptr operator->() {
		return &_node->_data;
	}

	// ++it
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}

	// it++
	Self operator++(int) {
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}

	// --it
	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}

	// it--
	Self operator--(int) {
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}


	// it != end()
	bool operator!=(const Self& it) {
		return _node != it._node;
	}

	bool operator==(const Self& it) {
		return _node == it._node;
	}
};

template<class T>
class List {
public:
	// 带头双向循环链表
	typedef __list_node<T> Node;
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	iterator begin() {
		return (iterator)_head->_next;
	}

	iterator end() {
		return (iterator)_head;
	}

	const_iterator begin() const {
		return (const_iterator)_head->_next;
	}

	const_iterator end() const {
		return (const_iterator)_head;
	}

	List() {
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	List(const List<T>& lt) {
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;

		const_iterator it = lt.begin();
		while(it != lt.end()) {
			push_back(it._node->_data);
			++it;
		}
	}

	/*List<T>& operator=(const List<T>& lt) {
		if (this != &lt) {
			clear();
			for (auto e : lt) {
				push_back(e);
			}
		}

		return *this;
	}*/

	list<T>& operator=(list<T> lt) {
		swap(_head, lt._head);
		return *this;
	}

	~List() {
		clear();
		delete _head;
		_head = nullptr;
	}

	void clear() {
		iterator it = begin();
		while (it != end()) {
			erase(it++);
		}
	}

	void push_back(const T& x) {
		/*Node* newnode = new Node(x);
		Node* _tail = _head->_prev;

		newnode->_next = _head;
		newnode->_prev = _tail;
		_tail->_next = newnode;
		_head->_prev = newnode;*/

		insert(end(), x);
	}

	void push_front(const T& x) {
		insert(begin(), x);
	}

	void pop_front() {
		erase(begin());
	}

	void pop_back() {
		erase(--end());
	}

	void insert(iterator pos, const T& x) {
		Node* newnode = new Node(x);
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;
	}

	iterator erase(iterator pos) {
		assert(pos != end());

		Node* node = pos._node;
		Node* prev = node->_prev;
		Node* next = node->_next;
		prev->_next = next;
		next->_prev = prev;
		delete node;

		return (iterator)next;
	}

private:
	Node* _head;
};