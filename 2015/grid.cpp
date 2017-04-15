#include <bits/stdc++.h>
#define ii pair<int, int>
#define NM 200000
using namespace std;
ii def = ii(-1, -1);
inline int mid(int l, int r){
	return (r-l)/2;
}
ii seg_tree[4*NM];
void build(int i, int l, int r){
	seg_tree[i] = ii(NM + 5, 0);
	if (l != r){
		build(i + i, l, l + mid(l, r));
		build(i + i + 1, l + mid(l, r) + 1, r);
	}
}
void update(int i, int l, int r, int ql, int qr, ii car){
	ii better = ii(min(seg_tree[i].first, car.first), max(seg_tree[i].second, car.second));
	if (l > qr || r < ql){

	}
	else if (l >= ql && r <= qr){
		seg_tree[i] = better;		
	}
	else if (l != r){
		update(i + i, l, l + mid(l, r), ql, qr, better);
		update(i + i + 1, l + mid(l, r) + 1, r, ql, qr, better);	
	}
}
ii query(int i, int l, int r, int ql, int qr, ii car){
	ii better = ii(min(seg_tree[i].first, car.first), max(seg_tree[i].second, car.second));
	if (l > qr || r < ql){
		return def;
	}
	else if (l >= ql && r <= qr){
		return better;
	}
	ii q1 = query(i + i, l, l + mid(l, r), ql, qr, better);
	ii q2 = query(i + i + 1, l + mid(l, r) + 1, r, ql, qr, better);
 	if (q1 == def){
 		return q2;
 	}
 	return q1;
}

signed main(){
	int n, u, q;
	cin >> n >> u >> q;
	build(1, 1, n);
	while (u--){
		int l, r, y1, y2;
		cin >> l >> y1 >> r >> y2;
		update(1, 1, n, l, r, ii(y1, y2));
	}
	while (q--){
		int l, r, y1, y2;
		cin >> l >> y1 >> r >> y2;
		ii range = query(1, 1, n, l, r, ii(NM + 5, 0));
		if (y2 < range.first || y1 > range.second){
			cout << 0 << endl;
		}
		else if (y2 <= range.second && y1 >= range.first ){
			cout << y2 - y1 + 1<< endl;
		}
		else if (y1 >= range.first){
			cout << range.second - y1 + 1 << endl;
		}
		else if (y2 <= range.second){
			cout << y2 - range.first + 1 << endl;
		}
		else {
			cout << range.second - range.first + 1 << endl;
		}
	}
	return 0;
}