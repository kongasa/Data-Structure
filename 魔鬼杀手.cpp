//dp漂亮
#include<cstdio>

int HP[101];
int single_cost[101];
int single_damage[101];
int all_cost[101];
int all_damage[101];
int f[100001];                     //单伤>=i的最小cost
int g[100001];                     //全伤>=i的最小cost
int h[100001];                     //记录f[i]时的实际cost
const int INF = 1000000;

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	char str[31];
	int N, M;
	scanf("%d", &N);
	int i;
	int max_HP = 0;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &HP[i]);
		if (max_HP < HP[i]) max_HP = HP[i];
	}
	scanf("%d", &M);
	int tmp;
	int count1 = 0;
	int count2 = 0;
	int min_all_damage = INF, min_single_damage = INF;
	int min_all_damage_cost = INF, min_single_damage_cost = INF;
	for (i = 1; i <= M; ++i) {
		scanf("%s %d", str, &tmp);
		scanf("%s", str);
		if (str[0] == 'S') {
			single_cost[++count1] = tmp;
			scanf("%d", &single_damage[count1]);
			if (tmp < min_single_damage_cost) {
				min_single_damage = single_damage[count1];
				min_single_damage_cost = tmp;
			}
		}
		else {
			all_cost[++count2] = tmp;
			scanf("%d", &all_damage[count2]);
			if (tmp < min_all_damage_cost) {
				min_all_damage = all_damage[count2];
				min_all_damage_cost = tmp;
			}
		}
	}
//	printf("min_all_cost:%d min_all_dam:%d\n", min_all_damage_cost, min_all_damage);
	for (i = 1; i <= max_HP; ++i) {
		if (i < min_all_damage) {
			g[i] = min_all_damage_cost;
			h[i] = min_all_damage;
			continue;
		}
		g[i] = INF;
		for (int k = 1; k <= count2; ++k) {
			if (i < all_damage[k]) {
				continue;
			}
			if (g[i - all_damage[k]] + all_cost[k] < g[i]) {
				g[i] = g[i - all_damage[k]] + all_cost[k];
				h[i] = h[i - all_damage[k]] + all_damage[k];           //i下的实际damage值
			}
		}
//		printf("%d ", g[i]);
	}

	for (i = 1; i <= max_HP; ++i) {
		if (i < min_single_damage) {
			f[i] = min_single_damage_cost;
			continue;
		}
		f[i] = INF;
		for (int k = 1; k <= count1; ++k) {

			if (i < single_damage[k]) {
				continue;
			}
			if (f[i - single_damage[k]] + single_cost[k] < f[i]) {
				f[i] = f[i - single_damage[k]] + single_cost[k];
			}
		}
	}

	int ans = INF;
	int sum = 0;
	for (i = 0; i <= max_HP; ++i) {                      //对每一个可能的全伤害枚举
		sum = g[i];
//		printf("%d ", sum);
		for (int j = 1; j <= N; ++j) {
			if (HP[j] > h[i]) {
				sum += f[HP[j] - h[i]];
			}
		}
		if (sum < ans) ans = sum;
	}
	printf("%d\n", ans);
	return 0;
}