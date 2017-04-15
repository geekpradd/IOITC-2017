#include <bits/stdc++.h>
#include <cstdio>
#define ii pair<int, int>
using namespace std;

signed main(){
	int n, m;
	scanf("%d %d", &n, &m);

	vector<ii> v(n+1, ii(-1, -1));
	vector<int> b(n+1, -1);
	int l = 0; // l represents count of elements left shifted
	bool work = true;
	for (int i=1; i<=m; ++i){
		int x, y;
		scanf("%d %d", &x, &y);
		if (y > l){
			// we discovered something new
			if (v[x].first != -1){
				work = false; break;
			}
			v[x] = ii(y-l, i);
			b[y-l] = x;
			++l;
		}
		else {
			ii cur = v[x];
			int should_be = i - cur.second;
			if (cur.second == -1 || y != should_be){
				work = false; break;
			}
			v[x].second = i;
		}
	}
	if (work == false){
		printf("-1");
	}
	else {
		int shift = 0;
		for (int i=1; i<=n; ++i){
			if (b[i] != -1){
				printf("%d ", b[i]);
			}
			else {
				while (v[shift + 1].first != -1){
					shift++;
				}
				printf("%d ", shift+1);
				shift++;
			}
		}
	}

	return 0;
}
