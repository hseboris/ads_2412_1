#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100'001;
vector<vector<int>> g(MAX_SIZE);
vector<int> visited(MAX_SIZE);

int color, n, m;
vector<vector<int>> components(1);

void dfs(int v) {
    visited[v] = color;
    components[color].push_back(v);
    for (int i : g[v]) {
        if (!visited[i]) {
            dfs(i);
        }
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
            ++color;
            components.push_back(vector<int>(0));
            dfs(i);
        }
    }
    cout << color << '\n';
    for (int i = 1; i <= color; ++i) {
        cout << components[i].size() << '\n';
        for (int j : components[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}