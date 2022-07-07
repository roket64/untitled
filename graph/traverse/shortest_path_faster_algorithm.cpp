#include "shortest_path_faster_algorithm.h"
#include <deque>

#define INF 0x3f3f3f3f

template<class T>
spfa<T>::spfa(T size_)
        : m_size(size_) {
    m_adj.assign(size_ + 1, std::vector<T>());
    m_distance.assign(size_ + 1, 0);
    m_occurred.assign(size_ + 1, 0);
    m_inq.assign(size_ + 1, 0);
}

template<class T>
spfa<T>::~spfa() {
    m_adj.clear();
    std::vector<std::vector<T>>().swap(m_adj);

    m_distance.clear();
    std::vector<T>().swap(m_distance);

    m_occurred.clear();
    std::vector<T>().swap(m_occurred);

    m_inq.clear();
    std::vector<bool>().swap(m_inq);
}

template<class T>
void spfa<T>::MakeEdge(T start_, T end_, T weight_, bool bidirectional_) {
    if (bidirectional_) {
        m_adj[start_].push_back(Node(end_, weight_));
        m_adj[end_].push_back(Node(end_, weight_));
    } else {
        m_adj[start_].push_back(Node(end_, weight_));
    }
}

template<class T>
bool spfa<T>::FindShortestPath(T start_) {
    std::fill(m_distance.begin(), m_distance.end(), INF);
    std::deque<T> deq;
    m_inq[start_] = true;
    m_distance[start_] = 0;
    deq.push_back(start_);

    while (!deq.empty()) {
        T cur_node = deq.front();
        m_inq[cur_node] = false;
        deq.pop_front();

        for (auto &[next_node, next_weight]: m_adj[cur_node]) {
            T cost = m_distance[cur_node] + next_weight;
            // update distance only if new cost is shorter than before
            if (m_distance[next_node] < cost) continue;
            m_distance[next_node] = cost;

            if (!m_inq[next_node]) {
                // return false when negative cycle is found
                if (++m_occurred[next_node] >= m_size) {
                    return false;
                }

                m_inq[next_node] = true;
                // small-label-first optimization
                if (m_distance[next_node] < m_distance[deq.front()]) {
                    deq.push_front(next_node);
                } else {
                    deq.push_back(next_node);
                }
            }
        }
    }

    return true;
}