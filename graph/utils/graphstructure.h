#ifndef UNTITLED_GRAPHSTRUCTURE_H
#define UNTITLED_GRAPHSTRUCTURE_H

#include <cstdlib>
#include <string>
#include <cassert>
#include <type_traits>

template<class T1, class T2>
class Node {
private:
    static_assert(!(std::is_floating_point<T1>::value
                    || std::is_same<bool, T1>::value));

    static_assert(!(std::is_unsigned<T2>::value
                    || std::is_same<bool, T2>::value
                    || std::is_same<char, T2>::value
                    || std::is_same<char16_t, T2>::value
                    || std::is_same<char32_t, T2>::value
                    || std::is_same<std::string, T2>::value));

    T1 m_node;
    T2 m_weight;

public:
    Node(T1 _Node, T2 _Weight = 1)
            : m_node(_Node), m_weight(_Weight) {};

    T1 node() { return m_node; }

    T2 weight() { return m_weight; }

    bool operator<(const Node &n) const { return n.m_weight < m_weight; }

    ~Node() {}
};

template<class T1, class T2>
class TreeNode : Node<T1, T2> {
private:
    Node<T1, T2> m_parent;
    Node<T1, T2> m_leftchild;
    Node<T1, T2> m_rightchild;

public:
    TreeNode(T1 _Id, T1 _Parent, T1 _Leftchild, T1 _Rightchild, T2 _Weight = 1)
            : Node<T1, T2>(_Id, _Weight), m_parent(_Parent), m_leftchild(_Leftchild), m_rightchild(_Rightchild) {};

    Node<T1, T2> parent() { return m_parent; }

    Node<T1, T2> lc() { return m_leftchild; }

    Node<T1, T2> rc() { return m_rightchild; }

    ~TreeNode() {}
};

template<class T1, class T2>
class TreapNode : Node<T1, T2> {
private:
    long long m_priority;

public:
    TreapNode(T1 _Id, T2 _Weight)
            : Node<T1, T2>(_Id, _Weight), m_priority(rand()) {};

    ~TreapNode() {};
};

template<class T>
class Edge {
private:
    static_assert(!(std::is_floating_point<T>::value
                    || std::is_same<bool, T>::value));

    T m_from;
    T m_to;
    long long weight;

public:
    Edge(T _From, T _To, long long _Weight = 1)
            : m_from(_From), m_to(_To), weight(_Weight) {};

    ~Edge() {}
};

template<class T>
class Point {
private:
    static_assert(!(std::is_same<bool, T>::value
                    || std::is_same<char, T>::value
                    || std::is_same<char16_t, T>::value
                    || std::is_same<char32_t, T>::value
                    || std::is_same<std::string, T>::value));

    T m_x;
    T m_y;
    T m_weight;

public:
    Point(T _X, T _Y, T _Weight)
            : m_x(_X), m_y(_Y), m_weight(_Weight) {};

    ~Point() {};
};

#endif //UNTITLED_GRAPHSTRUCTURE_H