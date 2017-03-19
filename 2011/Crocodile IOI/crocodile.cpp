#include <bits/stdc++.h>
#include <queue>
#define ii pair<int, int>
using namespace std;


int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]);

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
  // This solves for 46 marks using DP on trees.
  vector<ii> adj[N];

  for (int i=0; i<M; ++i){
  	adj[R[i][0]].push_back(ii(R[i][1], L[i]));
  	adj[R[i][1]].push_back(ii(R[i][0], L[i]));
  }
  queue<ii> bfs;
  vector<int> visit(N);
  vector<int> parent(N);
  int id = 0;
  bfs.push(ii(0, -1));
  while (!bfs.empty()){
  	ii cur = bfs.front();
  	parent[cur.first] = cur.second;
  	bfs.pop();
  	visit[id] = cur.first; id++;
  	int s1 = adj[cur.first].size();

  	for (int j=0; j<s1; ++j){
  		int to = adj[cur.first][j].first;
  		if (to != cur.second){
  			bfs.push(ii(to, cur.first));
  		}
  	}
  }
  int dp[N];
  for (int i=N-1; i>=0; --i){
  	int node = visit[i];
  	if (adj[node].size() == 1){
  		// exit node
  		dp[node] = 0;
  	}
  	else  {
  		int min1 = INT_MAX;
  		int min2 = INT_MAX;
  		int s2 = adj[node].size();
  		for (int j=0; j<s2; ++j){
  			int to = adj[node][j].first;
  			if (to != parent[node]){
  				int cur_cost = adj[node][j].second + dp[to];
  				if (cur_cost < min1){
  					min2 = min1;
  					min1 = cur_cost;
  				}
  				else if (cur_cost < min2){
  					min2 = cur_cost;
  				}
  			}
  		}
  		dp[node] = min2;
  	}
  }
  
  return dp[0];
}


