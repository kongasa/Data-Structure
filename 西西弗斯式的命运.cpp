#include<cstdio>

int main() {
	int M, T, U, F, D;
	scanf("%d%d%d%d%d", &M, &T, &U, &F, &D);
	getchar();
	int i;
	int farthest;
	char ch;
	int time = 0;
	int new_time;
	bool flag = false;
	for (i = 1; i <= T; ++i) {
		ch = getchar();
		getchar();
		if (flag == false) {
			switch (ch) {
			case 'u':case 'd':
				new_time = time + U + D;
				break;
			case 'f':
				new_time = time + F + F;
			}
			if (new_time > M) {
					flag = true;
					farthest = i - 1;
			}
			else {
				time = new_time;
			}
		}
	}
	printf("%d\n", farthest);
	return 0;
}