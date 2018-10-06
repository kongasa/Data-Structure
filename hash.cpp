#include<cstdio>


const int max_num = 1000000;

int A[501];
int B[501];
int C[501];
int D[501];

struct node {
	int data;
	node *next;
	node(int x, node *n = NULL) : data(x), next(n){}
};

node *hash[250001];
node *rear[250001];                 //hash[i]µÄÎ²½Úµã
int max_nums;

int query(int sum) {
	int count = 0;
	int tmp1;
	int tmp = (tmp1 = 4 * max_num - sum) % max_nums;
	node *p = hash[tmp];
	while (p != NULL) {
		if (p->data == tmp1) {
			count++;
		}
		p = p->next;
	}
	return count;
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	int tmp1, tmp2, tmp3, tmp4;
	for (i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &tmp1, &tmp2, &tmp3, &tmp4);
		A[i] = tmp1 + max_num;
		B[i] = tmp2 + max_num;
		C[i] = tmp3 + max_num;
		D[i] = tmp4 + max_num;
	}
	max_nums = n * n;
	for (i = 0; i <= max_nums; ++i) {
		hash[i] = NULL;
	}
	int j;
	int sum;
	int tmp;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			sum = A[i] + B[j];
			tmp = sum % max_nums;
			if (hash[tmp] == NULL) {
				hash[tmp] = new node(sum);
				rear[tmp] = hash[tmp];
			}
			else {
				rear[tmp]->next = new node(sum);
				rear[tmp] = rear[tmp]->next;
			}
		}
	}

	int count = 0;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			count += query(C[i] + D[j]);
		}
	}
	for (i = 0; i <= n; ++i) {
		node *p = hash[i], *q;
		while (p != NULL) {
			q = p;
			p = p->next;
			delete q;
		}
	}
	printf("%d\n", count);
	return 0;
}