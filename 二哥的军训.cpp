#include <iostream>
using namespace std;

class Results {                          
private:                                                          //用来保存query的结果
	int max_size;
	int length;
	int *results;
	void double_space();
public:
	Results() :max_size(10), length(0), results(new int[max_size]) {  }
	~Results() { delete[] results; }
	void push_back(int i) {
		if (max_size == length) double_space();
		results[length++] = i;
	}
	void print() {
		for (int i = 0; i < length; ++i) cout << results[i] << endl;
	}
};

void Results::double_space() {
	max_size *= 2;
	int *p = results;
	results = new int[max_size];
	for (int i = 0; i < length; ++i)
		results[i] = p[i];
	delete[] p;
}

int lowbit(int x) {
	return x & (-x);
}

void inc(int s[], int x, int y, int Size) {
	for (int i = x; i <= Size; i += lowbit(i))
		s[i] += y;
}

void dec(int s[], int x, int y, int Size) {
	for (int i = x; i <= Size; i += lowbit(i))
		s[i] -= y;
}

int get_sum(int s[], int x) {
	if (x < 1) return 0;
	int sum = 0;
	while (x > 0) {
		sum += s[x];
		x -= lowbit(x);
	}
	return sum;
}

int main() {
	int N;
	cin >> N;
	int i, sum, k, x, y;
	int *s = new int[N + 1], *data = new int[N + 1];
	for (i = 1; i <= N; ++i) cin >> data[i];
	char command[6];
	
	Results res;                                             

	for (i = 1; i <= N; ++i) {
		sum = 0;
		for (k = i - lowbit(i) + 1; k <= i; ++k) sum += data[k];
		s[i] = sum;
	}

	k = 0;
	while (cin >> command) {
		if (command[0] == 'e') break;
		switch (command[0]) {
		case 'i':                                               //情报为inc x y
			cin >> x >> y;
			inc(s, x, y, N);
			break;
		case 'd':
			cin >> x >> y;
			dec(s, x, y, N);
			break;
		case 'q':
			cin >> x >> y;
			sum = get_sum(s, y) - get_sum(s, x - 1);
			res.push_back(sum);
			break;
		}
	}
	res.print();
}