#include<cstdio>

struct Node {
	Node *left, *right;
	int data;
	Node(int x, Node *l = NULL, Node *r = NULL) :data(x), left(l), right(r) {  }
};
const int INF = 0x7fffffff;

Node *root = NULL;
int size = 0;
int ans[100001];
int count = 0;
int left_min = INF;
int right_min = INF;

void query(Node*, int, int&);
int Min(int, int);
void insert(Node*&, int);
void remove(Node*&, int);
void midorder(Node *p);

int main() {
	int M;
	scanf("%d", &M);
	int i;
	int command;
	int a;
	for (i = 1; i <= M; ++i) {
		scanf("%d", &command);
		switch (command) {
		case 0:
			int result;
			left_min = INF;
			right_min = INF;
			scanf("%d", &a);
			query(root, a, result);
			ans[++count] = result;
			break;
		case 1:
			scanf("%d", &a);
			insert(root, a);
			break;
		case 2:
			scanf("%d", &a);
			remove(root, a);
			break;
		}
//		midorder(root);
//		printf("midorder\n");
	}
	for (int i = 1; i <= count; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

void query(Node *p, int a, int &result) {
	if (p == NULL) {
		result = (left_min < right_min) ? left_min : right_min;
	}
	else if (p->data == a) {
		/*Node *tmp1, *tmp2;
		tmp1 = p->left;
		if (tmp1 != NULL) {
			while (tmp1->right != NULL) tmp1 = tmp1->right;
			left_min = Min(left_min, a - tmp1->data);
		}
		tmp2 = p->right;
		if (tmp2 != NULL) {
			while (tmp2->left != NULL) tmp2 = tmp2->left;
			right_min = Min(right_min, tmp2->data - a);
		}
		result = Min(left_min, right_min);*/
		result = 0;
	}
	else if (p->data > a) {
		right_min = p->data - a;
		query(p->left, a, result);
	}
	else {
		left_min = a - p->data;
		query(p->right, a, result);
	}
}

int Min(int a, int b) {
	return (a < b) ? a : b;
}

void insert(Node *&p, int x) {
	if (p == NULL) {
		p = new Node(x);
	}
	else if (p->data > x) {
		insert(p->left, x);
	}
	else {
		insert(p->right, x);
	}
}

void remove(Node *&p, int x) {
	if (p->data < x) {
		remove(p->right, x);
	}
	else if (p->data > x) {
		remove(p->left, x);
	}
	else if (p->left != NULL && p->right != NULL) {
		Node *tmp = p->right;
		while (tmp->left != NULL) tmp = tmp->left;
		p->data = tmp->data;
		remove(p->right, p->data);
	}
	else {
		Node *tmp = p;
		p = (p->left != NULL) ? p->left : p->right;
		delete tmp;
	}
}

void midorder(Node *p) {
	if (p->left != NULL) midorder(p->left);
	printf("%d ", p->data);
	if (p->right != NULL) midorder(p->right);
}