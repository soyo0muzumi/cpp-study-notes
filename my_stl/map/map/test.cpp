#include <set>
#include <map>
#include "AVLTree.h"


void test_set1() {
	set<int> s;
	s.insert(3);
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(5);

	// 排序 + 去重
	set<int>::iterator it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	auto pos = s.find(3);
	if (pos != s.end()) {
		s.erase(pos);
	}

	for (auto e : s) {
		cout << e << " ";
	}
	cout << endl;

	s.erase(10);
	for (auto e : s) {
		cout << e << " ";
	}
	cout << endl;
}

void test_map1() {
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(3, 3));
	m.insert(pair<int, int>(2, 2));

	map<int, int>::iterator it = m.begin();
	while (it != m.end()) {
		cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;
		++it;
	}

}

void test_map2() {
	string strs[] = { "watermellon", "berry", "apple","watermellon", "berry"
	,"apple" };
	map<string, int> countMap;

	//
	for (auto& str : strs) {
		map<string, int>::iterator ret = countMap.find(str);
		if (ret != countMap.end()) {
			// (*ret).second++;
			ret->second++;
		}
		else {
			countMap.insert(make_pair(str, 1));
		}
	}

	for (auto& e : countMap) {
		cout << e.first << ":" << e.second << endl;
	}

	// 更简单的方法
	// operator[] 返回second的值
	for (auto& str : strs) {
		// 1、如果水果不在map中，则[]会插入 pair<str, 0>, 返回映射对象次数的引用进行了++
		// 2、如果水果在map中，则operator[]会返回水果对应的映射对象（次数）的引用，对它++
		countMap[str]++;
	}

	
	for (auto& str : strs) {
		// 1、如果水果没在map中，则插入成功
		// 2、如果水果已经在map中，插入失败，通过返回值拿到水果所在的节点的迭代器，++次数
		pair<map<string, int>::iterator, bool> ret = countMap.insert(make_pair(str, 1));
		if (ret.second == false) {
			ret.first->second++;
		}
	}
}



//int main() {
//	test_set1();
//
//	return 0;
//}


// AVLTree 高度平衡二叉搜索树
// 1、搜索二叉树
// 2、要求数的左右子树的高度差不超过1，所有子树满足上述要求

// 为了方便实现，我们在每个节点中引入平衡因子
// 平衡因子 = 右子树的高度 - 左子树的高度

#include "MyMap.h"
#include "MySet.h"

int main() {
	// TestAVLTree();

	xqj::test_set();
	xqj::test_map();

	return 0;
}