#ifndef UNTITLED_SEGTREE_LAZY_H
#define UNTITLED_SEGTREE_LAZY_H

#include <vector>
#include <math.h>

template<class ArrayType>
class segment_tree_lazy {
private:
    typedef ArrayType A;

    int m_size;
    int m_last_idx;
    std::vector<A> m_arr;
    std::vector<A> m_tree;
    std::vector<A> m_lazy;

    A init(int idx, int start, int end) {
        // leaf 노드의 경우
        if (start == end) return m_tree[idx] = m_arr[start];

        int mid = (start + end) / 2;
        A lhs = init(2 * idx, start, mid);
        A rhs = init(2 * idx + 1, mid + 1, end);

        return m_tree[idx] = lhs + rhs;
    }

    // idx의 propagation을 하는 함수
    void propagate(int idx, int start, int end) {
        // lazy값이 0이라면 할 일 없음
        if (m_lazy[idx] == 0) return;
        // 하위 노드의 개수(end - start + 1) * lazy만큼 값 증가
        m_tree[idx] += (end - start + 1) * m_lazy[idx];
        // leaf 노드가 아닌 경우
        if (start != end) {
            // 하위 lazy 노드로 lazy 값 전파
            m_lazy[2 * idx] += m_lazy[idx];
            m_lazy[2 * idx + 1] += m_lazy[idx];
        }
        // propagation된 노드는 0으로 초기화
        m_lazy[idx] = 0;
    }

    // 구간 [start, end]의 값을 diff만큼 증가시키는 함수
    A update(int idx, int start, int end, int left, int right, A diff) {
        // idx의 propagate 수행
        propagate(idx, start, end);
        // 범위 밖이라면, 기존 트리의 값 반환
        if (right < start || end < left) return m_tree[idx];
        // 범위에 완전히 포함되는 경우
        if (left <= start && end <= right) {
            // 하위 노드의 개수(end- start + 1) * diff만큼 값 증가
            m_tree[idx] += (end - start + 1) * diff;
            // leaf 노드가 아니라면 하위 lazy 노드에 lazy값 증가
            if (start != end) {
                m_lazy[2 * idx] += diff;
                m_lazy[2 * idx + 1] += diff;
            }

            // 업데이트된 값 반환
            return m_tree[idx];
        }

        // 위 두 개의 경우가 아니라면, 두 개의 하위 노드로 나누어 계속 진행
        int mid = (start + end) / 2;
        A lhs = update(2 * idx, start, mid, left, right, diff);
        A rhs = update(2 * idx + 1, mid + 1, end, left, right, diff);

        return m_tree[idx] = lhs + rhs;
    }

    // 구간 [left, right]의 합을 묻는 쿼리를 답하는 함수
    A query(int idx, int start, int end, int left, int right) {
        // idx의 propagation 수행
        propagate(idx, start, end);
        // 범위 밖이라면 0 반환
        if (right < start || end < left) return 0;
        // 범위에 완전히 포함된다면 해당 트리의 노드 값 반환
        if (left <= start && end <= right) return m_tree[idx];

        // 위 두 경우가 아니라면, 두 개의 하위 노드로 나누어 계속 진행
        int mid = (start + end) / 2;
        A lhs = query(2 * idx, start, mid, left, right);
        A rhs = query(2 * idx + 1, mid + 1, end, left, right);

        return lhs + rhs;
    }

public:
    explicit segment_tree_lazy(std::vector<A> &arr_)
            : m_last_idx(static_cast<int>(arr_.size()) - 1) {
        m_arr.assign(arr_.begin(), arr_.end());
        m_tree.assign(1 << (int) ceil(log2(static_cast<int>(arr_.size())) + 1), 0);
        m_lazy.assign(1 << (int) ceil(log2(static_cast<int>(arr_.size())) + 1), 0);
        init(1, 0, m_last_idx);
    }

    // 구간 [left, right]의 값을 diff만큼 증가시키는 함수
    void update(int left, int right, A diff) { update(1, 0, m_last_idx, left, right, diff); }

    // 구간 [left, right]의 합을 묻는 쿼리에 답하는 함수
    A query(int left, int right) { return query(1, 0, m_last_idx, left, right); }
};

#endif
