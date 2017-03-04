#include <bits/stdc++.h>
#define MODL 1000000007
#define ii pair<int, int>
using namespace std;

// Getting WAs in a few cases. Check for possible bugs.

vector<int> *adj;
int *p;
int *dist;
int *child;
int *a;
int *b;
int n;
inline int mod(int n){
	int x = n%MODL;
	if (x < 0){
		x = x + MODL;
	}
	return x;
}
inline int c2(int n){
	if (n%2==0){
		return mod(mod(n/2) * mod(n-1));
	}
	else {
		return mod(mod((n-1)/2) * mod(n));
	}
}

ii dfs(int cur, int d){
	dist[cur] = d;
	child[cur] = 0;
	a[cur] = 0;

	if (adj[cur].size() == 0){
		return ii(1, 0);
	}
	int v = 0;
	
	for (int i=0; i<adj[cur].size(); ++i){
		ii res = dfs(adj[cur][i], d+1);
		child[cur] = mod(child[cur] + res.first);
		v = mod(v+res.second);
	}
	a[cur] = mod(c2(child[cur]) - v);
	return ii(mod(child[cur] + 1), c2(child[cur]+1));
}

ii dfs2(int cur){
	b[cur] = 0;
	if (adj[cur].size() == 0){
		return ii(a[cur], 1);
	}

	int x = 0;
	int y = mod(a[cur] - c2(child[cur]));
	
	for (int i=0; i<adj[cur].size(); ++i){
		ii res = dfs2(adj[cur][i]);
		x = mod(x + res.first);
		int z = mod(y + c2(mod(child[cur] - res.second))+ c2(res.second));
		b[cur] = mod(b[cur] + z*(res.first));
	}
	b[cur] = mod(b[cur]*(dist[cur]%MODL));

	return ii(mod(a[cur] + x), mod(child[cur]+1));
}

signed main(){
	cin >> n;
	adj = new vector<int>[n+1];
	p = new int[n+1];
	dist = new int[n+1];
	child = new int[n+1];
	a = new int[n+1];
	b = new int[n+1];

	for (int i=1; i<=n; ++i){
		cin >> p[i];
		adj[p[i]].push_back(i);
	}
	dfs(0, 0);
	dfs2(0);

	int ans = 0;
	for (int i=0; i<=n; ++i){
		ans = mod(ans + b[i]);
	}
	cout << ans << endl;
	return 0;

}