#ifndef UNTITLED_GRAPHSTRUCTURE_H
#define UNTITLED_GRAPHSTRUCTURE_H

#include <cstdlib>
#include <string>
#include <type_traits>

template<class T1, class T2>
class Node {
private:
    // can use all integral types but not floating point or bool type
    using ntype = typename std::enable_if_t
            <!(std::is_floating_point<T1>::value
               || std::is_same<bool, T1>::value)
             && (std::is_integral<T1>::value
                 || std::is_same<std::string, T1>::value), T1>;

    // can use all integral and floating point types but not unsigned or bool, char, string type
    using wtype = typename std::enable_if_t
            <!(std::is_unsigned<T2>::value
               || std::is_same<bool, T2>::value
               || std::is_same<char, T2>::value
               || std::is_same<char16_t, T2>::value
               || std::is_same<char32_t, T2>::value
               || std::is_same<std::string, T2>::value)
             && (std::is_integral<T2>::value
                 || std::is_floating_point<T2>::value), T2>;

    ntype node;
    wtype weight;

public:
    Node(T1 _Node, T2 _Weight = 1)
            : node(_Node), weight(_Weight) {}

    ntype GetNode() { return node; }

    wtype GetWeight() { return weight; }

    // in priority queue, this gives higher priority to lower weight edge
    bool operator<(const Node &n) const { return n.weight < weight; }

    ~Node() {}
};

template<class T>
class Edge {
private:
    T from;
    T to;
    long long weight;

public:
    Edge(T _From, T _To, long long _Weight = 1)
            : from(_From), to(_To), weight(_Weight) {}

    ~Edge() {}
};

template<class T1, class T2>
class TreeNode : Node<T1, T2> {
private:
    Node<T1, T2> parent;
    Node<T1, T2> left_child;
    Node<T1, T2> right_child;

public:
    TreeNode(T1 _Id, T1 _Parent, T1 _Leftchild, T1 _Rightchild, T2 _Weight)
            : Node<T1, T2>(_Id, _Weight), parent(_Parent), left_child(_Leftchild), right_child(_Rightchild) {}

    Node<T1, T2> GetParent() { return parent; }

    Node<T1, T2> Getlc() { return left_child; }

    Node<T1, T2> Getrc() { return right_child; }

    ~TreeNode() {}
};

template<class T1, class T2>
class TreapNode : Node<T1, T2> {
private:
    T1 priority;

public:
    TreapNode(T1 _Id, T2 _Weight)
            : Node<T1, T2>(_Id, _Weight), priority(rand()) {}

    ~TreapNode() {}
};

template<class T>
class Point {
private:
    T x;
    T y;
    long long weight;

public:
    Point(T _X, T _Y, long long _Weight)
            : x(_X), y(_Y), weight(_Weight) {}

    ~Point() {}
};

/**/

#endif //UNTITLED_GRAPHSTRUCTURE_H