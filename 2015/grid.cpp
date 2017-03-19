#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
#define vi vector<int>
struct interval {
	int l;
	int r;
	int d;
	int u;
	// int id;
};
using namespace std;
int block;

bool comp(const interval &a, const interval &b){
	if (a.l/block != b.l/ block){
		return a.l/block < b.l/block;
	}
	return a.r > b.r; // modified mo order, still N(SQRT(N))
}

signed main(){
	int n, u, q;
	scanf("%d %d %d", &n, &u, &q);
	block = sqrt(n);
	// Mo's Algorithm
	vi grid(n+1, 0); 
	// grid will serve two purpose:
	// a) It will show wheter current index has left bracket or right
	// b) If so then it will show the parent of this left or right bracket
	interval updates[u+1];
	interval nout = {0, n, 0, n};
	updates[0] = nout;
	// int id_link[u+1];

	for (int i=1; i<=u; ++i){
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		interval cur = {a, c, b, d};
		updates[i] = cur; 
	}
	sort(updates+1, updates+u+1, comp);

	int cur_l = 1, cur_r = n, l = 1, r = n, parent = 1;

	for (int i=1; i<=u; ++i){
		// id_link[updates[i].id] = i;
		l = updates[i].l;
		r = updates[i].r;

		while (cur_r < r){
			cur_r++;
			if (grid[cur_r] != 0){
				parent = grid[cur_r];
			}
		}
		while (cur_l > l){
			cur_l--;
			if (grid[cur_l] != 0){
				parent = grid[cur_l];
			}
		}
			
		while (cur_r > r){
			cur_r--;
			if (grid[cur_r] != 0){
				parent = grid[cur_r];
			}

		}
		while (cur_l < l){
			cur_l++;
			if (grid[cur_l] != 0){
				parent = grid[cur_l];
			}
		}
		
		grid[cur_r] = parent;
		grid[cur_l] = parent;
		if (parent != 1){
			parent--;
			updates[i].d = min(updates[i].d, updates[parent].d);
			updates[i].u = max(updates[i].u, updates[parent].u);
		}
		parent = i + 1;
		// Parent signal: 1 = parent is unbounded
		// Else value - 1 gives location in array

	}
	for (int i=1; i<=n; ++i){
		if (grid[i] != 0){
			cout << "Parent[" << i << "] = " << updates[grid[i]-1].l << ", " << updates[grid[i]-1].r << endl;
		}
	}
	interval query[q+1];

	for (int i=1; i<=q; ++i){
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		interval cur = {a, c, b, d};
		query[i] = cur; 
		cout << "llf = " << query[i].l << endl;
		cout << "rrf = " << query[i].r << endl;
	}
	sort(query+1, query+q+1, comp);

	cur_l = 1, cur_r = n, parent = 1;
	for (int i=1; i<=q; ++i){
		// id_link[updates[i].id] = i;
		int l = query[i].l;
		int r = query[i].r;
		cout << "ll = " << l << endl;
		cout << "rr = " << r << endl;


		while (cur_r < r){
			cur_r++;
			if (grid[cur_r] != 0){
				parent = grid[cur_r];
				cout << "Changed BAAP to " << parent << endl;
			}
		}
		while (cur_l > l){
			cur_l--;
			if (grid[cur_l] != 0){
				parent = grid[cur_l];
				cout << "Changed BABP to " << parent << endl;
			}
		}
			
		while (cur_r > r){
			cur_r--;
			if (grid[cur_r] != 0){
				parent = grid[cur_r];
				cout << "Changed BACP to " << parent << endl;
			}

		}
		while (cur_l < l){
			cur_l++;
			if (grid[cur_l] != 0){
				parent = grid[cur_l];
				cout << "Changed BADP to " << parent << endl;
			}
		}
		cout << "L = " << cur_l << " R = " << cur_r << endl;
		if (parent != 1){
			cout << "Got ID " << parent << endl; 
			int op = parent - 1;
			int right = min(query[i].u, updates[op].u);
			int left = max(query[i].d, updates[op].d);
			if (right - left > 0){
				printf("%d\n", (right-left+1)*(r-l+1));
			}
			else {
				printf("0\n");
			}
		}
		else {
			printf("0\n");
		}

	}

	return 0;
}