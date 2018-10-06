#include<iostream>
#include<cstdio>
using namespace std;

const int INF = 0x7fffffff / 2 - 2;

int graph[1001][1001];
int dstn[1001][1001];
int prv[1001][1001];
int vers;
int edges;

void printpath(int i, int j) {
	if (prv[i][j] == j) {
		printf("%d ", j);
	}
	else {
		printpath(i, prv[i][j]);
		printf("-- %d", j);
	}
}

int main() {
	cout << "输入结点个数:";
	cin >> vers;
	cout << "输入边数:";
	cin >> edges;
	cout << "输入：" << endl;
	int i, j;
	int a, b;
	int w;
	for (i = 1; i <= vers; ++i) {
		for (j = 1; j <= vers; ++j) {
			if (i != j) {
				dstn[i][j] = INF;
			}
			else {
				prv[i][j] = i;
			}
		}
	}
	for (i = 1; i <= edges; ++i) {
		scanf("%d%d%d", &a, &b, &w);
		graph[a][b] = w;
		dstn[a][b] = w;
		prv[a][b] = a;
	}
	int k;
	for (k = 1; k <= vers; ++k) {
		for (i = 1; i <= vers; ++i) {
			for (j = 1; j <= vers; ++j) {
				if (dstn[i][j] > dstn[i][k] + dstn[k][j]) {
					prv[i][j] = prv[k][j];
					dstn[i][j] = dstn[i][k] + dstn[k][j];
				}
			}
		}
	}

	for (i = 1; i <= vers; ++i) {
		for (j = 1; j <= vers; ++j) {
			if (dstn[i][j] != INF && i != j) {
				printf("%d to %d:", i, j);
				printpath(i, j);
				cout << endl;
			}
		}
	}
	/*for (i = 1; i <= vers; ++i) {
		cout << endl;
		for (j = 1; j <= vers; ++j) {
			cout << prv[i][j] << '\t';
		}
	}*/
	return 0;
}