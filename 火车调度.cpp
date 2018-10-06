#include<iostream>
using namespace std;

class Station{
private:
	int *data;
	int top_p, max_size;
public:
	Station() :top_p(-1) { data = new int[10]; }
	void initialize(int init_size){
		top_p = -1;
		if (!init_size) return;
		max_size = init_size;
		delete [] data;
		data = new int[max_size];
	}
	int top() {
		if (is_empty()) return -1;
		return data[top_p]; 
	}
	bool push(int i) {
		if (top_p == max_size - 1) return false;
		data[++top_p] = i;
		return true;
	}
	bool is_empty() { return top_p == -1; }
	int pop() {
		if (is_empty()) return -1;
		return data[top_p--];
	}
	~Station() { delete[] data; }
};

int main() {
	int T, N, M, i, j, k, current;         //T:测试点数量， N：每次测试火车数量 M：每次测试车站最大容量
	cin >> T;
	bool flag, j_flag;
	Station A;
	char **result = new char *[T], n[10000];
	for (i = 0; i < T; ++i) {
		flag = true;
		cin >> N >> M;
		A.initialize(M);
		cin >> current;
		for (k = 0, j = 0; j < N;) {
			if (A.top() == current) {
				A.pop();
				cin >> current;
				++k;
				continue;
			}
			if (j == current) {
				if (k != N - 1) {
					cin >> current; 
					++k;
				}
				++j;
				continue; 
			}
			j_flag = A.push(j);
			j++;
			if (!j_flag) { 
				for (; k < N - 1; ++k) cin >> current;
				flag = false; 
				break; 
			}
		}
		if (flag == false) { result[i] = "NO"; continue; }

		if (!A.is_empty() && A.pop() != current) { flag = false;  }
		while (!A.is_empty()) {
			cin >> current;
			if (A.pop() != current) { flag = false; }
		}
		if (!flag) result[i] = "NO";
		else result[i] = "YES";
	}
	for (i = 0; i < T; ++i) cout << result[i] << endl;
	delete [] result;
	return 0;
}