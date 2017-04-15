#include <bits/stdc++.h>
#include <cstdio>
#define INF 100000000
using namespace std;

int dfs_directed(int src, vector< vector<int> > &adj, vector<bool> &reached){
	reached[src] = 1;
	int lowest_reached = INF;
	for (int i = 0; i < adj[src].size(); ++i){
		int to = adj[src][to];
		if (!reached[to]){

		}
		else {

		}
	}
}

// Test Data is screwed up. Pending implementation
signed main(){
	int t;
	cin >> t;
	while (t--){
		int n, m;
		cin >> n >> m;
		vector< vector<int> > adj(n+1);
		while (m--){
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b); adj[b].push_back(a);
		}
		vector<int> marker(n+1, -1);
		queue<int> bfs; bfs.push(1);
		marker[1] = 0;
		while (!bfs.empty()){
			int cur = bfs.front();
			bfs.pop();
			for (int i=0; i<adj[cur].size(); ++i){
				int to = adj[cur][i];
				if (marker[to] == -1){
					marker[to] = marker[cur] + 1;
					bfs.push(to);
				}
			}
		}

		vector< vector<int> > tree(n+1);
		int parent[n+1]; parent[1] = -1;
		for (int i=2; i<=n; ++i){
			cin >> parent[i];
			tree[parent[i]].push_back(i);
		}

		bfs.push(1);
		vector<int> post_order(n-1);
		vector<int> mark(n+1, -1);
		mark[1] = 0;
		int pos = 1;
		int id = 0;

		while (!bfs.empty()){
			int cur = bfs.front();
			if (cur != 1){
				post_order[id] = cur; id++;	
			}
			bfs.pop();
			for (int i=0; i<tree[cur].size(); ++i){
				int to = tree[cur][i];
				if (to != parent[cur]){
					mark[to] = 1 + mark[cur];
					if (mark[to] != marker[to]){
						pos = 0;
						break;
					}
					bfs.push(to);
				}
			}
			if (pos == 0){
				break;
			}
		}
		if (pos == 0){
			cout << "NO" << endl; continue;
		}

		vector< vector<int> > dag(n+1);
		int level = marker[post_order[n-2]];

		for (int i=n-2; i>=0; --i){
			int cur = post_order[i];

			if (marker[cur] != level){
				level--;
				vector<bool> reached(n+1, 0);
				vector<int> reach_num(n+1);
				for (int j=1; j<=n; ++j){
					if (!reached[j]){
						dfs_directed(j, dag, reached, reach_num, 0);
					}
				}
			}
			if (pos == 0) break;
			

			int threshold = marker[parent[cur]];
			for (int j=0; j<adj[cur].size(); ++j){
				int to = adj[cur][j];
				if (marker[to] == threshold && to != parent[cur]){
					dag[parent[cur]].push_back(to);
				}
			}
		}
		if (pos == 0){
			cout << "NO" << endl; continue;
		}
		cout << "YES" << endl;
	}
}