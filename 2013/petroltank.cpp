#include <bits/stdc++.h>
#include <cstdio>
#define vi vector<int>
#define ii pair<int, int>
using namespace std;

void dfs(int src, vector<ii> adj[], vector<vi> &parent, vector<vi> &cost, vi &depth){
	for (int i=0; i<adj[src].size(); ++i){
		int to = adj[src][i].first;

		if (to != parent[src][0]){
			parent[to][0] = src;
			cost[to][0] = adj[src][i].second;
			depth[to] = depth[src] + 1;

			dfs(to, adj, parent, cost, depth);
		}
	}
}

class DSU {
private:
	vi p, rank;
public:
	DSU(int n){
		p.assign(n, 0); rank.assign(n, 0);
		for (int i=0; i<n; ++i){
			p[i] = i;
		}
	}
	int find(int i){
		return (p[i] == i ? i : p[i] = find(p[i]));
	}
	void merge(int a, int b){
		int x = find(a), y = find(b);
		if (rank[x] < rank[y]){
			p[x] = y;
		}
		else {
			p[y] = x;
			if (rank[x] == rank[y]) rank[x]++;
		}
	}
};

signed main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector< pair<int, ii> > edges(m);

	for (int i=0; i<m; ++i){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		x--; 
		y--;
		edges[i] = make_pair(z, ii(x, y));
	}

	sort(edges.begin(), edges.end());
	DSU set_union(n);
	vector<ii> adj[n];

	for (int i=0; i<m; ++i){
		int a = edges[i].second.first, b = edges[i].second.second;
		if (set_union.find(a) != set_union.find(b)){
			set_union.merge(a, b);
			adj[a].push_back(ii(b, edges[i].first));
			adj[b].push_back(ii(a, edges[i].first));
		}
	}
	// we have a tree now. We will set up LCA now.
	int up = log2(n) + 1;

	vector<vi> parent(n, vi(up));
	vi depth(n);
	depth[0] = 0;
	parent[0][0] = -1;
	vector<vi> cost(n, vi(up));
	dfs(0, adj, parent, cost, depth);

	for (int i=1; i<up; ++i){
		for (int j=0; j<n; ++j){
			if (pow(2, i) > depth[j]) {
				parent[j][i] = -1;
				cost[j][i] = -1;
			}
			else {
				parent[j][i] = parent[parent[j][i-1]][i-1];
				cost[j][i] = max(cost[j][i-1], cost[parent[j][i-1]][i-1]);
			}
		}
	}

	int q;
	scanf("%d", &q);

	while (q--){
		int a, b;
		scanf("%d %d", &a, &b);

		if (a==b){
			printf("0\n"); continue;
		} 
		a--;
		b--;
		int x = a, y = b;
		int lca = -1;

		if (depth[a] != depth[b]){
			if (depth[a] < depth[b]) swap(a, b);
			for (int i=up; i>=0; --i){
				if (depth[a] - pow(2, i) < depth[b]) continue;
				a = parent[a][i];
				if (depth[a] == depth[b]) break;
			}
			if (a == b) lca = b;
		}

		if (lca == -1){
			for (int i=up; i>=0; --i){
				if (parent[a][i] == parent[b][i]) continue;
				a = parent[a][i];
				b = parent[b][i];
			}
			lca = parent[a][0];
		}
		int mini = -1;

		if (lca != -1){
			for (int i=up; i>=0; --i){
				if (depth[x] - pow(2, i) < depth[lca]) continue;
				mini = max(mini, cost[x][i]);
				x = parent[x][i];
			}

			for (int i=up; i>=0; --i){
				if (depth[y] - pow(2, i) < depth[lca]) continue;
				mini = max(mini, cost[y][i]);
				y = parent[y][i];
			}
		}

	
		printf("%d\n", mini);
	}


	return 0;
}