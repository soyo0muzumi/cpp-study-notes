#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "HashTable.h"

using namespace std;

void test_unordered_map_set() {
	unordered_set<int> us;
	us.insert(1);
	us.insert(5);
	us.insert(4);
	us.insert(7);
	us.insert(3);
	us.insert(2);
	us.insert(2);

	// 去重，不排序(set 去重 + 排序)
	for (auto e : us) {
		cout << e << " ";
	}
	cout << endl;

	unordered_map<string, string> dict;

}

// 哈希概念
// 哈希是一种映射的对应关系

// 1. 直接定址法
// 2. 除留余数法

// 哈希冲突
// 两个不同值的映射到了同一个位置
// 如何解决？
// 1. 开放定址法（闭散列）
//   (1. 线性探测（挨着往后找，直到找到空位置）
//   (2. 二次探测（按i^2, 跳跃着往后找，直到找到空位置）
// 2. 拉链法/哈希桶（开散列）
//


int main() {
	test_unordered_map_set();

	return 0;
}