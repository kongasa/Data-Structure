#include <iostream>
using namespace std;

class Divided_by_zero{};

class Long_int {
private:
	struct node {
		char num;
		node *next;

		node(char ch = '0', node *n = NULL) :num(ch), next(n) {}
	};
	node *head;
	int length;

public:
	Long_int() :length(0) { head = new node('0'); }
	Long_int(const Long_int &other);
	void clear();
	~Long_int();
	void push_front(char ch);
	void delete_front();
	Long_int &operator=(Long_int other);
	Long_int operator+(const Long_int &other);
	void display(node *p);
	void display() { display(head->next); }
	Long_int operator*(int i);
	bool operator<=(const Long_int &other);
	void lower(node *p, node *q, int &flag);
	Long_int operator/(Long_int &other);
};

void Long_int::clear() {
	node *p = head->next, *q;
	head->next = NULL;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}

Long_int::~Long_int() {
	clear();
	delete head;
}

Long_int &Long_int::operator=(Long_int other) {
	if (this == &other) { return *this; }

	clear();
	node *p = other.head->next, *q = head;
	while (p != NULL) {
		q->next = new node(p->num);
		q = q->next;
		p = p->next;
	}
	length = other.length;
	return *this;
}

Long_int::Long_int(const Long_int &other) {
	head = new node;
	head->next = NULL;
	node *p = other.head->next, *q = head;
	while (p != NULL) {
		q->next = new node(p->num);
		q = q->next;
		p = p->next;
	}
	length = other.length;
}

void Long_int::push_front(char ch) {
	head->next = new node(ch, head->next);
	length++;
}

void Long_int::display(node *p) {
	if (p->next == NULL) cout << p->num;
	else {
		display(p->next);
		cout << p->num;
	}
}

Long_int Long_int::operator+(const Long_int &other) {
	int excess = 0, i, sum;
	Long_int new_Bigint;
	node *self = head->next, *other_num = other.head->next, *new_current = new_Bigint.head;
	while (self != NULL && other_num != NULL) {
		sum = self->num - '0' + other_num->num - '0' + excess;
		if (sum >= 10) { excess = 1; sum -= 10; }
		else excess = 0;
		new_current->next = new node(sum + '0');
		new_current = new_current->next;
		new_Bigint.length++;
		self = self->next;
		other_num = other_num->next;
	}
	while (self != NULL) {
		sum = self->num - '0' + excess;
		if (sum == 10) { excess = 1; sum = 0; }
		else excess = 0;
		new_current->next = new node(sum + '0');
		new_current = new_current->next;
		self = self->next;
		new_Bigint.length++;
	}
	while (other_num != NULL) {
		sum = other_num->num - '0' + excess;
		if (sum == 10) { excess = 1; sum = 0; }
		else excess = 0;
		new_current->next = new node(sum + '0');
		new_current = new_current->next;
		other_num = other_num->next;
		new_Bigint.length++;
	}

	if (excess == 1) {
		new_current->next = new node('1');
		new_Bigint.length++;
	}
	return new_Bigint;
}

Long_int Long_int::operator*(int i) {
	Long_int result;
	node *p = head->next, *new_node = result.head;
	int excess = 0, multi;
	while (p != NULL) {
		multi = (p->num - '0') * i + excess;
		excess = multi / 10;
		multi %= 10;
		new_node->next = new node(multi + '0');
		new_node = new_node->next;
		p = p->next;
		result.length++;
	}
	if (excess != 0) {
		new_node->next = new node(excess + '0');
		result.length++;
	}
	return result;
}

void Long_int::lower(node *p, node *q, int &flag) {
	if (p->next == NULL) {
		if (p->num < q->num) flag = 1;
		if (p->num > q->num) flag = -1;
		return;
	}
	lower(p->next, q->next, flag);
	if (flag == 0) {
		if (p->num < q->num) flag = 1;
		if (p->num > q->num) flag = -1;
	}
}

bool Long_int::operator<=(const Long_int &other) {
	if (length < other.length) return true;
	if (length > other.length) return false;
	node *p = head->next, *q = other.head->next;
	int flag = 0;
	lower(p, q, flag);
	return flag == 1 || flag == 0;
}

void Long_int::delete_front() {
	node *p = head->next;
	head->next = p->next;
	delete p;
	length--;
}

Long_int Long_int::operator/(Long_int &other) {
	if (other.head->next->num == '0' && other.head->next->next == NULL) throw Divided_by_zero();
	int delt_length = length - other.length;
	Long_int result, tmp = other, sum;
	sum.push_front('0');
	int i, j;
	if (delt_length < 0) { result.push_front('0'); return result; }

	for (i = 0; i < delt_length; i++) tmp.push_front('0');
	for (j = 0; j <= delt_length; j++) {
		for (i = 1; i <= 10; i++) 
			if (!(sum + tmp * i <= *this)) {
				if (i != 1 || j != 0)
					result.push_front('0' + i - 1);
				sum = tmp * (i - 1) + sum;
				break;
			}
		tmp.delete_front();
	}
	if (result.head->next == NULL) result.push_front('0');
	return result;
}

int main() {
	char ch;
	Long_int a, b, c;
	while ((ch = cin.get()) != '\n') a.push_front(ch);
	while ((ch = cin.get()) != '\n') b.push_front(ch);
	c = a / b;
	c.display();
}