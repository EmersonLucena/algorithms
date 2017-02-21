//Shortest Path Faster Algorithm

const int INF = 1000000000;

using namespace std;

int dist[MAXN];
bool inqueue[MAXN];
vector<pair<int,int> > adj[MAXN];

void SPFA(int node) {
	for(int i=0;i<MAXN;i++)
		dist[i] = INF;

	dist[node] = 0;

	queue <int> fila;
	fila.push(node);
	inqueue[node] = 1;

	while(!fila.empty()) {
		int u = fila.front();
		fila.pop();
		inqueue[u] = 0;

		for(int i=0; i<adj[u].size(); i++) {
			int v = adj[u][i].first;
			ll cost = adj[u][i].second;

			if(dist[u] + cost < dist[v]) {
				dist[v] = dist[u] + cost;
				if(!inqueue[v]) {
					fila.push(v);
					inqueue[v] = 1;
				}
			}
		}
	}
}
