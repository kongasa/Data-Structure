#include<cstdio>
#include<iostream>
using namespace std;

struct Node {
	int data;
	Node *next;
	Node(int x, Node *n = NULL) :data(x), next(n) {  }
};

struct row {
	Node *head, *rear;
	row() { head = rear = NULL; }
	void push_back(int x) {
		if (head == NULL) {
			head = rear = new Node(x);
		}
		else {
			rear->next = new Node(x);
			rear = rear->next;
		}
	}
	/*~row() {
		Node *tmp;
		while (head != NULL) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}*/
};

row books[101];
char ch;

int main() {
	int n;
	scanf("%d", &n);
	int i;
	getchar();
	bool flag;
	for (i = 1; i <= n; ++i) {
		flag = false;
		while ((ch = getchar()) != '\n') {
			if (ch >= '0' && ch <= '9') {
				int tmp = ch - '0';
				while ((ch = getchar()) != ' ') {
					if (ch != '\n')
						tmp = tmp * 10 + ch - '0';
					else {
						flag = true;
						break;
					}
				}
				books[i].push_back(tmp);
				if (flag) break;
			}
		}
	}

	int x, y;
	for (i = 1; i <= n - 1; ++i) {
		scanf("%d%d", &x, &y);
	    books[y].rear->next = books[x].head;
		books[y].rear = books[x].rear;
	}
	Node *tmp = books[y].head;
	while (tmp != NULL) {
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
}