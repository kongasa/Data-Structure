#include<cstdio>
#include<iostream>
using namespace std;

struct candy {
	candy *parent;
	int size;
	bool deleted;               //是否被删除
	candy(int s = 1, bool flag = false, candy *p = NULL):size(s), deleted(flag), parent(p){}
};

struct tnode {
	int times;
	int data;
	tnode *left, *right;
	tnode(int x = -1, int t = 1, tnode *l = NULL, tnode *r = NULL):times(t), data(x), left(l), right(r){}
};

const int N = 500001;
int n, m;
candy orig[N];
candy box[N + 10];
int length;           //新建box数目

tnode tree[N];               //bst的node
tnode *root = &tree[0];               //bst的根
int num = 1;
int ans[N];
int cnt;

void insert(tnode *&p, int x) {
	if (p == NULL) {
		p = &tree[num++];
		p->data = x;
//		p->times = 1;
	}
	else if (p->data < x) {
		insert(p->right, x);
	}
	else if (p->data > x) {
		insert(p->left, x);
	}
	else {
		++p->times;
	}
}

void remove(tnode *&p, int x) {
	if (p == NULL) return;
	else if (p->data > x) {
		remove(p->left, x);
	}
	else if (p->data < x) {
		remove(p->right, x);
	}
	else if (p->times > 1) {
		--p->times;
	}
	else if (p->left != NULL && p->right != NULL) {
		tnode *tmp = p->right;
		tnode *tmp1 = tmp->left;
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

void combine(int x, int y) {
	candy *tmpx = &orig[x];
	candy *tmpy = &orig[y];
	while (tmpx->parent != NULL) {
		tmpx = tmpx->parent;
	}
	while (tmpy->parent != NULL) {
		tmpy = tmpy->parent;
	}
	if (!(tmpx == tmpy || tmpx->deleted == true || tmpy->deleted == true)) {
		tmpx->parent = tmpy->parent = &box[length++];
		tmpx->parent->size = tmpx->size + tmpy->size;
		remove(root, tmpx->size);
		remove(root, tmpy->size);
		insert(root, tmpx->parent->size);
	}
}

void del(int x) {
	candy *tmp = &orig[x];
	while (tmp->parent != NULL) {
		tmp = tmp->parent;
	}
	if (tmp->deleted != true) {
		tmp->deleted = true;
		remove(root, tmp->size);
	}
}

void query(tnode *p, int &ans, int x, int &cnt) {
	if (p == NULL) return;
	query(p->right, ans, x, cnt);
	if (ans != 0) return;

	cnt += p->times;
	if (cnt >= x) {
		ans = p->data;
		return;
	}
	query(p->left, ans, x, cnt);
}

int main() {
	scanf("%d%d", &n, &m);
	root->times = n;
	root->data = 1;
	int i;
	int x, y;
	char com[2];
	for (i = 1; i <= m; ++i) {
		scanf("%s", com);
		switch (com[0]) {
		case 'C':
			scanf("%d%d", &x, &y);
			combine(x, y);
			break;
		case 'D':
			scanf("%d", &x);
			del(x);
			break;
		case 'Q':
			scanf("%d", &x);
			int m = 0;
			query(root, ans[++cnt], x, m);
		}
	}
	for (i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}