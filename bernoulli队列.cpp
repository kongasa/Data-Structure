#include<cstdio>
#include<iostream>
using namespace std;
const int INF = 99999999;

struct Node {
	int data;
	Node *left, *right;
	Node(int x, Node *l = NULL, Node *r = NULL):data(x), left(l), right(r){}
};

bool strequal(char *a, char *b) {
	for (; *a != '\0' && *b != '\0'; ++a, ++b) {
		if (*a != *b) {
			return false;
		}
	}
	if (*a == '\0' && *b == '\0') { return true; }
	else { return false; }
}

Node *trees[100];

Node *merge(Node *a, Node *b) {
	Node *tmp;
	if (a->data > b->data) {
		tmp = a;
		a = b;
		b = tmp;
	}
	tmp = a->left;
	if (tmp == NULL) {
		a->left = b;
	}
	else {
		while (tmp->right != NULL) {
			tmp = tmp->right;
		}
		tmp->right = b;
	}
	return a;
}

void merge(int idx, Node *x) {
	Node *tmp = x;
	int i;
	for (i = idx; trees[i] != NULL; ++i) {
		tmp = merge(trees[i], tmp);
		trees[i] = NULL;
	}
	trees[i] = tmp;
}

void Delete(int idx) {
    Node *tmp = trees[idx]->left;
	Node *p;
	delete trees[idx];
	trees[idx] = NULL;
	int i = 0;
	while (tmp != NULL) {
		merge(i, tmp);
		p = tmp;
		tmp = tmp->right;
		p->right = NULL;
		++i;
	}
}

int min(int &idx) {
	int Min = INF;
	for (int i = 0; i < 100; ++i) {
		if (trees[i] != NULL && trees[i]->data < Min) {
			Min = trees[i]->data;
			idx = i;
		}
	}
	return Min;
}

void destruct(Node *p) {
	if (p == NULL) { return; }
	if (p->left != NULL) { destruct(p->left); }
	if (p->right != NULL) { destruct(p->right); }
	delete p;
}

int main() {
	int i;
	for (i = 0; i < 100; ++i) {
		trees[i] = NULL;
	}
	int M;
	scanf("%d", &M);
	char command[7];
	int a;
	int ans[20000];
	int count = -1;
	for (i = 0; i < M; ++i) {
		scanf("%s", command);
		if (strequal(command, "insert")) {
			scanf("%d", &a);
			Node *p = new Node(a);
			merge(0, p);
		}
		else if (strequal(command, "delete")) {
			int idx;
			min(idx);
			Delete(idx);
		}
		else if (strequal(command, "min")) {
			int Min = min(Min);
			if (Min == INF) Min = 0;
			ans[++count] = Min;
		}
	}
//	printf("%d\n", trees[0]->left->data);
//	printf("%d\n", trees[0] == NULL);
	for (i = 0; i <= count; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}