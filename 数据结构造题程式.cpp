#include<cstdio>
#include<iostream>
using namespace std;


int nums[60001][32];
int tree[60001][32][2];               //tree[i][j][k] = m��ʾi - lowbit(i) + 1��i������j��������λ��m��k
int ans[60001];
int tmp[32];
int tmp2[94];
int t = 0;
int n;
int cc = 1000000007;

void trans(int x, int m[32]) {
	for (int i = 31; i > 0; --i) {
		m[i] = (x & 1);
		x >>= 1;
	}
}

void b(int m[94]) {                  //ʹtmp�е��Ѿ����ҵ��������ƻ�
	int i = 93;
	for (; i >= 1; --i) {
		if (m[i] > 1) {
			m[i - 1] += m[i] / 2;
			m[i] %= 2;
		}
	}
}

int lowbit(int x) {
	return (x & (-x));
}

void update(int x, int y, int new_value) {          //��x�����ĵ�y��������λ����Ϊnew_value
	if (new_value == nums[x][y]) return;
	int dlt = new_value - nums[x][y];
	while (x <= n) {
		tree[x][y][0] -= dlt;
		tree[x][y][1] += dlt;
		x += lowbit(x);
	}
}

void update(int x, int y) {                        //�ѵ�x��Ԫ�ظ���Ϊy
	trans(y, tmp);
	int i;
	for (i = 1; i <= 31; ++i) {
		update(x, i, tmp[i]);
		nums[x][i] = tmp[i];
	}

}

int get_sum(int i, int j, int k) {          //�õ�ǰi�����Ķ����Ƶ�jλ���м���k
	int ans = 0;
	int idx = i;
	while (idx) {
		ans += tree[idx][j][k];
		idx -= lowbit(idx);
	}
	return ans;
}

int c() {                     //��tmpʮ���ƻ�
	int ans = 0;
	for (int i = 1; i <= 93; ++i) {
		ans = (ans * 2 + tmp2[i]) % cc;
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	int i;
	int j;
	int tmp1;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &tmp1);
		trans(tmp1, nums[i]);
		for (j = 1; j <= 31; ++j) {
			int idx = i;
			while (idx <= n) {
				++tree[idx][j][nums[i][j]];
				idx += lowbit(idx);
			}
		}
	}

	int q;
	scanf("%d", &q);
	int com;
	int x, y;
	int l, r;
	for (i = 1; i <= q; ++i) {
		scanf("%d", &com);
		switch (com) {
		case 0:
			scanf("%d%d", &l, &r);
			for (int k = 1; k <= 62; ++k) tmp2[k] = 0;
			for (j = 63; j <= 93; ++j) {
				tmp2[j] = (get_sum(r, j - 62, 0) - get_sum(l - 1, j - 62, 0)) * (get_sum(r, j - 62, 1) - get_sum(l - 1, j - 62, 1));
			}
			b(tmp2);
			ans[++t] = c();
			break;
		default:
			scanf("%d%d", &x, &y);
			update(x, y);
		}
	}

	for (i = 1; i <= t; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}