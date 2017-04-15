#include <bits/stdc++.h>
#define int long long
#include <climits>
using namespace std;
// To-Do

struct edge {
	int from;
	int to;
	int quality;
	int length;
};

bool compare(const edge &a, const edge &b){
	if (a.quality == b.quality){
		return a.length < b.length;
	}
	return a.quality > b.quality;
}

signed main(){
	int n, m;
	cin >> n >> m;
	vector<edge> adj[n];

	vector<edge> edges(m);

	for (int i=0; i<m; ++i){
		int f, t, q, l;
		cin >> f >> t >> q >> l;
		edge a = {f, t, q, l};
		edge b = {t, f, q, l};

		adj[f].push_back(a);
		adj[t].push_back(b);

		edges[i] = a;
	}

	int count = 0;
	vector<int> visited(n, false);

	stack<int> dfs;

	dfs.push(0);
	while (!dfs.empty()){
		int cur = dfs.top();
		dfs.pop();

		if (visited[cur] != true){
			visited[cur] = true;
			count++;

			for (int i=0; i<adj[cur].size(); ++i){
				edge t = adj[cur][i];

				if (!visited[t.to]){
					dfs.push(t.to);
				}
			}
		}
	}
	
	if (count==n){
		// We maintain a DSU structure and run 
		// a modified variant of Kruskal's
		sort(edges.begin(), edges.end(), compare);

		int component[n]; // tracks components of nodes
		for (int i=0; i<n; ++i) component[i] = i;

		vector<int> members[n];
		for (int i=0; i<n; ++i) members[i].push_back(i);

		vector<int> size(n);
		for (int i=0; i<n; ++i) size[i] = 1;

		int length = 0;
		int min_quality = INT_MAX;

		for (int i=0; i<m; ++i){
			edge cur = edges[i];

			int a = cur.from;
			int b = cur.to;
			
			if (component[a] != component[b]){
				min_quality = min(min_quality, cur.quality);
				length += cur.length;

				if (size[component[a]] < size[component[b]]){
					swap(a, b);
				}
				// merge b to a, a has larger size
				int orig = component[b];

				for (int j=0; j < size[component[b]]; ++j){
					// cout << "J is  " << j << endl;

					int e = members[component[b]][j];
					// cout << "Member e is " << e << endl;

					component[e] = component[a];
					members[component[a]].push_back(e);
				}
				size[component[a]] += size[orig];
				// cout << "Component a has size " << size[component[a]] << endl;
				size[orig] = 0;
			}
		}
		cout << min_quality << " " << length << endl;
	}
	else {
		cout << -1 << endl;
	}

	return 0;
}