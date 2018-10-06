#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int size;
	int data;
	node *left, *right;
	node *parent;
	int time;
	node(int x = 0, int t = 1, int s = 1, node *p = NULL, node *l = NULL, node *r = NULL) {
		left = l;
		right = r;
		parent = p;
		data = x;
		size = s;
		time = t;
	}
};

node t[222223];
node *root = NULL;
int num;

int Size(node *p) {
	if (p == NULL) return 0;
	else return p->size;
}

void LL(node *&p, node *father) {
	int flag;
	if (father != NULL) {
		if (father->left == flag) flag = 0;
		else flag = 1;
	}
	node *tmp = p->left;
	p->left = tmp->right;
	if (tmp->right != NULL) tmp->right->parent = p;
	p->parent = tmp;
	tmp->right = p;
	tmp->parent = father;
	p->size = Size(p->left) + Size(p->right) + p->time;
	tmp->size = Size(p) + Size(tmp->left) + tmp->time;
	p = tmp;
	if (father != NULL) {
		if (flag == 0) father->left = p;
		else father->right = p;
	}
}

void RR(node *&p, node *father) {
	int flag;
	if (father != NULL) {
		if (father->left == flag) flag = 0;
		else flag = 1;
	}
	node *tmp = p->right;
	p->right = tmp->left;
	if (tmp->left != NULL) tmp->left->parent = p;
	p->parent = tmp;
	tmp->left = p;
	tmp->parent = father;
	p->size = Size(p->left) + Size(p->right) + p->time;
	tmp->size = Size(p) + Size(tmp->left) + tmp->time;
	p = tmp;
	if (father != NULL) {
		if (flag == 0) father->left = p;
		else father->right = p;
	}
}

void splay(node *p, node *target) {
	node *f = p->parent;
	node *gf;
	while (f != target && f->parent != target) {
		gf = f->parent;
		if (gf->left == f) {
			if (f->left == p) {
				LL(gf, gf->parent);
				LL(gf, gf->parent);
			}
			else {
				RR(f, gf);
				LL(gf, gf->parent);
			}
		}
		else {
			if (f->left == p) {
				LL(f, gf);
				RR(gf, gf->parent);
			}
			else {
				RR(gf, gf->parent);
				RR(gf, gf->parent);
			}
		}
		p = gf;
		f = p->parent;
	}
	if (f != target) {
		if (f->left == p) {
			LL(f);
		}
		else RR(f);
	}
	if (target == NULL) root = p;
}

void insert(node *&p, int x, node *father) {
	if (p == NULL) {
		p = &t[num++];
		p->data = x;
		p->size = p->time = 1;
		p->parent = father;
	}
	else if (p->data > x) {
		insert(p->left, x, p);
		p->size = Size(p->left) + Size(p->right) + p->time;
		splay(p, NULL);
	}
	else if (p->data < x) {
		insert(p->right, x, p);
		p->size = Size(p->left) + Size(p->right) + p->time;
		splay(p, NULL);
	}
	else {
		++p->time;
		++p->size;
	}
}

void erase(node *&p, int x, node *father) {
	if (p == NULL) return;
	if (p->data > x) {
		erase(p->left, x, p);
	}
	else if (p->data < x) {
		erase(p->right, x, p);
	}
	else {
		splay(p, NULL);
		node *tmp = root->left;
		if (tmp == NULL) {

		}
	}
}

int main() {

}