//treapÈü¸ß
#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int data;
	int idx;
	int r;
	int left, right;
	node(int x = 0, int i = 0, int l = 0, int r = 0) {
		data = x;
		idx = i;
		left = l;
		right = r;
	}
};
const int INF = 0x7fffffff;
const int N = 111111;
node treap[N];
int planes[N];
int tsize;
int seed = 101;
int n;
int root = 0;
int ans[10010];
int cnt;

void LL(int &x) {
	int tmp = treap[x].left;
	treap[x].left = treap[tmp].right;
	treap[tmp].right = x;
	x = tmp;
}

void RR(int &x) {
	int tmp = treap[x].right;
	treap[x].right = treap[tmp].left;
	treap[tmp].left = x;
	x = tmp;
}

void insert(int &p, int data, int idx) {
	if (p == 0) {
		seed = (seed << 7) + (seed >> 7);
		p = (++tsize);
		treap[p].data = data;
		treap[p].idx = idx;
		treap[p].r = seed;
	}
	else if (treap[p].data > data) {
		insert(treap[p].left, data, idx);
		if (treap[p].r > treap[treap[p].left].r) {
			LL(p);
		}
	}
	else if (treap[p].data < data) {
		insert(treap[p].right, data, idx);
		if (treap[p].r > treap[treap[p].right].r) {
			RR(p);
		}
	}
	else if (treap[p].idx > idx) {
		insert(treap[p].left, data, idx);
		if (treap[p].r > treap[treap[p].left].r) {
			LL(p);
		}
	}
	else if (treap[p].idx < idx) {
		insert(treap[p].right, data, idx);
		if (treap[p].r > treap[treap[p].right].r) {
			RR(p);
		}
	}
}

void remove(int &p, int data, int idx) {
	if (p == 0) return;
	if (treap[p].data > data) {
		remove(treap[p].left, data, idx);
	}
	else if (treap[p].data < data) {
		remove(treap[p].right, data, idx);
	}
	else if (treap[p].idx > idx) {
		remove(treap[p].left, data, idx);
	}
	else if (treap[p].idx < idx) {
		remove(treap[p].right, data, idx);
	}
	else if (treap[p].left != 0 && treap[p].right != 0) {
		int tmp = treap[p].right;
		while (treap[tmp].left != 0) {
			tmp = treap[tmp].left;
		}
		treap[p].data = treap[tmp].data;
		treap[p].idx = treap[tmp].idx;
		remove(treap[p].right, treap[tmp].data, treap[tmp].idx);
	}
	else {
		p = (treap[p].left != 0) ? treap[p].left : treap[p].right;
	}
}

void get_ans(int p, int &ans, int x, bool &flag) {
	if (p == 0) return;
	get_ans(treap[p].left, ans, x, flag);
	if (flag == true) return;

	if (treap[p].data > x) {
		ans = treap[p].idx;
		flag = true;
		return;
	}
	get_ans(treap[p].right, ans, x, flag);
}

int main() {
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &planes[i]);
		insert(root, planes[i], i);
	}
	char command[10];
	int x, y;
	bool flag;
	while (cin >> command) {
		switch (command[0]) {
		case 'f':
			scanf("%d", &x);
			flag = false;
			get_ans(root, ans[++cnt], x, flag);
			break;
		case 'd':
			scanf("%d%d", &x, &y);
			remove(root, planes[x], x);
			planes[x] -= y;
			insert(root, planes[x], x);
			break;
		}
	}
	for (i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}