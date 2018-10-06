#include <iostream>
#include <iomanip>
using namespace std;

class Divided_by_zero{};

class MyComplex
{
	friend istream &operator>>(istream &is, MyComplex &n);
	friend ostream &operator<<(ostream &os, const MyComplex &n);
private:
	double x, y;
public:
	MyComplex() { x = 0, y = 0; }
	MyComplex(const MyComplex &other) { x = other.x; y = other.y; }
	MyComplex &operator=(const MyComplex &other) {
		if (this == &other) return *this;
		x = other.x, y = other.y;
		return *this;
	}
	MyComplex operator+(const MyComplex &other)const;
	MyComplex operator-(const MyComplex &other)const;
	MyComplex operator*(const MyComplex &other)const;
	MyComplex operator/(const MyComplex &other)const;
	MyComplex &operator+=(const MyComplex &other);
	MyComplex &operator-=(const MyComplex &other) ;
	MyComplex &operator*=(const MyComplex &other) ;
	MyComplex &operator/=(const MyComplex &other) ;
};


MyComplex MyComplex::operator+(const MyComplex &other)const {
	MyComplex new_c;
	new_c.x = x + other.x;
	new_c.y = y + other.y;
	return new_c;
}

MyComplex &MyComplex::operator+=(const MyComplex &other) {
	x += other.x;
	y += other.y;
	return *this;
}

MyComplex MyComplex::operator-(const MyComplex &other)const {
	MyComplex new_c;
	new_c.x = x - other.x;
	new_c.y = y - other.y;
	return new_c;
}

MyComplex &MyComplex::operator-=(const MyComplex &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

MyComplex MyComplex::operator*(const MyComplex &other)const {
	MyComplex new_c;
	new_c.x = x * other.x - y * other.y;
	new_c.y = x * other.y + y * other.x;
	return new_c;
}

MyComplex &MyComplex::operator*=(const MyComplex &other) {
	double old_x = x;
	x = x * other.x - y * other.y;
	y = old_x * other.y + y * other.x;
	return *this;
}

MyComplex MyComplex::operator/(const MyComplex &other)const {
	if (other.x == 0 && other.y == 0) throw Divided_by_zero();

	MyComplex new_c;
	new_c.x = (x * other.x + y * other.y) / (other.x * other.x + other.y * other.y);
	new_c.y = (y * other.x - x * other.y) / (other.x * other.x + other.y * other.y);
	return new_c;
}

MyComplex &MyComplex::operator/=(const MyComplex &other) {
	if (other.x == 0 && other.y == 0) throw Divided_by_zero();
	double old_x = x;

	x = (x * other.x + y * other.y) / (other.x * other.x + other.y * other.y);
	y = (y * other.x - old_x * other.y) / (other.x * other.x + other.y * other.y);
	return *this;
}

istream &operator>>(istream &is, MyComplex &n) {
	is >> n.x >> n.y;
	return is;
}

ostream &operator<<(ostream &os, const MyComplex &n) {
	os << setiosflags(ios::fixed) << setprecision(2)<<  n.x << ' ' << n.y;
	return os;
}

int main()
{
	MyComplex z1;
	MyComplex z2;

	cin >> z1 >> z2;

	cout << z1 + z2 << endl;
	cout << z1 - z2 << endl;
	cout << z1 * z2 << endl;
	cout << z1 / z2 << endl;
	cout << (z1 += z2) << endl;
	cout << (z1 -= z2) << endl;
	cout << (z1 *= z2) << endl;
	cout << (z1 /= z2) << endl;

	return 0;
}