#pragma once
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

template<class T>
class Vector {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{}

	// v2(v1)
	/*Vector(const Vector<T>& v) {
		_start = new T[v.capacity()];
		_finish = _start;
		_endofstorage = _start + v.capacity();

		for (size_t i = 0; i < v.size(); ++i) {
			*_finish = v[i];
			++_finish;
		}
	}*/

	Vector(const Vector<T>& v) 
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		reserve(v.capacity());
		for (const auto& e : v) {
			push_back(e);
		}
	}

	// v1 = v3
	/*Vector<T>& operator=(const Vector<T>& v) {
		if (this != &v) {
			delete[] _start;
			_start = new T[v.capacity()];
			memcpy(_start, v._start, sizeof(T) * v.size());
		}

		return *this;
	}*/

	Vector<T>& operator=(Vector<T> v) {
		if (this != &v) {
			swap(v);
		}

		return *this;
	}

	void swap(Vector<T>& v) {
		::swap(_start, v._start);
		::swap(_finish, v._finish);
		::swap(_endofstorage, v._endofstorage);
	}

	~Vector() {
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}

	void reserve(size_t n) {
		if (n > capacity()) {
			size_t sz = size();
			iterator tmp = new T[n];
			if (_start) {
				//memcpy(tmp, _start, sizeof(T) * sz); // 按字节拷贝
				// 这里不用memcpy，因为当遇到更深一层拷贝的时候，memcpy就变成了浅拷贝
				for (size_t i = 0; i < sz; ++i) {
					tmp[i] = _start[i]; // 调用的是T的 operator=，深拷贝
				}
				delete[] _start;
			}
			_start = tmp;
			_finish = _start + sz;
			_endofstorage = _start + n;
		}
	}

	// 传一个T类型的缺省值
	void resize(size_t n, const T& val = T()) {
		if (n < size()) {
			_finish = _start + n;
		}
		else {
			if (n > capacity()) {
				reserve(n);
			}
			while (_finish < _start + n) {
				*_finish = val;
				++_finish;
			}
		}
	}

	void push_back(const T& x) {
		/*if (size() == capacity()) {
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);
		}

		*_finish = x;
		++_finish;*/

		insert(_finish, x);
	}

	void pop_back() {
		/*assert(_start < _finish);
		--_finish;*/

		erase(_finish - 1);
	}

	void insert(iterator pos, const T& x) {
		assert(pos <= _finish);
		
		if (_finish == _endofstorage) {
			size_t n = pos - _start;
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);
			pos = _start + n;
		}

		// 如果增容，原来的pos就失效了，这里需要重新计算位置
		iterator end = _finish - 1;
		while (end >= pos) {
			*(end + 1) = *end;
			--end;
		}

		*pos = x;
		++_finish;
	}

	iterator erase(iterator pos) {
		assert(pos < _finish);

		iterator it = pos;
		while (it < _finish) {
			*it = *(it + 1);
			++it;
		}
		--_finish;

		return pos;
	}

	size_t size() const {
		return _finish - _start;
	}

	size_t capacity() const {
		return _endofstorage - _start;
	}

	iterator begin() {
		return _start;
	}
	
	const_iterator begin() const {
		return _start;
	}

	iterator end() {
		return _finish;
	}

	const_iterator end() const {
		return _finish;
	}

	T& operator[](size_t n) {
		assert(n < size());

		return *(_start + n);
	}

	const T& operator[](size_t n) const {
		assert(n < size());

		return *(_start + n);
	}

private:
	iterator _start;
	iterator _finish;
	iterator _endofstorage;
};
