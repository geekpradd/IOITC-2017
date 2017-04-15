#include <bits/stdc++.h>
#include <queue>
#include <cstdio>
using namespace std;
struct edge {
	int from; 
	int to;
	char cost;
};
struct h{
	int node;
	string path;
};

signed main(){
	int n, m;
	scanf("%d %d", &n, &m);
	int s, t;
	scanf("%d %d", &s, &t);
	vector<edge> adj[n+1];

	for (int i=0; i<m; ++i){
		int a, b;
		char c;
		scanf("%d %c %d", &a, &c, &b);
		edge v = {a, b, c};
		edge l = {b, a, c};
		adj[a].push_back(v);
		adj[b].push_back(l);
	}

	queue<h> q;
	string emp;
	h init = {s, emp};
	q.push(init);

	vector<string> so_far(n+1);
	vector<int> process;
	vector<short> visited(n+1, 0);
	vector<int> tentative(n+1);
	// 1 visited, 0 not visited, -1 under processing
	string ans;

	while (!q.empty()){
		h cur = q.front();
		if (cur.node == t){
			ans = cur.path;
			break;
		}
		visited[cur.node] = 1;
		q.pop();

		for (int i=0; i<adj[cur.node].size(); ++i){
			edge cc = adj[cur.node][i];
			string gg = cur.path;
			gg.push_back(cc.cost);

			if (visited[cc.to] == 0){
				process.push_back(cc.to);
				so_far[cc.to] = gg;
				visited[cc.to] = -1;
			}
			if (visited[cc.to] == -1){
				if (gg < so_far[cc.to]){
					so_far[cc.to] = gg;
				}
			}
		}
		if (q.empty()){
			for (int i=0; i<process.size(); ++i){
				int r = process[i];
				h p = {r, so_far[r]};
				visited[r] = 2;
				string em;
				so_far[r] = em;
				q.push(p);
			}
			process.clear();
		}
	}
	cout << ans << endl;
	return 0;
}