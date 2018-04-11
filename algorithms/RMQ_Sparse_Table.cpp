//Range Minimum Query in N log N using sparse tables

#define MN 100100
#define LG 20 // > Log2 MN

using namespace std;
typedef long long ll;

ll N,a[MN],rmq[MN][LG]; // a[] is the initial array

void build() {
    for(int i=0;i<N;i++)
        rmq[i][0] = a[i];

    for(int j=1;(1 << j) <= N; j++)
        for(int i=0; i + (1 << j) <= N; i++)
            rmq[i][j] = min(rmq[i][j-1], rmq[i + (1 << (j-1))][j-1]);
}

ll query(int a, int b) {
    if(a > b) swap(a,b);
    int lg = __builtin_clz(1) - __builtin_clz(b - a + 1);

    return min(rmq[a][lg], rmq[b -(1 << lg)+1][lg]);
}
