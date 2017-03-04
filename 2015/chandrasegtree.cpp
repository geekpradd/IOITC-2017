#include <bits/stdc++.h>
using namespace std;
int *seg_tree;
int *zero; 

// BTW, Anne Hathaway. Christan Bale.
// Coincidence. I was wondering why she responded that way.
// Atleast the resemblance haunts someone..
// 3/3/17 - Another attempt at seg tree
// We will store two pieces of data
// a) Number of members of the interval that are = 0 
//    ignoring all interval paints of nodes above the node
// b) Number of paints to that ENTIRE INTERVAL

int build(int i, int l, int r){
	seg_tree[i] = 0;
	if (l == r){
		zero[i] = 1;
	}
	else {
		int mid = (r-l)/2;
		zero[i] = build(2*i, l, l+mid) + build(2*i+1, l+mid+1, r);
	}
	return zero[i];

}

int update_i(int i, int l, int r, int ql, int qr){
	if ((r < ql) || (qr < l)){

	}
	else if ((l >= ql ) && (r <= qr)){
		seg_tree[i]++;
		zero[i] = 0;
	}
	else {
		if (l != r){
			int mid = (r-l)/2;
			zero[i] = update_i(2*i, l, l + mid, ql, qr) + update_i(2*i+1, l+mid+1, r, ql, qr);
		}
	}
	return zero[i];
}
void print_stree(int i, int l, int r, int height){
	cout << "Height: " << height << " L = " << l << " R = " << r << " Value = " << seg_tree[i] << endl;
	if (l != r){
		int mid = (r-l)/2;
		print_stree(2*i, l, l+mid, height+1);
		print_stree(2*i+1, l+mid+1, r, height+1);

	}	

}

int update_d(int i, int l, int r, int ql, int qr){
	if ((r < ql) || (qr < l)){

	}
	else if ((l >= ql ) && (r <= qr)){
		seg_tree[i]--;
		if (seg_tree[i] == 0){
			int mid = (r-l)/2;
			zero[i] = update_d(2*i, l, l + mid, ql, qr) + update_d(2*i+1, l+mid+1, r, ql, qr);
		}
	}
	else {
		if (l != r){
			int mid = (r-l)/2;
			int v1 = update_d(2*i, l, l + mid, ql, qr);
			int v2 = update_d(2*i+1, l+mid+1, r, ql, qr);
			if (seg_tree[i] == 0){
				zero[i] = v1 + v2;
			}
		}
	}
	return zero[i];
}

int query(int i, int l, int r, int ql, int qr){
	if ((r < ql) || (qr < l)){
		return 0;
	}
	else if ((l >= ql ) && (r <= qr)){
		return zero[i];
	}
	else {
		int mid = (r-l)/2;
		return query(2*i, l, l+mid, ql, qr) + query(2*i + 1, l+mid+1, r, ql, qr);
	}
}

signed main(){
	int n, m, q;
	cin >> n >> m >> q;

	
	seg_tree = new int[3*n];
	zero = new int[3*n];
	build(1, 1, n-1);

	while (m--){
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		update_i(1, 1, n-1, a, b-1);
	}
	// print_stree(1, 1, n-1, 1);
	while (q--){
		int code;
		cin >> code;
		if (code == 0){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			update_i(1, 1, n-1, a, b-1);
		}
		if (code == 1){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			update_d(1, 1, n-1, a, b-1);
		}
		if (code == 2){
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);

			int count = query(1, 1, n-1, a, b-1);
			cout << count << endl;
		}
	}

	return 0;
}