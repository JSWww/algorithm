#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<pair<int, int>> tree[10001];

pair<int, int> bfs(int v) {
  pair<int, int> p = {0, -1};
  queue<pair<int, int>> q;
  bool visited[n + 1];

  for (int i = 1; i <= n; i++) {
    visited[i] = false;
  }

    q.push({v, 0});
    visited[v] = true;

    while (!q.empty()) {
        int here = q.front().first;
        int d = q.front().second;

        q.pop();

        if (p.second < d) {
            p.first = here;
            p.second = d;
        }

        for (auto e : tree[here]) {
            int next = e.first;
            int nd = e.second;

            if (visited[next]) continue;
            q.push({next, d + nd});
            visited[next] = true;
        }
    }
    return p;
}

int main()
{
    cin >> n;

    int a, b, c;

    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;

        tree[a].push_back({b, c});
        tree[b].push_back({a, c});
    }

    pair<int, int> p;

    p = bfs(1);
    p = bfs(p.first);

    cout << p.second << '\n';

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int dist[10001];
vector<pair<int, int>> tree[10001];
priority_queue<pair<int, int>> pq;

int dijkstra(int v) {
    for (int i = 1; i <= n; i++) {
        dist[i] = 1e9;
    }

    dist[v] = 0;
    pq.push({0, v});

    while (!pq.empty()) {
        int here = pq.top().second;
        int cost = -pq.top().first;

        pq.pop();

        for (auto e : tree[here]) {
            if (dist[here] + e.second <dist[e.first]) {
                dist[e.first] = dist[here] + e.second;
                pq.push({-dist[e.first], e.first});
            }
        }
    }

    int result = -1;
    int value = -1;

    for (int i = 1; i <= n; i++) {
        if (value < dist[i]) {
            result = i;
            value = dist[i];
        }
    }

    return result;
}

int main()
{
    cin >> n;

    int a, b, c;

    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;

        tree[a].push_back({b, c});
        tree[b].push_back({a, c});
    }

    int v = dijkstra(1);
    v = dijkstra(v);

    cout << dist[v] << '\n';
    
    return 0;
}
*/
