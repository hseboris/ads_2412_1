#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100'001;
vector<vector<int>> g(MAX_SIZE);
vector<int> visited(MAX_SIZE);
vector<int> tin(MAX_SIZE), up(MAX_SIZE);
bool is_cycle = false;
vector<int> top_sort;
int n, m;

void dfs(int v) {
  visited[v] = 1;
  for (int w : g[v]) {
    if (!visited[w]) {
      dfs(w);
    } else if (visited[w] == 1) {
      is_cycle = true;
    }
  }
  visited[v] = 2;
  top_sort.push_back(v);
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  if (is_cycle) {
    cout << -1 << '\n';
  } else {
    reverse(top_sort.begin(), top_sort.end());
    for (int v : top_sort) {
      cout << v << ' ';
    }
  }
}
