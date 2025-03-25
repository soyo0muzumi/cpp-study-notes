## String 类

## 1. stl库中的string

### 1.1 string类的常用接口说明

> 1. **string类对象的常见构造**
>
> 	| (constractor)函数名称    | 功能说明                             |
> 	| ------------------------ | ------------------------------------ |
> 	| string()                 | **构造空的string对象，即空的字符串** |
> 	| string(const char* str)  | **用C-string来构造string类对象**     |
> 	| string(size_t n, char c) | string类对象中包含n个字符c           |
> 	| string(const string&s)   | **拷贝构造函数**                     |
>
> 	```cpp
> 	void Teststring()
> 	{
> 		string s1;                // 构造空的string类对象s1
> 		string s2("hello bit");   // 用C格式字符串构造string类对象s2
> 		string s3(s2);            // 拷贝构造s3
> 	}
> 	```
>
> 2. **string类对象的容量操作**
>
> 	| 函数名称                                                     | 功能说明                                            |
> 	| ------------------------------------------------------------ | --------------------------------------------------- |
> 	| [size](http://www.cplusplus.com/reference/string/string/size/) | **返回字符串有效字符长度**                          |
> 	| [length](http://www.cplusplus.com/reference/string/string/length/) | **返回字符串有效字符长度**                          |
> 	| [capacity](http://www.cplusplus.com/reference/string/string/capacity/) | **返回空间总大小**                                  |
> 	| [empty](http://www.cplusplus.com/reference/string/string/empty/) | **检测字符串是否为空串，是返回true，否则返回false** |
> 	| [clear](http://www.cplusplus.com/reference/string/string/clear/) | **清空有效字符**                                    |
> 	| [reserve](http://www.cplusplus.com/reference/string/string/reserve/) | **为字符串预留空间**                                |
> 	| [resize](http://www.cplusplus.com/reference/string/string/resize/) | **将有效字符的个数该成n个，多出的空间用字符c填充**  |
>
> 	注意：
>
> 	1. size()与length()方法底层实现原理完全相同，引入size()的原因是为了与其他容器的接口保持一 致，一般情况下基本都是用size()。
> 	2. clear()只是将string中有效字符清空，不改变底层空间大小。
> 	3. resize(size_t n) 与 resize(size_t n, char c)都是将字符串中有效字符个数改变到n个，不同的是当字 符个数增多时：resize(n)用0来填充多出的元素空间，resize(size_t n, char c)用字符c来填充多出的 元素空间。注意：resize在改变元素个数时，如果是将元素个数增多，可能会改变底层容量的大 小，如果是将元素个数减少，底层空间总大小不变。
> 	4. reserve(size_t res_arg=0)：为string预留空间，不改变有效元素个数，当reserve的参数小于 string的底层空间总大小时，reserver不会改变容量大小。
>
> 	```cpp
> 	void test_string4() {
> 		string s1("hello world");
> 		string s2("hello");
> 		cout << s1.size() << endl;
> 		cout << s2.size() << endl;
> 		cout << s1.length() << endl;
> 		cout << s2.length() << endl;
> 	
> 		cout << s1.capacity() << endl;
> 		s1.clear();
> 	}
> 	
> 	void test_string5() {
> 		string s;
> 	
> 		//reserve & resize
> 		s.reserve(100);
> 		s.resize(100, 'x');
> 	
> 		size_t sz = s.capacity();
> 		cout << "making s grow:\n";
> 		for (int i = 0; i < 100; i++) {
> 			s.push_back('c');
> 			if (sz != s.capacity()) {
> 				sz = s.capacity();
> 				cout << "capacity changed:" << sz << "\n";
> 			}
> 		}
> 	
> 		string s1("hello world");
> 		s.resize(5);		//小于的时候，会删空间
> 		s.resize(20, 'x');  //大于的时候，会扩空间并且把后面的改成给的字符，没给的话默认\0
> 	}
> 	```
>
> 3. **string类对象的访问及遍历操作**
>
> 	| 函数名称                                                     | 功能说明                                                     |
> 	| ------------------------------------------------------------ | ------------------------------------------------------------ |
> 	| [operator[]](http://www.cplusplus.com/reference/string/string/operator%5B%5D/) | **返回pos位置的字符，const string类对象调用**                |
> 	| [begin](http://www.cplusplus.com/reference/string/string/begin/) + [end](http://www.cplusplus.com/reference/string/string/end/) | **begin获取一个字符的迭代器 + end获取最后一个字符下一个位置的迭代器** |
> 	| [rbegin](http://www.cplusplus.com/reference/string/string/rbegin/) + [rend](http://www.cplusplus.com/reference/string/string/rend/) | **begin获取一个字符的迭代器 + end获取最后一个字符下一个位置的迭代器** |
> 	| 范围for                                                      | c++11支持                                                    |
>
> 	```cpp
> 	void test_string2() {
> 		string s1("hello");
> 		s1 += " ";
> 		s1 += "world";
> 		cout << s1 << endl;
> 	
> 		// [] + 下标
> 		// operator[]
> 		for (int i = 0; i < s1.size(); ++i) {
> 			s1[i] -= 1;
> 		}
> 	
> 		for (int i = 0; i < s1.size(); ++i) {
> 			cout << s1[i];
> 		}
> 		cout << endl;
> 	
> 		// 迭代器
> 		string::iterator it = s1.begin();
> 		while (it != s1.end()) {
> 			*it += 1;
> 			++it;
> 		}
> 	
> 		// 范围for
> 		// c++11 -> 原理：被替换成迭代器
> 		for (auto ch : s1) {
> 			cout << ch << " ";
> 		}
> 		cout << endl;
> 	}
> 	
> 	int string2int(const string& nums) {
> 		int val = 0;
> 		string::const_iterator it = nums.begin();
> 		while (it != nums.end()) {
> 			val *= 10;
> 			val += (*it - '0');
> 	
> 			it++;
> 		}
> 	
> 		return val;
> 	}
> 	
> 	// 迭代器
> 	void test_string3() {
> 		string s1("hello world");
> 		// 倒着遍历
> 		string::reverse_iterator rit = s1.rbegin();
> 		while (rit != s1.rend()) {
> 			cout << *rit;
> 			++rit;
> 		}
> 		cout << endl;
> 	
> 		string nums("12345");
> 		cout << string2int(nums) << endl;
> 	
> 		// 方向：正向、反向
> 		// 属性：普通和const
> 	}
> 	```
>
> 4. **string类对象的修改操作**
>
> 	| 函数名称                                                     | 功能说明                                                     |
> 	| ------------------------------------------------------------ | ------------------------------------------------------------ |
> 	| [push_back](http://www.cplusplus.com/reference/string/string/push_back/) | **在字符串后尾插字符**                                       |
> 	| [append](http://www.cplusplus.com/reference/string/string/append/) | **在字符串后追加一个字符串**                                 |
> 	| [operator+=](http://www.cplusplus.com/reference/string/string/operator+=/) | **在字符串后面追加字符串**                                   |
> 	| [c_str](http://www.cplusplus.com/reference/string/string/c_str/) | **返回c格式字符串**                                          |
> 	| [find](http://www.cplusplus.com/reference/string/string/find/) + [npos](http://www.cplusplus.com/reference/string/string/npos/) | **从字符串pos位置开始往后找字符c，返回该字符在字符串中的位置** |
> 	| [rfind](http://www.cplusplus.com/reference/string/string/rfind/) | **从字符串pos位置开始往前找字符c，返回该字符在字符串中的位置** |
> 	| [substr](http://www.cplusplus.com/reference/string/string/substr/) | **返回从pos位置开始的往后n个字符组成的字符串**               |
>
> 	```cpp
> 	void test_string6() {
> 		string s;
> 		/*s.push_back('x');
> 		s.append("11111");
> 	
> 		s += 'x';
> 		s += "xxxxx";
> 		cout << s << endl;*/
> 	
> 		s += '1';
> 		s += "3456";
> 		cout << s << endl;
> 		s.insert(s.begin(), '0');
> 		cout << s << endl;
> 		s.insert(2, "2");
> 		cout << s << endl;
> 	
> 		s.erase(2, 3);
> 		cout << s << endl;
> 	
> 	}
> 	
> 	void test_string7() {
> 		string s1("string.cpp");
> 		string s2("string.c");
> 		string s3("string.txt");
> 	
> 		size_t pos1 = s1.find('.');
> 		if (pos1 != string::npos) {
> 			cout << s1.substr(pos1) << endl;
> 		}
> 	
> 		size_t pos2 = s2.find('.');
> 		if (pos2 != string::npos) {
> 			cout << s2.substr(pos2) << endl;
> 		}
> 	
> 		size_t pos3 = s3.find('.');
> 		if (pos3 != string::npos) {
> 			cout << s3.substr(pos3) << endl;
> 		}
> 	
> 		// 协议  域名  资源名称
> 		string url("http://www.cplusplus.com/reference/string/string/rfind");
> 	
> 		// 分离url 协议 域名 资源名称
> 		size_t i1 = url.find(':');
> 		if (i1 != string::npos); {
> 			cout << url.substr(0, i1) << endl;
> 		}
> 	
> 		size_t i2 = url.find('/', i1 + 3);
> 		if (i2 != string::npos); {
> 			cout << url.substr(i1 + 3, i2 - (i1 + 3));
> 		}
> 	
> 		cout << url.substr(i2 + 1) << endl;
> 	}
> 	```
>
> 	注：==一般在使用string类型的时候用"operator+="==
>
> 5. **string 非类成员函数**
>
> 	| 函数名称                                                     | 功能说明                                 |
> 	| ------------------------------------------------------------ | ---------------------------------------- |
> 	| [operator+](http://www.cplusplus.com/reference/string/string/operator+/) | 尽量少用，因为传值返回，导致深拷贝效率低 |
> 	| [operator<<](http://www.cplusplus.com/reference/string/string/operator%3E%3E/) | 输出运算符重载                           |
> 	| [operator>>](http://www.cplusplus.com/reference/string/string/operator%3C%3C/) | 输入运算符重载                           |
> 	| [getline](http://www.cplusplus.com/reference/string/string/getline/) | 获取一行字符串                           |
> 	| [relational operators](http://www.cplusplus.com/reference/string/string/operators/) | 大小比较                                 |

## 2. string 类的模拟实现

### 2.1 实现一个基础的string类

> 实现string类的构造、拷贝构造、赋值运算符重载以及析构函数
>
> ```cpp
> class String {
> public:
> 	/*string()
> 		:_str(new char[1])
> 	{
> 		_str[0] = '\0';
> 	}*/
> 
> 	/*string(const char* str)
> 		:_str(new char[strlen(str) + 1])
> 	{
> 		strcpy(_str, str);
> 	}*/
> 
> 	String(const char* str = "")
> 		// string对象中存储指针，指针指向的数组中存储字符，字符最后必须保留\0
> 		:_str(new char[strlen(str) + 1])
> 	{
> 		strcpy(_str, str);
> 	}
> 
> 	// string s2(s1) 深拷贝
> 	String(const String& s)
> 		:_str(new char[strlen(s._str) + 1])
> 	{
> 		strcpy(_str, s._str);
> 	}
> 
> 	~String() {
> 		delete[] _str;
> 		_str = nullptr;
> 	}
> 
> 	size_t size() {
> 		return strlen(_str);
> 	}
> 
> 	char& operator[](int i) {
> 		return _str[i];
> 	}
> 
> 	String& operator=(const String& str) {
> 		if (this != &str) {
> 			char* tmp = new char[strlen(str._str) + 1];
> 			strcpy(tmp, str._str);
> 			delete[] _str;
> 			_str = tmp;
> 		}
> 
> 		return *this;
> 	}
> 
> private:
> 	char* _str;
> };
> ```
>
> **当我们不式定义其拷贝构造函数与赋值运算符重载时，编译器会合成默认的拷贝构造，最终导致的问题是s1、s2共用同一块内存空间，在析构函数释放时同一块空间被释放多次而引起程序崩溃**

### 2.2 浅拷贝

> **浅拷贝：也称位拷贝，编译器只是将对象中的值拷贝过来。**如果对象中**管理资源**，最后就会**导致多个对象共享同一份资源，当一个对象销毁时就会将该资源释放掉，而此时另一些对象不知道该资源已经被释放，以为还有效，所以当继续对资源进项操作时，就会发生发生了访问违规**。
>
> ![image-20250208220605983](../../../../AppData/Roaming/Typora/typora-user-images/image-20250208220605983.png)

### 2.3 深拷贝

> 如果一个类中涉及到资源的管理，其拷贝构造函数、赋值运算符重载以及析构函数必须要显式给出。一般情况都是按照深拷贝方式提供。
>
> ![image-20250208220702356](../../../../AppData/Roaming/Typora/typora-user-images/image-20250208220702356.png)

### 2.4 现代写法与传统写法

> ```cpp
> // 深拷贝 - 传统写法
> string(const string& s) {
> 	_str = new char[s._capacity + 1];
> 	strcpy(_str, s._str);
> }
> 
> // 深拷贝 - 现代写法
> string(const string& s)
> 	:_str(nullptr)
> {
> 	string tmp(s._str);
> 	swap(_str, tmp._str);
> }
> 
> // 赋值 - 现代写法
> string& operator=(const string& s) {
> 	if (this != &s) {
> 		string tmp(s);
> 		swap(_str, tmp._str);
> 	}
> 
> 	return *this;
> }
> ```

### 2.5 string类的模拟实现

> ```cpp
> namespace xqj {
> 	// 实现一个可以增删查改的string类
> 	class string {
> 	public:
> 		typedef char* iterator;
> 
> 		iterator begin() {
> 			return _str;
> 		}
> 
> 		iterator end() {
> 			return _str + _size;
> 		}
> 
> 		string(const char* str = "") 
> 			:_size(strlen(str))
> 			,_capacity(_size)
> 			,_str(new char[_capacity + 1])
> 		{
> 			strcpy(_str, str);
> 		}
> 
> 		// 深拷贝 - 传统写法
> 		string(const string& s) {
> 			_str = new char[s._capacity + 1];
> 			_capacity = s._capacity;
> 			_size = s._size;
> 			strcpy(_str, s._str);
> 		}
> 
> 		// 深拷贝 - 现代写法
> 		string(const string& s)
> 			:_str(nullptr)
> 		{
> 			string tmp(s._str);
> 			swap(_str, tmp._str);
> 		}
> 
> 		// 赋值 - 现代写法
> 		string& operator=(const string& s) {
> 			if (this != &s) {
> 				string tmp(s);
> 				swap(_str, tmp._str);
> 			}
> 
> 			return *this;
> 		}
> 
> 		string& operator=(string& s) {
> 			swap(_str, s._str);
> 			return *this;
> 		}
> 
> 		~string() {
> 			delete[] _str;
> 			_str = nullptr;
> 			_size = _capacity = 0;
> 		}
> 
> 		size_t size() const {
> 			return _size;
> 		}
> 
> 		size_t capacity() const {
> 			return _capacity;
> 		}
> 
> 		char& operator[](size_t i) {
> 			assert(i < _size);
> 
> 			return _str[i];
> 		}
> 		
> 		const char& operator[](size_t i) const {
> 			assert(i < _size);
> 
> 			return _str[i];
> 		}
> 		
> 		string& operator=(string& s) {
> 			if (this != &s) {
> 				char* tmp = new char[s.size() + 1];
> 				strcpy(tmp, s._str);
> 				delete[] _str;
> 				_str = tmp;
> 				_capacity = s._capacity;
> 				_size = s._size;
> 			}
> 
> 			return *this;
> 		}
> 
> 		const char* c_str() {
> 			return _str;
> 		}
> 		
> 		void reserve(size_t n) {
> 			if (n > _capacity) {
> 				char* tmp = new char[n + 1];
> 				strcpy(tmp, _str);
> 				delete[] _str;
> 				_str = tmp;
> 				_capacity = n;
> 			}
> 		}
> 
> 		void push_back(char ch) {
> 			if (_size == _capacity) {
> 				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 3 / 2;
> 				reserve(newcapacity);
> 			}
> 
> 			_str[_size] = ch;
> 			++_size;
> 			_str[_size] = '\0';
> 		}
> 
> 		void append(const char* str) {
> 			size_t len = strlen(str);
> 			if (_size + len > _capacity) {
> 				size_t newcapacity = _size + len;
> 				reserve(newcapacity);
> 			}
> 
> 			strcpy(_str + _size, str);
> 			_size += len;
> 			_str[_size] = '\0';
> 		}
> 
> 		string& insert(size_t pos, char ch) {
> 			assert(pos <= _size);
> 			if (_size == _capacity) {
> 				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
> 				reserve(newcapacity);
> 			}
> 
> 			int end = _size;
> 			while (end >= (int)pos) {
> 				_str[end + 1] = _str[end];
> 				--end;
> 			}
> 			_str[pos] = ch;
> 			++_size;
> 
> 			return *this;
> 		}
> 
> 		string& insert(size_t pos, const char* str) {
> 			int len = strlen(str);
> 			if (_size + len > _capacity) {
> 				size_t newcapacity = _size + len;
> 				reserve(newcapacity);
> 			}
> 
> 			int end = _size;
> 			while (end >= pos) {
> 				_str[end + len] = _str[end];
> 				--end;
> 			}
> 
> 			strncpy(_str + pos, str, len);
> 			_size += len;
> 
> 			return *this;
> 		}
> 
> 		void resize(size_t n, char ch = '\0') {
> 			if (n < _size) {
> 				_str[n] = '\0';
> 				_size = n;
> 			}
> 			else {
> 				if (n > _capacity) {
> 					reserve(n);
> 				}
> 
> 				for (size_t i = _size; i < n; i++) {
> 					_str[i] = ch;
> 				}
> 				_size = n;
> 				_str[_size] = '\0';
> 			}
> 		}
> 
> 		void erase(size_t pos, size_t n = npos) {
> 			assert(pos < _size);
> 			if (pos + n > _size) {
> 				_str[pos] = '\0';
> 			}
> 			else {
> 				size_t i = pos + n;
> 				while (i <= _size) {
> 					_str[i - n] = _str[i];
> 					++i;
> 				}
> 
> 				_size -= n;
> 			}
> 		}
> 
> 		size_t find(char ch, size_t pos = 0) {
> 			for (size_t i = pos; i < _size; ++i) {
> 				if (_str[i] == ch) {
> 					return i;
> 				}
> 			}
> 
> 			return npos;
> 		}
> 
> 		size_t find(const char* str, size_t pos = 0) {
> 			char* p = strstr(_str, str);
> 			if (p == nullptr) {
> 				return npos;
> 			}
> 			else {
> 				return p - _str;
> 			}
> 		}
> 
> 		// s1 += 'a'
> 		string& operator+=(char ch) {
> 			this->push_back(ch);
> 			return *this;
> 		}
> 
> 		// s1 += 字符串
> 		string& operator+=(const char* str) {
> 			this->append(str);
> 			return *this;
> 		}
> 
> 		bool operator<(const string& s) {
> 			int ret = strcmp(_str, s._str);
> 			return ret < 0;
> 		}
> 		bool operator<=(const string& s) {
> 			int ret = strcmp(_str, s._str);
> 			return ret <= 0;
> 		}
> 		bool operator>(const string& s) {
> 			int ret = strcmp(_str, s._str);
> 			return ret > 0;
> 		}
> 		bool operator>=(const string& s) {
> 			int ret = strcmp(_str, s._str);
> 			return ret >= 0;
> 		}
> 		bool operator!=(const string& s) {
> 			return !(*this == s._str);
> 		}
> 		bool operator==(const string& s) {
> 			int ret = strcmp(_str, s._str);
> 			return ret == 0;
> 		}
> 
> 	private:
> 		char* _str;
> 		size_t _size;       // 已经存了多少个有效字符
> 		size_t _capacity;   // 能存多少有效字符
> 
> 		static size_t npos;
> 	};
> 
> 	size_t string::npos = -1;
> 
> 	istream& operator>>(istream& in, string& s) {
> 		
> 		while (1) {
> 			char ch;
> 			ch = in.get();
> 			//ch = getchar();
> 			if (ch == ' ' || ch == '\n') {
> 				break;
> 			}
> 			else {
> 				s += ch;
> 			}
> 		}
> 
> 		return in;
> 	}
> 
> 	ostream& operator<<(ostream& out, const string& s) {
> 		for (size_t i = 0; i < s.size(); i++) {
> 			out << s[i];
> 		}
> 
> 		return out;
> 	}
> }
> ```
>
> 