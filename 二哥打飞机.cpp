#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int INF = 0x7fffffff;

struct node {
	int data;
	int idx;
	node *left, *right;
	node *parent;
	node (int x, int i, node *p = NULL, node *l = NULL, node *r = NULL):data(x), idx(i), parent(p), left(l), right(r){}
};

node *root;

int Min(int a, int b) {
	return (a < b) ? a : b;
}


void insert(node *&p, int x, int idx, node *father) {
	if (p == NULL) p = new node(x, idx, father);
	else if (p->data > x) {
		insert(p->left, x, idx, p);
	}
	else if (p->data < x) {
		insert(p->right, x, idx, p);
	}
	else if (p->idx > idx) {
		insert(p->left, x, idx, p);
	}
	else if (p->idx < idx) {
		insert(p->right, x, idx, p);
	}
}

void remove(node *&p, int x, int idx, node *father) {
	if (p == NULL) return;
	if (p->data < x) {
		remove(p->right, x, idx, p);
	}
	else if (p->data > x) {
		remove(p->left, x, idx, p);
	}
	else if (p->idx < idx) {
		remove(p->right, x, idx, p);
	}
	else if (p->idx > idx) {
		remove(p->left, x, idx, p);
	}
	else if (p->left != NULL && p->right != NULL) {
		node *tmp = p->right;
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}
		p->data = tmp->data;
		p->idx = tmp->idx;
		remove(p->right, tmp->data, tmp->idx, p);
	}
	else {
		node *tmp = p;
		p = (p->left != NULL) ? p->left : p->right;
		if (p != NULL) p->parent = father;
		delete tmp;
	}
}

int get_higher(node *p) {              //保证p->data == x
	if (p == NULL) return INF;
	int tmp = p->data;
	if (p->right != NULL) {
		node *t = p->right;
		while (t->left != NULL) {
			t = t->left;
		}
		if (t->data == p->data) {
			return get_higher(t);
		}
		else {
			return t->idx;
		}
	}
	else {
		node *tmp = p, *tmp1 = tmp->parent;
		while (tmp1 != NULL && tmp1->right != tmp) {
			tmp1 = tmp1->parent;
			tmp = tmp->parent;
		}
		if (tmp1 == NULL) return INF;
		else {
			if (tmp1->data == p->data) {
				return get_higher(tmp1);
			}
			else {
				return tmp1->idx;
			}
		}
	}
}

int get_ans(node *p, int &ans, int x) {       //return 高度
	if (p == NULL) {
		return INF;
	}
	else if (p->data < x) {
		get_ans(p->right, ans, x);
	}
	else if (p->data > x){
		if (p->left == NULL) {
			ans = p->idx; return p->data;
		}
		else {
			int i = get_ans(p->left, ans, x);
			if (i > p->data) {
				ans = p->idx;
				return p->data;
			}
			else if (i == p->data) {
				if (p->idx < ans) {
					ans = p->idx;
					return p->data;
				}
				else return i;
			}
			else {
				return i;
			}
		}
	}
	else {
		ans = get_higher(p);
	}
}

int planes[100001];
int ans[10001];
int cnt = 0;

int main() {
	int n;
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &planes[i]);
		insert(root, planes[i], i, NULL);
	}
	char command[10];
	int x, y;

	while (cin >> command) {
		switch (command[0]) {
		case 'f':
			scanf("%d", &x);
			ans[++cnt] = INF;
			get_ans(root, ans[cnt], x);
			break;
		case 'd':
			scanf("%d%d", &x, &y);
			remove(root, planes[x], x, NULL);
			planes[x] -= y;
			insert(root, planes[x], x, NULL);
			break;
		}
	}
	for (i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}