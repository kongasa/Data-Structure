#include "stdio.h"
#include<iostream>
using namespace std;

template <class Type>
class Queue {
private:
	struct Node {
		Type data;
		Node *next;

		Node(Type d, Node *n = NULL) :data(d), next(n) {}
	};
	Node *front, *rear;
public:
	Queue() { front = rear = NULL; }
	~Queue();
	void enQueue(Type &elem);
	Type deQueue();
	Type get_head() { return front->data; }
	bool is_empty() { return front == NULL; }
};

template <class Type>
Queue<Type>::~Queue() {
	Node *p;
	while (front != NULL) {
		p = front->next;
		delete front;;
		front = p;
	}
}

template <class Type>
void Queue<Type>::enQueue(Type &x) {
	if (front == NULL)  front = rear = new Node(x);
	else {
		rear->next = new Node(x);
		rear = rear->next;
	}
}

template <class Type>
Type Queue<Type>::deQueue() {
	Node *p = front;
	front = front->next;
	if (front == NULL) rear = front;
	Type tmp = p->data;
	delete p;
	return tmp;
}

class Binary_tree {
private:
	struct Node {
		int data;
		Node *left, *right;
		Node(int n = -1, Node *l = NULL, Node *r = NULL) :data(n), left(l), right(r) {}
	};
	Node *root;
	void clear(Node *r);
	bool is_empty() { return root == NULL; }
public:
	Binary_tree();
	~Binary_tree() { clear(root); }
	void level_order();
};

void Binary_tree::clear(Node *r) {
	if (r == NULL) return;
	clear(r->left);
	clear(r->right);
	delete r;
}

void Binary_tree::level_order() {
	Queue<Node*> que;
	if (!is_empty()) que.enQueue(root);
	Node *tmp;
	while (!que.is_empty()) {
		tmp = que.deQueue();
		if (tmp->left != NULL)  que.enQueue(tmp->left);
		if (tmp->right != NULL) que.enQueue(tmp->right);
		printf("%d ", tmp->data);
	}
}

Binary_tree::Binary_tree() {
	root = NULL;
	int N, lleft, rright, self, i;
	scanf("%d", &N);
	Node **elems = new Node*[N + 1];
	for (i = 1; i < N + 1; ++i) elems[i] = new Node;

	int *posible_roots = new int[N + 1]();
	for (i = 1; i < N + 1; ++i) {
		scanf("%d %d %d", &lleft, &rright, &self);
		elems[i]->data = self;
		if (lleft) elems[i]->left = elems[lleft];
		if (rright) elems[i]->right = elems[rright];
		posible_roots[lleft] = posible_roots[rright] = 1;
	}
	for (i = 1; i < N + 1; ++i)
		if (posible_roots[i] == 0) root = elems[i];
	delete[] elems;
	delete[] posible_roots;
}

int main() {
	Binary_tree A;
	A.level_order();
	return 0;
}
