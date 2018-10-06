#include<iostream>
#include"stdio.h"
using namespace std;

int get_pos(int all_nums[], int num, int start, int end) {
	if (start == end) {
		if (all_nums[start] <= num) return start + 1;
		else return start;
	}
	int middle = (start + end) / 2;
	if (all_nums[middle] > num) return get_pos(all_nums, num, start, middle);
	else if (all_nums[middle] == num) return middle + 1;
	else return get_pos(all_nums, num, middle + 1, end);
}

int main() {
	int N, T, i, num, pos;            //N:手上数字个数，T：喜欢的数字个数
	int all_nums[100000];        //手上的数字和喜欢的数字
	cin >> N >> T;
	for (i = 0; i < N; ++i) cin >> all_nums[i];

	for (i = 0; i < T; ++i) {
		cin >> num;
		pos = get_pos(all_nums, num, 0, N - 1);
		cout << N - pos << endl;
	}
	return 0;
}