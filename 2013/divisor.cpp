#include <bits/stdc++.h>
#include <climits>
using namespace std;
// Solved 23/2/2017

signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int m, n, q;
	cin >> m >> n >> q;

	vector<int> divisors[501];
	for (int i=0; i<=500; ++i){
		divisors[0].push_back(i);
	}
	for (int i=1; i<501; ++i){
		for (int j = 1; j<= i; ++j){
			if (i%j == 0){
				divisors[i].push_back(j);
			}
		}
	}
	int grid[m][n];
	for (int i=0; i<m; ++i){
		for (int j=0; j<n; ++j)
			cin >> grid[i][j];
	}
	int dp[m][n];
	dp[0][0] = grid[0][0];
	for (int i=0; i<m; ++i){
		for (int j=0; j<n; ++j){
			if (i == 0 && j==0) continue;
			dp[i][j] = INT_MIN;

			for (int k=0; k<divisors[i].size(); ++k){
				int cur = divisors[i][k];

				if (binary_search(divisors[j].begin(), divisors[j].end(), cur)){

					if (i - cur >=0 && j-cur >=0){
						dp[i][j] = max(dp[i][j], grid[i][j] + dp[i-cur][j-cur]);
					}
					if (i - cur >= 0){
						dp[i][j] = max(dp[i][j], grid[i][j] + dp[i-cur][j]);
					}
					if (j - cur >= 0){
						dp[i][j] = max(dp[i][j], grid[i][j] + dp[i][j-cur]);
					}
				}
			}
		}
	}

	while (q--){
		int r, c;
		cin >> r >> c;
		cout << dp[r][c] << endl;
	}

	return 0;
}