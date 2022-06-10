#include <vector>
#include <stack>
#include <algorithm>

class SCC_FINDER {
private:
    std::vector<bool> m_fin;
    std::vector<std::vector<int>> m_adj;
    std::vector<std::vector<int>> m_scc;
    std::vector<int> m_parent, m_belong;
    std::stack<int> m_stk;
    int m_id;
    int m_sn;

    void extract(int cur) {
        m_sn++;
        std::vector<int> tmp;
        while (1) {
            int top = m_stk.top();
            m_stk.pop();
            m_fin[top] = 1;
            m_belong[top] = m_sn;
            tmp.push_back(top);
            if (top == cur) break;
        }
        std::sort(tmp.begin(), tmp.end());
        m_scc.push_back(tmp);
    }

public:
    SCC_FINDER(int size_) : m_id(0), m_sn(0) {
        m_fin.assign(size_ + 1, 0);
        m_adj.assign(size_ + 1, std::vector<int>());
        m_parent.assign(size_ + 1, 0);
        m_belong.assign(size_ + 1, 0);
    }

    void MakeEdge(int start_, int end_) {
        m_adj[start_].push_back(end_);
    }

    int dfs(int cur) {
        m_parent[cur] = ++m_id;
        m_stk.push(cur);
        int ret = m_parent[cur];

        for (auto &next: m_adj[cur]) {
            if (!m_parent[next]) ret = std::min(ret, dfs(next));
            else if (!m_fin[next]) ret = std::min(ret, m_parent[next]);
        }

        if (ret == m_parent[cur]) { extract(cur); }

        return ret;
    }

    std::vector<std::vector<int>> scc() { return m_scc; }
};