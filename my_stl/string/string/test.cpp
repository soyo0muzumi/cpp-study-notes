#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

// 1. 4个默认成员函数

void test_string1() {
	string s1; //
	string s2("hello world!"); //
	string s3("hello", 2);
	string s4(s1); //
	string s5(s2, 2, 5);
	string s6(s2, 1);

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;

	s1 = s6; //
}


// 2. 遍历
void test_string2() {
	string s1("hello");
	s1 += " ";
	s1 += "world";
	cout << s1 << endl;

	// [] + 下标
	// operator[]
	for (int i = 0; i < s1.size(); ++i) {
		s1[i] -= 1;
	}

	for (int i = 0; i < s1.size(); ++i) {
		cout << s1[i];
	}
	cout << endl;

	// 迭代器
	string::iterator it = s1.begin();
	while (it != s1.end()) {
		*it += 1;
		++it;
	}

	it = s1.begin();
	while (it != s1.end()) {
		cout << *it;
		++it;
	}
	cout << endl;

	// 范围for
	// c++11 -> 原理：被替换成迭代器
	for (auto ch : s1) {
		cout << ch << " ";
	}
	cout << endl;


	// 用获取字符数组首元素地址，用c字符串的形式遍历
	const char* str = s1.c_str();
	while (*str) {
		cout << *str << " ";
	}
	cout << endl;

}

int string2int(const string& nums) {
	int val = 0;
	string::const_iterator it = nums.begin();
	while (it != nums.end()) {
		val *= 10;
		val += (*it - '0');

		it++;
	}

	return val;
}

// 迭代器
void test_string3() {
	string s1("hello world");
	// 倒着遍历
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend()) {
		cout << *rit;
		++rit;
	}
	cout << endl;

	string nums("12345");
	cout << string2int(nums) << endl;

	// 方向：正向、反向
	// 属性：普通和const
}

void test_string4() {
	string s1("hello world");
	string s2("hello");
	cout << s1.size() << endl;
	cout << s2.size() << endl;
	cout << s1.length() << endl;
	cout << s2.length() << endl;

	cout << s1.capacity() << endl;
	s1.clear();
}

void test_string5() {
	string s;

	//reserve & resize
	s.reserve(100);
	s.resize(100, 'x');

	size_t sz = s.capacity();
	cout << "making s grow:\n";
	for (int i = 0; i < 100; i++) {
		s.push_back('c');
		if (sz != s.capacity()) {
			sz = s.capacity();
			cout << "capacity changed:" << sz << "\n";
		}
	}

	string s1("hello world");
	s.resize(5);		//小于的时候，会删空间
	s.resize(20, 'x');  //大于的时候，会扩空间并且把后面的改成给的字符，没给的话默认\0
}

void test_string6() {
	string s;
	/*s.push_back('x');
	s.append("11111");

	s += 'x';
	s += "xxxxx";
	cout << s << endl;*/

	s += '1';
	s += "3456";
	cout << s << endl;
	s.insert(s.begin(), '0');
	cout << s << endl;
	s.insert(2, "2");
	cout << s << endl;

	s.erase(2, 3);
	cout << s << endl;

}

void test_string7() {
	string s1("string.cpp");
	string s2("string.c");
	string s3("string.txt");

	size_t pos1 = s1.find('.');
	if (pos1 != string::npos) {
		cout << s1.substr(pos1) << endl;
	}

	size_t pos2 = s2.find('.');
	if (pos2 != string::npos) {
		cout << s2.substr(pos2) << endl;
	}

	size_t pos3 = s3.find('.');
	if (pos3 != string::npos) {
		cout << s3.substr(pos3) << endl;
	}

	// 协议  域名  资源名称
	string url("http://www.cplusplus.com/reference/string/string/rfind");

	// 分离url 协议 域名 资源名称
	size_t i1 = url.find(':');
	if (i1 != string::npos); {
		cout << url.substr(0, i1) << endl;
	}

	size_t i2 = url.find('/', i1 + 3);
	if (i2 != string::npos); {
		cout << url.substr(i1 + 3, i2 - (i1 + 3));
	}

	cout << url.substr(i2 + 1) << endl;
}

void test_string9() {
	string s1("hello");
	string ret1 = s1 + "world";
	string ret2 = s1 += "world";
	cout << ret1 << endl;
	cout << ret2 << endl;

	string s2("abcd");
	string s3("bbcd");
	cout << (s2 < s3) << endl;

}


#include "string.h"


int main() {
	//test_string1();
	//test_string2();
	//test_string3();
	//test_string4();
	//test_string5();
	//test_string6();

	//xqj::test_string1();
	//xqj::test_string2();
	xqj::test_string3();

	return 0;
}