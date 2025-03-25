## list

## 1. stl中的list

为什么会有list
补充vector的缺点存在的
vector的缺点

1. 头部和中部的插入删除效率低、O(N), 因为需要挪动数据

2. 插入数据空间不够需要增容。增容要开辟新空间、拷贝数据、释放就空间，付出很大代价

优点

1. 支持下标的随机访问。 就支持排序、二分查找、堆算法等

list优点
list头部、中间插入不再需要挪动数据，效率高
list插入数据不需要新开辟空间
缺点
不能随机访问

### 1.1 list的使用

> list中的接口比较多，此处类似，只需要掌握如何正确的使用，然后再去深入研究背后的原理，已达到可扩展的能力。以下为list中一些常见的重要接口。

#### 1.1.1 list的构造

> | 构造函数（ [(constructor)](http://www.cplusplus.com/reference/list/list/list/) ） | 接口说明                            |
> | ------------------------------------------------------------ | ----------------------------------- |
> | **list (size_type n, const value_type& val = value_type())** | 构造的list中包含n个值为val的元素    |
> | list()                                                       | 构造空的list                        |
> | list (const list& x)                                         | 拷贝构造函数                        |
> | list (InputIterator first, InputIterator last)               | 用[first, last)区间中的元素构造list |
>

#### 1.1.2 list迭代器的使用

> | 函数声明                                                     | 接口说明                                                     |
> | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | [begin](http://www.cplusplus.com/reference/list/list/begin/) + [end](http://www.cplusplus.com/reference/list/list/end/) | 返回第一个元素的迭代器+返回最后一个元素下一个位置的迭代器    |
> | [rbegin](http://www.cplusplus.com/reference/list/list/rbegin/) + [rend](http://www.cplusplus.com/reference/list/list/rend/) | 返回第一个元素的reverse_iterator,即end位置，返回最后一个元素下一个位置的 reverse_iterator,即begin位置 |
>
> ```cpp
> void test_list1() {
> 	list<int> l1;
> 	l1.push_back(1);
> 	l1.push_back(2);
> 	l1.push_back(3);
> 	l1.push_back(4);
> 	l1.push_back(5);
> 	l1.push_front(0);
> 
> 	list<int>::iterator it1 = l1.begin();
> 	while (it1 != l1.end()) {
> 		cout << *it1 << " ";
> 		++it1;
> 	}
> 	cout << endl;
> 
> 	print_list(l1);
> 
> 	list<int> l3;
> 	l3.push_back(10);
> 	l3.push_back(20);
> 	l3.push_back(30);
> 	l3.push_back(40);
> 
> 	l1 = l3;
> 
> 	for (auto e : l1) {
> 		cout << e << " ";
> 	}
> 	cout << endl;
> }
> ```

#### 1.1.3 list capacity

> | 函数声明                                                     | 接口说明                                    |
> | ------------------------------------------------------------ | ------------------------------------------- |
> | [empty](http://www.cplusplus.com/reference/list/list/empty/) | 检测list是否为空，是返回true，否则返回false |
> | [size](http://www.cplusplus.com/reference/list/list/size/)   | 返回list中有效节点的个数                    |

#### 1.1.4 list modifiers

> | 函数声明                                                     | 接口说明                                |
> | ------------------------------------------------------------ | --------------------------------------- |
> | [push_front](http://www.cplusplus.com/reference/list/list/push_front/) | 头插                                    |
> | [pop_front](http://www.cplusplus.com/reference/list/list/pop_front/) | 头删                                    |
> | [push_back](http://www.cplusplus.com/reference/list/list/push_back/) | 尾插                                    |
> | [pop_back](http://www.cplusplus.com/reference/list/list/pop_back/) | 尾删                                    |
> | [insert](http://www.cplusplus.com/reference/list/list/insert/) | 在list position 位置中插入值为val的元素 |
> | [erase](http://www.cplusplus.com/reference/list/list/erase/) | 删除list position位置的元素             |
> | [swap](http://www.cplusplus.com/reference/list/list/swap/)   | 交换两个list中的元素                    |
> | [clear](http://www.cplusplus.com/reference/list/list/clear/) | 清空list中的有效元素                    |
>
> ```cpp
> void test_list2() {
> 	list<int> lt;
> 	lt.push_back(1);
> 	lt.push_back(2);
> 	lt.push_back(3);
> 	lt.push_back(4);
> 	lt.push_back(5);
> 	lt.push_front(0);
> 	lt.push_front(-1);
> 
> 	print_list(lt);
> 
> 	lt.pop_back();
> 	lt.pop_front();
> 	print_list(lt);
> 
> }
> 
> void test_list3() {
> 	list<int> lt;
> 	lt.push_back(1);
> 	lt.push_back(2);
> 	lt.push_back(3);
> 	lt.push_back(4);
> 	lt.push_back(5);
> 	
> 	print_list(lt);
> 
> 	list<int>::iterator pos = find(lt.begin(), lt.end(), 3);
> 	if (pos != lt.end()) {
> 		lt.insert(pos, 30);
> 		lt.erase(pos);
> 	}
> 	print_list(lt);
> 
> }
> ```

#### 1.1.5 list的迭代器失效

> 前面说过，此处大家可将迭代器暂时理解成类似于指针，**迭代器失效即迭代器所指向的节点的无效，即该节点被删除了。因为list的底层结构为带头结点的双向循环链表，因此在list中进行插入时是不会导致list的迭代器失效的，只有在删除时才会失效，并且失效的只是指向被删除节点的迭代器，其他迭代器不会受到影响**。
>
> ```cpp
> void test_list4() {
> 	list<int> lt;
> 	lt.push_back(3);
> 	lt.push_back(2);
> 	lt.push_back(1);
> 	lt.push_back(5);
> 	lt.push_back(4);
> 	lt.push_back(6);
> 
> 	print_list(lt);
> 
> 
> 	list<int>::iterator it = lt.begin();
> 	while (it != lt.end()) {
> 		if (*it % 2 == 0) {
> 			//lt.erase(it);
> 			// erase过后迭代器失效
> 			it = lt.erase(it);
> 		}
> 		else {
> 			++it;
> 		}
> 	}
> 	print_list(lt);
> 
> }
> ```

## 2. list的模拟实现

### 2.1 模拟实现

> ```cpp
> #pragma once
> #include <assert.h>
> 
> //用一个类型去封装节点的指针构成一个自定义类型
> //然后重载*、++等运算符就可以达到我们的目的构建出迭代器
> 
> template<class T>
> struct __list_node {
> 	__list_node* _next;
> 	__list_node* _prev;
> 	T _data;
> 
> 	__list_node(const T& x = T()) 
> 		:_data(x)
> 		, _next(nullptr)
> 		, _prev(nullptr)
> 	{}
> };
> 
> // 封装后的迭代器
> // __list_iterator<T, T&, T*> -> iterator
> // __list_iterator<T, const T&, const T*> -> const_iterator
> 
> template<class T, class Ref, class Ptr>
> struct __list_iterator {
> 	typedef __list_node<T> Node;
> 	typedef __list_iterator<T, Ref, Ptr> Self;
> 	Node* _node;
> 
> 	__list_iterator(Node* node)
> 		:_node(node)
> 	{}
> 
> 	Ref operator*() {
> 		return _node->_data;
> 	}
> 
> 	Ptr operator->() {
> 		return &_node->_data;
> 	}
> 
> 	// ++it
> 	Self& operator++() {
> 		_node = _node->_next;
> 		return *this;
> 	}
> 
> 	// it++
> 	Self operator++(int) {
> 		Self tmp(*this);
> 		_node = _node->_next;
> 		return tmp;
> 	}
> 
> 	// --it
> 	Self& operator--() {
> 		_node = _node->_prev;
> 		return *this;
> 	}
> 
> 	// it--
> 	Self operator--(int) {
> 		Self tmp(*this);
> 		_node = _node->_prev;
> 		return tmp;
> 	}
> 
> 
> 	// it != end()
> 	bool operator!=(const Self& it) {
> 		return _node != it._node;
> 	}
> 
> 	bool operator==(const Self& it) {
> 		return _node == it._node;
> 	}
> };
> 
> template<class T>
> class List {
> public:
> 	// 带头双向循环链表
> 	typedef __list_node<T> Node;
> 	typedef __list_iterator<T, T&, T*> iterator;
> 	typedef __list_iterator<T, const T&, const T*> const_iterator;
> 
> 	iterator begin() {
> 		return (iterator)_head->_next;
> 	}
> 
> 	iterator end() {
> 		return (iterator)_head;
> 	}
> 
> 	const_iterator begin() const {
> 		return (const_iterator)_head->_next;
> 	}
> 
> 	const_iterator end() const {
> 		return (const_iterator)_head;
> 	}
> 
> 	List() {
> 		_head = new Node;
> 		_head->_next = _head;
> 		_head->_prev = _head;
> 	}
> 
> 	List(const List<T>& lt) {
> 		_head = new Node;
> 		_head->_next = _head;
> 		_head->_prev = _head;
> 
> 		const_iterator it = lt.begin();
> 		while(it != lt.end()) {
> 			push_back(it._node->_data);
> 			++it;
> 		}
> 	}
> 
> 	/*List<T>& operator=(const List<T>& lt) {
> 		if (this != &lt) {
> 			clear();
> 			for (auto e : lt) {
> 				push_back(e);
> 			}
> 		}
> 
> 		return *this;
> 	}*/
> 
> 	list<T>& operator=(list<T> lt) {
> 		swap(_head, lt._head);
> 		return *this;
> 	}
> 
> 	~List() {
> 		clear();
> 		delete _head;
> 		_head = nullptr;
> 	}
> 
> 	void clear() {
> 		iterator it = begin();
> 		while (it != end()) {
> 			erase(it++);
> 		}
> 	}
> 
> 	void push_back(const T& x) {
> 		/*Node* newnode = new Node(x);
> 		Node* _tail = _head->_prev;
> 
> 		newnode->_next = _head;
> 		newnode->_prev = _tail;
> 		_tail->_next = newnode;
> 		_head->_prev = newnode;*/
> 
> 		insert(end(), x);
> 	}
> 
> 	void push_front(const T& x) {
> 		insert(begin(), x);
> 	}
> 
> 	void pop_front() {
> 		erase(begin());
> 	}
> 
> 	void pop_back() {
> 		erase(--end());
> 	}
> 
> 	void insert(iterator pos, const T& x) {
> 		Node* newnode = new Node(x);
> 		Node* cur = pos._node;
> 		Node* prev = cur->_prev;
> 		prev->_next = newnode;
> 		newnode->_prev = prev;
> 		newnode->_next = cur;
> 		cur->_prev = newnode;
> 	}
> 
> 	iterator erase(iterator pos) {
> 		assert(pos != end());
> 
> 		Node* node = pos._node;
> 		Node* prev = node->_prev;
> 		Node* next = node->_next;
> 		prev->_next = next;
> 		next->_prev = prev;
> 		delete node;
> 
> 		return (iterator)next;
> 	}
> 
> private:
> 	Node* _head;
> };
> ```

### 2.2 关于list的const迭代器问题

> 由于本来的迭代器和const迭代器的区别仅仅有返回值不同，所以给出Ref，Ptr来控制