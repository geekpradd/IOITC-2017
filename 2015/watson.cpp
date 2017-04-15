#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

// AIM: Top 10 in IOITC.
// Wondering why I have to put up with Financial Market ratios!!
// Deliberating peace.
// Observing patterns.
// Thinking of unfinished business.
// 100/100 here. Good problem.

signed main(){
	int t;
	scanf("%d", &t);
	while (t--){
		int n;
		cin >> n;
		int a[n];
		for (int i=0; i<n; ++i){
			scanf("%d", &a[i]);
		} 
		// Optimal choice is take b[i] = a[i] OR 1
		// 2^n states. Reduced to O(n) DP
		int dp[n][2];
		dp[0][0] = 0;
		dp[0][1] = 0;
		for (int i=1; i<n; ++i){
			// 0 = take b[i] = a[i]
			dp[i][0] = max(abs(a[i]-1) + dp[i-1][1], abs(a[i] - a[i-1]) + dp[i-1][0]);
			// 1 = take b[i] = 1;
			dp[i][1] = max(abs(1 - 1) + dp[i-1][1], abs(1 - a[i-1]) + dp[i-1][0]);
		}
		printf("%d\n", max(dp[n-1][0], dp[n-1][1]));
	}
	return 0;
}