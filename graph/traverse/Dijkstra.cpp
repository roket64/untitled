#include <vector>
#include <queue>
#include "../utils/graphstructure.h"

#define INF 0x3f3f3f3f

template<class T1, class T2>
class Dijkstra {
private:
    class Dijkstra_Node : Node<T1, T2> {
    private:
    public:
        Dijkstra_Node(T1 _Node, T2 _Weight)
                : Node<T1, T2>(_Node, _Weight) {};

    };

    std::vector<T2> m_distance;
    std::vector<std::vector<T1>> m_adj_list;

public:
    Dijkstra(int _Size) {
        m_distance.assign(_Size, INF);
        m_adj_list.assign(_Size, std::vector<T1>());
    };

    ~Dijkstra() {
        m_distance.clear();
        m_adj_list.clear();
        std::vector<T2>().swap(m_distance);
        std::vector<std::vector<T1>>().swap(m_adj_list);
    };

    void MakeEdge(T1 _Start, T1 _End, T2 _Weight, bool _Bidirectional) {
        if (_Bidirectional) {
            m_adj_list[_Start].push_back(Dijkstra_Node(_End, _Weight));
            m_adj_list[_End].push_back(Dijkstra_Node(_Start, _Weight));
        } else {
            m_adj_list[_Start].push_back(Dijkstra_Node(_End, _Weight));
        }
    }
};