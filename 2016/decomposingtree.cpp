#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
// Solved. Works correctly with the few
// test cases I've checked.
// Yay! I'm getting more pro __/\__
// Complexity O(N+Q)

vector< vector<int> > adj(100001);
int p[100001];
int s[100001];

int dfs(int src){
	int ret = (adj[src].size() % 2 ? (adj[src].size() + 1)/2 : adj[src].size()/2);

	for (int i=0; i<adj[src].size(); ++i){
		int temp = dfs(adj[src][i]);
		ret += temp + (adj[adj[src][i]].size() % 2 ? -1 : 0);
	}
	return ret;
}

signed main(){
	int n;
	scanf("%d", &n);
	p[1] = -1;
	for (int i=2; i<=n; ++i){
		cin >> p[i];
		adj[p[i]].push_back(i);
		s[p[i]]++;
	}
	int q;
	scanf("%d", &q);
	int ans = dfs(1);
	printf("%d\n", ans);
	while (q--){
		int v, u;
		scanf("%d %d", &v, &u);

		if (s[p[v]] % 2 == 0){
			ans--;
		}
		s[p[v]]--;
		p[v] = u;
		s[u]++;
		if (s[u] % 2 == 0){
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}