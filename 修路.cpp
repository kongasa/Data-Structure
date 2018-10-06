#include<cstdio>

struct Node {
	int idx;
	int data;
	Node *parent;
	Node (int i = 0, int d = 0, Node *p = NULL):idx(i), data(d), parent(p){}
};

int a[2001];
const int INF = 2000000000;
Node tmp[2001];

int get_pos(int x, int left, int right) {
	if (left >= right) {
		return left;
	}
	int mid = (left + right) / 2;
	if (tmp[mid].data == x) { return mid; }
	if (tmp[mid].data > x) {
		return get_pos(x, left, mid);
	}
	else return get_pos(x, mid + 1, right);
}

int main() {
	a[0] = -1;
	int N;
	scanf("%d", &N);
	a[N + 1] = INF;

	int i;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a[i]);
	}
	
	tmp[0].idx = 0;
	int len = 0;
	int count1 = 0, count2 = 0;
	for (i = 1; i <= N; ++i) {
		if (a[i] > tmp[len].data) {
			++len;
			tmp[len] = Node(i, a[i], &tmp[len - 1]);
		}
		else if(a[i] < tmp[len].data){
			count2 = 0;
			while (a[i] < tmp[len].data) {
				++i;
				++count2;
			}
			
			int index = get_pos(a[i], 1, len);
			printf("index:%d\n", index);
			tmp[index] = Node(i, a[i], &tmp[index - 1]);
		}
		else {
			count1 = 0;
			while (a[i] == tmp[len].data) {
				++i;
				++count1;
			}
		}
	}
	printf("test %d\n", tmp[1].data);
	int ans = 0;
	tmp[len + 1] = Node(2001, INF, &tmp[len]);
	Node p = tmp[len + 1];
	for (i = N; i >= 1; --i) {
		while (i > p.parent->idx) {
			if (a[i] > p.data) {
				ans += a[i] - p.data;
			}
			else if (a[i] < p.parent->data) {
				ans += p.parent->data - a[i];
			}
			--i;
			printf("ans:%d   data:%d\n", ans, p.data);
		}
		p = *(p.parent);
	}
	printf("%d\n", ans);
	return 0;
}