#ifndef UNTITLED_SHORTEST_PATH_FASTER_ALGORITHM_H
#define UNTITLED_SHORTEST_PATH_FASTER_ALGORITHM_H

#include <vector>

template<class T>
class spfa {
private:
    struct Node {
        T m_node;
        T m_weight;

        Node(T node_, T weight_ = 1)
                : m_node(node_), m_weight(weight_) {}
    };

    std::vector<std::vector<Node>> m_adj;
    std::vector<T> m_distance;
    std::vector<T> m_occurred;
    std::vector<bool> m_inq;
    T m_size;

public:
    spfa(T size_);

    ~spfa();

    void MakeEdge(T start_, T end_, T weight_, bool bidirectional_ = false);

    bool FindShortestPath(T start_);

    std::vector<T> GetDistance() { return m_distance; }
};

#endif
