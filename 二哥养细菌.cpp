#include <cstdio>
#include<iostream>
using namespace std;
struct pos {
	int i, j, distance;
	pos(int ii = 0, int jj = 0) :i(ii), j(jj) {  }
};

template <class T>
class Queue {
private:
	struct Node {
		Node *next;
		T data;
		Node(T x, Node *n = NULL) : next(n), data(x) {  }
	};
	Node *front, *rear;
public:
	Queue() { front = rear = NULL; }
	~Queue();
	bool is_empty() { return front == NULL; }
	T dequeue();
	void enqueue(T x);
};

template <class T>
Queue<T>::~Queue() {
	Node *p;
	while (front != NULL) {
		p = front;
		front = front->next;
		delete p;
	}
}

template <class T>
T Queue<T>::dequeue() {
	Node *p = front;
	front = front->next;
	if (front == NULL) rear = NULL;
	T tmp = p->data;
	delete p;
	return tmp;
}

template <class T>
void Queue<T>::enqueue(T x) {
	if (front == NULL) front = rear = new Node(x);
	else {
		rear->next = new Node(x);
		rear = rear->next;
	}
}

int main() {
	int N, i, j, count = 0;
	scanf("%d", &N);
	Queue<pos *> next_round;
	int **grids = new int *[N];
	for (i = 0; i < N; ++i)
		grids[i] = new int[N];
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j) {
			scanf("%d", &grids[i][j]);
			if (grids[i][j] == 1) next_round.enqueue(new pos(i, j));
		}
	
	next_round.enqueue(NULL);
	pos *tmp;
	while (true) {
		tmp = next_round.dequeue();
		if (tmp == NULL) {
			if (next_round.is_empty()) break;
			else { ++count; next_round.enqueue(NULL); continue; }
		}
		if (tmp->i - 1 >= 0 && grids[tmp->i - 1][tmp->j] == 0) {
			next_round.enqueue(new pos(tmp->i - 1, tmp->j));
			grids[tmp->i - 1][tmp->j] = 1;
		}
		if (tmp->j - 1 >= 0 && grids[tmp->i][tmp->j - 1] == 0) {
			next_round.enqueue(new pos(tmp->i, tmp->j - 1));
			grids[tmp->i][tmp->j - 1] = 1;
		}
		if (tmp->i + 1 != N && grids[tmp->i + 1][tmp->j] == 0) {
			next_round.enqueue(new pos(tmp->i + 1, tmp->j));
			grids[tmp->i + 1][tmp->j] = 1;
		}
		if (tmp->j + 1 != N && grids[tmp->i][tmp->j + 1] == 0) {
			next_round.enqueue(new pos(tmp->i, tmp->j + 1));
			grids[tmp->i][tmp->j + 1] = 1;
		}
		delete tmp;
	}
	printf("%d", count);
}