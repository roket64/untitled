#include "dinic.h"
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f

template<class T>
Dinic<T>::Dinic(T source_, T sink_, T size_)
        :m_source(source_), m_sink(sink_), m_max_flow(0) {
    m_capacity.assign(size_ + 1, std::vector<T>(size_ + 1, 0));
    m_flow.assign(size_ + 1, std::vector<T>(size_ + 1, 0));
    m_adj.assign(size_ + 1, std::vector<T>(size_ + 1));
    m_level.assign(size_ + 1);
    m_work.assign(size_ + 1);
}

template<class T>
Dinic<T>::~Dinic() {
    m_capacity.clear();
    std::vector<std::vector<T>>().swap(m_capacity);

    m_flow.clear();
    std::vector<std::vector<T>>().swap(m_flow);

    m_adj.clear();
    std::vector<std::vector<T>>().swap(m_adj);

    m_level.clear();
    std::vector<T>().swap(m_level);

    m_work.clear();
    std::vector<T>().swap(m_work);
}

template<class T>
void Dinic<T>::MakeEdge(T start_, T end_, bool bidirectional_) {
    if (bidirectional_) {
        m_adj[start_].push_back(end_);
        m_adj[end_].push_back(start_);
    } else {
        m_adj[start_].push_back(end_);
    }
}

template<class T>
void Dinic<T>::SetCap(T start_, T end_, T val_, bool bidirectional_) {
    if (bidirectional_) {
        m_capacity[start_][end_] = val_;
        m_capacity[end_][start_] = val_;
    } else {
        m_capacity[start_][end_] = val_;
    }
}

template<class T>
bool Dinic<T>::MakeLevelGraph() {
    std::fill(m_level.begin(), m_level.end(), -1);
    std::fill(m_work.begin(), m_work.end(), 0);
    std::queue<T> q;
    m_level[m_source] = 0;
    q.push(m_source);

    while (!q.empty()) {
        T cur_node = q.front();
        q.pop();

        if (cur_node == m_sink) {
            return true;
        }

        for (auto &next_node: m_adj[cur_node]) {
            if (m_level[next_node] != -1) continue;
            if (m_capacity[cur_node][next_node] - m_flow[cur_node][next_node] <= 0) continue;
            m_level[next_node] = m_level[cur_node] + 1;
            q.push(next_node);
        }
    }

    return false;
}

template<class T>
T Dinic<T>::FindAugmentingPath(T cur_node, T cur_flow) {
    if (cur_node == m_sink) {
        return cur_flow;
    }

    for (int &i = m_work[cur_node]; i < m_adj[cur_node].size(); ++i) {
        T next_node = m_adj[cur_node][i];
        T spare = m_capacity[cur_node][next_node] - m_flow[cur_node][next_node];
        if (m_level[next_node] != m_level[cur_node] + 1 || spare <= 0) continue;
        T ret = dfs(next_node, std::min(cur_flow, spare));

        if (ret > 0) {
            m_flow[cur_node][next_node] += ret;
            m_flow[next_node][cur_node] -= ret;
            return ret;
        }
    }

    return 0;
}

template<class T>
T Dinic<T>::GetMaxFlow() {
    while (MakeLevelGraph()) {
        while (true) {
            T cur_flow = FindAugmentingPath(m_source, INF);
            if (cur_flow == 0) break;
            m_max_flow += cur_flow;
        }
    }

    return m_max_flow;
}