///Binary Indexed Tree / Fenwick Tree
///1-indexed

#define MN 100100

int bit[MN];

//Point Update
void update(int idx, int delta) {
    for(;idx < MN; idx += (idx & -idx)) bit[idx] += delta;
}

//Range Update
void update(int left, int right, int delta) {
    update(left, delta);
    update(right + 1, -delta);
}

//Point Query
int query(int idx) {
    int sum = 0;
    for(;idx > 0; idx -= (idx & -idx)) sum += bit[idx];
    return sum;
}

//Range Query
int query(int left, int right) {
    return query(right) - query(left - 1);
}
