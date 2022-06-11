#include <vector>
#include <stack>
#include <algorithm>

template<class T>
struct scc_finder_ps {
    std::vector<bool> fin;
    std::vector<std::vector<T>> adj, scc;
    std::vector<T> par, belong;
    std::stack<T> s;

    T id, cnt, end;

    scc_finder_ps(T n): end(n) {
        fin.assign(n + 1, 0);
        adj.assign(n + 1, std::vector<T>());
        par.assign(n + 1, 0);
        belong.assign(n + 1, 0);
    }

    T dfs(T cur) {
        par[cur] = ++id;
        s.push(cur);
        T ret = par[cur];

        for (auto &next: adj[cur]) {
            if (!par[next]) ret = std::min(ret, dfs(next));
            else if (!fin[next]) ret = std::min(ret, par[next]);
        }

        if (ret == par[cur]) {
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
            if (!par[i]) dfs(i);
        }
    }
};