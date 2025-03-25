## vector类

## 1. stl 中的vector

> ### 1.1 vector的构造
>
> | ([constructor](http://www.cplusplus.com/reference/vector/vector/vector/))构造函数声明 | 接口说明                 |
> | ------------------------------------------------------------ | ------------------------ |
> | vector()                                                     | 无参构造                 |
> | vector（size_type n, const value_type& val = value_type()）  | 构造并初始化n个val       |
> | vector (const vector& x);                                    | 拷贝构造                 |
> | vector (InputIterator first, InputIterator last);            | 使用迭代器进行初始化构造 |
>
> ```cpp
> int TestVector1()
> {
>     // constructors used in the same order as described above:
>     vector<int> first;                                // empty vector of ints
>     vector<int> second(4, 100);                       // four ints with value 100
>     vector<int> third(second.begin(), second.end());  // iterating through second
>     vector<int> fourth(third);                       // a copy of third
> 
>     // the iterator constructor can also be used to construct from arrays:
>     int myints[] = { 16,2,77,29 };
>     vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
> 
>     cout << "The contents of fifth are:";
>     for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
>         cout << ' ' << *it;
>     cout << '\n';
> 
>     return 0;
> }
> 
> ```
>
> ### 1.2 vector iterator 的使用
>
> | iterator的使用                                               | 接口说明                                                     |
> | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | [begin](http://www.cplusplus.com/reference/vector/vector/begin/) + [end](http://www.cplusplus.com/reference/vector/vector/end/) | 获取第一个数据位置的iterator/const_iterator， 获取最后一个数据的下一个位置的iterator/const_iterator |
> | [rebegin](http://www.cplusplus.com/reference/vector/vector/rbegin/) + [rend](http://www.cplusplus.com/reference/vector/vector/rend/) | 获取最后一个数据位置的reverse_iterator，获取第一个数据前一个位置的 reverse_iterator |
>
> ### 1.3 vector 空间增长问题
>
> | 容量空间                                                     | 接口说明             |
> | ------------------------------------------------------------ | -------------------- |
> | [size](http://www.cplusplus.com/reference/vector/vector/size/) | 获取数据个数         |
> | [capacity](http://www.cplusplus.com/reference/vector/vector/capacity/) | 获取容量大小         |
> | [empty](http://www.cplusplus.com/reference/vector/vector/empty/) | 判断是否为空         |
> | [resize](http://www.cplusplus.com/reference/vector/vector/resize/) | 改变vector的size     |
> | [reserve](http://www.cplusplus.com/reference/vector/vector/reserve/) | 改变vector的capacity |
>
> - reserve只负责开辟空间，如果确定知道需要用多少空间，reserve可以缓解vector增容的代价缺陷问 题。
> - resize在开空间的同时还会进行初始化，影响size。
>
> ```cpp
> // 如果已经确定vector中要存储元素大概个数，可以提前将空间设置足够
> // 就可以避免边插入边扩容导致效率低下的问题了
> void TestVectorExpandOP()
> {
> 	vector<int> v;
> 	size_t sz = v.capacity();
> 	v.reserve(100);
> 	// 提前将容量设置好，可以避免一遍插入一遍扩容
> 	cout << "making bar grow:\n";
> 	for (int i = 0; i < 100; ++i)
> 	{
> 		v.push_back(i);
> 		if (sz != v.capacity())
> 		{
> 			sz = v.capacity();
> 			cout << "capacity changed: " << sz << '\n';
> 		}
> 	}
> }
> ```
>
> ### 1.4 vector 增删查改
>
> | vector增删查改                                               | 接口说明                                               |
> | ------------------------------------------------------------ | ------------------------------------------------------ |
> | [push_back](http://www.cplusplus.com/reference/vector/vector/push_back/) | 尾插                                                   |
> | [pop_back](http://www.cplusplus.com/reference/vector/vector/pop_back/) | 尾删                                                   |
> | [find](http://www.cplusplus.com/reference/algorithm/find/?kw=find) | 查找。（注意这个是算法模块实现，不是vector的成员接口） |
> | [insert](http://www.cplusplus.com/reference/vector/vector/insert/) | 在position之前插入val                                  |
> | [erase](http://www.cplusplus.com/reference/vector/vector/erase/) | 删除position位置的数据                                 |
> | [swap](http://www.cplusplus.com/reference/vector/vector/swap/) | 交换两个vector的数据空间                               |
> | [operator[]](http://www.cplusplus.com/reference/vector/vector/operator%5B%5D/) | 像数组一样访问                                         |
>
> ```cpp
> void TestVector4()
> {
> 	vector<int> v;
> 	v.push_back(1);
> 	v.push_back(2);
> 	v.push_back(3);
> 	v.push_back(4);
> 
> 	auto it = v.begin();
> 	while (it != v.end()) 
> 	{
> 		cout << *it << " ";
> 		++it;
> 	}
> 	cout << endl;
> 
> 	v.pop_back();
> 	v.pop_back();
> 
> 	it = v.begin();
> 	while (it != v.end()) 
> 	{
> 		cout << *it << " ";
> 		++it;
> 	}
> 	cout << endl;
> }
> ```
>
> ### 1.5 vector 迭代器失效问题
>
> **迭代器的主要作用就是让算法能够不用关心底层数据结构，其底层实际就是一个指针，或者是对指针进行了封装**，比如：**vector的迭代器就是原生态指针T*** 。因此**迭代器失效**，**实际就是迭代器底层对应指针所指向的 空间被销毁了，而使用一块已经被释放的空间**，造成的后果是程序崩溃(即**如果继续使用已经失效的迭代器**， 程序可能会崩溃)。
>
> 对于vector可能会导致其迭代器失效的操作有：
>
> 1. **会引起其底层空间改变的操作，都有可能是迭代器失效**，比如：resize、reserve、insert、assign、 push_back等。
>
> 	```cpp
> 	int main()
> 	{
> 		vector<int> v{ 1,2,3,4,5,6 };
> 	
> 		auto it = v.begin();
> 	
> 		// 将有效元素个数增加到100个，多出的位置使用8填充，操作期间底层会扩容
> 		// v.resize(100, 8);
> 	
> 		// reserve的作用就是改变扩容大小但不改变有效元素个数，操作期间可能会引起底层容量改变
> 		// v.reserve(100);
> 	
> 		// 插入元素期间，可能会引起扩容，而导致原空间被释放
> 		// v.insert(v.begin(), 0);
> 		// v.push_back(8);
> 	
> 		// 给vector重新赋值，可能会引起底层容量改变
> 		v.assign(100, 8);
> 	
> 		/*
> 		出错原因：以上操作，都有可能会导致vector扩容，也就是说vector底层原理旧空间被释放掉，
> 	而在打印时，it还使用的是释放之间的旧空间，在对it迭代器操作时，实际操作的是一块已经被释放的
> 	空间，而引起代码运行时崩溃。
> 		解决方式：在以上操作完成之后，如果想要继续通过迭代器操作vector中的元素，只需给it重新
> 	赋值即可。
> 		*/
> 		while (it != v.end())
> 		{
> 			cout << *it << " ";
> 			++it;
> 		}
> 		cout << endl;
> 		return 0;
> 	}
> 	```
>
> 2. 指定位置元素的删除操作--**erase**
> 	```cpp
> 	int main()
> 	{
> 		int a[] = { 1, 2, 3, 4 };
> 		vector<int> v(a, a + sizeof(a) / sizeof(int));
> 		
> 		// 使用find查找3所在位置的iterator
> 		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
> 		
> 		// 删除pos位置的数据，导致pos迭代器失效。
> 		v.erase(pos);
> 		cout << *pos << endl; // 此处会导致非法访问
> 		return 0;
> 	}
> 	```
>
> 	erase删除pos位置元素后，pos位置之后的元素会往前搬移，没有导致底层空间的改变，理论上讲迭代器不应该会失效，但是：如果pos刚好是最后一个元素，删完之后pos刚好是end的位置，而end位置是没有元素的，那么pos就失效了。因此删除vector中任意位置上元素时，vs就认为该位置迭代器失效了。
>
> 	解决方法：
>
> 	```cpp
> 	int main()
> 	{
> 		vector<int> v{ 1, 2, 3, 4 };
> 		auto it = v.begin();
> 		while (it != v.end())
> 		{
> 			if (*it % 2 == 0)
> 				it = v.erase(it);
> 			else
> 				++it;
> 		}
> 		return 0;
> 	}
> 	```
>
> 	erase的返回值是一个迭代器，指向函数调用擦除的最后一个元素之后的元素的新位置

## 2. vector模拟实现

### 2.1 模拟实现vector的重要接口

> ```cpp
> #pragma once
> #include <iostream>
> #include <assert.h>
> #include <string>
> 
> using namespace std;
> 
> template<class T>
> class Vector {
> public:
> 	typedef T* iterator;
> 	typedef const T* const_iterator;
> 	
> 	Vector()
> 		:_start(nullptr)
> 		, _finish(nullptr)
> 		, _endofstorage(nullptr)
> 	{}
> 
> 	// v2(v1)
> 	/*Vector(const Vector<T>& v) {
> 		_start = new T[v.capacity()];
> 		_finish = _start;
> 		_endofstorage = _start + v.capacity();
> 
> 		for (size_t i = 0; i < v.size(); ++i) {
> 			*_finish = v[i];
> 			++_finish;
> 		}
> 	}*/
> 
> 	Vector(const Vector<T>& v) 
> 		:_start(nullptr)
> 		, _finish(nullptr)
> 		, _endofstorage(nullptr)
> 	{
> 		reserve(v.capacity());
> 		for (const auto& e : v) {
> 			push_back(e);
> 		}
> 	}
> 
> 	// v1 = v3
> 	/*Vector<T>& operator=(const Vector<T>& v) {
> 		if (this != &v) {
> 			delete[] _start;
> 			_start = new T[v.capacity()];
> 			memcpy(_start, v._start, sizeof(T) * v.size());
> 		}
> 
> 		return *this;
> 	}*/
> 
> 	Vector<T>& operator=(Vector<T> v) {
> 		if (this != &v) {
> 			swap(v);
> 		}
> 
> 		return *this;
> 	}
> 
> 	void swap(Vector<T>& v) {
> 		::swap(_start, v._start);
> 		::swap(_finish, v._finish);
> 		::swap(_endofstorage, v._endofstorage);
> 	}
> 
> 	~Vector() {
> 		delete[] _start;
> 		_start = _finish = _endofstorage = nullptr;
> 	}
> 
> 	void reserve(size_t n) {
> 		if (n > capacity()) {
> 			size_t sz = size();
> 			iterator tmp = new T[n];
> 			if (_start) {
> 				//memcpy(tmp, _start, sizeof(T) * sz); // 按字节拷贝
> 				// 这里不用memcpy，因为当遇到更深一层拷贝的时候，memcpy就变成了浅拷贝
> 				for (size_t i = 0; i < sz; ++i) {
> 					tmp[i] = _start[i]; // 调用的是T的 operator=，深拷贝
> 				}
> 				delete[] _start;
> 			}
> 			_start = tmp;
> 			_finish = _start + sz;
> 			_endofstorage = _start + n;
> 		}
> 	}
> 
> 	// 传一个T类型的缺省值
> 	void resize(size_t n, const T& val = T()) {
> 		if (n < size()) {
> 			_finish = _start + n;
> 		}
> 		else {
> 			if (n > capacity()) {
> 				reserve(n);
> 			}
> 			while (_finish < _start + n) {
> 				*_finish = val;
> 				++_finish;
> 			}
> 		}
> 	}
> 
> 	void push_back(const T& x) {
> 		/*if (size() == capacity()) {
> 			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
> 			reserve(newcapacity);
> 		}
> 
> 		*_finish = x;
> 		++_finish;*/
> 
> 		insert(_finish, x);
> 	}
> 
> 	void pop_back() {
> 		/*assert(_start < _finish);
> 		--_finish;*/
> 
> 		erase(_finish - 1);
> 	}
> 
> 	void insert(iterator pos, const T& x) {
> 		assert(pos <= _finish);
> 		
> 		if (_finish == _endofstorage) {
> 			size_t n = pos - _start;
> 			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
> 			reserve(newcapacity);
> 			pos = _start + n;
> 		}
> 
> 		// 如果增容，原来的pos就失效了，这里需要重新计算位置
> 		iterator end = _finish - 1;
> 		while (end >= pos) {
> 			*(end + 1) = *end;
> 			--end;
> 		}
> 
> 		*pos = x;
> 		++_finish;
> 	}
> 
> 	iterator erase(iterator pos) {
> 		assert(pos < _finish);
> 
> 		iterator it = pos;
> 		while (it < _finish) {
> 			*it = *(it + 1);
> 			++it;
> 		}
> 		--_finish;
> 
> 		return pos;
> 	}
> 
> 	size_t size() const {
> 		return _finish - _start;
> 	}
> 
> 	size_t capacity() const {
> 		return _endofstorage - _start;
> 	}
> 
> 	iterator begin() {
> 		return _start;
> 	}
> 	
> 	const_iterator begin() const {
> 		return _start;
> 	}
> 
> 	iterator end() {
> 		return _finish;
> 	}
> 
> 	const_iterator end() const {
> 		return _finish;
> 	}
> 
> 	T& operator[](size_t n) {
> 		assert(n < size());
> 
> 		return *(_start + n);
> 	}
> 
> 	const T& operator[](size_t n) const {
> 		assert(n < size());
> 
> 		return *(_start + n);
> 	}
> 
> private:
> 	iterator _start;
> 	iterator _finish;
> 	iterator _endofstorage;
> };
> ```

### 2.2 使用memcpy函数的问题

> 假设模拟实现的vector中的reserve接口中，使用memcpy进行的拷贝，以下代码会发生什么问题？
>
> ```cpp
> int main()
> {
> 	bite::vector<bite::string> v;
> 	v.push_back("1111");
> 	v.push_back("2222");
> 	v.push_back("3333");
> 	return 0;
> }
> ```
>
> 问题分析：
>
> 1. memcpy是内存的二进制格式拷贝，将一段内存空间中内容原封不动的拷贝到另外一段内存空间中
> 2. 如果拷贝的是自定义类型的元素，memcpy既高效又不会出错，但如果拷贝的是自定义类型元素，并且 自定义类型元素中涉及到资源管理时，就会出错，因为memcpy的拷贝实际是浅拷贝。
>
> **结论：如果对象中涉及到资源管理时，千万不能使用memcpy进行对象之间的拷贝，因为memcpy是浅拷贝，否则可能会引起内存泄漏甚至程序崩溃。**
