#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;
const int maxn = 202;

int n, m, c[maxn][maxn], pre[maxn];
bool vis[maxn];

bool bfs() {
	queue<int> qu;
	memset(vis, 0, sizeof(vis));

	qu.push(1);
	vis[1] = true;

	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();

		// printf("cur:%d\n", cur);

		for (int i = 1; i <= n; ++i)
			if (c[cur][i] > 0 && !vis[i]) {	
				vis[i] = true;
				pre[i] = cur;

				if (i == n)
					return true;

				qu.push(i);
			}
	}

	return false;
}

int EK() {

	int ans = 0;

	while (bfs()) {
		int minf = INT_MAX;

		int i = n;
		while (i != 1) {
			minf = min(minf, c[pre[i]][i]);

			i = pre[i];
		}

		ans += minf;

		i = n;
		while (i != 1) {
			c[pre[i]][i] -= minf;
			c[i][pre[i]] += minf;

			i = pre[i];
		}
	}

	return ans;
}

int main() {

	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);

	while (cin >> m >> n) {

		memset(c, 0, sizeof(c));
		
		int u, v, w;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			if (u == v)
				continue;

			c[u][v] += w;
		}
		
		cout << EK() << endl;
	
	}

	return 0;
}