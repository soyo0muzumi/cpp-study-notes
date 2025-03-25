#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

//namespace xqj {
//	class string {
//	public:
//		/*string()
//			:_str(new char[1])
//		{
//			_str[0] = '\0';
//		}*/
//
//		/*string(const char* str)
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}*/
//
//		string(const char* str = "")
//			// string对象中存储指针，指针指向的数组中存储字符，字符最后必须保留\0
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//
//		// string s2(s1) 深拷贝
//		string(const string& s) 
//			:_str(new char[strlen(s._str) + 1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		~string() {
//			delete[] _str;
//			_str = nullptr;
//		}
//
//		size_t size() {
//			return strlen(_str);
//		}
//
//		char& operator[](int i) {
//			return _str[i];
//		}
//
//		string& operator=(const string& str) {
//			if (this != &str) {
//				char* tmp = new char[strlen(str._str) + 1];
//				strcpy(tmp, str._str);
//				delete[] _str;
//				_str = tmp;
//			}
//
//			return *this;
//		}
//
//	private:
//		char* _str;
//	};
//
//	void test_string1() {
//		string s1("hello");
//		string s2;
//
//		for (size_t i = 0; i < s1.size(); i++) {
//			s1[i] += 1;
//			cout << s1[i] << " ";
//		}
//		cout << endl;
//	}
//
//	void test_string2() {
//		string s1("hello");
//		string s2(s1);
//		
//
//	}
//}


namespace xqj {
	// 实现一个可以增删查改的string类
	class string {
	public:
		typedef char* iterator;

		iterator begin() {
			return _str;
		}

		iterator end() {
			return _str + _size;
		}

		string(const char* str = "") 
			:_size(strlen(str))
			,_capacity(_size)
			,_str(new char[_capacity + 1])
		{
			strcpy(_str, str);
		}

		// 深拷贝 - 传统写法
		string(const string& s) {
			_str = new char[s._capacity + 1];
			_capacity = s._capacity;
			_size = s._size;
			strcpy(_str, s._str);
		}

		// 深拷贝 - 现代写法
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}

		// 赋值 - 现代写法
		string& operator=(const string& s) {
			if (this != &s) {
				string tmp(s);
				swap(_str, tmp._str);
			}

			return *this;
		}

		string& operator=(string& s) {
			swap(_str, s._str);
			return *this;
		}

		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		size_t size() const {
			return _size;
		}

		size_t capacity() const {
			return _capacity;
		}

		char& operator[](size_t i) {
			assert(i < _size);

			return _str[i];
		}
		
		const char& operator[](size_t i) const {
			assert(i < _size);

			return _str[i];
		}
		
		string& operator=(string& s) {
			if (this != &s) {
				char* tmp = new char[s.size() + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_capacity = s._capacity;
				_size = s._size;
			}

			return *this;
		}

		const char* c_str() {
			return _str;
		}
		
		void reserve(size_t n) {
			if (n > _capacity) {
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch) {
			if (_size == _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 3 / 2;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		void append(const char* str) {
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				size_t newcapacity = _size + len;
				reserve(newcapacity);
			}

			strcpy(_str + _size, str);
			_size += len;
			_str[_size] = '\0';
		}

		string& insert(size_t pos, char ch) {
			assert(pos <= _size);
			if (_size == _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}

			int end = _size;
			while (end >= (int)pos) {
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;

			return *this;
		}

		string& insert(size_t pos, const char* str) {
			int len = strlen(str);
			if (_size + len > _capacity) {
				size_t newcapacity = _size + len;
				reserve(newcapacity);
			}

			int end = _size;
			while (end >= pos) {
				_str[end + len] = _str[end];
				--end;
			}

			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		void resize(size_t n, char ch = '\0') {
			if (n < _size) {
				_str[n] = '\0';
				_size = n;
			}
			else {
				if (n > _capacity) {
					reserve(n);
				}

				for (size_t i = _size; i < n; i++) {
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		void erase(size_t pos, size_t n = npos) {
			assert(pos < _size);
			if (pos + n > _size) {
				_str[pos] = '\0';
			}
			else {
				size_t i = pos + n;
				while (i <= _size) {
					_str[i - n] = _str[i];
					++i;
				}

				_size -= n;
			}
		}

		size_t find(char ch, size_t pos = 0) {
			for (size_t i = pos; i < _size; ++i) {
				if (_str[i] == ch) {
					return i;
				}
			}

			return npos;
		}

		size_t find(const char* str, size_t pos = 0) {
			char* p = strstr(_str, str);
			if (p == nullptr) {
				return npos;
			}
			else {
				return p - _str;
			}
		}

		// s1 += 'a'
		string& operator+=(char ch) {
			this->push_back(ch);
			return *this;
		}

		// s1 += 字符串
		string& operator+=(const char* str) {
			this->append(str);
			return *this;
		}

		bool operator<(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		bool operator<=(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret <= 0;
		}
		bool operator>(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret > 0;
		}
		bool operator>=(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret >= 0;
		}
		bool operator!=(const string& s) {
			return !(*this == s._str);
		}
		bool operator==(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}

	private:
		char* _str;
		size_t _size;       // 已经存了多少个有效字符
		size_t _capacity;   // 能存多少有效字符

		static size_t npos;
	};

	size_t string::npos = -1;

	istream& operator>>(istream& in, string& s) {
		
		while (1) {
			char ch;
			ch = in.get();
			//ch = getchar();
			if (ch == ' ' || ch == '\n') {
				break;
			}
			else {
				s += ch;
			}
		}

		return in;
	}

	ostream& operator<<(ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); i++) {
			out << s[i];
		}

		return out;
	}

	void test_string1() {
		string s1;
		string s2("hello");
		cout << s1 << endl;
		cout << s2 << endl;

		// 三种遍历方式
		for (size_t i = 0; i < s2.size(); i++) {
			cout << s2[i];
		}
		cout << endl;

		string::iterator it2 = s2.begin();
		while (it2 != s2.end()) {
			*it2 -= 1;
			cout << *it2 << " ";
			++it2;
		}
		cout << endl;

		// 范围for由迭代器支持的，也就是说这段代码最终会被编译器替换成迭代器
		for (auto ch : s2) {
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string2() {
		string s1("hello");
		s1.insert(1, 'x');
		s1.insert(1, "xyz");

		cout << s1 << endl;
	}

	void test_string3() {
		string s;
		cin >> s;
		cout << s;
	}
}