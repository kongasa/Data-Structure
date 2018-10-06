#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	char data;
	int x, y;
	node(char d = ' ', int xx = 0, int yy = 0) {
		data = xx;
		x = xx;
		y = yy;
	}
};

const int N = 101;
char map[N][N];
node q[2 * N * N];
int num;
node *queue;
int length;
bool f[101][101];        //标记是否走过的点
int ans;
int flag = true;
int n, m;

void enqueue(char x, int xx, int yy) {
	queue[length].data = x;
	queue[length].x = xx;
	queue[length++].y = yy;
}

node dequeue() {
	node tmp = queue[0];
	++queue;
	--length;
	return tmp;
}

void bfs(int x1, int y1, int x2, int y2) {
	f[x1][y1] = 1;
	queue = q;
	enqueue(map[x1][y1], x1, y1);
	enqueue(' ', x1, y1);
	node tmp;
	int x, y;
	while (length) {
		tmp = dequeue();
		if (tmp.data == ' ') {
			if (length == 0) {
				break;
			}
			else {
				enqueue(' ', 0, 0);
				++ans;
				continue;
			}
		}
		if (tmp.x == x2 && tmp.y == y2) {
			return;
		}
		x = tmp.x;
		y = tmp.y;
		switch (tmp.data) {
		case '.':
			if (x - 1 > 0 && f[x - 1][y] == 0 && map[x - 1][y] != '*' && map[x - 1][y] != '-') {
				enqueue(map[x - 1][y], x - 1, y);
				f[x - 1][y] = 1;
			}
			if (x + 1 <= n && f[x + 1][y] == 0 && map[x + 1][y] != '*' && map[x + 1][y] != '-') {
				enqueue(map[x + 1][y], x + 1, y);
				f[x + 1][y] = 1;
			}
			if (y - 1 > 0 && f[x][y - 1] == 0 && map[x][y - 1] != '|' && map[x][y - 1] != '*') {
				enqueue(map[x][y - 1], x, y - 1);
				f[x][y - 1] = 1;
			}
			if (y + 1 <= m && f[x][y + 1] == 0 && map[x][y + 1] != '|' && map[x][y + 1] != '*') {
				enqueue(map[x][y + 1], x, y + 1);
				f[x][y + 1] = 1;
			}
			break;
		case '|':
			if (x - 1 > 0 && f[x - 1][y] == 0 && map[x - 1][y] != '*' && map[x - 1][y] != '-') {
				enqueue(map[x - 1][y], x - 1, y);
				f[x - 1][y] = 1;
			}
			if (x + 1 <= n && f[x + 1][y] == 0 && map[x + 1][y] != '*' && map[x + 1][y] != '-') {
				enqueue(map[x + 1][y], x + 1, y);
				f[x + 1][y] = 1;
			}
			break;
		case '-':
			if (y - 1 > 0 && f[x][y - 1] == 0 && map[x][y - 1] != '|' && map[x][y - 1] != '*') {
				enqueue(map[x][y - 1], x, y - 1);
				f[x][y - 1] = 1;
			}
			if (y + 1 <= m && f[x][y + 1] == 0 && map[x][y + 1] != '|' && map[x][y + 1] != '*') {
				enqueue(map[x][y + 1], x, y + 1);
				f[x][y + 1] = 1;
			}
			break;
		}
	}
	flag = false;
}

int main() {
	int x1, y1, x2, y2;
	scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			cin >> map[i][j];
		}
	}

	bfs(x1, y1, x2, y2);
	if (flag == false) {
		printf("%d\n", -1);
	}
	else {
		printf("%d\n", ans);
	}
	return 0;
}