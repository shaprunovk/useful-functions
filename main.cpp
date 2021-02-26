#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>


template <typename InIter1, typename InIter2, typename OutIter>
OutIter SetDifference(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2, OutIter out) {
    while (first1 != last1) {
        if (first2 == last2) {
            return std::copy(first1, last1, out);
        }
        if (*first1 < *first2) {
            *out++ = *first1++;
        } else {
            if (*first2 >= *first1) {
                ++first1;
            }
            ++first2;
        }
    }
    return out;
}


template <typename Iter>
Iter Unique(Iter first, Iter last) {
    if (first == last) {
        return first;
    }
    auto position_to_change = first;
    while (++first != last) {
        if (*position_to_change != *first && ++position_to_change != first) {
            *position_to_change = std::move(*first);
        }
    }
    return ++position_to_change;
}


template <typename InIter, typename OutIter, typename Predicate>
OutIter RemoveCopyIf(InIter first, InIter last, OutIter out, Predicate f) {
    for (auto it = first; it != last; ++it) {
        if (!f(*it)) {
            *out = *it;
            ++out;
        }
    }
    return out;
}


template <typename InIter, typename OutIter>
OutIter ReverseCopy(InIter first, InIter last, OutIter out) {
    while (last != first) {
        --last;
        *out = *last;
        ++out;
    }
    return out;
}


template <typename It, typename Pred>
bool AnyOf(It first, It last, Pred f) {
    for (auto jt = first; jt != last; ++jt) {
        if (f(*jt)) {
            return true;
        }
    }
    return false;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    auto file = freopen("input.txt", "r", stdin);
    if (!file) {
        std::cout << "Cannot open this file\n";
    }
    int n, k;
    std::cin >> n >> k;
    std::vector<int> first(n);
    for (int i = 0; i != n; ++i) {
        std::cin >> first[i];
    }
    for (int i = 0; i != k; ++i) {
        int number;
        std::cin >> number;
        auto lower = std::lower_bound(first.begin(), first.end(), number);
        if (lower != first.begin() && lower != first.end()) {
            auto prev = std::prev(lower);
            abs(number - *prev) <= abs(number - *lower)
            ? std::cout << *prev << '\n'
            : std::cout << *lower << '\n';
        } else if (lower != first.end()) {
            std::cout << *lower << '\n';
        } else {
            auto prev = --lower;
            std::cout << *prev << '\n';
        }
    }
    return 0;
}
