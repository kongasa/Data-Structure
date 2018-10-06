#include <iostream>
using namespace std;

int get_min_index(long long int a[3]) {
	int t = 0;
	long long int Min = a[0];
	for (int i = 1; i < 3; i++)
		if (a[i] < Min) { Min = a[i]; t = i; }
	return t;
}

long long int find_max(long long int a[3]) {
	a[0] = (a[0] > a[1]) ? a[0] : a[1];
	a[0] = (a[0] > a[2]) ? a[0] : a[2];
	return a[0];
}

int main() {
	int N, i = 0, t, index, *list;
	long long int timer[3] = { 0 }, waiting_time[3] = { 0 };
	cin >> N;

	list = new int[N];
	for (i = 0; i < N; i++) {
		cin >> t;
		list[i] = t;
	}
	i = 0;
	while (i < N) {
		waiting_time[0] += timer[0];
		timer[0] += list[i];
		i++;
		if (i == N) break;
		waiting_time[1] += timer[1];
		timer[1] += list[i];
		i++;
		if (i == N) break;
		waiting_time[2] += timer[2];
		timer[2] += list[i];
		i++;
	}
	cout << waiting_time[0] + waiting_time[1] + waiting_time[2] << ' ' << find_max(timer) << endl;
	for (i = 0; i < 3; i++)
		waiting_time[i] = timer[i] = 0;
	for (i = 0; i < N; i++){
		index = get_min_index(timer);
		waiting_time[index] += timer[index];
		timer[index] += list[i];
	}
	cout << waiting_time[0] + waiting_time[1] + waiting_time[2] << ' ' << find_max(timer) << endl;

	return 0;
}
 