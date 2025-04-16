// 111649
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 101;
const int INF = numeric_limits<int>::max();
vector<vector<int>> g(MAX_N);
vector<int> dist(MAX_N, INF);
int n, ans = -1;

void bfs(int s, int f) {
  queue<int> q;
  q.push(s);
  dist[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == f) {
      ans = dist[v];
      return;
    }
    for (int w : g[v]) {
      if (dist[w] > dist[v] + 1) {
        dist[w] = dist[v] + 1;
        q.push(w);
      }
    }
  }
}
