#include<cstdio>
#include<iostream>
using namespace std;

char a[500];
char b[500];

int main() {
	for (int i = 0; i < 500; ++i) {
		a[i] = b[i] = '0';
	}

	int dot_idx1;
	int dot_idx2;
	int length1 = 0;
	int length2 = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		a[++length1] = ch;
		if (ch == '.') {
			dot_idx1 = length1;
		}
	}
	while ((ch = getchar()) != '\n') {
		b[++length2] = ch;
		if (ch == '.') {
			dot_idx2 = length2;
		}
	}

	char *c, *d;                          //c是整数部分长的 d是整数部分短的
	int dot_idx_c, dot_idx_d;
	int length_c, length_d;
	if (dot_idx1 >= dot_idx2) {
		c = a;
		d = b;
		dot_idx_c = dot_idx1;
		dot_idx_d = dot_idx2;
		length_c = length1;
		length_d = length2;
	}
	else {
		c = b;
		d = a;
		dot_idx_c = dot_idx2;
		dot_idx_d = dot_idx1;
		length_c = length2;
		length_d = length1;
	}

	int j;
	int dot_len_c = length_c - dot_idx_c;
	int dot_len_d = length_d - dot_idx_d;
	int orig_length_c = length_c;

	if (dot_len_c < dot_len_d) {
		length_c += dot_len_d - dot_len_c;
		dot_len_c = dot_len_d;
	}
	if (dot_len_c > dot_len_d) {
		length_d += dot_len_c - dot_len_d;
		dot_len_d = dot_len_c;
	}

	int carry = 0;
	int sum;
	int rightc = length_c;
	int rightd = length_d;
	for (; rightd > 0; --rightc, --rightd) {
		if (c[rightc] == '.') {
			continue;
		}
		sum = c[rightc] - '0' + d[rightd] - '0' + carry;
		if (sum >= 10) {
			sum -= 10;
			carry = 1;
		}
		else carry = 0;
		c[rightc] = sum + '0';
	}
	for (; rightc > 0; --rightc) {
		sum = c[rightc] - '0' + carry;
		if (sum >= 10) {
			sum -= 10;
			carry = 1;
		}
		else carry = 0;
		c[rightc] = sum + '0';
	}
	if (carry == 1) c[0] = '1';

	if (c[0] == '1') printf("%c", c[0]);
	for (int i = 1; i <= length_c; ++i) {
		printf("%c", c[i]);
	}
	return 0;
}