#include<cstdio>
#include<iostream>
using namespace std;

struct point {
	int x;
	int y;
	point(int xx = 0, int yy = 0){
		x = xx;
		y = yy;
	}
};

int maze[101][101];
int flag[101][101];
point tre[6];
int num;
int dstn[6][6];   //distance[i][j] = x表示第i个和第j个宝藏的最短距离
int length[6];         //length[i] = j表示起点和第i个点的最短距离为j
int n, m;
point orig;
point queu[101 * 101];
point *queue;
int len;         //队列长度

int Min(int a, int b) {
	return a < b ? a : b;
}

void clear() {
	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			flag[i][j] = 0;
		}
	}
}

void enqueue(point x) {
	queue[len++] = x;
}

point dequeue() {
	point tmp = queue[0];
	--len;
	++queue;
	return tmp;
}

int gettreidx(point x) {
	int i;
	for (i = 1; i <= num; ++i) {
		if (tre[i].x == x.x && tre[i].y == x.y) return i;
	}
}

void bfs(point orig, int i, bool &f, int com) { //第i个节点的bfs,com为0是节点间的bfs，为1是起点的bfs
	len = 0;
	int step = 0;
	queue = queu;
	enqueue(orig);
	enqueue(point(0, 0));
	flag[orig.x][orig.y] = 1;
	int cnt = num;
	point tmp;
	int idx;
	while (len) {
		tmp = dequeue();

		if (tmp.x == 0) {
			++step;
			if (len == 0) break;
			enqueue(point(0, 0));
			continue;
		}

		if (maze[tmp.x][tmp.y] == 1) {
			idx = gettreidx(tmp);
			--cnt;
			if (com == 0) {
				dstn[i][idx] = step;
			}
			else {
				length[idx] = step;
			}
			if (cnt == 0) {
				f = true;
				return;
			}
		}
		if (tmp.x - 1 > 0 && maze[tmp.x - 1][tmp.y] != -1 && flag[tmp.x - 1][tmp.y] == 0) {
			enqueue(point(tmp.x - 1, tmp.y));
			flag[tmp.x - 1][tmp.y] = 1;
		}
		if (tmp.x + 1 <= n && maze[tmp.x + 1][tmp.y] != -1 && flag[tmp.x + 1][tmp.y] == 0) {
			enqueue(point(tmp.x + 1, tmp.y));
			flag[tmp.x + 1][tmp.y] = 1;
		}
		if (tmp.y - 1 > 0 && maze[tmp.x][tmp.y - 1] != -1 && flag[tmp.x][tmp.y - 1] == 0) {
			enqueue(point(tmp.x, tmp.y - 1));
			flag[tmp.x][tmp.y - 1] = 1;
		}
		if (tmp.y + 1 <= m && maze[tmp.x][tmp.y + 1] != -1 && flag[tmp.x][tmp.y + 1] == 0) {
			enqueue(point(tmp.x, tmp.y + 1));
			flag[tmp.x][tmp.y + 1] = 1;
		}
	}
	if (cnt > 0) {
		f = false;
	}
}

void getans(int now, int a[], int &shortest) {
	if (now == num) {
		int route = length[a[1]];
		for (int i = 2; i <= num; ++i) {
			route += dstn[a[i - 1]][a[i]];
		}
		shortest = Min(shortest, route);
	}
	else {
		int tmp;
		for (int i = now; i <= num; ++i) {
			tmp = a[now];
			a[now] = a[i];
			a[i] = tmp;
			getans(now + 1, a, shortest);
			tmp = a[now];
			a[now] = a[i];
			a[i] = tmp;
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
				tre[++num].x = i;
				tre[num].y = j;
			}
			else if (maze[i][j] == 2) {
				orig.x = i;
				orig.y = j;
			}
		}
	}
	bool f;
	for (i = 1; i <= num; ++i) {
		clear();
		bfs(tre[i], i, f, 0);
		if (f == false) {
			printf("-1\n");
			return 0;
		}
	}
	clear();
	bfs(orig, 0, f, 1);
	int shortest = 100000000;
	int route = 0;
	int a[6] = { 0, 1, 2, 3, 4, 5 };
	getans(1, a, shortest);
	printf("%d\n", shortest);
	return 0;
}