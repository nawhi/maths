#include <cmath>

namespace linalg::vectors {

    template <typename T>
    T len(const std::vector<T>& input) {
        auto sum_squares = std::reduce(
                input.begin(),
                input.end(),
                0, [](const T &acc, const T& prev) { return acc + prev * prev; });
        return sqrt(sum_squares);
    }

    std::vector<int> norm(const std::vector<int>& input) {
        return { input[0] / len(input) };
    }
}

#ifndef MATRIX_NORM_H
#define MATRIX_NORM_H

#endif //MATRIX_NORM_H
