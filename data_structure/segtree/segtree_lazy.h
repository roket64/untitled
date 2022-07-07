#ifndef UNTITLED_SEGTREE_LAZY_H
#define UNTITLED_SEGTREE_LAZY_H

#include <vector>
#include <math.h>

template<class T>
class Segment_tree_lazy {
private:
    std::vector<T> m_arr;
    std::vector<T> m_tree;
    std::vector<T> m_lazy;

    T init(std::vector<T> arr_, int idx_, int start_, int end_) {
        if (start_ == end_) return m_tree[idx_] = arr_[start_];

        int mid = (start_ + end_) / 2;
        T lhs = init(arr_, 2 * idx_, start_, mid);
        T rhs = init(arr_, 2 * idx_ + 1, mid + 1, end_);

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

public:
    Segment_tree_lazy(std::vector<T> &arr_) {
        int sz = arr_.size();
//        m_arr.assign(arr_.begin(), arr_.end());
        m_tree.assign(1 << (int) ceil(log2(sz) + 1), 0);
        m_lazy.assign(1 << (int) ceil(log2(sz) + 1), 0);
        init(arr_, 1, 0, sz - 1);
    }

    T update(int idx_, int start_, int end_, int left_, int right_, T diff_) {
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
        T lhs = update(2 * idx_, start_, mid, left_, right_, diff_);
        T rhs = update(2 * idx_ + 1, mid + 1, end_, left_, right_, diff_);

        return m_tree[idx_] = lhs + rhs;
    }

    T query(int idx_, int start_, int end_, int left_, int right_) {
        propagate(idx_, start_, end_);
        if (right_ < start_ || end_ < left_) return 0;
        if (left_ <= start_ && end_ <= right_) return m_tree[idx_];

        int mid = (start_ + end_) / 2;
        T lhs = query(2 * idx_, start_, mid, left_, right_);
        T rhs = query(2 * idx_ + 1, mid + 1, end_, left_, right_);

        return lhs + rhs;
    }
};

#endif //UNTITLED_SEGTREE_LAZY_H
