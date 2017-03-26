#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
#define int long long
#define ii pair<int, int>
using namespace std;
int t = 0;
int weights[100001];
int height[100001];
int size[100001];
int timer[100001];
int pre_ans[100001];

typedef struct {
	int v;
	int a;
	int d;
} custom;

int dfs(int src, vector<int> adj[], int father){
	timer[src] = t; t++;
	height[src] = (father > 0 ? height[father] + 1 : 0);
	size[src] = 0;
	pre_ans[src] = (father > 0 ? pre_ans[father] + weights[src] : weights[src]);
	for (int i=0; i<adj[src].size(); ++i){
		int to = adj[src][i];
		if (to != father){
			size[src] += dfs(to, adj, src);
		}
	}
	return 1 + size[src];
}

void update(int cur, vector<int> adj[], vector<ii>& future, int a, int d, int passed, int father){
	a += future[cur].first; d += future[cur].second;
	future[cur].first = 0; future[cur].second = 0;

	pre_ans[cur] += passed + a;

	for (int i=0; i < adj[cur].size(); ++i){
		int to = adj[cur][i];
		if (to != father){
			update(to, adj, future, a+d, d, passed+a, cur);
		}
	}
}

signed main(){
	int n, q;
	scanf("%d %d", &n, &q);
	vector<int> adj[n+1];

	for (int i=0; i<n-1; ++i){
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i=1; i<=n; ++i){
		scanf("%d", &weights[i]);
	} 

	dfs(1, adj, -1);

	int block_size = sqrt(q) + 1;

	vector<ii> future(n+1, ii(0, 0));
	vector<custom> queries;

	int j = 0;
	for (int i=0; i<q; ++i, ++j){
		if (j == block_size){
			j = 0;
			update(1, adj, future, 0, 0, 0, -1);
			queries.clear();
		}
		int code;
		scanf("%d", &code);
		if (code == 1){
			int a, b, c;
			scanf("%d", &a, &b, &c);
			custom current = {a, b, c};
			queries.push_back(current);
			future[a].first += b; future[a].second += c;
		}
		if (code == 2){
			int v;
			scanf("%d", &v);
			int base_ans = pre_ans[v];

			for (int k=0; k<queries.size(); ++k){
				int p = queries[k].v, a = queries[k].a, d = queries[k].d;
				
				if (timer[v] >= timer[p] && timer[v] <= timer[p] + size[p]){
					int difference = height[v] - height[p] + 1;
					base_ans += (difference*(2*a + (difference - 1)*d))/2;
				}
			}
			printf("%d\n", base_ans);
		}
	}
	return 0;
}