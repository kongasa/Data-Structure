#include<cstdio>

int tree[100001];
int parent[100001];
int left[100001];
int right[100001];
int output[100001];           //-1代表"OK", -2代表“Error", -3代表连续输出output三个数
int output2[300003];

void pre_order(int idx){
	printf("%d ", idx);
	if (left[idx] != 0) pre_order(left[idx]);
	if (right[idx] != 0) pre_order(right[idx]);
}

int main() {
	int m;
	scanf("%d", &m);
	tree[1] = 1;

	int i;
	int j = 1;
	int command;
	int a, b, c;
	for (i = 1; i <= m; ++i) {
		scanf("%d", &command);
		switch (command) {
		case 1:
			scanf("%d %d %d", &a, &b, &c);
			if (tree[a] == 0 || left[a] != 0 || right[a] != 0 || tree[b] != 0 || tree[c] != 0 || b == c) {
				output[i] = -2;
				break;
			}
			else {
				tree[b] = tree[c] = 1;
				left[a] = b;
				right[a] = c;
				parent[b] = parent[c] = a;
				output[i] = -1;
				break;
			}
		case 2:
			scanf("%d", &a);
			if (tree[a] == 0) {
				output[i] = -2; 
				break;
			}
			else {
				output2[j++] = parent[a];
				output2[j++] = left[a];
				output2[j++] = right[a];
				output[i] = -3;
				break;
			}
		case 3:
			scanf("%d", &a);
			if (tree[a] == 0 || a == 1) {
				output[i] = -2;
				break;
			}
			else {
				int tmp;
				if (a == left[parent[a]]) {
					tmp = right[parent[a]];
					right[parent[a]] = a;
					left[parent[a]] = tmp;
				}
				else {
					tmp = left[parent[a]];
					left[parent[a]] = a;
					right[parent[a]] = tmp;
				}
				output[i] = tmp;
				break;
			}
		}
	}
	j = 1;
	for (i = 1; i <= m; ++i) {
		switch (output[i]) {
		case -1:
			printf("Ok!\n");
			break;
		case -2:
			printf("Error!\n");
			break;
		case -3:
			printf("%d ", output2[j++]);
			printf("%d ", output2[j++]);
			printf("%d\n", output2[j++]);
			break;
		default:
			printf("%d\n", output[i]);
		}
	}
	pre_order(1);
}