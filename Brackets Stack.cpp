#include<iostream>
#include<cstdio>
using namespace std;

class Stack {
private:
	int max_size;
	int top_p;
	char *data;
	void double_space();
public:
	Stack() : max_size(10), top_p(-1), data(new char[max_size]) {  }
	bool is_empty() { return top_p == -1; }
	char pop() { return data[top_p--]; }
	void push(char ch);
	char top() { return data[top_p]; }
	~Stack() { delete[] data; }
	char &operator[](int i) { return data[i]; }
	int length() { return top_p + 1; }
};

void Stack::double_space() {
	max_size *= 2;
	char *p = data;
	data = new char[max_size];
	for (int i = 0; i <= top_p; ++i)
		data[i] = p[i];
	delete[] p;
}

void Stack::push(char ch) {
	if (top_p == max_size - 1) double_space();
	data[++top_p] = ch;
}

bool check(Stack &store) {
	int i;
	Stack referee;
	for (i = 0; i < store.length(); ++i) {
		switch (store[i]) {
		case '(':case '[':case '{':
			referee.push(store[i]);
			break;
		case ')':
			if (referee.is_empty() || referee.pop() != '(') return false;
			break;
		case ']':
			if (referee.is_empty() || referee.pop() != '[') return false;
			break;
		case '}':
			if (referee.is_empty() || referee.pop() != '{') return false;
			break;
		}
	}
	if (referee.is_empty()) return true;
	else return false;
}

int main() {
	int n, i, command;
	char ch;
	scanf("%d", &n);
	Stack store, ans;
	for (i = 0; i < n; ++i) {
		scanf("%d", &command);
		switch (command) {
		case 1:
			scanf(" %c", &ch);
			store.push(ch);
			break;
		case 2:
			if (!store.is_empty()) store.pop();
			break;
		case 3:
			if (!store.is_empty()) ans.push(store.top());
			break;
		case 4:
			if (check(store)) ans.push('Y');
			else ans.push('N');
			break;
		}
	}
	for (int i = 0; i < ans.length(); ++i) {
		switch (ans[i]) {
		case 'Y':
			printf("YES\n");
			break;
		case 'N':
			printf("NO\n");
			break;
		default:
			printf("%c\n", ans[i]);
		}
	}
}