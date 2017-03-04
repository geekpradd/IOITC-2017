#include <bits/stdc++.h>
#define ii pair<int, int>
#define edge pair<int, pair<int, int> >
#define vi vector<int>
using namespace std;

// DSU is giving errors. 

class DSU {
private:
	vi rank, p, s;
public:
	DSU(int N) {
		rank.assign(N+1, 0);
		p.assign(N+1, 0);
		s.assign(N+1, 1);
		for (int i=1; i<=N; ++i) p[i] = i;
	}
	int find(int i){
		return ( p[i] == i ? i : (p[i] = find(p[i])));
	}
	int is_same(int i, int j){
		return find(i) == find(j);
	}
	void unionSet(int i, int j){
		if (!is_same(i, j)){
			int x = find(i), y = find(j);
			if (rank[x] > rank[y]) {
				p[y] = x;
				s[x] += s[y];
			}
			else {
				p[x] = y;
				s[y] += s[x];
				if (rank[x] == rank[y]){
					rank[y]++;
				}
			}
		}
	}
	int size(int i){
		return s[find(i)];
	}
	
};

signed main(){
	int n;
	cin >> n;
	vector<edge> e(n-1);
	for (int i=0; i<n-1; ++i){
		int a, b, c;
		cin >> a >> b >> c;

		edge cur = edge((-1)*c, ii(a, b));
		e[i] = cur;
	}
	sort(e.begin(), e.end());
	DSU set_union(n);
	int cost = 0;

	for (int i=0; i<n-1; ++i){
		int weight = (-1)*e[i].first;
		int a = e[i].second.first, b = e[i].second.second;
		cost += weight * set_union.size(a) * set_union.size(b);

		set_union.unionSet(a, b);
		
	}

	cout << cost << endl;
	
	return 0;
}