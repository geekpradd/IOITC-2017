#include <bits/stdc++.h>
using namespace std;
int dp[25];
bool correct = 1;

vector<int> ans(int n, int dist){
	vector<int> ret(n);
	if (dist > dp[n]) {
		correct = 0;
		return ret;
	}
	int acum = 0;
	for (int i = 1; i<= n; ++i){
		acum += dp[i-1]*dp[n-i];

		if (acum >= dist){
			acum -= dp[i-1]*dp[n-i];
			ret[0] = i;
			int leeway = (dist - acum)/dp[n-i];
			vector<int> future_1 = ans(i-1, leeway);
			vector<int> future_2 = ans(n-i, (dist - acum)%(dp[n-i]));
				
			for (int j=0; j<i-1; ++j){
				ret[j+1] = future_1[j];
			}
			for (int j=0; j<n-i; ++j){
				ret[i+j] = future_2[j] + i;
			}

			break;
		}
	}
	return ret;
}

signed main(){
	int n, k;
	cin >> n >> k;
	dp[0] = 1; dp[1] = 1;
	for (int i=2; i<=n; ++i){
		dp[i] = 0;
		for (int j=0; j<i; ++j){
			dp[i] += dp[j]*dp[i-1-j];
		}
	}
	vector<int> cur = ans(n, k);
	if (correct = 0){
		cout << -1 << endl;
	}
	else {
		for (int i=0; i<n; ++i){
			char curs = 'a' - 1 + cur[i];
			cout << curs << "";
		}
		cout << endl;
	}

	return 0;
}