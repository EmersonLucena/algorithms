using namespace std;
typedef long long ll;

struct treap {

    struct node {
        ll key, size, prior, sum, lazy;
        node *l, *r;

        node(ll key):
            key(key), size(1), prior(my_rand()), sum(key), lazy(0),
            l(NULL), r(NULL) {}

        int my_rand() {
            return ((rand()<<16) ^ rand()) & 0x7fffffff;
        }

        ~node() {
            delete l;
            delete r;
        }
    };
    typedef node* pnode;

    pnode root = NULL;

    ll get_size(pnode t) {
        return (t) ? t->size : 0;
    }

    void update_size(pnode t) {
        if(t) t->size = 1 + get_size(t->l) + get_size(t->r);
    }

    void push_lazy(pnode t) {
        if(t && t->lazy) {

        }
    }

    ll get_sum(pnode t) {
        return (t) ? t->sum : 0;
    }

    void update_sum(pnode t) {
        if(t) t->sum = t->key + get_sum(t->l) + get_sum(t->r);
    }

    // Kth element (0-indexed) [Careful with repeated elements]
    ll kth(pnode t, int k) {
        if(!t) return -1;
        int cur_k = get_size(t->l);
        if(cur_k == k) return t->key;
        else if(cur_k < k) return kth(t->r, k - cur_k - 1);
        else return kth(t->l, k);
    }

    // Elements equal to key => LEFT TREE
    void split(pnode t, pnode &l, pnode &r, ll key) {
        if(!t) {
          l = r = NULL;
          return;
        }
        push_lazy(t);

        if(t->key <= key) {
            split(t->r, t->r, r, key);
            l = t;
        } else {
            split(t->l, l, t->l, key);
            r = t;
        }

        update_size(t);
        push_lazy(t);
        update_sum(t);
    }

    // KEY stays on the LEFT tree
    void split_by_index(pnode t, pnode &l, pnode &r, int key) {
        if(!t) {
            l = r = NULL;
            return;
        }
        push_lazy(t);

        int cur_key = get_size(t->l);
        if(key >= cur_key) {
            split_by_index(t->r,t->r,r,key - cur_key - 1);
            l = t;
        } else {
            split_by_index(t->l,l,t->l,key);
            r = t;
        }

        update_size(t);
        push_lazy(t);
        update_sum(t);
    }

    // (L->key) <= (R->key), for every(L, R) in (l, r)
    void merge(pnode &t, pnode l, pnode r) {
        push_lazy(l);
        push_lazy(r);

        if(!l || !r) t = l?l:r;
        else if(l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }

        update_size(t);
        push_lazy(t);
        update_sum(t);
    }

    // How many nodes with value key
    int count(pnode t, ll key) {
        pnode L, M, R;

        split(t, L, M, key);
        split(M, M, R, key + 1);

        int count_ = get_size(M);
        merge(M, M, R);
        merge(t, L, M);

        return count_;
    }

    void add(pnode &t, ll key) {
        pnode toAdd = new node(key);
        pnode L, R;

        split(t, L, R, key);
        merge(L, L, toAdd);
        merge(t, L, R);
    }

    void add_implicit(pnode &t, ll key, int pos) {
        pnode toAdd = new node(key);
        pnode L, R;

        split_by_index(t, L, R, pos - 1);
        merge(L, L, toAdd);
        merge(t, L, R);
    }

    void erase(pnode &t, ll key) {
        if(!t) return;
        if(t->key == key) merge(t,t->l,t->r);
        else erase(t->key > key ? t->l : t->r, key);
        update_size(t);
    }

    void eraseALL(pnode &t, ll key) {
        pnode L, M, R;
        split(t, L, R, key);
        split(L, L, M, key - 1);
        merge(t, L, R);
    }

    void erase_implicit(pnode &t, int pos) {
        pnode L, M, R;
        split_by_index(t, L, R, pos);
        split_by_index(L, L, M, pos - 1);
        merge(t, L, R);
    }

    void print(pnode t) {
        if(!t) return;
        print(t->l);
        printf("%d ", t->key);
        print(t->r);
    }

    ~treap() {
        delete root;
    }
};
