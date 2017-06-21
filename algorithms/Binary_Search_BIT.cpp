
/* Last index pos where query(pos) <= k
 * prefix(4) => 1 2 3 4 4 {4} 5 6
 * prefix(4) => 0 1 1 2 2 {2} 5 6
 * usage: prefix(k, bit, MAXN)
 * 0 <= pos < N
 * */
int prefix(int k, int bit[], int N) {
    int pos = 0, pot = 0;
    while((1 << (pot+1)) <= N) pot++;
    while(pot >= 0) {
        int size = (1 << pot);
        if(pos + size < N && bit[pos + size] <= k) {
            k -= bit[pos + size];
            pos += size;
        }
        pot--;
    }
    return pos;
}
