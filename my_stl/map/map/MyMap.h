#pragma once

#include "RBTree.h"

namespace xqj {
	template<class K, class V>
	class map {

		// ·Âº¯Êı
		struct MapKeyOfT {
			const K& operator() (const pair<K, V>& kv) {
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _t.Insert(kv);
		}

		V& operator[](const K& key) {
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};

	void test_map() {
		map<int, int> m;
		m.insert(make_pair(1, 1));
		m.insert(make_pair(3, 1));
		m.insert(make_pair(7, 1));
		m.insert(make_pair(50, 1));
		m.insert(make_pair(20, 1));

		map<int, int>::iterator it = m.begin();
		while (it != m.end()) {
			cout << (*it).first << " :" << (*it).second << endl;
			++it;
		}
	}
}