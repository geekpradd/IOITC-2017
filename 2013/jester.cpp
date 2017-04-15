#include <bits/stdc++.h>
using namespace std;

// To-Do. O(NM^2)

signed main(){
	int n = 200;
	int m = 200;
	int ***dp;
	int ***sum;
	// dp[i][f][l]
	// Number of valis sequences of length
	// i with first member f and last
	// member l
	dp = new int**[n+1];
	sum = new int**[n+1];


	for (int i=1; i<=2; ++i){
		dp[i] = new int*[m+1];
		sum[i] = new int*[m+1];

		for (int j=1; j<=200; ++j){
			dp[i][j] = new int[m+1];
			sum[i][j] = new int[m+1];

			for (int k=1; k<=200; ++k){
				if (i==1){
					if (j==k){
						dp[i][j][k] = 1;
					} 
					else {
						dp[i][j][k] = 0;
					}
				}
				else {
					dp[i][j][k] = 1;
				}
			}
		}
	}

	for (int i=3; i<=200; ++i){
		dp[i] = new int*[m+1];


		for (int j=1; j<=200; ++j){
			dp[i][j] = new int[m+1];
			for (int k=1; k<=200; ++k){
				dp[i][j][k] = dpl[i-2][j][k];

			}
		}
	}
}