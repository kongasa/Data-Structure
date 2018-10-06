#include<iostream>
using namespace std;

/*
class Binary_tree {
	struct Node {
	private:
		Node *left, *right;
		Node(Node *l = NULL, Node *r = NULL) :left(l), right(r) {}
	}
	Node *root;
public:
	Binary_tree();

};
*/

void fill(int &pre_order_index, int mid_order_index_left, int mid_order_index_right, char pre_order[], char mid_order[], int Array[], int Array_index, int &max_index) {
	if (pre_order[pre_order_index] == '\0') return;
	if (mid_order_index_left > mid_order_index_right) return;
	int index;
	for (index = mid_order_index_left; index <= mid_order_index_right && mid_order[index] != pre_order[pre_order_index]; ++index);
	if (index <= mid_order_index_right) {
		Array[Array_index] = pre_order[pre_order_index] - 'A' + 1;
		++pre_order_index;
		if (Array_index > max_index) max_index = Array_index;
		fill(pre_order_index, mid_order_index_left, index - 1, pre_order, mid_order, Array, 2 * Array_index, max_index);
		fill(pre_order_index, index + 1, mid_order_index_right, pre_order, mid_order, Array, 2 * Array_index + 1, max_index);
	}
}

int main() {
	int max = 0, length = 0, n = 0;
	int Array[1001] = { 0 };
	char pre_order[27], mid_order[27], output;
	cin >> pre_order >> mid_order;
	for ( ; pre_order[length] != '\0'; ++length);
	fill(n, 0, length - 1, pre_order, mid_order, Array, 1, max);
	for (int i = 1; i <= max; ++i) {
		if (Array[i] == 0) cout << "NULL ";
		else cout << (output = 'A' + Array[i] - 1) << ' ';
	}
	cout << endl;
	return 0;
}