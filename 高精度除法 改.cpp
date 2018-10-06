#include <iostream>
using namespace std;

struct Number {
	char num[302];
	int length;
	Number() { length = 0; }
	void subtract(Number *other);
	void print() {
		char *c = num;
		int i = 0;
		while (*c == '0') { c++; i++; }
		for (; i < length; i++, c++) cout << *c;
		cout << endl;
	}
	bool less(Number *other);
};

void Number::subtract(Number *other) {
	int  i, carry = 0, res, dlt = length - other->length;
	char *ch;
	for (i = length; i > dlt; i--) {
		res = num[i - 1] -  other->num[i - dlt - 1] - carry;
		if (res < 0) { res += 10; carry = 1; }
		else carry = 0;
		num[i - 1] = '0' + res;
	}
	for (; i > 0; i--) {
		res = num[i - 1] - '0' - carry;
		if (res < 0) { res += 10; carry = 1; }
		else carry = 0;
		num[i - 1] = res + '0';
	}
}

bool Number::less(Number *other) {
	int i = length;
	char *s = num;
	while (*s == '0' && i > other->length) { s++; i--; }
	if (i > other->length) return false;
	else {
		for (; i > 0; i--) {
			if (num[length - i] < other->num[other->length - i]) return true;
			if (num[length - i] > other->num[other->length - i]) return false;
		}
		return false;
	}
}

int main(){
	Number *n1 = new Number, *n2 = new Number, *result = new Number;
	char ch;
	int orig_length, count;

	while ((ch = cin.get()) != '\n') n1->num[n1->length++] = ch;
	while ((ch = cin.get()) != '\n') n2->num[n2->length++] = ch;
	
	orig_length = n1->length;
	n1->length = n2->length;
	for (; n1->length <= orig_length; n1->length++) {
		count = 0;
		while (!n1->less(n2)) {
			n1->subtract(n2);
			count++;
		}
		result->num[result->length++] = count + '0';
	}
	result->print();
	return 0;
}