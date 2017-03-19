#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

signed main(){
	int q;
	cin >> q;
	int n = 10000;
	int m = 40;
	int ***dp = new int**[n+1];
	int ***sum = new int**[n+1];
	int ***pref_sum = new int**[n+1];

	for (int i=1; i<=n; ++i){
		dp[i] = new int*[m+1], sum[i] = new int*[m+1];
		pref_sum[i] = new int*[m+1];
		for (int j=0; j<=m; ++j){
			dp[i][j] = new int[m+1], sum[i][j] = new int[m+1];
			pref_sum[i][j] = new int[m+1];
		}
	}

	// dp[n][m][p] = number of sequences of length n with first digit m such that all digits are from 1 to p
	// sum[n][m][p] = dp[n][1][p] + dp[n][2][p] ... dp[n][m][p]
	// pref_sum[n][m][p] = sum[n][1][p] + sum[n][2][p] .. sum[n][m][p]
	for (int j = 1; j<=m; ++j){
		sum[1][0][j] = 0;
		pref_sum[1][0][j] = 0;
		sum[2][0][j] = 0;
		pref_sum[2][0][j] = 0;

		for (int k = 1; k<j; ++k){
			dp[1][k][j] = 1;
			sum[1][k][j] = (dp[1][k][j] + sum[1][k-1][j])%MOD;
			pref_sum[1][k][j] = (sum[1][k][j] + pref_sum[1][k-1][j])%MOD;

			dp[2][k][j] = (j-k)%MOD;
			sum[2][k][j] = (dp[2][k][j] + sum[2][k-1][j])%MOD;
			pref_sum[2][k][j] = (sum[2][k][j] + pref_sum[2][k-1][j])%MOD;
		}
	}

	for (int i = 3; i<=n; ++i){
		for (int j = 1; j<=m; ++j){
			sum[i][0][j] = 0;
			pref_sum[i][0][j] = 0;

			for (int k = 1; k<j; ++k){
				dp[i][k][j] = (pref_sum[i-2][j-1][j] - pref_sum[i-2][k-1][j])%MOD;
				sum[i][k][j] = (dp[i][k][j] + sum[i][k-1][j])%MOD;
				pref_sum[i][k][j] = (sum[i][k][j] + pref_sum[i][k-1][j])%MOD;
			}
		}
	}
	while (q--){
		int a, b;
		cin >> a >> b;
		cout << sum[a][b-1][b] << endl;
	}
	return 0;
}