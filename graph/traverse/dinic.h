#ifndef UNTITLED_DINIC_H
#define UNTITLED_DINIC_H

#include <vector>

template<class T>
class Dinic {
private:
    std::vector<std::vector<T>> m_capacity;
    std::vector<std::vector<T>> m_flow;
    std::vector<std::vector<T>> m_adj;
    std::vector<T> m_level;
    std::vector<T> m_work;
    T m_source;
    T m_sink;
    T m_max_flow;

public:
    Dinic(T source_, T sink_, T size_);

    ~Dinic();

    void MakeEdge(T start_, T end_, bool bidirectional_ = false);

    void SetCap(T start_, T end_, T val_, bool bidirectional_ = false);

    bool MakeLevelGraph();

    T FindAugmentingPath(T cur_node, T cur_flow);

    T GetMaxFlow();
};

#endif //UNTITLED_DINIC_H
