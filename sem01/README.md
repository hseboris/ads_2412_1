# Depth-First Search: связность, циклы, двудольность

## Поиск количества компонент связности

```cpp
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
```

## Практическое применение dfs

Задача [площадь комнаты](https://informatics.msk.ru/mod/statements/view.php?id=26604)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 11;
vector<vector<int>> field(MAX_SIZE + 1, vector<int>(MAX_SIZE + 1));
vector<vector<int>> g(MAX_SIZE * MAX_SIZE + 1);
vector<int> visited(MAX_SIZE * MAX_SIZE + 1);
int s, n;

void dfs(int v) {
    if (!visited[v]) {
        visited[v] = 1;
        ++s;
        for (int i : g[v]) {
            dfs(i);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if (c == '.') {
                field[i][j] = 1;
            }
        }
    }
    for (int i = 2; i < n; ++i) {
        for (int j = 2; j < n; ++j) {
            if (field[i][j] == 1) {
                if (field[i - 1][j] == 1) {
                    g[(i - 1) * n + j].push_back((i - 2) * n + j);
                }
                if (field[i + 1][j] == 1) {
                    g[(i - 1) * n + j].push_back(i * n + j);
                }
                if (field[i][j - 1] == 1) {
                    g[(i - 1) * n + j].push_back((i - 1) * n + j - 1);
                }
                if (field[i][j + 1] == 1) {
                    g[(i - 1) * n + j].push_back((i - 1) * n + j + 1);
                }
            }
        }
    }
    int x, y;
    cin >> x >> y;
    dfs((x - 1) * n + y);
    cout << s << '\n';
}
```