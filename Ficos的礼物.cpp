#include<cstdio>

class Easy_vector {
private:
	int max_size;
	int length;
	int *data;
	void double_space();
public:
	Easy_vector() :max_size(10), length(0), data(new int[max_size]) {}
	void push_back(int x);
	~Easy_vector() { delete[] data; }
	void print();
	void sort();
	int get_length() { return length; }
};

void Easy_vector::sort() {
	int i, j, tmp;
	bool flag;
	for (i = 0; i < length - 1; ++i) {
		flag = false;
		for (j = 0; j < length - 1 - i; ++j)
			if (data[j] > data[j + 1]) {
				tmp = data[j], data[j] = data[j + 1], data[j + 1] = tmp;
				flag = true;
			}
		if (!flag) break;
	}
}

void Easy_vector::double_space() {
	max_size <<= 1;
	int *p = data;
	data = new int[max_size];
	for (int i = 0; i < length; ++i) data[i] = p[i];
	delete[] p;
}

void Easy_vector::push_back(int x) {
	if (length == max_size) double_space();
	data[length++] = x;
}

void Easy_vector::print() {
	for (int i = 0; i < length; ++i) printf("%d ", data[i]);
}

int power(int a, int b) {
	int ans = 1;
	while (b != 0) {
		if (b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

/*
int main() {
	int k, p, q;
	Easy_vector A;
	scanf("%d %d %d", &k, &p, &q);
	int x, l, r, count = 0, tmp, sum = 0;
	scanf("%d %d", &l, &r);
	for (x = l; x <= r; ++x) {
		for (tmp = x, sum = 0; tmp != 0; sum += tmp % 10, tmp /= 10);
		if (power(sum, k) * p + q == x) {
			A.push_back(x);
			++count;
		}
	}
	printf("%d\n", count);
	if (count == 0) printf("%d\n", -1);
	else { A.print(); }
}
*/

int main() {
	int k, p, q, value, l, r, ans, sum, tmp;
	Easy_vector A;
	scanf("%d %d %d %d %d", &k, &p, &q, &l, &r);
	for (value = 0; value <= 81; ++value) {
		ans = power(value, k) * p + q;
		if (l <= ans && ans <= r) {
			for (sum = 0, tmp = ans; tmp != 0; sum += tmp % 10, tmp /= 10);
			if (sum == value) A.push_back(ans);
		}
	}

	printf("%d\n", A.get_length());
	if (A.get_length() == 0) printf("%d", -1);
	else {
		A.sort();
		A.print();
	}
}