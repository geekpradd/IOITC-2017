#include <bits/stdc++.h>
#define INF 100000000
#include <stdio.h>
#define ii pair<int, int>
using namespace std;
int n, m;
int visited[10001];
int dfs_num[10001];
int baap[10001];
int special[10001];
int mark[100001];

int dfs(int src, vector<ii> adj[], int dist, int edge_id, int parent){
	visited[src] = 1;
	dfs_num[src] = dist;
	baap[src] = parent; 
	int min_reach = INF;

	for (int i=0; i<adj[src].size(); ++i){
		int to = adj[src][i].first;
		if (visited[to]){
			if (edge_id != adj[src][i].second){
				min_reach = min(min_reach, dfs_num[to]);
			}
		}
		else {
			int up = dfs(to, adj, dist + 1, adj[src][i].second, src);
			mark[adj[src][i].second] = 2;
			if (up > dist){
				mark[adj[src][i].second] = 1;
			}
			min_reach = min(min_reach, up);
		}
	}

	return min_reach;
}

signed main(){
	scanf("%d %d", &n, &m);
	vector<ii> adj[n+1];
	ii edges[m];

	for (int i=0; i<m; ++i){
		int x, y; 
		scanf("%d %d", &x, &y);
		adj[x].push_back(ii(y, i));
		adj[y].push_back(ii(x, i));
		edges[i] = ii(x, y);
	}
	dfs(1, adj, 1, -1, -1);
	queue<ii> bfs;
	bfs.push(ii(1, 0)); // bfs is done on the dfs spanning tree
	
	vector<int> post_order(n);
	int k = 0;
	while (!bfs.empty()){
		ii current = bfs.front();
		bfs.pop();
		int cur = current.first, acum = current.second;
		special[cur] = acum;
		post_order[k] = cur; k++;

		for (int i=0; i<adj[cur].size(); ++i){
			int to = adj[cur][i].first, id = adj[cur][i].second;
			if ( (mark[id] == 1 || mark[id] == 2) && to != baap[cur]){
				bfs.push(ii(to, acum + (mark[id] == 1) ));
			}
		}
	}
	// for (int i=0; i<m; ++i){
	// 	cout << "Edge from " << edges[i].first << " to " << edges[i].second << endl;
	// 	cout << " Status " << mark[i] << endl;
	// }

	vector<int> global(3); global[0] = 0; global[1] = -INF; global[2] = -INF;
	vector<ii> pairs(n);
	for (int i=n-1; i>=0; --i){
		int current = post_order[i];
		// cout << "At " << current << endl;

		ii pair_1 = ii(special[current], -1*current);
		ii pair_2 = ii(special[current], -1*current);
		// cout << "At node " << current << " " << pair_1.first << " " << pair_1.second << endl;

		for (int j=0; j<adj[current].size(); ++j){
			int to = adj[current][j].first, id = adj[current][j].second;
			if ((mark[id] == 1 || mark[id] == 2) && to != baap[current]){
				ii delta = pairs[to];
				if (delta > pair_1){
					pair_2 = pair_1; pair_1 = delta;
				}
				else if (delta > pair_2){
					pair_2 = delta;
				}
			}
		}

		vector<int> ans(3); ans[0] = pair_1.first + pair_2.first - 2*special[current];
		ans[1] = (pair_1.second > pair_2.second ? pair_1.second : pair_2.second);
		ans[2] = (pair_1.second < pair_2.second ? pair_1.second : pair_2.second);

		// cout << "At node " << current << " " << pair_1.first << " " << pair_1.second << endl;
		global = max(global, ans);
		pairs[current] = pair_1;

	}
	cout << (-1)*global[1] << " " << (-1)*global[2] << endl;
	return 0;
}