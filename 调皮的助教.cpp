#include<iostream>
using namespace std;

int main() {
	int n, m, k, x, tmp, length, t;
	int i;                                    //��������
	cin >> n >> m >> k >> x;
	int p;                                              //pΪ10^k % n��ֵ
	int n1;
	for (n1 = n, length = 0; n1 > 0; n1 /= 10, ++length);
	for (tmp = 1, i = length; i > 0; tmp *= 10, --i);
	int *nums1 = new int[n](), *nums2 = new int[n];         //nums1�У�1������������֮һ��nums2�У�����Ϊi��ֵ��nums1�е�����,������
	i = 0;
    tmp %= n;
	nums1[nums2[i] = tmp] = 1;
	while (true) {
		tmp = (10 * tmp) % n;
		++i;
		if (tmp == 0) {
			if (k <= i) { cout << ((nums2[k - 1] * m) % n  + x) % n<< endl; return 0; }
			else { cout << x << endl; return 0; }
		}
		if (nums1[tmp]) break;
		else {
			nums1[nums2[i] = tmp] = 1;
		}
	}
	if (k >= length) {
		p = nums2[(k - length) % i];
		cout << ((p * m) % n + x) % n << endl;
	}
	else {
		for (i = 0, t = 1; i < k; t *= 10, ++i);
		cout << (((t % n) * m) % n + x) % n<< endl;
		return 0;
	}
	return 0;
}