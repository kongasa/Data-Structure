#include<cstdio>

struct List_node {
	int num;                     //此人编号
	int id;                       //此人的团体编号
	List_node *next;
	List_node(int x, int y, List_node *n = NULL):num(x), id(y), next(n){}
};

struct Tree_node {
	int id;
	int t;                             //队列中同id的人的个数
	List_node *last;                      //属于团体id的人的最后一个人
	Tree_node *left, *right;
	Tree_node(int x, int m, List_node *pp, Tree_node *l = NULL, Tree_node *r = NULL):id(x), t(m), last(pp), left(l), right(r){}
};

List_node *head = NULL, *rear = NULL;
Tree_node *root = NULL;
int length = 0;                          //队列长度
int ids[2000001];
int ans[2000001]; 
int count = 0;

Tree_node *find(Tree_node *, int);
List_node *enqueue(int,int);
List_node *dequeue();
void tree_insert(Tree_node *&, int, List_node *);
List_node *list_insert(List_node *, int, int);
void destruct(Tree_node *);
void remove(Tree_node*&, int);

void print1() {
	List_node *p = head;
	printf("list:");
	while (p != NULL) {
		printf("%d ", p->num);
		p = p->next;
	}
	printf("\n");
}

void print2(Tree_node *p) {
	if (p->left != NULL) print2(p->left);
	printf("%d ", p->id);
	if (p->right != NULL) print2(p->right);
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &ids[i]);
	}

	int q;
	int command;
	int j = 1;
	scanf("%d", &q);
	for (i = 1; i <= q; ++i) {
		scanf("%d", &command);
		switch (command) {
		case 0:
			if (j <= n) {
				Tree_node *tmp1;
				tmp1 = find(root, ids[j]);
				if (tmp1 == NULL) {
					enqueue(j, ids[j]);                    //在队尾排队
					tree_insert(root, ids[j], rear);
				}
				else {
					tmp1->last = list_insert(tmp1->last, j, ids[j]);         //在tmp1->p后面插队, 返回插队的人
					++(tmp1->t);
//					printf("tmp->last->id:%d tmp->last->num:%d tmp1->id:%d\n",tmp1->last->id, tmp1->last->num, tmp1->id);
				}
				++j;
			}
			break;
		default:
			if (length == 0) {
				ans[++count] = -1;
			}
			else {
				List_node *tmp = dequeue();
				ans[++count] = tmp->num;
				remove(root, tmp->id);
				delete tmp;
			}
			break;
		}
		//if (root != NULL) {
		//	printf("root:%d\n", root->t);
		//}
		/*print1(); 
		printf("tree:");
		if (root != NULL) print2(root);
		printf("\n");*/
	}
	for (i = 1; i <= count; ++i) {
	    printf("%d\n", ans[i]);
	}

	List_node *tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
	destruct(root);
	return 0;
}

Tree_node *find(Tree_node *p, int x) {
	if (p == NULL) return NULL;
	else if (p->id == x) {
		return p;
	}
	else if (p->id > x) {
		return find(p->left, x);
	}
	else {
		return find(p->right, x);
	}
}

List_node *enqueue(int x, int id) {
	if (length == 0) {
		head = rear = new List_node(x, id);
		++length;
		return head;
	}
	else {
		rear->next = new List_node(x, id);
		rear = rear->next;
		++length;
		return rear;
	}
}

List_node *dequeue() {
	List_node *tmp = head;
	head = head->next;
	if (head == NULL) rear = head;
	--length;
	return tmp;
}

void tree_insert(Tree_node *&p, int x, List_node *y) {
	if (p == NULL) p = new Tree_node(x, 1, y);
	else if (p->id < x) {
		tree_insert(p->right, x, y);
	}
	else {
		tree_insert(p->left, x, y);
	}
}

List_node *list_insert(List_node *p, int j, int id) {
	++length;
	List_node *q = p->next;
	p->next = new List_node(j, id, q);
	if (p == rear) rear = p->next;
	return p->next;
}

void destruct(Tree_node *p) {
	if (p == NULL) return;
	if (p->left != NULL) destruct(p->left);
	if (p->right != NULL) destruct(p->right);
	delete p;
}

void remove(Tree_node *&p, int id) {
	if (p->id < id) {
		remove(p->right, id);
	}
	else if (p->id > id) {
		remove(p->left, id);
	}
	else if (p->t != 1) {
		--(p->t);
	}
	else if (p->left != NULL && p->right != NULL) {
		Tree_node *tmp = p->right;
		while (tmp->left != NULL) tmp = tmp->left;
		p->id = tmp->id;
		p->t = tmp->t;
		p->last = tmp->last;
		tmp->t = 1;
		remove(p->right, tmp->id);
	}
	else {
		Tree_node *tmp = p;
		p = (p->left != NULL) ? p->left : p->right;
		delete tmp;
	}
}