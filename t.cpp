#include<iostream>
using namespace std;

double epsilon = 0.001;

int main() {
	double ans = 50000;
	int i = 0;
	while (ans > 0) {
		ans = 1.01 * ans - 1000;
		printf("%d\n", ++i);
	}
	return 0;
}