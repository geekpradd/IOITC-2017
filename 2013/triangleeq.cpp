#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

// To-Do

signed main(){
	int n;
	cin >> n;

	vector<ii> points(n);

	for (int i=0; i<n; ++i){
		int x, y;
		cin >> x >> y;
		points[i] = ii(x, y);
	}

	sort(points.begin(), points.end());
	int incr[n];
	int decr[n];
	int same[n];

	int ans = 0;
	for (int i=0; i<n; ++i){
		ii cur = points[i];
		incr[i] = 0;
		decr[i] = 0;
		same[i] = 0;

		for (int j=i+1; j<n; ++j){
			ii th = points[j];
			if (th.second > cur.second){
				incr[i]++;
			}
			else if (th.second == cur.second){
				same[i]++;
			}
			else {
				decr[i]++;
			}
		}
	}
	for (int i=0; i<n; ++i){
		ii cur = points[i];

		for (int j=i+1; j<n; ++j){
			ii th = points[j];
			if (th.second > cur.second){
				ans += incr[j] + same[j];
			}
			else if (th.second == cur.second) {
				ans += incr[j] + decr[j] + same[j];
			}
			else {
				ans += decr[j] + same[j];
			}
		}
	}

	ans = 2*ans;

	cout << ans%10243 << endl;
	return 0;
}