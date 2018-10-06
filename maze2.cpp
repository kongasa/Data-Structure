#include<cstdio>
#include<iostream>
using namespace std;

struct vers {
	int idx;
	vers *next;
	vers(int x = 0, vers* n = NULL):idx(x), next(n){}
};

const int N = 1001;
int n; 

int nums[N];                                //nums[i] = j表示前i层有j个节点
int parent[N * (N + 1) / 2 + 1];             //不相交集
vers maze[N * (N + 1) / 2 + 1];            //节点
vers edges[4 * N * (N + 1)];               //边
int numedges;

int route[N * N];//用于压缩路径

int queu[4 * N * (N + 1)];
int *queue = queu;
bool flag[N * (N + 1) + 1];
int length;
int ans[N * (N + 1) + 1];

void enqueue(int x) {
	queue[length++] = x;
}

int dequeue() {
	int tmp = queue[0];
	++queue;
	--length;
	return tmp;
}

int find(int a) {
	int num = 0;
	int root = a;
	while (parent[root] > 0) {
		route[num++] = root;
		root = parent[root];
	}
	int i;
	for (i = 0; i < num; ++i) {
		parent[route[i]] = root;
	}
	return root;
}

void Union(int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	if (root1 == root2) return;
	if (parent[root1] < parent[root2]) {
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
	else {
		parent[root2] += parent[root1];
		parent[root1] = root2;
	}
}

int getrow(int p) {
	int left = 1, right = n;
	int mid;
	while (left < right) {
		mid = (left + right) >> 1;
		if (nums[mid] < p) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	return left;
}

int gettarget(int p, int q) {
	int row = getrow(p);
	switch (q) {
	case 0:
		if (p == nums[row - 1] + 1 || row == 1) return -1;
		return p - row;
	case 1:
		if (p == nums[row] || row == 1) return -1;
		return p - row + 1;
	case 2:
		if (row == n) return -1;
		return p + row;
	case 3:
		if (row == n) return -1;
		return p + row + 1;
	}
}

void insert(int a, int b) {           //在a和b之间插入一条边
	vers *tmp = &maze[a];
	vers *tmp1;
	while (tmp->next != NULL && tmp->next->idx < b) {
		tmp = tmp->next;
	}
	tmp1 = tmp->next;
	tmp->next = &edges[numedges++];
	tmp->next->idx = b;
	tmp->next->next = tmp1;
	tmp = &maze[b];

	while (tmp->next != NULL && tmp->next->idx < a) {
		tmp = tmp->next;
	}
	tmp1 = tmp->next;
	tmp->next = &edges[numedges++];
	tmp->next->idx = a;
	tmp->next->next = tmp1;
}

void print(int b, int a) {
	if (b == a) {
		printf("%d ", a);
	}
	else {
		print(ans[b], a);
		printf("%d ", b);
	}
}

int main() {
	int a, b;
	scanf("%d%d%d", &n, &a, &b);
	int i;

	for (i = 1; i <= n; ++i) {
		parent[i] = -1;
	}
	for (i = 1; i <= n; ++i) {
		nums[i] += nums[i - 1] + i;
	}
	int p, q;
	int target;
	while (true) {
		scanf("%d%d", &p, &q);
		target = gettarget(p, q);
		if (target != -1) {
			Union(p, target);
			insert(p, target);
			if (find(a) == find(b)) {
				break;
			}
		}
	}
	enqueue(a);
	flag[a] = 1;
	int tmp;
	vers *v;
	while (length) {
		tmp = dequeue();
		v = &maze[tmp];
		while (v->next != NULL) {
			v = v->next;
			if (flag[v->idx] == 0) {
				enqueue(v->idx);
				ans[v->idx] = tmp;
				flag[v->idx] = 1;
				if (v->idx == b) {
					print(b, a);
					return 0;
				}
			}
		}
	}
}