#include <bits/stdc++.h>
#define int long long
#define ii pair<double, double>
#include <climits>
#define NINF INT_MIN
using namespace std;
// Solved but answer not matching.
// To - Do

inline double x_i (int x1, int x2, int y1, int y2){
		double frac = (y1 - y2);
		double denom = (x1 - x2);
		double m = frac/denom;
		double cc = y1;
		double dd = x1;

		double xi = (-1)* (cc/m) + dd;
		return xi;
}

signed main(){
	int lx, ly;
	cin >> lx >> ly;

	int ml, mr;
	cin >> ml >> mr;
	int s, c;
	cin >> s >> c;

	
	vector<ii> intervals(2*s);


	for (int i=0; i<s; ++i){
		int x, y, z;
		cin >> x >> y >> z;
		double x1 = x_i(x, lx, y, ly);
		double x2 = x_i(x, lx, z, ly);


		ii vv = ii(x1, x2);
		cout << "Interval A [" << x1 << ", " << x2 << "]" << endl; 
		intervals[2*i] = vv;

		double z1 = x_i(x, lx, (-1) * y, ly);
		double z2 = x_i(x, lx, (-1) * z, ly);

		ii zz = ii(z2, z1);
		cout << "Interval B [" << z2 << ", " << z1 << "]" << endl;
		intervals[2*i+1] = zz;

	}
	sort(intervals.begin(), intervals.end());

	vector<ii> crystals;

	int j = 0;
	vector<bool> mark(c, false);
	for (int i=0; i<c; ++i){
		int x, y;
		cin >> x >> y;

		double xi = x_i(x, lx, (-1)* y, ly);
		cout << "Reflection Intersection = (" << xi << ", 0)" << endl;

		if (xi >= ml && xi <= mr){
			j++;
			double k = i;
			cout << "Added to List" << endl;
			crystals.push_back(ii(xi, k));
		}
		else {
			mark[i] = true;
		}
	}
	sort(crystals.begin(), crystals.end());
	cout << endl;
	double right = NINF;
	for (int i=0; i<2*s; ++i){
		ii cur = intervals[i];
		cout << "Right End " << right << endl;
		cout << "Interval [" << cur.first << ", " << cur.second << "]" << endl;
		if (cur.second < ml) continue;
		if (cur.first > mr) break;

		double l;
		if (cur.first > right){
			cout << "Segment Right Shifted" << endl;
			l = cur.first;
		}
		else if (cur.second > right){
			cout << "Right Extended" << endl;
			l = right;
			cout << "Left Currently Is " << l << endl;
		}
		else {
			continue;
		}
		
		ii temp = ii(l, -1);
		vector<ii>::iterator iter = lower_bound(crystals.begin(), crystals.end(), temp);
		if (iter == crystals.end()) break;

		int dist = iter - crystals.begin();
		for (int j=dist; j<crystals.size(); ++j){
			ii gg = crystals[j];

			if (gg.first > cur.second) break;
			cout << "Visiting point at " << gg.first << endl;
			mark[gg.second] = true;
		}
		right = cur.second;

	}

	int count = 0;
	for (int i=0; i<c; ++i){
		if (!mark[i]) count++;
	}
	cout << count << endl;
	for (int i=0; i<c; ++i){
		if (!mark[i]){
			cout << i + 1 << endl;
		} 
	}
	return 0;
}