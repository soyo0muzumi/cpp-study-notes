#pragma once

template<class T, class Container>
class Queue {
public:
	void push(const T& x) {
		_con.push_back(x);
	}
	void pop() {
		_con.pop_front();
	}
	size_t size() {
		return _con.size();
	}
	bool empty() {
		return _con.empty();
	}
	T& front() {
		return _con.front();
	}
	T& back() {
		return _con.back();
	}
private:
	Container _con;
};

// 仿函数/函数对象
template<class T>
struct Less {
	bool operator()(const T& x1, const T& x2) {
		return x1 < x2;
	}
};

template<class T>
struct Greater {
	bool operator()(const T& x1, const T& x2) {
		return x1 > x2;
	}
};


template<class T, class Container = vector<T>, class Compare = less<T>>
class priority_Queue {
public:
	void AdjustUp(size_t n) {
		Compare com;
		size_t child = n;
		size_t parent = (child - 1) / 2;
		while (child > 0) {
			if (com(_con[parent], _con[child])) {
				swap(_con[child], _con[parent]);
			}
			else {
				break;
			}
			child = parent;
			parent = (child - 1) / 2;
		}
	}

	void AdjustDown(size_t root) {
		Compare com;
		size_t parent = root;
		size_t child = parent * 2 + 1;
		while (child < _con.size()) {
			if (child + 1 < _con.size() && com(_con[child], _con[child + 1])) {
				child++;
			}
			if (com(_con[parent], _con[child])) {
				swap(_con[child], _con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else {
				break;
			}
		}
	}

	void push(const T& x) {
		// 默认大堆
		_con.push_back(x);
		AdjustUp(_con.size() - 1);
	}

	void pop() {
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();

		AdjustDown(0);
	}

	size_t size() {
		return _con.size();
	}

	bool empty() {
		return _con.empty();
	}

	T& top() {
		return _con.front();
	}

private:
	Container _con;
};