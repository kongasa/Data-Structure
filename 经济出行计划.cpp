#include<cstdio>
#include<iostream>
using namespace std;

struct edge {
	int idx;
	int weight;
	edge *next;
	edge(int i = 0, int x = 0, edge *n = NULL) : idx(i), weight(x), next(n){}
};

struct ver {
	edge *e;
	ver(edge *x = NULL):e(x){}
};

struct hnode {
	int start, end;  //两端点编号
	int value;        //边的长度
	hnode(int a = 0, int b = 0, int c = 0) {
		start = a;
		end = b;
		value = c;
	}
};

const int MAX = 1000001;
const int INF = 1000000000;
edge edges[MAX * 2];
ver vers[MAX];
int num; //边
int dstn[MAX];

bool flag[MAX];              //记录节点i是否已经找到最短路径
hnode heap[MAX];             //用于找未加入的最短路径节点
int length;

int n, m;

void percolate_down(int idx) {
	hnode m = heap[idx];
	int child;
	for (; idx * 2 <= length; idx = child) {
		child = idx * 2;
		if (child + 1 <= length && heap[child].value > heap[child + 1].value) {
			++child;
		}
		if (heap[child].value < m.value) {
			heap[idx] = heap[child];
		}
		else break;
	}
	heap[idx] = m;
}

void enqueue(hnode x) {
	++length;
	int idx = length;
	for (; idx > 1 && heap[idx / 2].value > x.value; idx /= 2){
		heap[idx] = heap[idx / 2];
	}
	heap[idx] = x;
}

hnode dequeue() {
	hnode ans = heap[1];
	heap[1] = heap[length--];
	percolate_down(1);
	return ans;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

void insert(int a, int b, int w) { //a和b之间插入权值weight的边
		edge *tmp = vers[a].e;
		vers[a].e = &edges[num++];
		vers[a].e->weight = w;
		vers[a].e->next = tmp;
		vers[a].e->idx = b;

		tmp = vers[b].e;
		vers[b].e = &edges[num++];
		vers[b].e->weight = w;
		vers[b].e->next = tmp;
		vers[b].e->idx = a;
}

void getans() {
	flag[1] = 1;
	dstn[1] = 0;
	edge *tmp;
	int lastver = 1;
	hnode tmp1;
	while (flag[n] == 0) {
		tmp = vers[lastver].e;
		while (tmp != NULL) {
			if (flag[tmp->idx] == 0) {
				dstn[tmp->idx] = Min(dstn[lastver] + tmp->weight, dstn[tmp->idx]);
				enqueue(hnode(lastver, tmp->idx, dstn[tmp->idx]));
			}
			tmp = tmp->next;
		}
		while (true) {
			tmp1 = dequeue();
			if (flag[tmp1.end] == 0)break;
		}
		flag[tmp1.end] = 1;
		lastver = tmp1.end;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int u, v, c;
	int i;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &c);
		insert(u, v, c);
	}
	for (i = 1; i <= n; ++i) {
		dstn[i] = INF;
	}
	getans();
	printf("%d\n", dstn[n]);
	return 0;
}