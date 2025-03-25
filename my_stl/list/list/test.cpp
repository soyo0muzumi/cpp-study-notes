#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

// 为什么会有list
// 补充vector的缺点存在的
// vector的缺点
// 1. 头部和中部的插入删除效率低、O(N), 因为需要挪动数据
// 2. 插入数据空间不够需要增容。增容要开辟新空间、拷贝数据、释放就空间，付出很大代价
// 优点
// 1. 支持下标的随机访问。 就支持排序、二分查找、堆算法等

// list优点
// list头部、中间插入不再需要挪动数据，效率高
// list插入数据不需要新开辟空间
// 缺点
// 不能随机访问


void print_list(const list<int>& lt) {
	// const迭代器
	list<int>::const_iterator it = lt.begin();
	while (it != lt.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_list1() {
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_front(0);

	list<int>::iterator it1 = l1.begin();
	while (it1 != l1.end()) {
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;

	print_list(l1);

	list<int> l3;
	l3.push_back(10);
	l3.push_back(20);
	l3.push_back(30);
	l3.push_back(40);

	l1 = l3;

	for (auto e : l1) {
		cout << e << " ";
	}
	cout << endl;
}

// 支持的操作接口的角度分迭代器：单向(forward_list)、双向(list)、随机(vector)
// 从使用的场景的角度分迭代器的类型：(正向迭代器、反向迭代器) + const迭代器

void test_list2() {
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_front(0);
	lt.push_front(-1);

	print_list(lt);

	lt.pop_back();
	lt.pop_front();
	print_list(lt);

}

void test_list3() {
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	
	print_list(lt);

	list<int>::iterator pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end()) {
		lt.insert(pos, 30);
		lt.erase(pos);
	}
	print_list(lt);

}

// list的迭代器失效
void test_list4() {
	list<int> lt;
	lt.push_back(3);
	lt.push_back(2);
	lt.push_back(1);
	lt.push_back(5);
	lt.push_back(4);
	lt.push_back(6);

	print_list(lt);


	list<int>::iterator it = lt.begin();
	while (it != lt.end()) {
		if (*it % 2 == 0) {
			//lt.erase(it);
			// erase过后迭代器失效
			it = lt.erase(it);
		}
		else {
			++it;
		}
	}
	print_list(lt);

}

// 迭代器失效的总结：
// 1、vector的iterator，insert、erase都会导致失效（增容）
// 2、list的迭代器，erase会失效



#include "list.h"

void print_List(const List<int>& lt) {
	List<int>::const_iterator it = lt.begin();
	while (it != lt.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_List1() {
	List<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);

	List<int>::iterator it = lt.begin();
	while (it != lt.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	print_List(lt);

}

struct Date {
	int _year = 0;
	int _month = 1;
	int _day = 1;
};

void test_List2() {
	List<Date> lt;
	lt.push_back(Date());
	lt.push_back(Date());

	List<Date>::iterator it = lt.begin();
	while (it != lt.end()) {
		// 这里原本应该是it->->_year，但是为了可读性，编译器特殊处理了一下
		cout << it->_year << " " << it->_month << " " << it->_day;
		++it;
	}

}

void test_List3() {
	List<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);
	lt1.push_back(5);
	lt1.push_back(6);

	List<int> lt2(lt1);
	for (auto e : lt2) {
		cout << e << " ";
	}
	cout << endl;
}

int main() {
	//test_list1();
	//test_list2();
	test_List3();

	return 0;
}