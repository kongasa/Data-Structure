#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int ans[11];
int q2[5] = { 0, 3, 4, 1, 2 };

int Min(int a, int b, int c, int d) {
	int tmp = a;
	if (tmp > b) tmp = b;
	if (tmp > c) tmp = c;
	if (tmp > d) tmp = d;
	return tmp;
}

int Max(int a, int b, int c, int d) {
	int tmp = a;
	if (tmp < b) tmp = b;
	if (tmp < c) tmp = c;
	if (tmp < d) tmp = d;
	return tmp;
}

void print() {
	for (int i = 1; i <= 10; ++i) {
		printf("%c", 'A' + ans[i] - 1);
	}
	printf("\n");
}

bool check2() {
	if (ans[5] != q2[ans[2]]) return false;
	else return true;
}

bool check3() {
	int q3[5] = { 0, 3, 6, 2, 4 };
	bool flag = true;
	int tmp = -1, cnt = 0;
	for (int i = 1; i <= 4; ++i) {
		if (i != ans[3]) {
			if (tmp == -1) {
				tmp = ans[q3[i]];
				++cnt;
			}
			else if (ans[q3[i]] == tmp) ++cnt;
		}
	}
	if (tmp == ans[q3[ans[3]]] || cnt != 3) return false;
	else return true;
}

bool check4() {
	int q41[5] = { 0, 1, 2, 1, 6 };
	int q42[5] = { 0, 5, 7, 9, 10 };
	if (ans[q41[ans[4]]] != ans[q42[ans[4]]]) return false;
	else return true;
}

bool check5() {
	int q5[5] = { 0, 8, 4, 9, 7 };
	if (ans[q5[ans[5]]] != ans[5]) return false;
	else return true;
}

bool check6() {
	int q61[5] = { 0, 2, 1, 3, 5 };
	int q62[5] = { 0, 4, 6, 10, 9 };
	if (ans[8] == ans[q61[ans[6]]] && ans[8] == ans[q62[ans[6]]]) return true;
	else return false;
}

bool check7() {
	int q7[5] = { 0, 3, 2, 1, 4 };
	int cnt[5] = { 0 };
	for (int i = 1; i <= 10; ++i) {
		++cnt[ans[i]];
	}
	int minvalue = Min(cnt[1], cnt[2], cnt[3], cnt[4]);
	int idx;
	for (int i = 1; i <= 4; ++i) {
		if (cnt[i] == minvalue) idx = i;
	}
	if (q7[idx] == ans[7]) return true;
	else return false;
}

bool check8() {
	int q8[5] = { 0, 7, 5, 2, 10 };
	if (abs(ans[1] - ans[q8[ans[8]]]) != 1) return true;
	else return false;
}

bool check9() {
	int q9[5] = { 0, 6, 10, 2, 9 };
	if (ans[1] == ans[6]) {
		if (ans[q9[ans[9]]] == ans[5]) return false;
		else return true;
	}
	else {
		if (ans[q9[ans[9]]] == ans[5]) return true;
		else return false;
	}
}

bool check10() {
	int cnt[5] = { 0 };
	for (int i = 1; i <= 10; ++i) {
		++cnt[ans[i]];
	}
	int minvalue = Min(cnt[1], cnt[2], cnt[3], cnt[4]);
	int maxvalue = Max(cnt[1], cnt[2], cnt[3], cnt[4]);
	int q10[5] = { 0, 3, 2, 4, 1 };
	if (maxvalue - minvalue == q10[ans[10]]) return true;
	else return false;
}

bool check() {
	return (check2() && check3() && check4() && check5() &&
		check6() && check7() && check8() && check9() && check10());
}

void dfs(int num, bool flag) {
	if (flag == true) return;
	if (num == 10) {
		for (int i = 1; i <= 4; ++i) {
			ans[10] = i;
			if (check()) {
				flag = true;
				print();
			}
		}
	}
	else {
		for (int i = 1; i <= 4; ++i) {
			ans[num] = i;
			dfs(num + 1, flag);
		}
	}
}

int main(){
	dfs(1, false);
	return 0;
}