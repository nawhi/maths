

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include "Vector.h"

namespace matrices {

    class bad_matrix : std::exception {
    };

    using vectors::Vector;

    template<typename I>
    class Matrix {
    public:
        Matrix(const std::initializer_list<std::initializer_list<I>> &&init) {
            if (init.size() == 0)
                throw bad_matrix();
            auto i = std::move(init);
            for (const std::initializer_list<I> &row: i) {
                Vector<I> v{row};
                rows.push_back(v);
            }
        }

        bool operator==(const Matrix &other) const {
            return rows == other.rows;
        }

        bool operator!=(const Matrix &other) const {
            return rows != other.rows;
        }

        Matrix operator+(const Matrix &other) const {
            return combine(other, [](const auto &a, const auto &b) { return a + b; });
        }

        Matrix operator-(const Matrix &other) const {
            return combine(other, [](const auto &a, const auto &b) { return a - b; });
        }

        Matrix operator*(const I &i) const {
            return row_map([&i](const auto &row) { return row * i; });
        }

        Matrix operator/(const I &i) const {
            return row_map([&i](const auto &row) { return row / i; });
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix &mx) {
            os << mx.rows[0];
            std::for_each(mx.rows.begin() + 1, mx.rows.end(), [&os](const auto &row) { os << "\n" << row; });
            return os;
        }

    private:
        std::vector<Vector<I>> rows;

        Matrix(std::vector<Vector<I>> rows) : rows(rows) {}

        Matrix combine(const Matrix &other, std::function<Vector<I>(Vector<I>, Vector<I>)> binary_op) const {
            std::vector<Vector<I>> result;
            for (size_t i = 0; i < rows.size(); i++) {
                result.push_back(binary_op(rows[i], other.rows[i]));
            }
            return Matrix(result);
        }

        Matrix row_map(std::function<Vector<I>(Vector<I>)> mapper) const {
            std::vector<Vector<I>> result;
            for (size_t i = 0; i < rows.size(); i++) {
                result.push_back(mapper(rows[i]));
            }
            return result;
        }
    };

}

#endif //MATRIX_MATRIX_H
