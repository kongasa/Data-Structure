//用斜堆
#include<cstdio>

struct Node {
	int data;
	Node *left, *right;
	Node(int x, Node *l = NULL, Node *r = NULL):data(x), left(l), right(r){}
};

Node *trees[300000];
int ans[300000];

Node *merge(Node *b, Node *a) {                  //归并：b归并入a
	if (a == NULL) {
		a = b;
		return a;
	}
	if (b == NULL) {
		return a;
	}
	Node *tmp;
	if (a->data > b->data) {
		tmp = a;
		a = b;
		b = tmp;
	}
	a->right = merge(b, a->right);
	tmp = a->left;
	a->left = a->right;
	a->right = tmp;
	return a;
}

void destruct(Node *p) {
	if (p == NULL) {
		return;
	}
	if (p->left != NULL) {
		destruct(p->left);
	}
	if (p->right != NULL) {
		destruct(p->right);
	}
	delete p;
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int i;
	int m;
	for (i = 0; i < N; ++i) {
		scanf("%d", &m);
		trees[i] = new Node(m);
	}
	int count = -1;
	int command;
	int a, b;
	Node *tmp;
	for (i = 0; i < M; ++i) {
		scanf("%d", &command);
		switch (command) {
		case 0:
			scanf("%d %d", &a, &b);
			if (trees[a] == NULL) {
				trees[a] = trees[b];
			}
			else {
				trees[a] = merge(trees[b], trees[a]);
			}
			trees[b] = NULL;
			break;
		case 1:
			scanf("%d", &a);
			if (trees[a] == NULL) {
				ans[++count] = -1;
			}
			else {
				int k = trees[a]->data;
				ans[++count] = k;
				trees[a]->right = merge(trees[a]->left, trees[a]->right);
				tmp = trees[a];
				trees[a] = tmp->right;
				delete tmp;
			}
			break;
		case 2:
			scanf("%d %d", &a, &b);
			tmp = new Node(b);
			trees[a] = merge(tmp, trees[a]);
			break;
		}
	}
	for (i = 0; i <= count; ++i) {
		printf("%d\n", ans[i]);
	}
	for (i = 0; i < N; ++i) {
		destruct(trees[i]);
	}
	return 0;
}