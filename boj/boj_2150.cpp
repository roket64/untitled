#include <bits/stdc++.h>

#define MAX 10001
#define INF 1e9
#define pb(X) push_back(X)

using namespace std;

vector<int> adj[MAX];
vector<vector<int>> ans;
stack<int> s;
bool finish[MAX];
int d[MAX];
int id, cnt;

int dfs(int node) {
    d[node] = ++id;
    s.push(node);

    int parent = d[node];
    for (auto &i: adj[node]) {
        if (d[i] == 0) parent = min(parent, dfs(i));
        else if (not finish[i]) parent = min(parent, d[i]);
    }

    if (parent == d[node]) {
        vector<int> scc;
        while (true) {
            int now = s.top();
            s.pop();
            scc.pb(now);
            finish[now] = true;
            if (now == node) break;
        }

        sort(scc.begin(), scc.end());
        ans.pb(scc);
        cnt++;
    }

    return parent;
}

void solve() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] == 0) dfs(i);
    }

    sort(ans.begin(), ans.end());

    cout << cnt << "\n";
    for (auto &vec: ans) {
        for (auto &node: vec) {
            cout << node << " ";
        }
        cout << "-1\n";
    }
}

/*
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
/**/