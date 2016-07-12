/// Segment Tree implemented for Sums. Point Update, Range Query
#define MN 100100

int tree[4 * MN], arr[MN];

void create(int node, int a, int b) {
    if(a == b) {
        tree[node] = arr[a];
        return;
    }

    create(node*2, a, (a + b)/2);
    create(node*2 + 1, (a+b)/2 + 1, b);

    tree[node] = tree[node*2] + tree[node*2 + 1];
}

void update(int node, int a, int b, int x, int delta) {
    if(x > b || x < a) return;

    if(a == b) {
        tree[node] += delta;
        return;
    }

    update(node*2, a, (a+b)/2, x , delta);
    update(node*2 + 1, (a+b)/2 + 1, b, x , delta);

    tree[node] = tree[node*2] + tree[node*2 + 1];
}

int query(int node, int a, int b, int x, int y) {
    if(y < a || x > b) return 0;

    if(x <= a && b <= y) return tree[node];

    return query(node*2, a, (a+b)/2, x, y)
            + query(node*2 + 1, (a+b)/2 + 1, b, x, y);
}
