#include"stdio.h"
#include<iostream>
using namespace std;


template <class T>
class Queue {
private:
	int max_size;
	int front, rear;
	T *data;
	void double_space();
public:
	Queue(int init_size = 10):max_size(init_size), data(new T[max_size + 1]) { front = rear = 0; }
	T dequeue();
	void enqueue(T &x);
	~Queue();
	T get_head() { return data[(front + 1) % (max_size + 1)]; }
	bool is_empty() { return front == rear; }
};

template <class T>
void Queue<T>::double_space() {
	T *p = data;
	data = new T[max_size * 2];
	for(int i = 1; i < max_size; ++i){
		data[i] = p[(front + i) % (max_size)];
	}
	front = 0;
	rear = max_size;
	max_size *= 2;
	delete[] p;
}

template <class T>
T Queue<T>::dequeue() {
	front = (front + 1) % (max_size + 1);
	return data[front];
}

template<class T>
void Queue<T>::enqueue(T &x) {
	if ((rear + 1) % (max_size + 1) == front) double_space();
	data[(rear + 1) % (max_size + 1)] = x;
	rear = (rear + 1) % (max_size + 1);
}

template<class T>
Queue<T>::~Queue() {
	delete[] data;
}

class Binary_tree {
private:
	struct Node {
		Node *left, *right;
		Node(Node *l = NULL, Node *r = NULL) : left(l), right(r) {  }
	};
	Node *root;
	void clear(Node *p);
public:
	Binary_tree();
	~Binary_tree() { clear(root); }
	bool is_CBT();
};

Binary_tree::Binary_tree() {
	int N, i, lleft, rright;
	scanf("%d", &N);
	Node **datas = new Node *[N + 1];
	for (i = 1; i < N + 1; ++i) datas[i] = new Node;
	int *posible_root = new int[N + 1]();
	for (i = 1; i < N + 1; ++i) {
		scanf("%d %d", &lleft, &rright);
		if (lleft) datas[i]->left = datas[lleft];
		if (rright) datas[i]->right = datas[rright];
		posible_root[lleft] = posible_root[rright] = 1;
	}
	for (i = 1; i < N + 1; ++i)
		if (posible_root[i] == 0) root = datas[i];
	delete[] datas;
	delete[] posible_root;
}

void Binary_tree::clear(Node *p) {
	if (p->left != NULL) clear(p->left);
	if (p->right != NULL) clear(p->right);
	delete p;
}

bool Binary_tree::is_CBT() {
	Queue<Node *> nodes;
	nodes.enqueue(root);
	Node *p;
	while (!nodes.is_empty()) {
		p = nodes.dequeue();
		if (p->right == NULL) {
			if (p->left != NULL) nodes.enqueue(p->left);
			while (!nodes.is_empty()) {
				p = nodes.dequeue();
				if (p->left != NULL || p->right != NULL) return false;
			}
			return true;
		}
		else if (p->right != NULL && p->left == NULL) return false;
		else {
			nodes.enqueue(p->left);
			nodes.enqueue(p->right);
		}
	}
}

int main() {
	Binary_tree A;
	if (A.is_CBT()) printf("Y\n");
	else printf("N\n");
}
