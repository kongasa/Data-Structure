#include<cstdio>
#include<iostream>
using namespace std;

int ops[4] = { -1, -2, -3, -4 };//+, -, x, /
int op[3];
int orignums[4];
int numbers[4];

int cal(int a, int b, int operation) {
	switch (operation) {
	case -1:
		return a + b;
	case -2:
		return a - b;
	case -3:
		return a * b;
	case -4:
		if (b == 0) return -1;
		else return a / b;
	}
}

bool check1() {
	int ans1, ans2, ans3;
	ans1 = cal(orignums[0], orignums[1], op[1]);
	ans2 = cal(orignums[2], orignums[3], op[2]);
	ans3 = cal(ans1, ans2, op[0]);
	if (ans3 == 24) {
		return true;
	}
	else return false;
}

bool check2() {
	int ans1, ans21, ans22, ans31, ans32, ans33, ans34;
	ans1 = cal(orignums[0], orignums[1], op[2]);
	ans21 = cal(ans1, orignums[2], op[2]);
	ans22 = cal(orignums[2], ans1, op[2]);
	ans31 = cal(ans21, orignums[3], op[0]);
	ans32 = cal(orignums[3], ans22, op[0]);
	ans33 = cal(orignums[3], ans21, op[0]);
	ans34 = cal(ans22, orignums[3], op[0]);
	if (ans31 == 24 || ans21 == 24 || ans33 == 24 || ans34 == 24) {
		return true;
	}
	else return false;
}

void permutation(int n, bool &flag) {
	if (flag == true) return;
	if (n == 3) {
		if (check1() || check2()) {
			flag = true;
		}
		return;
	}
	else {
		int tmp;
		for (int i = n; i <= 3; ++i) {
			tmp = orignums[i];
			orignums[i] = orignums[n];
			orignums[n] = tmp;
			permutation(n + 1, flag);
			orignums[n] = orignums[i];
			orignums[i] = tmp;
		}
	}
}

bool solve() {
	int i, j, k;
	bool flag;
	for (i = 0; i < 4; ++i) {
		op[0] = ops[i];
		for (j = 0; j < 4; ++j) {
			op[1] = ops[j];
			for (k = 0; k < 4; ++k) {
				op[2] = ops[k];
				flag = false;
				permutation(0, flag);
				if (flag == true) return true;
			}
		}
	}
	return false;
}

int main() {
	int a, b, c, d;
	scanf("%d%d%d%d", &orignums[0], &orignums[1], &orignums[2], &orignums[3]);
	cout << solve() << endl;
	return 0;
}