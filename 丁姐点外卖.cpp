#include<iostream>
using namespace std;

char *reverse(char *s, int length) {
	char tmp;
	int i;
	for (i = 0; i < length / 2; ++i) {
		tmp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1] = tmp;
	}
	return s;
}

int main() {
	char str1[101];
	char str2[101];
	char ans[102];
	char *c1, *c2;
	cin >> str1 >> str2;
	int length1 = 0, length2 = 0, i;
	while (str1[length1] != '\0') ++length1;
	while (str2[length2] != '\0') ++length2;
	
	reverse(str1, length1);
	reverse(str2, length2);

	int carry = 0, sum;
	for(i = 0, c1 = str1, c2 = str2; *c1 != '\0' && *c2 != '\0'; ++i, ++c1, ++c2){
		sum = *c1 - 'a' + *c2 - 'a' + carry;
		carry = 0;
		if (sum >= 26) { carry = 1; sum %= 26; }
		ans[i] = 'a' + sum;
	}
	while (*c1 != '\0') {
		sum = *c1 - 'a' + carry;
		carry = 0;
		if (sum >= 26) { carry = 1; sum %= 26; }
		ans[i++] = 'a' + sum;
		++c1;
	}
	while (*c2 != '\0') {
		sum = *c2 - 'a' + carry;
		carry = 0;
		if (sum >= 26) { carry = 1; sum %= 26; }
		ans[i++] = 'a' + sum;
		++c2;
	}

	if (carry == 1) ans[i++] = 'b';
	
	reverse(ans, i);
	ans[i] = '\0';
	cout << ans << endl;
}