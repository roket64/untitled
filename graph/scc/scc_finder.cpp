#include "scc_finder.h"

template<class T>
void scc_finder<T>::MakeEdge(T start_, T end_) {
    m_adj[start_].push_back(end_);
}

template<class T>
void scc_finder<T>::extract(T cur) {
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

template<class T>
T scc_finder<T>::dfs(T cur) {
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

template<class T>
void scc_finder<T>::find() {
    switch (m_start) {
        case 0:
            for (int i = m_start; i < m_end; i++) { // 0 to n - 1
                if (m_parent[i]) dfs(i);
            }
            break;
        case 1:
            for (int i = m_start; i <= m_end; i++) { // 1 to n
                if (m_parent[i]) dfs(i);
            }
            break;
    }
}