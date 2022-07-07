#ifndef UNTITLED_SEGTREE_LAZY_H
#define UNTITLED_SEGTREE_LAZY_H

#include <vector>
#include <math.h>

template<class ArrayType>
class Segment_tree_lazy {
private:
    typedef ArrayType A;

    int m_size;
    int m_last_idx;
    std::vector<A> m_arr;
    std::vector<A> m_tree;
    std::vector<A> m_lazy;

    A init(int idx_, int start_, int end_) {
        if (start_ == end_) return m_tree[idx_] = m_arr[start_];

        int mid = (start_ + end_) / 2;
        A lhs = init(2 * idx_, start_, mid);
        A rhs = init(2 * idx_ + 1, mid + 1, end_);

        return m_tree[idx_] = lhs + rhs;
    }

    void propagate(int idx_, int start_, int end_) {
        if (m_lazy[idx_] == 0) return;
        m_tree[idx_] += (end_ - start_ + 1) * m_lazy[idx_];
        if (start_ != end_) {
            m_lazy[2 * idx_] += m_lazy[idx_];
            m_lazy[2 * idx_ + 1] += m_lazy[idx_];
        }
        m_lazy[idx_] = 0;
    }

    A update_(int idx_, int start_, int end_, int left_, int right_, A diff_) {
        propagate(idx_, start_, end_);
        if (right_ < start_ || end_ < left_) return m_tree[idx_];
        if (left_ <= start_ && end_ <= right_) {
            m_tree[idx_] += (end_ - start_ + 1) * diff_;
            if (start_ != end_) {
                m_lazy[2 * idx_] += diff_;
                m_lazy[2 * idx_ + 1] += diff_;
            }
            return m_tree[idx_];
        }

        int mid = (start_ + end_) / 2;
        A lhs = update_(2 * idx_, start_, mid, left_, right_, diff_);
        A rhs = update_(2 * idx_ + 1, mid + 1, end_, left_, right_, diff_);

        return m_tree[idx_] = lhs + rhs;
    }

    A query_(int idx_, int start_, int end_, int left_, int right_) {
        propagate(idx_, start_, end_);
        if (right_ < start_ || end_ < left_) return 0;
        if (left_ <= start_ && end_ <= right_) return m_tree[idx_];

        int mid = (start_ + end_) / 2;
        A lhs = query_(2 * idx_, start_, mid, left_, right_);
        A rhs = query_(2 * idx_ + 1, mid + 1, end_, left_, right_);

        return lhs + rhs;
    }

public:
    explicit Segment_tree_lazy(std::vector<A> &arr_)
            : m_size((int) arr_.size()), m_last_idx(m_size - 1) {
        m_arr.assign(arr_.begin(), arr_.end());
        m_tree.assign(1 << (int) ceil(log2(m_size) + 1), 0);
        m_lazy.assign(1 << (int) ceil(log2(m_size) + 1), 0);
        init(1, 0, m_last_idx);
    }

    void update(int left_, int right_, A diff_) { update_(1, 0, m_last_idx, left_, right_, diff_); }

    A query(int left_, int right_) { return query_(1, 0, m_last_idx, left_, right_); }
};

#endif //UNTITLED_SEGTREE_LAZY_H
