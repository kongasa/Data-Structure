#include<cstdio>

struct node {
	int x, y;
	int z;
	node *next;
	node (int xx, int yy, int zz = 0, node *n = NULL):x(xx), y(yy), z(zz), next(n){}
};

int row[100000];
int col[100000];
node *Hash[997][997];
node *rear[997][997];
int ans[20001];
int count;

int hash(int x) {
	return x % 997;
}

int main() {
	int n, m;
	scanf("%d", &n);
	int i;
	int x, y, z;
	for (i = 1; i <= n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		int xx = hash(x), yy = hash(y);
		if (Hash[xx][yy] != NULL) {
			rear[xx][yy]->next = new node(x, y, z);
			rear[xx][yy] = rear[xx][yy]->next;
		}
		else {
			Hash[xx][yy] = new node(x, y, z);
			rear[xx][yy] = Hash[xx][yy];
		}
		row[x] = x;
		col[y] = y;
	}

	scanf("%d", &m);
	int com;
	int tmp;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &com, &x, &y);
		switch (com) {
		case 0:
			tmp = row[x];
			row[x] = row[y];
			row[y] = tmp;
			break;
		case 1:
			tmp = col[x];
			col[x] = col[y];
			col[y] = tmp;
			break;
		case 2:
			node *tmp1 = Hash[hash(row[x])][hash(col[y])];
			bool flag = false;
			while (tmp1 != NULL) {
				if (tmp1->x == row[x] && tmp1->y == col[y]) {
					ans[++count] = tmp1->z;
					flag = true;
					break;
				}
				tmp1 = tmp1->next;
			}
			if (flag == false) {
				ans[++count] = 0;
			}
			break;
		}
	}
	for (i = 1; i <= count; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}