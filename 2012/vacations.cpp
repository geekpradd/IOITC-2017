#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
// Mo's ordering. O((N+Q)SQRT(N))
struct cus{
	int l;
	int r;
	int id;
};
using namespace std;

int counter[1000001];
int block_size;

bool compare(const cus a, const cus b){
	if (a.l/block_size != b.l/block_size){
		return a.l < b.l;
	}
	return a.r < b.r;
}

signed main(){
	int n;
	scanf("%d", &n);
	int values[n];
	for (int i=0; i<n; ++i) cin >> values[i];
	int q; scanf("%d", &q);	
	block_size = sqrt(n);
	vector<cus> queries(q);
	for (int i=0; i<q; ++i){
		int a, b;
		scanf("%d %d", &a, &b);
		cus cur = {a-1, b-1, i};
		queries[i] = cur;
	}
	sort(queries.begin(), queries.end(), compare);
	int l = 0;
	int r = 0;
	int cl = 0;
	int cr = -1;
	int distinct = 0;
	int ans[q];
	for (int i=0; i<q; ++i){
		l = queries[i].l;
		r = queries[i].r;
		while (cr < r){
			cr++;
			if (counter[values[cr]] == 0) {
				distinct++;
			}
			counter[values[cr]]++;
		}
		while (cr > r){
			if (counter[values[cr]] == 1){
				distinct--;
			}
			counter[values[cr]]--;
			cr--;
		}
		while (cl < l){
			if (counter[values[cl]] == 1){
				distinct--;
			}
			counter[values[cl]]--;
			cl++;
		}
		while (cl > l){
			cl--;
			if (counter[values[cl]] == 0){
				distinct++;
			}
			counter[values[cl]]++;
		}
		ans[queries[i].id] = distinct;
	}
	for (int i=0; i<q; ++i){
		printf("%d\n", ans[i]);
	}
	return 0;
}