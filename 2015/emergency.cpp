#include <bits/stdc++.h>
#define pq priority_queue<int>
using namespace std;
// Solved Partially
// Maybe switching to scanf will work

signed main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;

		pq queue[101];

		for (int i=0; i<=100; ++i){
			priority_queue<int> cur;
			queue[i] = cur;
		}

		while (n--){
			char id;
			cin >> id;

			if (id == 'P'){
				int t_, s_t, r;
				cin >> t_ >> s_t >> r;

				int c = s_t - r*t_;
				queue[r].push(c);
			}
			else {
				int tim;
				cin >> tim;

				int pr = -100000000;
				int r = 0;

				for (int i=0; i<=100; ++i){
					if (queue[i].empty() == false){
						int top = queue[i].top();

						int val = i*tim + top;
						if (val >= pr){
							pr = val;
							r = i;
						}
					}
			
				}

				queue[r].pop();
				cout << pr << " " << r << endl;
			}
		}
	}
}