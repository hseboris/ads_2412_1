# Depth-First Search: мосты и точки сочленения, топологическая сортировка

## Поиск мостов
```cpp
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
```

## Поиск точек сочленения
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 20'001;
vector<vector<int>> g(MAX_SIZE);
vector<bool> visited(MAX_SIZE);
vector<int> tin(MAX_SIZE), up(MAX_SIZE);
set<int> articulation_points;

int timer, m, n;

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = up[v] = ++timer;
  int children = 0;
  for (int w : g[v]) {
    if (w == p) {
      continue;
    }
    if (!visited[w]) {
      dfs(w, v);
      up[v] = min(up[v], up[w]);
      if (up[w] >= tin[v] && p != -1) {
        articulation_points.insert(v);
      }
      ++children;
    } else {
      up[v] = min(up[v], tin[w]);
    }
  }
  if (p == -1 && children > 1) {
    articulation_points.insert(v);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  cout << articulation_points.size() << '\n';
  for (int v : articulation_points) {
    cout << v << '\n';
  }
}
```

## Топологическая сортировка
```cpp
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

```