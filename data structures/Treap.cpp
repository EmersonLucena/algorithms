#include <bits/stdc++.h>

inline int my_rand() {
    return ((rand()<<16) ^ rand()) & 0x7fffffff;
}

struct node{
    int key;
    int prior, size;
    node * l, * r;

    node(int key) :
        key(key),
        prior(my_rand()),
        size(1),
        l(NULL),
        r(NULL) {}
};

typedef node* pnode;

int get_size(pnode t) {
    return (t) ? t->size : 0;
}

void update_size(pnode t) {
    if(t) t->size = get_size(t->l) + 1 + get_size(t->r);
}

///Kth element (0-indexed) [May be wrong with repeated elements]
int kth(pnode t, int k) {
    if(!t) return -1;

    int cur_k = get_size(t->l);

    if(cur_k == k) return t->key;
    else if(cur_k < k) return kth(t->r, k - cur_k - 1);
    else return kth(t->l, k);
}

///Elements equal to key ==> LEFT TREE
void split(pnode t, pnode &l, pnode &r, int key) {
    if(!t)
        l = r = NULL;

    else if(t->key <= key) {
        split(t->r, t->r, r, key);
        l = t;
    }

    else {
        split(t->l, l, t->l, key);
        r = t;
    }

    update_size(t);
}

///KEY stays on the LEFT tree
void split_by_index(pnode t, pnode &l, pnode &r, int key) {
    if(!t) {
        l = r = NULL;
        return;
    }

    int cur_key = get_size(t->l);

    if(key >= cur_key) {
        split(t->r,t->r,r,key - cur_key - 1);
        l = t;
    }

    else {
        split(t->l,l,t->l,key);
        r = t;
    }

    update_size(t);
}

///REMEMBER: (L->key) <= (R->key), for every(L, R) in (l, r)
void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) t = l?l:r;

    else if(l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    }

    else {
        merge(r->l, l, r->l);
        t = r;
    }

    update_size(t);
}

///Treap toString
void print(pnode t) {
    if(!t) return;

    print(t->l);
    printf("%d ", t->key);
    print(t->r);
}

///How many nodes with value key
int count(pnode t, int key) {
    pnode L, M, R;

    split(t, L, M, key);
    split(M, M, R, key + 1);

    int count_ = get_size(M);
    merge(M, M, R);
    merge(t, L, M);

    return count_;
}

void add(pnode &t, int key) {
    pnode toAdd = new node(key);
    pnode L, R;

    split(t, L, R, key);
    merge(L, L, toAdd);
    merge(t, L, R);
}

void erase(pnode &t, int key) {
    if(!t) return;

    if(t->key == key)
        merge(t,t->l,t->r);

    else
        erase(t->key > key ? t->l : t->r, key);

    update_size(t);
}

void eraseALL(pnode &t, int key) {
    pnode L, M, R;

    split(t, L, R, key);
    split(L, L, M, key - 1);

    merge(t, L, R);
}

int main() {
    int n,k;
    pnode root = NULL;

    printf("0 to stop, 1 X to add X, 2 X to erase X, 3 X to erase every X, 4 to kth element, 5 to print\n");

    scanf("%d",&n);
    while(n != 0) {

        if(n == 1) {
            scanf("%d",&k);
            add(root, k);
        }

        else if(n == 2) {
            scanf("%d",&k);
            erase(root,k);
        }

        else if(n == 3) {
            scanf("%d",&k);
            eraseALL(root,k);
        }

        else if(n == 4) {
            scanf("%d",&k);
            printf("KTH %d is %d\n", k, kth(root, k));
        }

        else if(n == 5) {
            print(root);
            puts("");
        }

        scanf("%d",&n);
    }

    puts("");
    print(root);
}
