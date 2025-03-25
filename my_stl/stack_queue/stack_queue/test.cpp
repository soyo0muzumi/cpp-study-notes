#include <iostream>
#include <stack>
#include <queue>
#include <list>

using namespace std;

void test_stack() {
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

}

#include "stack.h"
#include "queue.h"

void test_Stack1() {
	Stack<int, vector<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}

void test_Queue() {
	// Queue<int, vector<int>> q; 不能用vector，vector没有提供pop_front
	Queue<int, list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}


#include <functional>
void test_priority_Queue() {
	//priority_queue<int> pq; // 默认大的优先级高
	priority_Queue<int, vector<int>> pq; // 小的优先级高
	pq.push(3);
	pq.push(1);
	pq.push(6);
	pq.push(8);
	pq.push(19);

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}




int main() {
	//test_Stack1();
	//test_Queue();
	test_priority_Queue();

	return 0;
}

// 总结：
// stl中的stack和queue是通过容器适配转换出来的，不是原生实现的。 ->复用

// deque
// 支持任意位置插入删除，也支持随机访问
