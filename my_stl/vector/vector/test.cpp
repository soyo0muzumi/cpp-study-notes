#include "vector.h"

void test_Vector1() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;

	for (size_t i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void test_Vector2() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	v.insert(v.begin(), 0);
	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;

	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		if (*it % 2 == 0) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;
}

void test_Vector3() {
	Vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);

	Vector<int> v2(v1);

	for (size_t i = 0; i < v1.size(); ++i) {
		cout << v1[i] << " ";
	}
	cout << endl;

	for (size_t i = 0; i < v1.size(); ++i) {
		cout << v2[i] << " ";
	}
	cout << endl;

	Vector<int> v3;
	v3 = v1;
	for (size_t i = 0; i < v1.size(); ++i) {
		cout << v3[i] << " " ;
	}
	cout << endl;
}

void test_Vector4() {
	Vector<string> v;
	v.push_back("111");
	v.push_back("222");
	v.push_back("333");

	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;
}

int main() {
	//test_Vector1();
	//test_Vector2();
	//test_Vector3();
	test_Vector4();

	return 0;
}