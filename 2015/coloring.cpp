#include <bits/stdc++.h>
#include <cstdio>
#define MOD 1000000007
#define vi vector<int>
using namespace std;

class DSU {
private:
	vi rank, p, weight, color;
	int t;
	// Index IDs:
	// 1 to N, elements of graph
	// N+1 to 2N, members belonging to cause 0 red
	// 2N+1 to 3N, members belonging to cause 0 blue
	// 3N+1 to 4N, represenatitves of cause red
	// 4N+1 to 5N, representatives of cause blue
public:
	DSU(int N){
		t = N;
		color.assign(N+1, -1); rank.assign(5N+1, 0); p.assign(5N+1, 0); weight.assign(N+1, 0);
		for (int i=1; i<=N; ++i) p[i] = i;
		for (int i=N+1; i<=3N; ++i) p[i] = -1; // sleeping
		for (int i=3N+1; i<=5N; ++i) p[i] = i;
	} 
	int find(int i){
		return (p[i] == i ? i : p[i] = find(i));
	}
	int merge(int a, int b){
		int x = find(a), y = find(b);
		int w_1 = weight[a], w_2 = weight[b];
		if (w_1 == w_2){
			if (length[])
		}
		if (x != y){
			if (rank[x] > rank[y]){
				p[y] = x;
			}
			else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};

signed main(){
	int n, m, q, k1, k2;
	scanf("%d %d %d %d %d", &n, &m, &q, &k1, &k2);
	int power[n+1];
	power[0] = 1;
	for (int i=1; i<=n; ++i){
		power[i] = (power[i-1] + power[i-1])%MOD;
	}

}