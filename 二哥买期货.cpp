#include<cstdio>

int normal_year[13] = {0,  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int leap_year[13] = {0,  31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int a[10000];               //记录xxxx年一月一日星期几

bool is_leap_year(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int cal_fes(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day) {
	int yuandan = 0;
	int wuyi = 0;
	int guoqin = 0;
	if (start_month == 1 && start_day == 1) ++yuandan;
	yuandan += end_year - start_year;

	if (start_month < 5) wuyi += 3;
	if (start_month == 5 && start_day <= 3) wuyi += 4 - start_day;
	if ((end_month == 5 && end_day >= 3) || end_month > 5) wuyi += 3;
	if (end_month == 5 && end_day <= 3) wuyi += end_day;
	wuyi += 3 * (end_year - start_year - 1);

	if (start_month < 10) guoqin += 7;
	if (start_month == 10 && start_day <= 7) guoqin += 8 - start_day;
	if ((end_month == 10 && end_day >= 7) || end_month > 10) guoqin += 7;
	if (end_month == 10 && end_day <= 7) guoqin += end_day;
	guoqin += 7 * (end_year - start_year + 1);
	return yuandan + wuyi + guoqin;
}

int cal_total_day(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day) {
	int ans;
	if (is_leap_year(start_year)) {
		for (int k = start_month; k <= 12; ++k) {
			ans += leap_year[k];
		}
		ans -= start_day;
	}
	else {
		int tmp = 0;
		for (int k = start_month; k <= 12; ++k) {
			ans += normal_year[k];
		}
		ans -= start_day;
	}

	if (is_leap_year(end_year)) {
		for (int k = 1; k <= end_month - 1; ++k) {
			ans += leap_year[k];
		}
		ans += start_day;
	}
	else {
		for (int k = 1; k <= end_month - 1; ++k) {
			ans += normal_year[k];
		}
		ans += start_day;
	}
	for (int i = start_year + 1; i < end_year; ++i) {
		if (is_leap_year(i)) {
			ans += 366;
		}
		else ans += 365;
	}
}

int cal_weekend(int total_day, int start_year, int start_month, int start_day) {

}

void prepare() {
	int day_sum = 0;
	int day_num = 1;
	a[1900] = 1;
	for (int i = 1901; i <= 9999; ++i) {
		day_num += (is_leap_year(i - 1)) ? 366 : 365;
		a[i] = (day_num - 1) % 7 + 1;
	}
}

int trans(char s[], int left, int right) {
	int ans = 0;
	for (int i = left; i <= right; ++i) {
		ans = ans * 10 + s[i] - '0';
	}
	return ans;
}

int main() {

}