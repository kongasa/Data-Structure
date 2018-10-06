//二分高度差，枚举每一个高度差可以用bfs判定是否存在这条路径 枚举+二分+bfs
#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int i, j;
	node *next;
	node(int ii = 0, int jj = 0, node *n = NULL) { i = ii; j = jj; next = n; }
};

class Queue {
private:
	node *head, *rear;
public:
	Queue() { head = rear = NULL; }
	void enqueue(int i, int j);
	node dequeue();
	bool is_empty() { return head == NULL; }
	~Queue() {
		node *tmp;
		while (head != NULL) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
};

void Queue::enqueue(int i, int j) {
	if (head == NULL) { head = rear = new node(i, j); }
	else {
		rear->next = new node(i, j);
		rear = rear->next;
	}
}

node Queue::dequeue() {
	node ans = *head;
	node *tmp = head;
	head = head->next;
	if (head == NULL) rear = NULL;
	delete tmp;
	return ans;
}

int mount[101][101];
const int INF = 120;
int n;

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int Min(int a, int b) {
	return (a < b) ? a : b;
}

int abs(int x) {
	return (x > 0) ? x : -x;
}

bool route_exist(int low, int high) {
	Queue q;
	bool points[101][101];                                  //true代表走过了，false代表没走过            
	for (int i = 1; i <= 100; ++i) {
		for (int j = 1; j <= 100; ++j) {
			points[i][j] = false;
		}
	}
	if (mount[1][1] < low || mount[1][1] > high) return false;
	points[1][1] = true;
	q.enqueue(1, 1);
	bool flag = false;
	node tmp;
	while (!q.is_empty()) {
		tmp = q.dequeue();
		if (tmp.i == n && tmp.j == n) {
			flag = true;
			break;
		}
		int i = tmp.i, j = tmp.j;
		if (i - 1 >= 1 && points[i - 1][j] == false && low <= mount[i - 1][j] && mount[i - 1][j] <= high) {
			q.enqueue(i - 1, j);
			points[i - 1][j] = true;
		}
		if (i + 1 <= n && points[i + 1][j] == false && low <= mount[i + 1][j] && mount[i + 1][j] <= high) {
			q.enqueue(i + 1, j);
			points[i + 1][j] = true;
		}
		if (j - 1 >= 1 && points[i][j - 1] == false && low <= mount[i][j - 1] && mount[i][j - 1] <= high) {
			q.enqueue(i, j - 1);
			points[i][j - 1] = true;
		}
		if (j + 1 <= n && points[i][j + 1] == false && low <= mount[i][j + 1] && mount[i][j + 1] <= high) {
			q.enqueue(i, j + 1);
			points[i][j + 1] = true;
		}
	}
	return flag;
}

int main() {
	scanf("%d", &n);
	int i, j;
	int min_h = INF, max_h = -INF;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			scanf("%d", &mount[i][j]);
			min_h = Min(min_h, mount[i][j]);
			max_h = Max(max_h, mount[i][j]);
		}
	}
	int low = 0, high = max_h - min_h;
	int mid;
	bool flag;
	while (low != high) {
		flag = false;
		mid = (low + high) >> 1;
		for (i = min_h; i + mid <= max_h; ++i) {
			if (route_exist(i, i + mid)) {
				flag = true;
				break;
			}
		}
		if (flag == true) high = mid;
		else low = mid + 1;
	}
	if (low < abs(mount[1][1] - mount[n][n])) printf("%d\n", abs(mount[1][1] - mount[n][n]));
	else printf("%d\n", low);
	return 0;
}