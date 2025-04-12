#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 20'001;

vector<vector<int>> g(MAX_SIZE);
vector<bool> visited(MAX_SIZE);
vector<int> tin(MAX_SIZE), up(MAX_SIZE);
int timer, n, m;
map<pair<int, int>, pair<int, bool>> edges;
vector<int> bridges;

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = up[v] = ++timer;
  for (int w : g[v]) {
    if (w == p) {
      continue;
    }
    if (!visited[w]) {
      dfs(w, v);
      up[v] = min(up[v], up[w]);
      if (up[w] > tin[v] && !edges[{min(v, w), max(v, w)}].second) {
        bridges.push_back(edges[{min(v, w), max(v, w)}].first);
      }
    } else {
      up[v] = min(up[v], tin[w]);
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    if (v < u) {
      swap(u, v);
    }
    g[u].push_back(v);
    g[v].push_back(u);
    if (edges.find({min(u, v), max(u, v)}) == edges.end()) {
      edges[{u, v}] = {i, false};
    } else {
      edges[{u, v}].second = true;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  cout << bridges.size() << '\n';
  stable_sort(bridges.begin(), bridges.end());
  for (int b : bridges) {
    cout << b << ' ';
  }
}