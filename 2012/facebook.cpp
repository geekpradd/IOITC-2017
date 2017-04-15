#include <bits/stdc++.h>
#include <cstring>
#include <queue>
#define iii pair<int, pair<int, int> >
#define iiii pair< pair<int, int>, pair<int, int> >
#define ii pair<int, int>
#define INF 100000000
using namespace std;

signed main(){
	int n, m, q;
	cin >> n >> m >> q;
	vector<iii> adj[n+1];
	int final[m];

	for (int i=0; i<m; ++i){
		int a, b, p;
		cin >> a >> b >> p;
		adj[a].push_back(iii(b, ii(p, i)));
		adj[b].push_back(iii(a, ii(p, i)));
		final[i] = -1;
	}

	vector<int> tree[n+1];
	int parent[n+1];
	int dist[n+1];
	for (int i=0; i<n; ++i){
		dist[i] = INF;
	}
	int linker[n+1];
	parent[0] = -1;

	priority_queue<iiii, vector<iiii>, greater<iiii> > djk;
	djk.push(iiii(ii(0, -1), ii(0, -1)));
	dist[0] = 0;
	while (!djk.empty()){
		iiii top = djk.top();
		djk.pop();
		int node = top.second.first;

		if (top.first.first <= dist[node]){
			linker[node] = top.first.second;
			parent[node] = top.second.second;
			tree[top.second.second].push_back(node);
			for (int i=0; i < adj[node].size(); ++i){
				int to = adj[node][i].first;
				int len = adj[node][i].second.first;
				int id = adj[node][i].second.second;

				if (dist[to] > dist[node] + len){
					dist[to] = dist[node] + len;
					djk.push(iiii(ii(dist[to], id), ii(to, node)));
				}
			}
		}
	}
	
	vector<int> post_order(n);
	int k = 0;
	queue<int> bfs;
	bfs.push(0);
	while (!bfs.empty()){
		int cur = bfs.front();
		bfs.pop();
		post_order[k] = cur; k++;
		for (int i=0; i<tree[cur].size(); ++i){
			int to = tree[cur][i];
			bfs.push(to);
		}
	}
	int dp[n]; 
	dp[0] = INF;
	for (int i=n-1; i>0; --i){
		int node = post_order[i];
		dp[node] = INF;
		for (int j=0; j<adj[node].size(); ++j){
			int to = adj[node][j].first;
			int weight = adj[node][j].second.first;
			if (to == parent[node]){

			}
			else if (parent[to] == node){
				dp[node] = min(dp[node], weight + dp[to]);
			}
			else {
				dp[node] = min(dp[node], weight + dist[to]);
			}
		}
		// cout << "dp[" << node << "] = " << dp[node] << endl;
	}
	int child = INF;
	int cur = n-1;
	int ans;

	while (cur != 0){
		int d_ans = INF;
		for (int j=0; j<adj[cur].size(); ++j){
			int to = adj[cur][j].first;
			int weight = adj[cur][j].second.first;
			if (to == parent[cur]){

			}
			else if (parent[to] == cur){
				if (to == child){
					d_ans = min(d_ans, ans);
				}
				else {
					d_ans = min(d_ans, weight + dp[to]  + dist[n-1] - dist[cur]);
				}
			}
			else {
				d_ans = min(d_ans, weight + dist[to] + dist[n-1] - dist[cur]);
			}
		}
		ans = d_ans;
		final[linker[cur]] = ans;
		child = cur;
		cur = parent[cur];
	}
	while (q--){
		int i;
		cin >> i;
		if (final[i] == INF){
			cout << -1 << endl;
		}
		else if (final[i] == -1){
			cout << dist[n-1] << endl;
		}
		else {
			// cout << "i = " << i << endl;
			cout << final[i] << endl;
		}
	}
	return 0;
}