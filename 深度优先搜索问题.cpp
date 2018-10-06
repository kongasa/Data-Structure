#include<cstdio>

const int INF = 0x7fffffff;
int board[6][6];
int dst_x, dst_y;
int min_cost;
int tt[6][6];                    //记录走过的,0代表没走过，1代表走过

int min(int a, int b) {
	return (a < b) ? a : b;
}

void init() {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			tt[i][j] = 0;
			min_cost = INF;
		}
	}
}

void search(int x, int y, int state, int current_cost) {
	if (x == dst_x && y == dst_y) {
		min_cost = min(min_cost, current_cost);
	}
	else if (current_cost >= min_cost) {
		return;
	}
	else {
		tt[x][y] = 1;
		if (x - 1 >= 0 && tt[x - 1][y] == 0) {
			search(x - 1, y, (state * board[x - 1][y]) % 4 + 1, current_cost + state * board[x - 1][y]);
		}
		if (y - 1 >= 0 && tt[x][y - 1] == 0) {
			search(x, y - 1, (state * board[x][y - 1]) % 4 + 1, current_cost + state * board[x][y - 1]);
		}
		if (x + 1 <= 5 && tt[x + 1][y] == 0) {
			search(x + 1, y, (state * board[x + 1][y]) % 4 + 1, current_cost + state * board[x + 1][y]);
		}
		if (y + 1 <= 5 && tt[x][y + 1] == 0) {
			search(x, y + 1, (state * board[x][y + 1]) % 4 + 1, current_cost + state * board[x][y + 1]);
		}
		tt[x][y] = 0;
	}

}

int main() {
	int n;
	scanf("%d", &n);
	int *ans = new int[n];
	int i;
	int count = 0;
	int state = 1;
	int current_cost = 0;
	int x, y;
	for (i = 1; i <= n; ++i) {
		init();
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < 6; ++k) {
				scanf("%d", &board[j][k]);
			}
		}
		scanf("%d%d%d%d", &x, &y, &dst_x, &dst_y);
		search(x, y, 1, 0);
		ans[count++] = min_cost;
	}
	for (i = 0; i < count; ++i) {
		printf("%d\n", ans[i]);
	}
	delete[] ans;
	return 0;

	

}