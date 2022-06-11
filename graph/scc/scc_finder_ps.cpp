#include <vector>
#include <stack>
#include <algorithm>

template<class T>
struct scc_finder {
    std::vector<bool> fin;
    std::vector<std::vector<T>> adj, scc;
    std::vector<T> parent, belong;
    std::stack<T> s;

    T id, cnt, end;

    scc_finder(T n): end(n) {
        fin.assign(n + 1, 0);
        adj.assign(n + 1, std::vector<T>());
        parent.assign(n + 1, 0);
        belong.assign(n + 1, 0);
    }

    T dfs(T cur) {
        parent[cur] = ++id;
        s.push(cur);
        T ret = parent[cur];

        for (auto &next: adj[cur]) {
            if (!parent[next]) ret = std::min(ret, dfs(next));
            else if (!fin[next]) ret = std::min(ret, parent[next]);
        }

        if (ret == parent[cur]) {
            cnt++;
            std::vector<T> tmp;
            while (1) {
                auto top = s.top();
                s.pop();
                fin[top] = 1;
                belong[top] = cnt;
                tmp.push_back(top);
                if (top == cur) break;
            }
            std::sort(tmp.begin(), tmp.end());
            scc.push_back(tmp);
        }
        return ret;
    }

    void find() {
        for (int i = 1; i <= end; i++) {
            if (!parent[i]) dfs(i);
        }
    }
};