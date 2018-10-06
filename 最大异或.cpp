#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	node *zero, *one;
	node(node *z = NULL, node *o = NULL) :  zero(z), one(o) {}
};

node *root = new node;
int m[32];                       //保存每一位
const long long int INF = 2000000000000;

void trans(int x) {
	for (int i = 31; i >= 0; --i) {
		m[i] = (x & 1);
		x >>= 1;
	}
}

void build(int x) {
	trans(x);
	node *tmp = root;
	int i = 0;


	for (; i < 32; ++i) {
		switch (m[i]) {
		case 0:
			if (tmp->zero == NULL) {
				tmp->zero = new node;
			}
			tmp = tmp->zero;
			break;
		case 1:
			if (tmp->one == NULL) {
				tmp->one = new node;
			}
			tmp = tmp->one;
			break;
		}
	}
}

int cal(int x) {
	trans(x);
	node *tmp = root;
	int ans = 0;
	for (int i = 0; i < 32; ++i) {
		switch (m[i]) {
		case 0:
			if (tmp->one != NULL) {
				ans = ans * 2 + 1;
				tmp = tmp->one;
			}
			else {
				ans *= 2;
				tmp = tmp->zero;
			}
			break;
		case 1:
			if (tmp->zero != NULL) {
				ans = ans * 2 + 1;
				tmp = tmp->zero;
			}
			else {
				ans *= 2;
				tmp = tmp->one;
			}
		}
	}
	return ans;
}

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	int i;
	int tmp;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &tmp);
		build(tmp);
	}

	long long max_ans = -INF;
	for (i = 1; i <= M; ++i) {
		scanf("%d", &tmp);
		tmp = cal(tmp);
		if (tmp > max_ans) { max_ans = tmp; }
	}
	cout << max_ans << endl;
	cout << 0x7fffffff << endl;
	return 0;
}