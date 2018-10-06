#include<cstdio>
#include<iostream>
using namespace std;

struct point {
	int x;
	int y;
};

int maze[101][101];
int n, m;
int num;                   //宝藏个数
point tre[6];   //宝藏坐标
int ans;
int longest;
point longestidx;    //最长宝藏坐标
bool flag[101][101];
int parent[101 * 101]; //上一个节点

point queu[101 * 101];
point *queue;
int length;          //队列长度

void enqueue(int i, int j) {
	queue[length++].x = i;
	queue[length].y = j;
}

point dequeue() {
	point tmp = queue[0];
	--length;
	++queue;
	return tmp;
}

int Max(int a, int b) {
	return a > b ? a : b;
}

int getidx(int i, int j) {
	return (i - 1) * m + j;
}

int getpos(int idx, int &i, int &j) {
	i = (idx - 1) / m + 1;
	j = (idx - 1) % m + 1;
}

void clear() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			flag[i][j] = 0;
		}
	}
}

point find(int x, int y) {
	int i;
	for (i = 1; i <= num; ++i) {
		if (tre[i].x == x && tre[i].y == y) {
			return tre[i];
		}
	}
}

void bfs(int i, int j) {
	flag[i][j] = 1;
	enqueue(i, j);
	int idx;
	int num1 = num;
	point tmp;
	while (length) {
		tmp = dequeue();
		if (tmp.x - 1 > 0 && flag[tmp.x - 1][tmp.y] == 0 && maze[tmp.x - 1][tmp.y] != -1) {
			enqueue(tmp.x - 1, tmp.y);
			flag[tmp.x - 1][tmp.y] = 1;
			if (maze[tmp.x - 1][tmp.y] == 1) {
				--num1;
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			scanf("%d", &maze[i][j]);
			if (maze[i][j] == 1) {
				++num;
				tre[num].x = i;
				tre[num].y = j;
			}
		}
	}


}