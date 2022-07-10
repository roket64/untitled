#ifndef UNTITLED_SEGTREE_DEFAULT_H
#define UNTITLED_SEGTREE_DEFAULT_H

#include <vector>
#include <math.h>

template<class ArrayType>
class segment_tree {
private:
    typedef ArrayType A;

    int m_last_idx;
    std::vector<A> m_arr;
    std::vector<A> m_tree;

    A init(int idx, int start, int end) {
        if (start == end) return m_tree[idx] = m_arr[start];

        int mid = (start + end) / 2;
        A lhs = init(2 * idx, start, mid);
        A rhs = init(2 * idx + 1, mid + 1, end);

        return m_tree[idx] = lhs + rhs;
    }

    // idx에 위치한 노드의 값을 diff만큼 증가시키는 업데이트
    A update(int idx, int start, int end, A diff) {
        // 범위 밖이라면 기존 트리의 값 반환
        if (idx < start || end < idx) return m_tree[idx];
        // leaf 노드에 도달했다면 업데이트 후 반환
        if (start == end) return m_tree[idx] = diff;

        // 두 개의 하위 노드로 나누어 계속 진행
        int mid = (start + end) / 2;
        A lhs = update(2 * idx, start, mid, diff);
        A rhs = update(2 * idx + 1, mid + 1, end, diff);

        return m_tree[idx] = lhs + rhs;
    }

    // 구간 [left, right]의 합을 구하는 쿼리
    A query(int idx, int start, int end, int left, int right) {
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return m_tree[idx];

        int mid = (start + end) / 2;
        A lhs = query(2 * idx, start, mid, left, right);
        A rhs = query(2 * idx + 1, mid + 1, end, left, right);

        return lhs + rhs;
    }

public:
    explicit segment_tree(std::vector<A> &arr)
            : m_last_idx(static_cast<int>(arr.size() - 1)) {
        m_arr.assign(arr.begin(), arr.end());
        m_tree.assign(1 << (int) ceil(log2(static_cast<int>(arr.size())) + 1), 0);
        init(1, 0, m_last_idx);
    }

    void update(int idx, A diff) { update(idx, 0, m_last_idx, diff); }

    A query(int left, int right) { return query(1, 0, m_last_idx, left, right); }
};

#endif
