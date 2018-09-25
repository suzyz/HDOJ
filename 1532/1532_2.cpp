// Network flow. Using plain Dinic.
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
const int maxn = 202;

int n, m, c[maxn][maxn], level[maxn];
bool vis[maxn];

bool bfs() {
	memset(level, -1, sizeof(level));

	queue<int> qu;
	qu.push(1);
	level[1] = 0;
	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();

		for (int i = 1; i <= n; ++i)
			if (c[cur][i] > 0 && level[i] == -1) {
				level[i] = level[cur] + 1;

				qu.push(i);
			}
	}

	return level[n] != -1;
}

int maxFlow(int u, int flow) {
	if (u == n)
		return flow;
	
	for (int i = 1; i <= n; ++i)
		if (c[u][i] > 0 && level[i] == level[u]+1) {
			int curFlow = maxFlow(i, min(flow, c[u][i]));
			if (curFlow > 0) {
				c[u][i] -= curFlow;
				c[i][u] += curFlow;
				return curFlow;
			}
		}

	return 0;
}

int Dinic() {
	int ans = 0;

	while (bfs()) {
		while (true) {
			int flow = maxFlow(1, INT_MAX);
			if (flow == 0)
				break;
 			
			ans += flow;
		}
		// printf("abc\n");
	}

	return ans;
}


int main() {

	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);

	while (cin >> m >> n) {

		memset(c, 0, sizeof(c));
		
		int u, v, w;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			if (u == v)
				continue;

			c[u][v] += w;
		}
		
		cout << Dinic() << endl;
	
	}

	return 0;
}