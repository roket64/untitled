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
    T m_cnt;
    T m_start;
    T m_end;

    void extract(T cur);

    T dfs(T cur);

public:
    scc_finder(T start_, T end_);

    void MakeEdge(T start_, T end_);

    void find();

    T sn() { return m_cnt; }

    T start() { return m_start; }

    T end() { return m_end; }

    std::vector<std::vector<T>> scc() { return m_scc; }
};

#endif //UNTITLED_SCC_FINDER_H
