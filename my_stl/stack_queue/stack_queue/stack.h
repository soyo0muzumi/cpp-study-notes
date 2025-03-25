#pragma once

// stack queue都是适配器，可以用list和vector来转化
template<class T, class Container>
class Stack {
public:
	void push(const T& x) {
		_con.push_back(x);
	}

	void pop() {
		_con.pop_back();
	}

	size_t size() {
		return _con.size();
	}

	bool empty() {
		return _con.empty();
	}

	T& top() {
		return _con.back();
	}

private:
	Container _con;
};