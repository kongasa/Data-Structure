#include <iostream>
using namespace std;

int main() {
	int money = 0, cost;
	double deposit = 0;

	for (int i = 0; i < 12; i++) {
		cin >> cost;
		money += 300;
		if (money < cost) { cout << -i - 1<< endl; return 0; }
		
		money -= cost;
		if (money >= 100) { deposit += money - money % 100; money %= 100; }
	}
	cout << (money + 1.2 * deposit) << endl;
	return 0;
}