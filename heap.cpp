#include<cstdio>
#include<iostream>
using namespace std;

const int INF = 0x7fffffff;
int heap[20001];
int ans[20001];
int current_size = 0;
void percolate_up(int);
int find(int);
void enqueue(int);
bool str_equal(char*, char*);

int main() {
	int M;
	scanf("%d", &M);
	char command[9];
	int a;
	int b;
	int i;
	int count = 0;
	for (i = 1; i <= M; ++i) {
		cin >> command;

		if (str_equal(command, "insert")) {
			scanf("%d", &a);
			enqueue(a);
		}
		else if (str_equal(command, "find")) {
			scanf("%d", &a);
			ans[++count] = find(a);
		}
		else if (str_equal(command, "decrease")) {
			scanf("%d%d", &a, &b);
			heap[a] -= b;
			percolate_up(a);
		}
		/*for (int j = 1; j <= current_size; ++j) {
			cout << heap[j] <<" ";
		}
		cout << endl;*/
	}
	for (i = 1; i <= count; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

bool str_equal(char *s1, char *s2) {
	for (; *s1 != '\0' && *s2 != '\0'; ++s1, ++s2) {
		if (*s1 != *s2) return false;
	}
	if (*s1 != '\0' || *s2 != '\0') return false;
	else return true;
}

void percolate_up(int x) {
	int tmp = heap[x];
	for (; x > 1 && heap[x / 2] > tmp; x /= 2) {
		heap[x] = heap[x / 2];
	}
	heap[x] = tmp;
}

void enqueue(int x) {
	heap[++current_size] = x;
	percolate_up(current_size);
}

int find(int x) {
	int min_in_larger = INF;
	int idx;
	for (int i = 1; i <= current_size; ++i) {
		if (heap[i] > x && heap[i] < min_in_larger) {
			min_in_larger = heap[i];
			idx = i;
		}
	}
	return idx;
}