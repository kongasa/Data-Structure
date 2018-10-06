#include<iostream>
using namespace std;

bool is_valid(int sudoku[][9], int num, int i, int j) {
	int k, l;
	for (k = 0; k < j; ++k)
		if (sudoku[i][k] == num) return false;
	for (k = 0; k < i; ++k)
		if (sudoku[k][j] == num) return false;
	for (k = i / 3 * 3; k < (i / 3 + 1) * 3; ++k)
		for (l = j / 3 * 3; l < (j / 3 + 1) * 3; ++l) {
			if (i == k && j == l) return true;
			if (sudoku[k][l] == num) return false;
		}
}

int main() {
	int sudoku[9][9] = { {0} };
	int N;
	char **A;
	cin >> N;
	A = new char *[N];
	bool flag = true;
	int count, i, j;
	for (count = 0; count < N; count++) {
		flag = true;
		for (i = 0; i < 9; ++i)
			for (j = 0; j < 9; ++j) {
				cin >> sudoku[i][j];
				if (!is_valid(sudoku, sudoku[i][j], i, j)) { flag = false; }
			}
		if (!flag) A[count] = "Wrong";
		else  A[count] = "Right";
	}
	for (count = 0; count < N; ++count)
		cout << A[count] << endl;
	delete[] A;
	return 0;
}