#pragma once
#include <iostream>

namespace xqj {
	template<class K>
	class set {
		
		struct SetKeyOfT {
			const K& operator() (const K& k) {
				return k;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}

		pair<iterator, bool> insert(const K& k) {
			return _t.Insert(k);
		}

	private:
		RBTree<K, K, SetKeyOfT> _t;
	};

	void test_set() {
		set<int> s;
		s.insert(1);
		s.insert(3);
		s.insert(50);
		s.insert(7);
		s.insert(10);

		set<int>::iterator it = s.begin();
		while (it != s.end()) {
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}

