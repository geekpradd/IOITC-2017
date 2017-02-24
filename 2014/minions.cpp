#include <bits/stdc++.h>
using namespace std;
// Solved

signed main(){
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		int a[n];
		int b[n];
		int c[n];

		for (int i=0; i<n; ++i){
			cin >> a[i] >> b[i] >> c[i];
		}
		int dp[n][2];
		// 0 means left has already eaten
		// 1 means left has not eaten
		dp[n-1][0] = b[n-1];
		dp[n-1][1] = a[n-1];

		for (int i=n-2; i>=0; --i){
			dp[i][0] = max(b[i] + dp[i+1][0], c[i] + dp[i+1][1]);
			dp[i][1] = max(a[i] + dp[i+1][0], b[i] + dp[i+1][1]);
		}
		cout << dp[0][1]<< endl;
	}
	return 0;
}