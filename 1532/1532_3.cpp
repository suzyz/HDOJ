// Network flow. Using optimized Dinic. （当前弧优化）
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;
const int maxn = 202;

int n, m, level[maxn], head[maxn], nxt[maxn<<1], curEdge[maxn];

int tot;
struct edge
{
	int u, v, w;	
} edges[maxn<<1];

void addEdge(int u, int v,int w) {
	edges[tot].u = u;
	edges[tot].v = v;
	edges[tot].w = w;
	nxt[tot] = head[u];
	head[u] = tot;
	++tot;
}

bool bfs() {
	queue<int> qu;
	memset(level, -1, sizeof(level));

	qu.push(1);
	level[1] = 0;

	while (!qu.empty()) {
		int u = qu.front();
		qu.pop();

		for (int i = head[u]; i != -1; i = nxt[i]) {
			int v = edges[i].v, w = edges[i].w;
			if (w > 0 && level[v] == -1) {
				level[v] = level[u]+1;

				qu.push(v);
			}
		}
	}

	return level[n] != -1;
}

int maxFlow(int u, int flow) {
	if (u == n)
		return flow;

	for (int i = curEdge[u]; i != -1; i = nxt[i]) {
		int v = edges[i].v, w = edges[i].w;

		if (w > 0 && level[v] == level[u]+1) {
			int curFlow = maxFlow(v, min(flow, w));

			if (curFlow > 0) {
				edges[i].w -= curFlow;
				edges[i^1].w += curFlow;

				return curFlow;
			}
		}
		curEdge[u] = nxt[i];
	}

	return 0;
}

int Dinic() {
	int ans = 0;

	while (bfs()) {

		for (int i = 1; i <= n; ++i)
			curEdge[i] = head[i];

		while (true) {
			int flow = maxFlow(1, INT_MAX);
			if (flow == 0)
				break;

			ans += flow;
		}
	}

	return ans;

}
int main() {

	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);

	while (cin >> m >> n) {

		tot = 0;
		memset(head, -1, sizeof(head));
		memset(nxt, -1, sizeof(nxt));
		
		int u, v, w;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			if (u == v)
				continue;

			addEdge(u, v, w);
			addEdge(v, u, 0);
		}
		
		cout << Dinic() << endl;
	}

	return 0;
}