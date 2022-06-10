#ifndef UNTITLED_SCC_FINDER_H
#define UNTITLED_SCC_FINDER_H

#include <vector>
#include <stack>
#include <string>
#include <algorithm>

template<class T>
class scc_finder {
private:
    static_assert(!(std::is_unsigned<T>::value
                    || std::is_same<bool, T>::value
                    || std::is_same<char, T>::value
                    || std::is_same<char16_t, T>::value
                    || std::is_same<char32_t, T>::value
                    || std::is_same<std::string, T>::value));

    std::vector<bool> m_fin;
    std::vector<std::vector<T>> m_adj;
    std::vector<std::vector<T>> m_scc;
    std::vector<T> m_parent, m_belong;
    std::stack<T> m_stk;
    T m_id;
    T m_sn;
    T m_start;
    T m_end;

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
    scc_finder(T start_, T end_) : m_id(0), m_sn(0), m_start(start_), m_end(end_) {
        switch (start_) {
            case 0: // 0 to n - 1
                m_fin.assign(end_, 0);
                m_adj.assign(end_, std::vector<T>());
                m_parent.assign(end_, 0);
                m_belong.assign(end_, 0);
                break;

            case 1: // 1 to n
                m_fin.assign(end_ + 1, 0);
                m_adj.assign(end_ + 1, std::vector<T>());
                m_parent.assign(end_ + 1, 0);
                m_belong.assign(end_ + 1, 0);
                break;

            default:
                break;
        }
    }

    void MakeEdge(T start_, T end_) {
//        m_adj[start_].push_back(end_);
    }

    void find() {
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

    std::vector<std::vector<T>> scc() { return m_scc; }
};

#endif //UNTITLED_SCC_FINDER_H
