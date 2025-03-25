#include "BSTree.hpp"

void Test_BSTree() {
	int a[] = { 5,1,3,4,2,7,8,2,6,0,9 };
	BSTree<int> bt;

	for (auto e : a) {
		bt.Insert(e);
	}

	bt.InOrder();

	bt.Erase(5);
	bt.Erase(1);
	bt.InOrder();

	bt.Erase(2);
	bt.InOrder();
}


int main() {
	Test_BSTree();

	return 0;
}