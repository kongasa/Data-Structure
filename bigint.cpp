#include <iostream>
using namespace std;

class Bigint {
private:
	struct node {
		char num;
		node *next;

		node(char ch = '0', node *n = NULL):num(ch), next(n){}
	};
	node *head;
	int length;

public:
	Bigint():length(0) { head = new node('0'); }
	Bigint(const Bigint &other);
	void clear();
	~Bigint();
	void push_front(char ch);
	Bigint &operator=(Bigint other);
	Bigint operator+(const Bigint &other);
	void display(node *p);
	void display() { display(head->next); }
};

void Bigint::clear() {
	node *p = head->next, *q;
	head->next = NULL;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}

Bigint::~Bigint() {
	clear();
	delete head;
}

Bigint &Bigint::operator=(Bigint other) {
	if (this == &other) { return *this; }

	clear();
	node *p = other.head->next,  *q = head;
	while (p != NULL) {
		q->next = new node(p->num);
		q = q->next;
		p = p->next;
	}
	length = other.length;
	return *this;
}

Bigint::Bigint(const Bigint &other) {
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

void Bigint::push_front(char ch) {
	head->next = new node(ch, head->next);
	length++;
}

Bigint Bigint::operator+(const Bigint &other) {
	int excess = 0, i, sum;
	Bigint new_Bigint;
	node *self = head->next, *other_num = other.head->next, *new_current = new_Bigint.head;
	while(self != NULL && other_num != NULL) {
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

void Bigint::display(node *p) {
	if (p->next == NULL) cout << p->num;
	else {
		display(p->next);
		cout << p->num;
	}
}

int main() {
	char ch;
	Bigint A, B, C;
	while ((ch = cin.get()) != '\n') A.push_front(ch);
	while ((ch = cin.get()) != '\n') B.push_front(ch);
	C = A + B;
	C.display();
}