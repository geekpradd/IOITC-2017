#include <bits/stdc++.h>
#define ll long long
#define MAX 1e17
using namespace std;


signed main(){
	int n, k;
	cin >> n >> k;
	ll sum[k];
	for (int i=0; i<k; ++i) sum[i] = 0;
	map<ll, ll> m[k];

	for (int i=0; i<n; ++i){
		for (int j=0; j<k; ++j){
			ll coord;
			cin >> coord;
			sum[j] += coord;
			if (m[j].count(coord) == 0){
				m[j][coord] = 1;
			}
			else {
				m[j][coord]++;
			}
		}
	}

	for (int j=0; j<k; ++j){
		ll min = MAX;
		int has_min = 0;
		int c = n;
		int d = sum[j];
		ll r_lim = MAX;
		// At any instant, parameter is cx - d
		for (map<ll,ll>::iterator i = m[j].end() - 1; i>= m[j].begin(); --i){
			ll val = i->first;
			if (c > 0){
				if (c*(val) - d < min){
					min = c*(val) - d;
					has_min = 1;
					m[j][val] = -1;
				}
				else if (c*(val) - d = min){
					has_min++;
					m[j][val] = -1;
				}
			}
			if (c < 0){
				if (c*(r_lim) - d < mi)
			}
		}
	}
}
