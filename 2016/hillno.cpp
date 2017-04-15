#include <bits/stdc++.h>
#define int long long
using namespace std;

int dp[71][10];
int C[80][10];

signed main(){
	for (int i = 1; i<= 79; ++i){
		C[i][0] = 1, C[i][i] = 1;
		for (int r = 0; r < i; ++r){
			C[i+1][r+1] = C[i][r] + C[i][r+1];
		}
	}

	for (int i=1; i<=70; ++i){
		for (int j = 1; j<= 9; ++j){
			dp[i][j] += C[i - 1 + j][j];
			
			for (int k = 2; k<= i; ++k){
				for (int l = 1; l<=9; ++l){
					dp[i][j] += C[k + l - j - 2][l - j]*C[i - k + l][l];
					// cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
				}
			}
		}
	}
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		cout << dp[n][2] << endl;
	}
	return 0;
}