#include <bits/stdc++.h>
using namespace std;
// To-Do:: Missed Something

signed main(){
	int n, k;
	cin >> n >> k;
	vector<int> adj[n+1];

	for (int i=0; i<n-1; ++i){
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	// tree rooted at 1
	int parent[n+1];
	queue<int> bfs;

	bfs.push(1);
	parent[1] = -1;
	vector<int> visited(n+1, false);
	vector<int> ordered(n);
	int i = 0;

	while (!bfs.empty()){
		int cur = bfs.front();
		bfs.pop();

		if (!visited[cur]){
			visited[cur] = true;

			ordered[i] = cur;
			i++;

			for (int i=0; i<adj[cur].size(); ++i){
				int to = adj[cur][i];

				if (to != parent[cur] && !visited[to]){
					parent[to] = cur;
					bfs.push(to);
				}
			}
		}
	}

	int dp1[n+1][k+1]; 
	int dp2[n+1][k+1];
	// dp1[i][j] -> number of components of length j having i as an end point
	// with the rest of the segments of the components
	// facing away from the root
	// dp2[i][j] -> similar except facing towards the root

	int count = 0;
	for (int w=n-1; w>=0; --w){
		i = ordered[w];
		// cout << "Visiting " << i << endl;
		dp1[i][1] = 1;
		dp1[i][0] = 1;

		for (int j=2; j<=k; ++j){
			dp1[i][j] = 0;
			for (int l=0; l<adj[i].size(); ++l){
				int to = adj[i][l];
				// cout << "Neighbour node " << to << endl;
				if (to != parent[i]){
					// cout << "Parent check failed. Incrementing by " << dp1[to][j-1] << endl;
					dp1[i][j] += dp1[to][j-1];
				}
			}
			// cout << "Value for j = " << j << " is " << dp1[i][j] << endl;
		}
		count += dp1[i][k];
	}

	for (int w= 0; w<n; ++w){
		i = ordered[w];
		dp2[i][1] = 1;
		// cout << "Visiting " << i << endl;

		for (int j=2; j<=k; ++j){
			dp2[i][j] = 0;
			// cout << "Parent = " << parent[i] << endl;

			if (parent[i] != -1){
				// cout << "Upward trail incremented by " << dp2[parent[i]][j-1] << endl;
				dp2[i][j] += dp2[parent[i]][j-1];
				dp2[i][j] += dp1[parent[i]][j-1] - dp1[i][j-2];
				// cout << "Downward trail incremented by " << dp1[parent[i]][j-1] - dp1[i][j-2] << endl;
			}
			// cout << "Value for j = " << j << " is " << dp2[i][j] << endl;

		}

		count += dp2[i][k];
	}

	cout << (count/2)%10243 << endl;
	return 0;
}