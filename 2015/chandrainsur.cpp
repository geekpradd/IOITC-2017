#include <bits/stdc++.h>
using namespace std;

signed main(){
	int n, m, q;
	cin >> n >> m >> q;
	int arr[n];
	for (int i=1; i<n; ++i) arr[i] = 0;

	for (int i=0; i<m; ++i){
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		for (int j=a; j<b; ++j) arr[j]++;
	}
	
	while (q--){
		int code;
		cin >> code;
		if (code == 0){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			for (int j=a; j<b; ++j) arr[j]++;
		}
		if (code == 1){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			for (int j=a; j<b; ++j) arr[j]--;
		}
		if (code == 2){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			int count = 0;
			for (int j=a; j<b; ++j){
				if (arr[j] == 0) count++;
			}
			cout << count << endl;
		}
	}
	return 0;
}