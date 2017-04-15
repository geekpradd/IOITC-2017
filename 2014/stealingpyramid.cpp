#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

void dfs(vector<int> adj[], int src, int count, vector<int> &comp){
	comp[src] = count;
	for (int i=0; i<adj[src].size(); ++i){
		int to = adj[src][i];
		if (comp[to] == -1){
			dfs(adj, to, count, comp);
		}
	}
}

signed main(){
	int n;
	scanf("%d", &n);
	int heights[n+1];
	for (int i=1; i<=n; ++i){
		scanf("%d", &heights[i]);
	}
	
	vector<int> adj[n+1];
	for (int i=1; i<=n; ++i){
		int cur; 
		scanf("%d", &cur);
		if (i + cur <= n){
			adj[i+cur].push_back(i);
			adj[i].push_back(i+cur);
		}
		if (i - cur > 0){
			adj[i-cur].push_back(i);
			adj[i].push_back(i-cur);
		}
	}

	vector<int> components(n+1, -1);
	int current = 0;
	for (int i=1; i<=n; i++){
		if (components[i] == -1){
			dfs(adj, i, current, components);
			current++;
		}
	}
	bool pass = true;
	for (int i=1; i<=n; ++i){
		if (components[i] != components[heights[i]]){
			pass = false;
			break;
		}
	}

	if (pass){
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}

	return 0;
}