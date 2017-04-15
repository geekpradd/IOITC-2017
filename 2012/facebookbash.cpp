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
	vector<ii> adj[n+1];
	ii final[m];

	for (int i=0; i<m; ++i){
		int a, b, p;
		cin >> a >> b >> p;
		adj[a].push_back(ii(b, p));
		adj[b].push_back(ii(a, p));
		final[i] = ii(a, b);
	}
	while (q--){
		int id;
		cin >> id;
		ii disabled = final[id];
		int dist[n+1];
		for (int i=0; i<n; ++i){
			dist[i] = INF;
		}
		priority_queue<ii, vector<ii>, greater<ii> > djk;
		djk.push(ii(0, 0));
		dist[0] = 0;
		while (!djk.empty()){
			ii top = djk.top();
			djk.pop();
			int node = top.second;
			if (top.first <= dist[node]){
				for (int i=0; i < adj[node].size(); ++i){
					int to = adj[node][i].first;
					int len = adj[node][i].second;
					if (node == disabled.first && to == disabled.second){

					}
					else if (node == disabled.second && to == disabled.first){

					}
					else if (dist[to] > dist[node] + len){
						dist[to] = dist[node] + len;
						djk.push(ii(dist[to], to));
					}
				}
			}
		}
		cout << dist[n-1] << endl;
	}
	return 0;
}
