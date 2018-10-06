#include <iostream>
using namespace std;

int lowbit(int x) {
	return x & (-x);
}

class Tree {
private:
	int *data, *s;
	long long int sum;
	int size;
	int get_sum(int i);
public:
	Tree(int N) :size(N), sum(0) { data = new int[N + 1](); s = new int[N + 1](); }
	void update(int i);
	~Tree() { delete[] data; delete[] s; }
	void print_sum() { cout << sum << endl; }
};

int Tree::get_sum(int i) {
	if (i < 1) return 0;
	int s1 = 0;
	while (i > 0) {
		s1 += s[i];
		i -= lowbit(i);
	}
	return s1;
}

void Tree::update(int i) {
	int j = size + 1 - i, k;
	data[j] = 1;
	k = j;
	while (k <= size) {
		s[k] += 1;
		k += lowbit(k);
	}
	sum += get_sum(j - 1);
}

int main() {
	int N, num;
	cin >> N;
	Tree A(N);
	for (int i = 1; i <= N; ++i) {
		cin >> num;
		A.update(num);
	}
	A.print_sum();
	return 0;
}