#include<cstdio>
#include<iostream>
using namespace std;

int price[20001];
int idx[20001];          //idx[i] = j表示询问第i大的数是第j个询问           
int ans[11][1001];
int rs[11];              //每次询问的r值

struct node {
	int data;
	int time;
	int idx;
	node *left, *right;
	node(int x, int i, int t = 1, node *l = NULL, node *r = NULL) : data(x), idx(i), time(t), left(l), right(r){}
};

node *root;

void insert(node *&p, int x, int idx) {
	if (p == NULL) p = new node(x, idx);
	else if (p->data > x) {
		insert(p->left, x, idx);
	}
	else if (p->data < x) {
		insert(p->right, x, idx);
	}
	else {
		p->time++;
	}
}

void remove(node *&p, int x) {
	if (p->data < x) {
		remove(p->right, x);
	}
	else if (p->data > x) {
		remove(p->left, x);
	}
	else if (p->time > 1) {
		--p->time;
	}
	else if (p->left != NULL && p->right != NULL) {
		node *tmp = p->right;
		node *tmp1 = p->right;
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}
		p->data = tmp->data;
		p->time = tmp->time;
		if (tmp == tmp1) {
			p->right = tmp->right;
			delete tmp;
		}
		else {
			while (tmp1->left != tmp) {
				tmp1 = tmp1->left;
			}
			tmp1->left = tmp->right;
			delete tmp;
		}
	}
	else {
		node *tmp = p;
		p = (p->left != NULL) ? p->left : p->right;
		delete tmp;
	}
}

void get_ans(node *p, int &count, int &num) {          //num表示是第几次q
	if (p->right != NULL) {
		get_ans(p->right, count, num);
	}

	int i;
	for (i = 1; i <= p->time; ++i) {
		++count;
		if (idx[count] != 0) {
			ans[num][idx[count]] = p->idx + i - 1;
		}
	}
	cout << p->data << endl;

	if (p->left != NULL) {
		get_ans(p->left, count, num);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	int tmp;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		price[i] = tmp;
		insert(root, tmp, i);
	}
	int k;
	char command;
	int x, y;
	int r;
	int num = 0;
	scanf("%d", &k);
	for (i = 1; i <= k; ++i) {
		getchar();
		command = getchar();
		switch (command) {
		case 'M':
			scanf("%d%d", &x, &y);
			remove(root, price[x]);
			price[x] = y;
			insert(root, y, x);
			break;
		case 'Q':
			++num;
			scanf("%d", &r);
			rs[num] = r;
			int j;
			for (j = 1; j <= 20000; ++j) idx[j] = 0;
			for (j = 1; j <= r; ++j) {
				scanf("%d", &tmp);
				idx[tmp] = j;
			}
			j = 0;
			get_ans(root, j, num);
			break;
		}
	}

	for (i = 1; i <= num; ++i) {
		for (int j = 1; j <= rs[num]; ++j) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}