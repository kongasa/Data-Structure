#include<cstdio>

struct Node {
	int data;
	int times;
	Node *left, *right;
	Node (int x, int t = 1, Node *l = NULL, Node *r = NULL):data(x), times(t), left(l), right(r){}
};

void clear(Node *&p) {
	if (p == NULL) return;
	clear(p->left);
	clear(p->right);
	delete p;
	p = NULL;
}

int find(Node *p, int x) { 
	if (p == NULL) return -1;                    //-1代表没找到
	if (x == p->data) return -2;                 //-2代表找到了
	if (x > p->data) return find(p->right, x);
	else return find(p->left, x);
}

void insert(Node *&p, int x) {
	if (p == NULL) {
		p = new Node(x);
	}
	else if (p->data == x) {
		++p->times;
	}
	else if (p->data > x) {
		insert(p->left, x);
	}
	else if (p->data < x) {
		insert(p->right, x);
	}
}

void remove(Node *&p, int x) {
	if (p == NULL) return;
	if (p->data > x) {
		remove(p->left, x);
	}
	else if (p->data < x) {
		remove(p->right, x);
	}
	else if (p->data == x) {
		if (p->times > 1)  --p->times;
		else {
			Node *tmp = p->right;
			Node *pp;
			if (tmp == NULL) {
				pp = p;
				p = p->left;
				delete pp;
			}
			else {
				while (tmp->left != NULL) {
					tmp = tmp->left;
				}
				p->data = tmp->data;
				p->times = tmp->times;
				remove(p->right, tmp->data);
			}
		}
	}
}

void remove_less_than(Node *&p, int x) {
	if (p == NULL) return;
	if (p->data == x) {
		clear(p->left);
	}
	else if (p->data > x) {
		remove_less_than(p->left, x);
	}
	else {
		clear(p->left);
		Node *tmp = p;
		p = p->right;
		delete tmp;
		remove_less_than(p, x);
	}
}

void remove_greater_than(Node *&p, int x) {
	if (p == NULL) return;
	if (p->data == x) {
		clear(p->right);
	}
	else if (p->data > x) {
		clear(p->right);
		Node *tmp = p;
		p = p->left;
		delete tmp;
		remove_greater_than(p, x);
	}
	else if (p->data < x) {
		remove_greater_than(p->right, x);
	}
}

void remove_interval(Node *&p, int a, int b) {
	if (p == NULL) return;
	if (p->data == a) {
		remove_less_than(p->right, b);
	}
	else if (p->data < a) {
		remove_interval(p->right, a, b);
	}
	else {
		remove_less_than(p->right, b);
		remove_interval(p->left, a, b);
		if (p->data < b) {
			while (p->times > 1) remove(p, p->data);
			remove(p, p->data);
		}
	}
	
}

int find_ith(Node *p, int &count, int i) {
	int ans;
	if (p == NULL) return -1;
	if (p->left != NULL) {
		ans = find_ith(p->left, count, i);
	}
	if (count >= i) return ans;

	count += p->times;
	if (count >= i) {
		return p->data;
	}

	if (p->right != NULL) {
		ans = find_ith(p->right, count, i);
	}
	if (count >= i) {
		return ans;
	}
	return -1;
}

bool str_equal(char *s1, char *s2) {
	for (; *s1 != '\0' && *s2 != '\0'; ++s1, ++s2) {
		if (*s1 != *s2) return false;
	}
	if (*s1 != '\0' || *s2 != '\0') return false;
	return true;
}

//void tranverse(Node *p) {
//	if (p->left != NULL) tranverse(p->left);
//	printf("%d ", p->data);
//	if (p->right != NULL) tranverse(p->right);
//}

int ans[300001];
int m;
Node *root;

int main() {
	int n;
	scanf("%d", &n);
	char command[100];
	int i;
	int x;
	int a, b;
	for (i = 1; i <= n; ++i) {
		scanf("%s", command);
		if (str_equal(command, "insert")) {
			scanf("%d", &x);
			insert(root, x);
		}
		else if (str_equal(command, "delete")) {
			scanf("%d", &x);
			remove(root, x);
		}
		else if (str_equal(command, "delete_less_than")) {
			scanf("%d", &x);
			remove_less_than(root, x);
		}
		else if (str_equal(command, "delete_greater_than")) {
			scanf("%d", &x);
			remove_greater_than(root, x);
		}
		else if (str_equal(command, "delete_interval")) {
			scanf("%d%d", &a, &b);
			remove_interval(root, a, b);
		}
		else if (str_equal(command, "find")) {
			scanf("%d", &x);
			int t = find(root, x);
			ans[++m] = t;
		}
		else if (str_equal(command, "find_ith")) {
			scanf("%d", &x);
			int count = 0;
			int t = find_ith(root, count, x);
			ans[++m] = t;
		}
//		tranverse(root);
//		printf("\n");
	}
	for (i = 1; i <= m; ++i) {
		if (ans[i] == -1) {
			printf("N\n");
		}
		else if (ans[i] == -2) {
			printf("Y\n");
		}
		else printf("%d\n", ans[i]);
	}
	return 0;
}