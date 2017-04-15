#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
#define ii pair<int, int>
using namespace std;
int dfs_no[1000001];
int depth[1000001];
int size[1000001];
int no = 0;
int k = 0;
ii holder[1000001];
int p[1000001][25];
int power[26];
// Complexity O((N+Q)logN)

int dfs(int cur, vector<int> adj[], int dep){
	dfs_no[cur] = no;
	no++;
	depth[cur] = dep;
	int siz = 0;
	for (int i=0; i < adj[cur].size(); ++i){
		int th = dfs(adj[cur][i], adj, dep+1);
		siz += th;
	}
	size[cur] = siz;
	holder[k] = ii(dep, dfs_no[cur]); k++;
	return siz + 1;
}

signed main(){
	power[0] = 1;
	for (int i=1; i<= 25; ++i){
		power[i] = 2*power[i-1];
	}
	int n;
	scanf("%d", &n);
	int lim = log2(n);
	
	vector<int> adj[n+1];
	for (int i=1; i<=n; ++i){
		scanf("%d", &p[i][0]);
		adj[p[i][0]].push_back(i);
	}
	for (int i=0; i<adj[0].size(); ++i){
		dfs(adj[0][i], adj, 0);
	}
	sort(holder, holder+k);
	
	for (int i = 1; i <= lim; ++i){
		for (int j = 1; j<= n; ++j){
			if (p[j][i-1] == 0){
				p[j][i] = 0;
			}
			else {
				p[j][i] = p[p[j][i-1]][i-1];
			}
		}
	}
	int q;
	scanf("%d", &q);
	while (q--){
		int v, pa;
		scanf("%d %d", &v, &pa);
		int doori = pa;
		for (int i = lim; i>= 0; --i){
			if (power[i] > pa) continue;
			v = p[v][i];
			pa -= power[i];
			if (pa == 0){
				break;
			}
		}
		if (v != 0){
			int dist = depth[v] + doori;
			int ll = dfs_no[v];
			int ul = dfs_no[v] + size[v];
			int ans = upper_bound(holder, holder + k, ii(dist, ul)) - upper_bound(holder, holder + k, ii(dist, ll)) - 1;
			printf("%d\n", ans);
		}
		else {
			printf("0\n");
		}
	}
	return 0;
}