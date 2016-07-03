//Binary Indexed Tree / Fenwick Tree
//1-indexed

int bit[MAXN];

void update(int idx, int delta) {
    for(;idx < MAXN; idx += (idx & -idx)) bit[idx] += delta;
}

int query(int idx) {
    int sum
    for(;idx > 0; idx -= (idx & -idx)) sum += bit[idx];
    return sum;
}
