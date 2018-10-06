#include<cstdio>

int log2(int x) {
	int ans = 0;
	while (x != 1) {
		x >>= 1;
		++ans;
	}
	return ans;
}

int power(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

bool strequal(char *s1, char *s2) {
	char *c1 = s1, *c2 = s2;
	while (*c1 != '\0' && *c2 != '\0') {
		if (*c1 != *c2) return false;
		++c1;
		++c2;
	}
	if (*c1 != '\0' || *c2 != '\0') return false;
	return true;
}

class Easy_vector {
private:
	int max_size;
	int length;
	char *data;
	void double_space();
public:
	Easy_vector() :max_size(10), length(0), data(new char[max_size]) {}
	void push_back(char x);
	~Easy_vector() { delete[] data; }
	int get_length() { return length; }
	void print();
};

void Easy_vector::print() {
	for (int i = 0; i < length; ++i)
		printf("%c", data[i]);
	printf("\n");
}

void Easy_vector::double_space() {
	max_size <<= 1;
	char *p = data;
	data = new char[max_size];
	for (int i = 0; i < length; ++i) data[i] = p[i];
	delete[] p;
}

void Easy_vector::push_back(char x) {
	if (length == max_size) double_space();
	data[length++] = x;
}

class Binary_tree {
private:
	char *data;
	int length;
	void level_order_create(char *s, int length);
	void pre_order_create(char *s, int current_index, int left, int right, int length);
	void post_order_create(char *s, int current_index, int left, int right, int length);
	void mid_order_create(char *s, int current_index, int left, int right, int length);
	void pre_order(int current_index, Easy_vector &store);
	void mid_order(int current_index, Easy_vector &store);
	void post_order(int current_index, Easy_vector &store);
	void level_order(Easy_vector &store);
public:
	Binary_tree(char *s, char *nodes, int l);
	~Binary_tree() { delete[] data; }
	void save(char *command, Easy_vector &store);
};

void Binary_tree::save(char *command, Easy_vector &store) {
	if (strequal(command, "LEVELORDER")) level_order(store);
	else if (strequal(command, "PREORDER")) pre_order( 1,store);
	else if (strequal(command, "INORDER")) mid_order(1,store);
	else if (strequal(command, "POSTORDER")) post_order(1, store);
}

Binary_tree::Binary_tree(char *s, char *nodes, int l) {
	length = l;
	data = new char[length + 1];
	if (strequal(s, "LEVELORDER")) level_order_create(nodes, length);
	else if (strequal(s, "PREORDER"))  pre_order_create(nodes, 1, 0, length - 1, length);
	else if (strequal(s, "INORDER")) mid_order_create(nodes, 1, 0, length - 1, length);
	else if (strequal(s, "POSTORDER")) post_order_create(nodes, 1, 0, length - 1, length);
}

void Binary_tree::pre_order( int current_index, Easy_vector &store) {
	store.push_back(data[current_index]);
	if (current_index * 2 <= length) pre_order(current_index * 2, store);
	if (current_index * 2 + 1<= length) pre_order(current_index * 2 + 1, store);
}

void Binary_tree::post_order(int current_index, Easy_vector &store) {
	if (current_index * 2 <= length) post_order(current_index * 2, store);
	if (current_index * 2 + 1 <= length) post_order(current_index * 2 + 1, store);
	store.push_back(data[current_index]);
}

void Binary_tree::mid_order(int current_index, Easy_vector &store) {
	if (current_index * 2 <= length) mid_order(current_index * 2, store);
	store.push_back(data[current_index]);
	if (current_index * 2 + 1 <= length) mid_order(current_index * 2 + 1, store);
}


void Binary_tree::level_order(Easy_vector &store) {
	for (int i = 1; i <= length; ++i) 
		store.push_back(data[i]);
}

void Binary_tree::level_order_create(char *s, int length) {
	for (int i = 1; i <= length; ++i)
		data[i] = s[i - 1];
}


void Binary_tree::pre_order_create(char *s,int current_index, int left, int right, int length) {
	if (left == right) {
		data[current_index] = s[left];
		return;
	}
	int depth = log2(length) + 1, tmp;
	int excess = length - power(2, depth - 1) + 1;
	int left_excess, right_excess;
	if (excess > (tmp = power(2, depth - 1) / 2)) {
		left_excess = tmp;
		right_excess = excess - tmp;
	}
	else {
		left_excess = excess;
		right_excess = 0;
	}
	tmp = (power(2, depth - 1) - 2) / 2;
	int left_size = left_excess + tmp;
	int right_size = right_excess + tmp;
	data[current_index] = s[left];
	pre_order_create(s, current_index * 2, left + 1, left + left_size, left_size);
	if (right_size != 0) pre_order_create(s, current_index * 2 + 1, left + left_size + 1, left + left_size + right_size, right_size);
}

void Binary_tree::mid_order_create(char *s, int current_index, int left, int right, int length) {
	if (left == right) {
		data[current_index] = s[left];
		return;
	}
	int depth = log2(length) + 1, tmp;
	int excess = length - power(2, depth - 1) + 1;
	int left_excess, right_excess;
	if (excess > (tmp = power(2, depth - 1) / 2)) {
		left_excess = tmp;
		right_excess = excess - tmp;
	}
	else {
		left_excess = excess;
		right_excess = 0;
	}
	tmp = (power(2, depth - 1) - 2) / 2;
	int left_size = left_excess + tmp;
	int right_size = right_excess + tmp;
	data[current_index] = s[left + left_size];
	mid_order_create(s, current_index * 2, left, left + left_size - 1, left_size);
	if (right_size != 0)mid_order_create(s, current_index * 2 + 1, left + left_size + 1, right, right_size);
}

void Binary_tree::post_order_create(char *s, int current_index, int left, int right, int length) {
	if (left == right) {
		data[current_index] = s[left];
		return;
	}
	int depth = log2(length) + 1, tmp;
	int excess = length - power(2, depth - 1) + 1;
	int left_excess, right_excess;
	if (excess > (tmp = power(2, depth - 1) / 2)) {
		left_excess = tmp;
		right_excess = excess - tmp;
	}
	else {
		left_excess = excess;
		right_excess = 0;
	}
	tmp = (power(2, depth - 1) - 2) / 2;
	int left_size = left_excess + tmp;
	int right_size = right_excess + tmp;
	data[current_index] = s[right];
	post_order_create(s, current_index * 2, left, left + left_size - 1, left_size);
	if (right_size != 0)post_order_create(s, current_index * 2 + 1, left + left_size, right - 1, right_size);
}


int main() {
	int t, i, n;
	Easy_vector A[10];
	scanf("%d", &t);
	char order[10], code[7];
	for (i = 0; i < t; ++i) {
		scanf("%d", &n);
		char *data = new char[n + 1];
		scanf(" %s %s\n%s", order, code, data);
		if (strequal(code, "ENCODE")) {
			Binary_tree tree("LEVELORDER", data, n);
			tree.save(order, A[i]);
		}
		else {
			Binary_tree tree(order, data, n);
			tree.save("LEVELORDER", A[i]);
		}
		delete[] data;
	}
	scanf("%s", order);
	for (i = 0; i < t; ++i) A[i].print();
	return 0;
}

