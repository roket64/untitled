#include <vector>
#include <queue>
#include "graph/graphstructure.h"

#define INF 0x3f3f3f3f

template<class T1, class T2>
class Dijkstra {
private:
    using ntype = typename std::enable_if_t
            <!(std::is_floating_point<T1>::value
               || std::is_same<bool, T1>::value)
             && (std::is_integral<T1>::value
                 || std::is_same<std::string, T1>::value), T1>;

    using wtype = typename std::enable_if_t
            <!(std::is_unsigned<T2>::value
               || std::is_same<bool, T2>::value
               || std::is_same<char, T2>::value
               || std::is_same<char16_t, T2>::value
               || std::is_same<char32_t, T2>::value
               || std::is_same<std::string, T2>::value)
             && (std::is_integral<T2>::value
                 || std::is_floating_point<T2>::value), T2>;

    std::vector<std::vector<Node<ntype, wtype>>> adj_list;
    std::vector<wtype> distance;

public:
    Dijkstra(int _Size) {
        this->distance.assign(_Size, INF);
    };

    ~Dijkstra() {
        distance.clear();
        std::vector<wtype>().swap(distance);
        adj_list.clear();
        std::vector<Node<ntype, wtype>>().swap(adj_list);
    };

    void MakeEdge(ntype _Start, ntype _End, wtype _Weight, bool _Bidirectional) {
        if (_Bidirectional) {
            adj_list[_Start].push_back({_End, _Weight});
            adj_list[_End].push_back({_Start, _Weight});
        } else {
            adj_list[_Start].push_back({_End, _Weight});
        }
    }

    void GetMinDistance(ntype _Start) {
        std::priority_queue<Node<ntype, wtype>> pq;
        distance[_Start] = 0;
        pq.push({_Start, distance[_Start]});

        while (!pq.empty()) {
            auto cur = pq.top();
            ntype cur_node = cur.GetNode();
            wtype cur_dist = cur.GetWeight();

            if (distance[cur_node] < cur_dist) continue;
            for (auto next: adj_list[cur_node]) {
                ntype next_node = next.GetNode();
                wtype next_dist = next.GetWeight();
                wtype cost = distance[cur_node] + next_dist;

                if(distance[next_node] <= cost) continue;
                distance[next_node] = cost;
                pq.push({next_node, distance[next_node]});
            }
        }
    }
};