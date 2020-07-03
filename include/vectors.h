#include <cmath>

namespace linalg::vectors {

    template<typename T>
    T len(const std::vector<T> &input) {
        auto sum_squares = std::reduce(
                input.begin(),
                input.end(),
                0, [](const T &acc, const T &prev) { return acc + prev * prev; });
        return sqrt(sum_squares);
    }

    template<typename T>
    std::vector<T> norm(const std::vector<T> &input) {
        const auto l = len(input);
        auto result = input;
        std::transform(result.begin(), result.end(), result.begin(),
                       [&l](const T &i) { return i / l; });
        return result;
    }
}

#ifndef MATRIX_NORM_H
#define MATRIX_NORM_H

#endif //MATRIX_NORM_H
