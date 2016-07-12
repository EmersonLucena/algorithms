/// Always remember to initialize parent[] and rank[]
#define MN 100100

int parent[MN], rank[MN];

int read(int node) {
    if(node == parent[node]) return node;
    return parent[node] = read(parent[node]);
}

void join(int a, int b) {
    a = read(a);
    b = read(b);

    if(rank[a] > rank[b]) {
        parent[b] = a;
        rank[a]++;
    }

    else {
        parent[a] = b;
        rank[b]++;
    }
}

int main() {
    for(int i = 0; i < MN; i++) {
        rank[i] = 0;
        parent[i] = i;
    }
    return 0;
}
