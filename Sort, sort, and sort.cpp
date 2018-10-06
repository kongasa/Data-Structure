#include<cstdio>

int ans;
const int N = 1111111;
int a[N];
int b[N];          //mergesort¸¨Öú
int n;
int length;

void percolate_down(int i) {
	int m = a[i];
	int idx = i;
	int child;
	for (; idx * 2 <= length; idx = child) {
		child = idx * 2;
		if (child + 1 <= length && (++ans) && a[child + 1] < a[child]) {
			++child;
		}
		if ((++ans) && a[child] < m) {
			a[idx] = a[child];
		}
		else {
			break;
		}
	}
	a[idx] = m;
}

void insert(int x) {
	++length;
	int idx = length;
	for (; idx / 2 >= 1; idx /= 2) {
		if ((++ans) && a[idx / 2] > x) {
			a[idx] = a[idx / 2];
		}
		else {
			break;
		}
	}
	a[idx] = x;
}

int dequeue() {
	/*int tmp = a[length];
	a[length--] = a[1];
	a[1] = tmp;
	percolate_down(1);*/
	int tmp = a[1];
	a[1] = a[length--];
	percolate_down(1);
	return tmp;
}

void heapsort() {
	while (length > 0) {
		dequeue();
	}
}

void merge(int left1, int right1, int left2, int right2) {
	int i = left1, j = left2;
	int k = left1;
	for (; i <= right1 && j <= right2; ++k) {
		if ((++ans) && a[i] <= a[j]) {
			b[k] = a[i];
			++i;
		}
		else {
			b[k] = a[j];
			++j;
		}
	}
	for (; i <= right1; ++i, ++k) {
		b[k] = a[i];
	}
	for (; j <= right2; ++j, ++k) {
		b[k] = a[j];
	}
	for (i = left1; i <= right2; ++i) {
		a[i] = b[i];
	}
}

void mergesort(int left, int right) {
	if (left >= right) {
		return;
	}
	int mid = (left + right) >> 1;
	if ((right - left) & 1 == 1) {
		mergesort(left, mid);
		mergesort(mid + 1, right);
		merge(left, mid, mid + 1, right);
	}
	else {
		mergesort(left, mid - 1);
		mergesort(mid, right);
		merge(left, mid - 1, mid, right);
	}
}

int get_boundary(int start, int end, bool &flag1, bool &flag2) {
	int left = start;
	int right = end;
	int b = a[start];
	while (left < right) {
		while (left < right && (++ans) && a[right] > b) {
			if (right + 1 <= end && a[right] > a[right + 1]) flag2 = false;
			--right;
		}
		a[left] = a[right];
		while (left < right && (++ans) && a[left] <= b){
			if (left - 1 >= start && a[left] < a[left - 1]) flag1 = false;
			++left;
		}
		a[right] = a[left];
	}
	a[left] = b;
	return left;

}

void qsort(int start, int end) {
	if (start >= end) {
		return;
	}
	bool flag1 = true;
	bool flag2 = true;
	int boundary = get_boundary(start, end, flag1, flag2);
	if (flag1 == false) qsort(start, boundary - 1);
	if (flag2 == false) qsort(boundary + 1, end);
}

int main() {
	int n;
	int k;
	scanf("%d%d", &n, &k);
	int i;
	int tmp;
	switch (k) {
	case 1:
		for (i = 1; i <= n; ++i) {
			scanf("%d", &tmp);
			insert(tmp);
		}
		heapsort();
		break;
	case 2:
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		mergesort(1, n);
		break;
	case 3:
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		qsort(1, n);
		break;
	}
	printf("%d\n", ans);
	for (i = 1; i <= n; ++i) {
		printf("%d ", a[i]);
	}
	return 0;
}