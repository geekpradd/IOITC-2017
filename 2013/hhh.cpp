#include <bits/stdc++.h>
#include <queue>
#include <cstdio>
using namespace std;
struct edge {
	int from; 
	int to;
	int cost;
};
typedef struct  {
	int node;
	int level;
	vector<int> path;
} h;
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
		edge v = {a, b, c - 'a'};
		edge l = {b, a, c - 'a'};
		adj[a].push_back(v);
		adj[b].push_back(l);
	}
	queue< h > q;
	vector<int> emp;
	h init = {s, 0, emp};
	q.push(init);
	vector<int> so_far[n+1];
	vector<int> process;
	vector<int> visited(n+1, 0);
	// 1 visited, 0 not visited, -1 under processing
	vector<int> ans;
	int l;

	while (!q.empty()){
		h cur = q.front();
		if (cur.node == t){
			l = cur.level;
			ans = cur.path;
		}
		visited[cur.node] = 1;
		q.pop();
		// cout << "Visited " << cur.node << endl;

		for (int i=0; i<adj[cur.node].size(); ++i){
			edge cc = adj[cur.node][i];
			vector<int> gg = cur.path;
			gg.push_back(cc.cost);

			// cout << "Processing path to " << cc.to << endl;

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
			// cout << "Queue emptied" << endl;
			for (int i=0; i<process.size(); ++i){
				int r = process[i];
				// cout << "Adding " << r << endl;
				h p = {r, cur.level + 1, so_far[r]};
				visited[r] = 2;
				vector<int> khali;
				so_far[r] = khali;
				q.push(p);
			}
			process.clear();
		}
	}

	for (int i=0; i<ans.size(); ++i){
		char cur = ans[i] + 'a';
		printf("%c", cur);
	}
	printf("\n");
	return 0;
}