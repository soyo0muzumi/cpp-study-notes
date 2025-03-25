#pragma once

#include <vector>
#include <iostream>
using namespace std;

// 闭散列
/*
enum State {
	EMPTY,
	EXIST,
	DELETE,
};

template<class T>
struct HashData {
	T _data;
	State _state;
};

template<class K, class T, class KeyOfT>
class HashTable {
public:
	bool Insert(const T& d) {
		KeyOfT koft;

		// 负载因子 = 表中数据/表的大小 衡量哈希表满的程度
		// 表接近满，插入数据越容易冲突，冲突越多，效率越低

		// 哈希表并不是满了才增容，开放定址法中，一般负载因子到了0.7左右就开始增容
		// 负载因子越小，冲突概率越低
		if (_num * 10 / _table.size() >= 7) {
			// 1. 开两倍大小的新表
			// 2. 遍历旧表的数据，重新计算在新表中的位置
			// 3. 释放旧表
			vector<HashData> newtables;
			newtables.resize(_tables.size() * 2);
			for (size_t i = 0; i < _tables.size(); ++i) {
				if (_tables[i]._state == EXIST) {
					size_t index = koft(_tables[i]._data) % newtables.size();
					while (newtables[index]._state == EXIST) {
						++index;
						if (index == _tables.size()) {
							index = 0;
						}
					}

				}
				newtables[index] = _tables[i];

			}
		}

		_tables.swap(newtables);

		// 计算d的key在table中的位置
		size_t index = d % _tables.size();
		while (_table[index]._state == EXIST) {
			if (koft(_tables[index]._data) == koft(d)) {
				return false;
			}
			++index;
			if (index == _tables.size()) {
				index = 0;
			}
		}

		_tables[index]._data = d;
		_tables[index]._state = EXIST;
		_num++;

		return true;

	}

	HashData* Find(const K& key) {
		// 计算d的key在table中的位置
		KeyOfT koft;
		size_t index = d % _tables.size();
		while (_tables[index]._state != EMPTY) {
			if (koft(_tables[index]._data) == key) {
				if (_tables[index]._state == EXIST) {
					return &_tables[index];
				}
				else if (_tables[index]._state == DELETE) {
					return nullptr;
				}
			}

			++index;
			if (index == _tables.size()) {
				index = 0;
			}
		}
	}

	bool Erase(const K& key) {
		HashData* ret = Find(key);
		if (ret != nullptr) {
			ret->_state = DELETE;
			return true;
		}
		else {
			return false;
		}
	}
private:
	vector<HashData> _tables;
	size_t _num = 0;	// 存在多少有效数据
};

*/

// 开散列

namespace OPEN_HASH {
	template<class T>
	struct HashNode {
		T _data;
		HashNode<T>* _next;
	};

	template<class K, class T, class KeyOfT>
	class HashTable {
		typedef HashNode<T>* Node;
	public:
		bool Insert(const T& data) {
			KeyOfT koft;
			// 如果负载因子等于1，则增容，避免大量的哈希冲突
			if (_tables.size() == _num) {
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); ++i) {
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;
						size_t index = koft(cur->_data) % newtables.size();
						cur->_next = newtables[index];
						newtables[index] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}

				_tables.swap(newtables);
			}
			size_t index = koft(data) % _tables.size();
			// 先检查是否已经在表中
			Node* cur = _tables[index];
			while (cur) {
				if (koft(cur->_data) == koft(data)) {
					return false;
				}
				else {
					cur = cur->next;
				}
			}

			// 头插到挂的链表中（尾插也可以）
			Node* newNode = new Node(data);
			newNode->_next = _tables(data);
			_tables[index] = newNode;

			++_num;
			return true;
		}

		Node* Find(const K& key) {
			KeyOfT koft;
			size_t index = key % _tables.size();
			Node* cur = _tables.size();
			while (cur) {
				if (koft(cur->_data) == key) {
					return cur;
				}
				else {
					cur = cur->_next;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key) {
			KeyOfT koft;
			size_t index = key % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables.size();
			while (cur) {
				if (koft(cur->_data) == key) {
					if (prev == nullptr) {
						// 表示删除的是第一个节点
						_tables[index] = cur->_next;
					}
					else {
						prev->_next = cur->_next;
					}
					delete cur;

					return true;
				}
				else {
					prev = cur;
					cur = cur->_next;
				}
			}
			Node* pos = Find(key);
			if (pos != nullptr) {

			}
			else {
				return false;
			}
		}

	private:
		vector<Node*> _tables;
		size_t _num = 0; //记录表中存储的数据个数
	};
}