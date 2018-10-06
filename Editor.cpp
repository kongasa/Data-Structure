#include <iostream>
#include <cstring>
using namespace std;

class out_of_bound{};

struct A {
	char *str, *command;
	int i, j;
};

class Editor {
public:
	int line_number;
	struct Line {
		int length;
		char *data;
		int max_size;
		Line *next;
		Line(Line *n = NULL):length(0), data(new char [10]), max_size(10), next(n){}
		void double_space();
		void push_back(char ch);
	};
	Line *head;

	Editor():line_number(0) { head = new Line(); }
	~Editor();
	void read();
	void list(int n1, int n2)const;
	void ins(int i, int j, char *str);
	void del(int i, int j, int num);
	void quit();
};

void Editor::Line::double_space() {
	max_size *= 2;
	char *p = data;
	data = new char[max_size];
	for (int i = 0; i < length; i++)
		data[i] = p[i];
	delete[] p;
}

void Editor::Line::push_back(char ch) {
	if (length == max_size - 1) double_space();
	data[length++] = ch;
}

Editor::~Editor() {
	Line *p = head->next, *q;
	while (p != NULL) {
		delete[] p->data;
		q = p;
		p = p->next;
		delete q;
	}
	delete [] head->data;
	delete head;
}

void Editor::read() {
	Line *current_line = head;
	char ch;
	while (true) {
		current_line->next = new Line(current_line->next);
		current_line = current_line->next;
		line_number++;
		while ((ch = cin.get()) != '\n') 
			current_line->push_back(ch);
		current_line->data[current_line->length] = '\0';
		if (strcmp(current_line->data, "******") == 0 || strcmp(current_line->data, "quit") == 0) break;
	}
	line_number--;
}

void Editor::list(int n1, int n2)const {
	if (n1 < 1 || n2 > line_number || n1 > n2) throw out_of_bound();
	Line *p = head;
	int i;
	for (i = 0; i < n1; i++) p = p->next;
	for (; i <= n2; i++) { cout << p->data << endl; p = p->next; }
}

void Editor::ins(int i, int j, char *str) {
	if (i < 1 || i > line_number) throw out_of_bound();
	Line *p = head;
	for (; i > 0; i--) p = p->next;
	if (j < 1 || j > p->length + 1) throw out_of_bound();

	int len = strlen(str), k;
	while (p->length + len >= p->max_size) p->double_space();
	for (k = p->length; k >= j; k--) p->data[k + len - 1] = p->data[k - 1];
	for (i = 0; i < len; i++, k++) p->data[k] = str[i];
	p->length += len;
	p->data[p->length] = '\0';
}

void Editor::del(int i, int j, int num) {
	if (i < 1 || i > line_number) throw out_of_bound();
	Line *p = head;
	for (; i > 0; i--) p = p->next;
	if (j < 1 || j > p->length || num > p->length - j + 1) throw out_of_bound();

	int k;
	for (k = 0; k < p->length - num - j + 1; k++) p->data[j + k - 1] = p->data[j + k + num - 1];
	p->length -= num;
	p->data[p->length] = '\0';
}

void Editor::quit() {
	Line *p = head->next;
	for (int i = 0; i < line_number; i++) {
		if (p->length != 0) cout << p->data << endl;
		p = p->next;
	}
}

int main() {
	Editor A, B;
	A.read();
	B.read();
	char *command, *str, *s;
	int i, j, num;
	command = new char[5];
	str = new char[1000];
	Editor::Line *p = B.head->next;
	for (int k = 0; k < B.line_number; k++) {
		i = j = num = 0;
		try {
			strncpy(command, p->data, 4);
			command[4] = '\0';
			if (strcmp(command, "list") == 0) {
				for (s = p->data + 5; *s != ' '; s++) i = i * 10 + *s - '0';
				cout << *s << endl;
				for (++s; s < p->data + p->length; s++) j = j * 10 + *s - '0';
				A.list(i, j);
			}
			else if (strcmp(command, "del ") == 0) {
				for (s = p->data + 4; *s != ' '; s++) i = i * 10 + *s - '0';
				for (++s; *s != ' '; s++) j = j * 10 + *s - '0';
				for (++s; s < p->data + p->length; s++) num = num * 10 + *s - '0';
				A.del(i, j, num);
			}
			else  {
				for (s = p->data + 4; *s != ' '; s++) i = i * 10 + *s - '0';
				for (++s; *s != ' '; s++) j = j * 10 + *s - '0';
				strcpy(str, ++s);
				A.ins(i, j, str);
			}
		}
		catch (out_of_bound) { cout<< "Error!" << endl; }
		p = p->next;
	}
	A.quit();
	return 0;
}