#include <bits/stdc++.h>
using namespace std;
// 55/100

signed main(){
	int n, k;
	cin >> n >> k;

	int A[n];
	int B[n];
	for (int i=0; i<n; ++i) cin >> A[i];
	for (int i=0; i<n; ++i) cin >> B[i];

	int dp_1[n][k+1];
	int dp_2[n][k+1];

	// dp_i[j][k] -> Best cost
	// one can get from index j chossing i 
	// with k-1 already taken
	
	for (int j=k; j>=0; --j){
		dp_1[n-1][j] = A[n-1];
		dp_2[n-1][j] = B[n-1];
	}

	for (int i=n-2; i>=0; --i){
		dp_1[i][k] = A[i] + dp_2[i+1][1];
		dp_2[i][k] = B[i] + dp_1[i+1][1];
		for (int j=k-1; j>=0; --j){
			dp_1[i][j] = A[i] + min(dp_1[i+1][j+1], dp_2[i+1][1]);
			dp_2[i][j] = B[i] + min(dp_1[i+1][1], dp_2[i+1][j+1]);
		}
	}
	cout << min(dp_1[0][1], dp_2[0][1]) << endl;
	return 0;
}