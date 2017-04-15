#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
int occur[100001];

signed main(){
	int n;
	cin >> n;
	set<ii> ds;
	int unique = 0;
	int count = 0;
	while (n--){
		string com;
		cin >> com;
		int k; cin >> k;
		if (com == "insert"){
			ii cur = ii(k, -1);
			set<ii>::iterator net = ds.lower_bound(cur);
			ii next = *net;
			if (next.first == k){
				if (occur[next.second] == 1){
					count++;
				}
				occur[next.second]++;
			}
			else {
				unique++;
				ii ins = ii(k, unique);
				occur[unique]++;
				ds.insert(ins);
			}
		}
		else {
			ii cur = ii(k, -1);
			set<ii>::iterator net = ds.lower_bound(cur);
			ii next = *net;
			if (next.first == k){
				if (occur[next.second] == 1){
					ds.erase(net);
				}

				occur[next.second]--;
				if (occur[next.second] == 1){
					count--;
				}
			}
		}
		if (count >= 1 && ds.size() >= 2){
			cout << "both" << endl;
		}
		else if (count >= 1){
			cout << "homo" << endl;
		}
		else if (ds.size() >= 2){
			cout << "hetero" << endl;
		}
		else {
			cout << "neither" << endl;
		}
	}
	return 0;
}