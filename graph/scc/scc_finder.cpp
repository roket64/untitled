#include "scc_finder.h"

template<class T>
scc_finder<T>::scc_finder(T start_, T end_)
        :m_id(0), m_cnt(0), m_start(start_), m_end(end_) {
    static_assert(!(std::is_unsigned<T>::value
                    || std::is_same<bool, T>::value
                    || std::is_same<char, T>::value
                    || std::is_same<char16_t, T>::value
                    || std::is_same<char32_t, T>::value
                    || std::is_same<std::string, T>::value));

    static_assert(start_ == 0 || start_ == 1);

    switch (start_) {
        case 0:
            m_fin.assign(end_, 0);
            m_adj.assign(end_, std::vector<T>());
            m_parent.assign(end_, 0);
            m_belong.assign(end_, 0);
            break;

        case 1:
            m_fin.assign(end_ + 1, 0);
            m_adj.assign(end_ + 1, std::vector<T>());
            m_parent.assign(end_ + 1, 0);
            m_belong.assign(end_ + 1, 0);
            break;
    }
}

template<class T>
scc_finder<T>::~scc_finder() {
    m_fin.clear();
    std::vector<bool>().swap(m_fin);

    m_adj.clear();
    std::vector<std::vector<T>>().swap(m_adj);

    m_scc.clear();
    std::vector<std::vector<T>>().swap(m_scc);

    m_parent.clear();
    std::vector<T>().swap(m_parent);

    m_belong.clear();
    std::vector<T>().swap(m_belong);
}

template<class T>
void scc_finder<T>::MakeEdge(T start_, T end_) {
    m_adj[start_].push_back(end_);
}

template<class T>
void scc_finder<T>::extract(T cur) {
    std::vector<T> tmp;
    while (1) {
        T top = m_stk.top();
        m_stk.pop();
        m_fin[top] = 1;
        m_belong[top] = m_cnt;
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

    if (ret == m_parent[cur]) {
        m_cnt++;
        extract(cur);
    }

    return ret;
}

template<class T>
void scc_finder<T>::find() {
    switch (m_start) {
        case 0:
            for (int i = m_start; i < m_end; i++) { // 0 to n - 1
                if (!m_parent[i]) dfs(i);
            }
            break;

        case 1:
            for (int i = m_start; i <= m_end; i++) { // 1 to n
                if (!m_parent[i]) dfs(i);
            }
            break;
    }
}