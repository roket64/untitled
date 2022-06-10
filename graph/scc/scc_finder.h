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

    void extract(T cur);

    T dfs(T cur);

    void MakeEdge(T start_, T end_);

    void find();

    T sn() { return m_sn; }

    T start() { return m_start; }

    T end() { return m_end; }

    std::vector<std::vector<T>> scc() { return m_scc; }
};

#endif //UNTITLED_SCC_FINDER_H
