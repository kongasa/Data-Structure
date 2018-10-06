#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int times;
	int data;
	node *left, *right;
	node (int x = 0, int t = 1, node *l = NULL, node *r = NULL):data(x), times(t), left(l), right(r){}
};

const int N = 500001;
int parent[N];
node bst[N];
int num;
node *root;
int ans[N];
int num1;

int find(int x) {
	if (parent[x] <= 0) return x;
	else return parent[x] = find(parent[x]);
}

void combine(int rootx, int rooty) {
	if (rootx == rooty) return;
	if (parent[rootx] < parent[rooty]) {
		parent[rootx] += parent[rooty];
		parent[rooty] = rootx;
	}
	else {
		parent[rooty] += parent[rootx];
		parent[rootx] = rooty;
	}
}

void insert(node *&p, int x) {
	if (p == NULL) {
		p = &bst[++num];
		p->data = x;
	}
	else if (p->data > x) {
		insert(p->left, x);
	}
	else if (p->data < x) {
		insert(p->right, x);
	}
	else {
		p->times++;
	}
}

void del(node *&p, int x){
	if (p == NULL) return;
	else if (p->data > x) {
		del(p->left, x);
	}
	else if (p->data < x) {
		del(p->right, x);
	}
	else if (p->times > 1) {
		--p->times;
	}
	else if (p->left != NULL && p->right != NULL) {
		node *tmp, *tmp1;
		tmp = p->right;
		tmp1 = tmp->left;
		if (tmp1 == NULL) {
			p->data = tmp->data;
			p->times = tmp->times;
			p->right = tmp->right;
		}
		else {
			while (tmp1->left != NULL) {
				tmp1 = tmp1->left;
				tmp = tmp->left;
			}
			p->data = tmp1->data;
			p->times = tmp1->times;
			tmp->left = tmp1->right;
		}
	}
	else {
		p = (p->left != NULL) ? p->left : p->right;
	}
}

void getp(node *p, int n, int &cnt, int &ans) {
	if (p == NULL) return;
	getp(p->right, n, cnt, ans);
	if (ans != 0) return;
	cnt += p->times;
	if (cnt >= n) {
		ans = p->data;
		return;
	}

	getp(p->left, n, cnt, ans);
}

void C(int x, int y) {
	int rootx = find(x), rooty = find(y);
	if (parent[rootx] == 0 || parent[rooty] == 0 || rootx == rooty) {
		return;
	}
	else {
		del(root, -parent[rootx]);
		del(root, -parent[rooty]);
		insert(root, -parent[rootx] - parent[rooty]);
		combine(rootx, rooty);
	}
}

void eat(int x) {
	int rootx = find(x);
	del(root, -parent[rootx]);
	parent[rootx] = 0;
}

int query(int p) {
	int cnt = 0;
	int ans = 0;
	getp(root, p, cnt, ans);
	return ans;
}

void midorder(node *p) {
	if (p == NULL) return;
	midorder(p->left);
	printf("%d ", p->data);
	midorder(p->right);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= n; ++i) {
		parent[i] = -1;
	}
	root = &bst[num++];
	root->times = n;
	root->data = 1;
	int x, y;
	char com[2];
	for (i = 1; i <= m; ++i) {
		scanf("%s", com);
		switch (com[0]) {
		case 'C':
			scanf("%d%d", &x, &y);
			C(x, y);
			break;
		case 'D':
			scanf("%d", &x);
			eat(x);
			break;
		case 'Q':
			scanf("%d", &x);
			ans[num1++] = query(x);
		}
	}
	for (i = 0; i < num1; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}