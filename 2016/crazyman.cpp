#include <bits/stdc++.h>
using namespace std;
#define NMAX 100001
#define int long long
#define UL 1000000000
#define LL -1000000000
#define ii pair<int, int>
int n, q;
struct ds {
	int l;
	int r;
	int y;
	bool x;
	int max_child;
	int min_child;
};
ds seg_tree[4*NMAX];
void build(int i, int l, int r){
	seg_tree[i].l = l, seg_tree[i].r = r, seg_tree[i].y = 0;
	seg_tree[i].x = false;
	seg_tree[i].max_child = 0, seg_tree[i].min_child = 0;
	if (l != r){
		int mid = (r-l)/2;
		build(2*i, l, l + mid);
		build(2*i+1, l + mid+1, r);
	}
}
ii add_x(int i, int l, int r, int q_l, int q_r){
	if (r < q_l || l > q_r){
		return ii(seg_tree[i].y + seg_tree[i].max_child, seg_tree[i].y + seg_tree[i].min_child);
	}
	if (r <= q_r && l >= q_l){
		seg_tree[i].y = 0, seg_tree[i].x = 1;
		seg_tree[i].max_child = 0, seg_tree[i].min_child = 0;
		return ii(0, 0);
	}
	int mid = (r-l)/2;
	ii c1 = add_x(2*i, l, l + mid, q_l, q_r);
	ii c2 = add_x(2*i+1, l + mid+1, r, q_l, q_r);
	seg_tree[i].max_child = max(c1.first, c2.first);
	seg_tree[i].min_child = min(c1.second, c2.second);
	return ii(seg_tree[i].y + seg_tree[i].max_child, seg_tree[i].y + seg_tree[i].min_child);

}
ii add_y(int i, int l, int r, int q_l, int q_r, int y){
	if (r < q_l || l > q_r){
		return ii(seg_tree[i].y + seg_tree[i].max_child, seg_tree[i].y + seg_tree[i].min_child);
	}
	if (r <= q_r && l >= q_l){
		if (!seg_tree[i].x){
			seg_tree[i].y += y;
		}
		return ii(seg_tree[i].y + seg_tree[i].max_child, seg_tree[i].y + seg_tree[i].min_child);
	}
	int mid = (r-l)/2;
	ii c1 = add_y(2*i, l, l + mid, q_l, q_r, y);
	ii c2 = add_y(2*i+1, l + mid+1, r, q_l, q_r, y);
	seg_tree[i].max_child = max(c1.first, c2.first);
	seg_tree[i].min_child = min(c1.second, c2.second);
	return ii(seg_tree[i].y + seg_tree[i].max_child, seg_tree[i].y + seg_tree[i].min_child);
}
bool query(int i, int l, int r, int q_l, int q_r, int y_car){
	if (seg_tree[i].x){
		return 1;
	}
	if (r < q_l || l > q_r){
		return 1;
	}
	if (r <= q_r && l >= q_l){
		if (y_car + seg_tree[i].y + seg_tree[i].max_child > UL){
			return 0;
		}
		if (y_car + seg_tree[i].y + seg_tree[i].min_child < LL){
			return 0;
		}
		return 1;
	}

	int mid = (r-l)/2;
	bool c1 = query(2*i, l, l + mid, q_l, q_r, y_car + seg_tree[i].y);
	bool c2 = query(2*i+1, l + mid + 1, r, q_l, q_r, y_car + seg_tree[i].y);
	return (c1&c2);
}

signed main(){
	cin >> n >> q;
	build(1, 1, n);
	while (q--){
		int code; cin >> code;
		if (code == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			if (x != 0){
				add_x(1, 1, n, l, r);
			}
		}
		if (code == 2){
			int l, r, y;
			cin >> l >> r >> y;
			add_y(1, 1, n, l, r, y);
		}
		if (code == 3){
			int l, r;
			cin >> l >> r;
			cout << (query(1, 1, n, l, r, 0) ? "YES" : "NO") << endl;
		}
	}
	return 0;
}