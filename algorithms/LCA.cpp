//Lowest Common Ancestor using DP
//1-indexed
#include <algorithm>
#include <math.h>
#include <vector>

#define MN 100100

using namespace std;

int visit[MN], h[MN], dp[MN][20],N;
vector <int> adj[MN];

void dfs(int node) {
    visit[node] = 1;

    for(int i=0;i<adj[node].size();i++) {
        int v = adj[node][i];

        if(!visit[v]) {
            dp[v][0] = node;
            h[v] = h[node] + 1;
            dfs(v);
        }
    }
}

void build(int node) {
    dp[node][0] = node;

    for(int j = 1; (1 << j) <= N; j++)
        for(int i=1;i<=N;i++)
            dp[i][j] = dp[dp[i][j-1]][j-1];
}

int query(int a, int b) {
    if(h[a] > h[b]) swap(a,b);

    int lg;
    for(lg = 1;(1 << lg) <= h[a]; lg++);
    lg--;

    for(int i = lg; i >= 0; i--)
        if(h[dp[a][i]] >= h[b])
            a = dp[a][i];

    if(a == b) return a;

    for(int i = lg; i >= 0; i--) {
        if(dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }
    }

    return dp[a][0];
}
