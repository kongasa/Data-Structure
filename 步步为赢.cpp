#include<iostream>
using namespace std;

int get_divisor(int N, int a) {
	for (int i = a + 1; i <= N / 2; ++i)
		if (N % i == 0) return i;
	return -1;
}

int main() {
	char answer[101], code[101], str[101], ch;
	int length1 = 0, length2 = 0, a = 0, b, i, j;
	while ((ch = cin.get()) != '\n') answer[length1++] = ch;
	while ((ch = cin.get()) != '\n') code[length2++] = ch;
	if (length1 != length2) { cout << "No Solution" << endl; return 0; }
	bool flag;
	while (true) {
		a = get_divisor(length1, a);
		if (a == -1) { cout << "No Solution" << endl; return 0; }
		b = length1 / a;

		int count = 0;
		for (i = 0; i < a; ++i)
			for (j = 0; j < b; ++j)
				str[count++] = answer[j * a + i];
		str[length1] = '\0';

		flag = true;
		for (i = 0; i < length1; ++i)
			if (str[i] != code[i]) {	flag = false; break;	}
		if (flag) { cout << a << endl; return 0; }
	}
}