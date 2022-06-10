#include <vector>
#include <stack>
#include <algorithm>

template<class T>
class scc_finder {
private:
    std::vector<bool> m_fin;
    std::vector<std::vector<T>> m_adj;
    std::vector<std::vector<T>> m_scc;
    std::vector<T> m_parent, m_belong;
    std::stack<T> m_stk;
    T m_id;
    T m_sn;
    T m_size;

    void extract(T cur) {
        m_sn++;
        std::vector<T> tmp;
        while (1) {
            T top = m_stk.top();
            m_stk.pop();
            m_fin[top] = 1;
            m_belong[top] = m_sn;
            tmp.push_back(top);
            if (top == cur) break;
        }
        std::sort(tmp.begin(), tmp.end());
        m_scc.push_back(tmp);
    }

    T dfs(T cur) {
        m_parent[cur] = ++m_id;
        m_stk.push(cur);
        T ret = m_parent[cur];

        for (auto &next: m_adj[cur]) {
            if (!m_parent[next]) ret = std::min(ret, dfs(next));
            else if (!m_fin[next]) ret = std::min(ret, m_parent[next]);
        }

        if (ret == m_parent[cur]) { extract(cur); }

        return ret;
    }

public:
    scc_finder(T size_) : m_id(0), m_sn(0), m_size(size_) {
        m_fin.assign(size_ + 1, 0);
        m_adj.assign(size_ + 1, std::vector<T>());
        m_parent.assign(size_ + 1, 0);
        m_belong.assign(size_ + 1, 0);
    }

    void MakeEdge(T start_, T end_) {
        m_adj[start_].push_back(end_);
    }

    void find() {
        for (int i = 1; i <= m_size; i++) {
            if(!m_belong[i]) dfs(i);
        }
    }

    std::vector<std::vector<T>> scc() { return m_scc; }
};