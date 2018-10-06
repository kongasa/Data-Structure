#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct tnode {
	int label;
	int cnt;
	int left, right;
	int r;
	tnode(int lab = 0, int l = 0, int r = 0) {
		label = lab;
		left = l;
		right = r;
		cnt = 0;
	}
};

int seed = 101;
const int N = 111111;
int cows[N];
int ans[N];
tnode t[N];
int bgn;
int tsize;
int num;
int root = 0;
int k;
void LL(int &x) {
	int tmp = t[x].left;
	t[x].left = t[tmp].right;
	t[tmp].right = x;
	x = tmp;
}

void RR(int &x) {
	int tmp = t[x].right;
	t[x].right = t[tmp].left;
	t[tmp].left = x;
	x = tmp;
}

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int insert(int &p, int x) {
	if (p == 0) {
		seed = (seed >> 7) + (seed << 7);
		t[++num].label = x;
		p = num;
		++tsize;
		t[p].cnt = 1;
		t[p].r = seed;
		return num;
	}
	else if (t[p].label > x) {
		int tmp = insert(t[p].left, x);
		if (t[t[p].left].r < t[p].r) {
			LL(p);
		}
		return tmp;
	}
	else if (t[p].label < x) {
		int tmp = insert(t[p].right, x);
		if (t[t[p].right].r < t[p].r) {
			RR(p);
		}
		return tmp;
	}
	else {
		++t[p].cnt;
		return p;
	}
}

void remove(int &p, int x) {
	 if (t[p].label > x) {
		remove(t[p].left, x);
	}
	else if (t[p].label < x) {
		remove(t[p].right, x);
	}
	else if (t[p].cnt > 1) {
		--t[p].cnt;
	}
	else if (t[p].left != 0 && t[p].right != 0) {
		int tmp = t[p].right;
		int tmp1 = t[tmp].left;
		if (tmp1 == 0) {
		t[p].cnt = t[tmp].cnt;
		t[p].label = t[tmp].label;
		t[p].right = t[tmp].right;
		}
		else {
		while (t[tmp1].left != 0) {
		tmp1 = t[tmp1].left;
		tmp = t[tmp].left;
		}
		t[p].cnt = t[tmp1].cnt;
		t[p].label = t[tmp1].label;
		t[tmp].left = t[tmp1].right;
		}
		--tsize;
	}
	else {
		p = (t[p].left != 0) ? t[p].left : t[p].right;
		--tsize;
	}
}

void midorder(int p) {
	if (p == 0) return;
	midorder(t[p].left);
	printf("%d ", t[p].label);
	midorder(t[p].right);
}

int main() {
	int i;
	int n;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &cows[i]);
	}
	int tmp;
	for (i = 1; i <= n; ++i) {
		tmp = insert(root, cows[i]);
		ans[i] = t[tmp].cnt;
		while (tsize > k + 1) {
			remove(root,cows[++bgn]);
		}
	}
	int a = 1;
	for (i = 1; i <= n; ++i) {
		a = Max(a, ans[i]);
	}
	printf("%d\n", a);
	return 0;
}
