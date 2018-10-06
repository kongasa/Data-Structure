#include<cstdio>
#include<iostream>
using namespace std;

struct node {             //小根treap
	int data;
	int prio;
	int times;      //出现次数
	int size;           //以当前结点为根的树的结点个数
	node *left, *right;
	node(int x, int p, int s = 1, int t = 1, node *l = NULL, node *r = NULL) {
		data = x;
		prio = p;
		left = l;
		right = r;
		size = s;
		times = t;
	}
};

node *root;
int w;
int Min;
int seed = 10;
int ans[100001];
int cnt;

int Size(node *p) {
	if (p == NULL) return 0;
	else return p->size;
}

void L(node *&p) {
	node *tmp = p->left;
	p->left = tmp->right;
	tmp->right = p;
	p->size = Size(p->left) + Size(p->right) + p->times;
	tmp->size = Size(tmp->left) + Size(tmp->right) + p->times;
	p = tmp;
}

void R(node *&p) {
	node *tmp = p->right;
	p->right = tmp->left;
	tmp->left = p;
	p->size = Size(p->left) + Size(p->right) + p->times;
	tmp->size = Size(tmp->left) + Size(tmp->right) + p->times;
	p = tmp;
}

void clear(node *&p) {
	if (p == NULL) return;
	if (p->left != NULL) clear(p->left);
	if (p->right != NULL) clear(p->right);
	delete p;
	p = NULL;
}

void insert(node *&p, int x, int seed) {
	if (p == NULL) {
		p = new node(x, seed);
	}
	else if (p->data > x) {
		insert(p->left, x, seed);
		if (p->left->prio < p->prio) {
			L(p);
		}
		p->size = Size(p->left) + Size(p->right) + p->times;
	}
	else if (p->data < x) {
		insert(p->right, x, seed);
		if (p->right->prio < p->prio) {
			R(p);
		}
		p->size = Size(p->left) + Size(p->right) + p->times;
	}
	else if (p->data == x) {
		++p->size;
		++p->times;
	}
}

int del(node *&p) {
	int num = 0;
	if (p == NULL) return 0;
	if (p->data + w >= Min) {
		num = del(p->left);
		p->size -= num;
	}
	else {
		node *tmp = p;
		p = p->right;
		num += Size(tmp) - Size(p);
		clear(tmp->left);
		delete tmp;
		num += del(p);
	}
	return num;
}

void query(node *p, int k, int &ans) {     //查询第k大
////	if (p != NULL) cout << "test:" << (Size(p) == Size(p->left) + Size(p->right) + p->times) << endl;
//	if (p == NULL) return;
	if (Size(p->right) >= k) {
		query(p->right, k, ans);
	}
	else if (Size(p) - Size(p->left) < k) {
		query(p->left, k - Size(p) + Size(p->left), ans);
	}
	else {
		ans = p->data + w;
	}
}

void mid_order(node *p) {
	if (p == NULL) return;
	if (p->left != NULL) mid_order(p->left);
	printf("%d ", p->data);
	if (p->right != NULL) mid_order(p->right);
}

int main() {
	int n;
	scanf("%d%d", &n, &Min);
	char com[2];
	int k;
	int num = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%s%d", com, &k);
		switch (com[0]) {
		case 'I':
			if (k >= Min) {
				seed = (seed << 7) + (seed >> 7);
				insert(root, k - w, seed);
			}
			break;
		case 'A':
			w += k;
			break;
		case 'S':
			w -= k;
			num += del(root);
			break;
		case 'F':
			++cnt;
			if (k > Size(root)) {
				ans[cnt] = -1;
			}
			else {
				query(root, k, ans[cnt]);
			}
			break;
		}
		/*printf("mid_order:");
		mid_order(root);
		printf("\n");*/
	}
	for (int i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	printf("%d\n", num);
	clear(root);
	return 0;
}