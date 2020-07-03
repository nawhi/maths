#include <cmath>

namespace linalg::vectors {

    int len(const std::vector<int>& input) {
        int sum_squares = std::reduce(
                input.begin(),
                input.end(),
                0, [](const int &acc, const int& prev) { return acc + prev * prev; });
        return sqrt(sum_squares);
    }

    std::vector<int> norm(const std::vector<int>& input) {
        return input;
    }
}

#ifndef MATRIX_NORM_H
#define MATRIX_NORM_H

#endif //MATRIX_NORM_H
