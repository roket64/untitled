#include <bits/stdc++.h>
#include "graphstructure.h"

#define inf 0x3f3f3f3f
#define ll_inf 0x3f3f3f3f3f3f3f3f
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(x) (x).begin(), (x).end()
#define unq(x) sort(all(x)); (x).erase(unique(all(x)), (x).end())
#define rep(i, a, b) for (int i = (int) a; i < (int) b; i++)
#define MAX 20001

using namespace std;
typedef long long ll;

vector<ll> d(MAX + 1);
vector<Node<ll, ll>> adj[MAX];

void dijkstra(ll s) {
    fill(all(d), inf);
    priority_queue<Node<ll, ll>> pq;
    d[s] = 0;
    pq.push({s, d[s]});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        auto node = cur.GetNode();
        auto dist = cur.GetWeight();
        if (d[node] < dist) continue;
        for (auto &next: adj[node]) {
            auto v = next.GetNode();
            auto w = next.GetWeight();
            ll cost = d[node] + w;
            if (d[v] <= cost) continue;
            d[v] = cost;
            pq.push({v, d[v]});
        }
    }
}

int main() {
    fast_io;

    ll n, m, s;
    cin >> n >> m >> s;
    rep(i, 0, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(Node(v, w));
    }
    dijkstra(s);
    rep(i, 1, n + 1) {
        if (d[i] != inf) cout << d[i] << "\n";
        else cout << "INF\n";
    }

    return 0;
}