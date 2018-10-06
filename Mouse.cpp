#include<cstdio>
#include<iostream>
using namespace std;

const int N = 100001;
const int INF = 0x7fffffff;
int points[N * 2];
int strength[N * 2];
int idx[N * 2];
int winnerp[N];
int winners[N];
int winneri[N];
int num1;
int loserp[N];
int losers[N];
int loseri[N];
int num2;
int drawp[N];
int draws[N];
int drawi[N];
int num3;

int Max(int a, int b, int c) {     //哪个编号对应的数大
	if (winnerp[a] > loserp[b] || (winnerp[a] == loserp[b] && winneri[a] < loseri[b])) {
		return (winnerp[a] > drawp[c] || (winnerp[a] == drawp[c] && winneri[a] < drawi[c])) ? winneri[a] : drawi[c];
	}
	else {
		return (loserp[b] > drawp[c] || (loserp[b] == drawp[c] && loseri[b] < drawi[c])) ? loseri[b] : drawi[c];
	}
}

int getboundary(int start, int end) {
	int left = start;
	int right = end;
	int m = points[start];
	int n = strength[start];
	int k = idx[start];
	while (left < right) {
		while (left < right && points[right] <= m) {
			if (points[right] == m && idx[right] < k) break;
			--right;
		}
		points[left] = points[right];
		strength[left] = strength[right];
		idx[left] = idx[right];
		while (left < right && points[left] >= m) {
			if (points[left] == m && idx[left] > k) break;
			++left;
		}
		points[right] = points[left];
		strength[right] = strength[left];
		idx[right] = idx[left];
	}
	points[left] = m;
	strength[left] = n;
	idx[left] = k;
	return left;
}

void qsort(int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = getboundary(start, end);
	qsort(start, boundary - 1);
	qsort(boundary + 1, end);
}

void addwinner(int i) {
	winnerp[num1] = points[i];
	winners[num1] = strength[i];
	winneri[num1++] = idx[i];
}

void addloser(int i) {
	loserp[num2] = points[i];
	losers[num2] = strength[i];
	loseri[num2++] = idx[i];
}

void adddraw(int i) {
	drawp[num3] = points[i];
	draws[num3] = strength[i];
	drawi[num3++] = idx[i];
}

void merge() {
	int i, j, k;
	i = j = k = 0;
	int index = 1;
	int tmp;
	for (; i < num1 && j < num2 && k < num3; ++index) {
		tmp = Max(i, j, k);
		if (tmp == winneri[i]) {
			points[index] = winnerp[i];
			strength[index] = winners[i];
			idx[index] = winneri[i];
			++i;
		}
		else if (tmp == loseri[j]) {
			points[index] = loserp[j];
			strength[index] = losers[j];
			idx[index] = loseri[j];
			++j;
		}
		else {
			points[index] = drawp[k];
			strength[index] = draws[k];
			idx[index] = drawi[k];
			++k;
		}
	}
	for (; i < num1 && j < num2; ++index) {
		tmp = (winnerp[i] > loserp[j] || (winnerp[i] == loserp[j] && winneri[i] < loseri[j])) ? winneri[i] : loseri[j];
		if (tmp == winneri[i]) {
			points[index] = winnerp[i];
			strength[index] = winners[i];
			idx[index] = winneri[i];
			++i;
		}
		else {
			points[index] = loserp[j];
			strength[index] = losers[j];
			idx[index] = loseri[j];
			++j;
		}
	}
	for (; i < num1 && k < num3; ++index) {
		tmp = (winnerp[i] > drawp[k] || (winnerp[i] == drawp[k] && winneri[i] < drawi[k])) ? winneri[i] : drawi[k];
		if (tmp == winneri[i]) {
			points[index] = winnerp[i];
			strength[index] = winners[i];
			idx[index] = winneri[i];
			++i;
		}
		else {
			points[index] = drawp[k];
			strength[index] = draws[k];
			idx[index] = drawi[k];
			++k;
		}
	}
	for (; j < num2 && k < num3; ++index) {
		tmp = (loserp[j] > drawp[k] || (loserp[j] == drawp[k] && loseri[j] < drawi[k])) ? loseri[j] : drawi[k];
		if (tmp == loseri[j]) {
			points[index] = loserp[j];
			strength[index] = losers[j];
			idx[index] = loseri[j];
			++j;
		}
		else {
			points[index] = drawp[k];
			strength[index] = draws[k];
			idx[index] = drawi[k];
			++k;
		}
	}
	for (; i < num1; ++index) {
		points[index] = winnerp[i];
		strength[index] = winners[i];
		idx[index] = winneri[i];
		++i;
	}
	for (; j < num2; ++index) {
		points[index] = loserp[j];
		strength[index] = losers[j];
		idx[index] = loseri[j];
		++j;
	}
	for (; k < num3; ++index) {
		points[index] = drawp[k];
		strength[index] = draws[k];
		idx[index] = drawi[k];
		++k;
	}
}

int main() {
	int n, r;
	int i;
	scanf("%d%d", &n, &r);
	for (i = 1; i <= n * 2; ++i) {
		scanf("%d", &points[i]);
		idx[i] = i;
	}
	for (i = 1; i <= n * 2; ++i) {
		scanf("%d", &strength[i]);
	}
	points[0] = INF;
	qsort(1, 2 * n);
	int j;
	for (i = 1; i <= r; ++i) {
		num1 = num2 = num3 = 0;
		for (j = 1; j <= 2 * n; j += 2) {
			if (strength[j] > strength[j + 1]) {
				points[j] += 2;
				addwinner(j);
				addloser(j + 1);
			}
			else if (strength[j] < strength[j + 1]) {
				points[j + 1] += 2;
				addwinner(j + 1);
				addloser(j);
			}
			else {
				++points[j];
				++points[j + 1];
				adddraw(j);
				adddraw(j + 1);
			}
		}
		merge();
	}
	for (i = 1; i <= 2 * n; ++i) {
		printf("%d ", idx[i]);
	}
	printf("\n");
	return 0;
}