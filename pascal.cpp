#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class my_stack {
private:
	int top_p;
	int max_size;
	char *data;

	void double_space();
public:
	my_stack();
	char pop();
	void push(char ch);
	~my_stack();
	char top();
	bool is_empty() { return top_p == -1; }
};

void my_stack::double_space() {
	max_size *= 2;
	char *p = new char[max_size];
	for (int i = 0; i <= top_p; ++i)
		p[i] = data[i];
	delete data;
	data = p;
}

my_stack::my_stack() {
	top_p = -1;
	max_size = 10;
	data = new char[max_size];
}

char my_stack::pop() {
	return data[top_p--];
}

void my_stack::push(char ch) {
	if (top_p == max_size - 1) double_space();
	data[++top_p] = ch;
}

my_stack::~my_stack() {
	delete[] data;
}

char my_stack::top() {
	if (top_p == -1) return '9';
	return data[top_p];
}


void skip_space(char *&s) {
	while (*s == ' ' || *s == '\t' || *s == '\n') ++s;
}

void skip_ch(char *&s) {
	while (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\0') ++s;
	if (*s == '\0') --s;
}

char which_key(char *s) {
	if (s[1] == 'e' && s[2] == 'g' && s[3] == 'i' && s[4] == 'n') return '1';
	if (s[1] == 'n' && s[2] == 'd') return '4';
	if (s[1] == 'f') return '2';
	if (s[1] == 'h' && s[2] == 'e' && s[3] == 'n') return '3';
	if (s[1] == 'l' && s[2] == 's' && s[3] == 'e') return '5';
	return '0';
}

int main() {
	int i = 0;
	char code[4001], ch, *s, flag;
	while ((ch = cin.get()) != EOF) code[i++] = ch;
	code[i] = '\0';

	my_stack words;   
	s = code;
	while (*s != '\0') {
		flag = '0';
		skip_space(s);
		if (*s == '\'') {
			++s;
			while (*s != '\'') ++s;
		}
		if (*s == '{') { ++s; while (*s != '}')++s; }
		switch (*s) {
		case 'b':case'i':case't':case'e':flag = which_key(s);
		}
		switch (flag) {
		case '0':  break;
		case '1':
			if (!words.is_empty() && words.top() == '2') { cout << "Error!" << endl; return 0; }
			words.push('1'); 
			skip_ch(s);
			break;
		case '2':
			if (!words.is_empty() && words.top() == '2') { cout << "Error!" << endl; return 0; }
			words.push('2');
			skip_ch(s); 
			break;
		case '3':
			if (words.is_empty() || words.top() != '2') {
			cout << "Error!" << endl;
			return 0;
		}
				 words.pop();
				 words.push('3');
				 skip_ch(s);
				 break;
		case '4':
			while (words.top() == '3') words.pop();
			if (words.is_empty() || words.top() != '1') { cout << "Error!" << endl; return 0; }
				 words.pop();
				 skip_ch(s);
				 break;
		case '5':
			if (words.is_empty() || words.top() != '3') { cout << "Error!" << endl; return 0; }
				 words.pop(); 
				 skip_ch(s);
				 break;
		}
		++s;
	}
	while (words.top() == '3') words.pop();
	if (words.is_empty()) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
