#include <bits/stdc++.h>
#include <cstdio>
#define ii pair<int, int>
using namespace std;
ii *tree;

// First segtree with lazy propagation
// P.S: I got new spectacles :D
// FMM coming up
// Last time study for boards..
// Hope not to screw up IOITC!

// Complexity: O(Q log N)
int init(int i, int l, int r){
	tree[i].first = 0;
	
	int mid = (r-l)/2;
	if (r==l){

		tree[i].second = 1;
	}
	else {
		tree[i].second = init(2*i, l, l+mid) + init(2*i+1, l+mid+1, r);
	}
	return tree[i].second;
}

int query(int i, int l, int r, int ql, int qr){
	int mid = (r-l)/2;
	if (r < ql || l > qr){
		// lies outside
		return 0;
	}
	else if (l >= ql && r <= qr){
		// lies completely inside
		return tree[i].second;
	}
	else {
		if (tree[i].second == 0){
			return 0;
		}
		else {
			return query(2*i, l, l+mid, ql, qr) + query(2*i+1, l+mid+1, r, ql, qr);
		}
	}

}

int paint(int i, int l, int r, int ql, int qr){
	if (r < ql || l > qr){
		// lies outside
	}
	else if (l >= ql && r <= qr){
		// lies completely inside
		tree[i].first++;
		tree[i].second = 0;
	}
	else {
		// partial overlap
		int mid = (r-l)/2;
		tree[i].second = paint(2*i, l, l+mid, ql, qr) + paint(2*i+1, l+mid+1, r, ql, qr);
		if (tree[i].first != 0){
			tree[i].second = 0;
		}
	}

	return tree[i].second;
}
int coat(int i, int l, int r, int ql, int qr){
	int mid = (r-l)/2;
	if (r < ql || l > qr){
		// lies outside
	}
	else if (l >= ql && r <= qr){
		// lies completely inside
		tree[i].first--;
		if (tree[i].first == 0){
			if (l != r){
				tree[i].second = tree[2*i].second + tree[2*i+1].second;
			}
			else {
				tree[i].second = 1;
			}
		}
	}
	else {
		// partial overlap
		tree[i].second = coat(2*i, l, l+mid, ql, qr) + coat(2*i+1, l+mid+1, r, ql, qr);
		if (tree[i].first != 0){
			tree[i].second = 0;
		}
	}
	return tree[i].second;
}
signed main(){
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	// The graph has n nodes
	// and (n-1) initial edges which are stored in the seg_tree
	tree = new ii[3*n+1];
	init(1, 1, n-1);

	while (m--){
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		// Our segtree indices are from a to b-1
		paint(1, 1, n-1, a, b-1);
	}
	while (q--){
		int code;
		scanf("%d", &code);
		if (code == 0){
			int a, b;
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);
			paint(1, 1, n-1, a, b-1);
		}
		if (code == 1){
			int a, b;
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);
			coat(1, 1, n-1, a, b-1);
		}
		if (code == 2){
			int a, b;
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);

			int count = query(1, 1, n-1, a, b-1);
			printf("%d\n", count);
		}
	}

	return 0;
}