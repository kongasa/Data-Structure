#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int N, **mountain, i, j = 0, round = 0, count = 0;
	cin >> N;

	mountain = new int *[N];
	for (i = 0; i < N; i++)
		mountain[i] = new int[N];

	for (; round < (N + 1) / 2; round++) {
		for (i = round, j = round; j < N - round; j++) {
			count++;
			mountain[i][j] = count;
		}
		for (--j, ++i; i < N - round; i++) {
			count++;
			mountain[i][j] = count;
		}
		for (--j, --i; j > round - 1; --j) {
			count++;
			mountain[i][j] = count;
		}
		for (++j, --i; i > round; --i) {
			count++;
			mountain[i][j] = count;
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			cout << setw(6) << mountain[i][j];
		cout << endl;
		delete[] mountain[i];
	}
	delete[] mountain;
	return 0;
}