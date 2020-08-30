

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
            for (const std::initializer_list<I> &row: std::move(init)) {
                Vector<I> v{row};
                _rows.push_back(v);
            }
            _width = _rows[0].dimension();
            _height = _rows.size();
        }

        bool operator==(const Matrix &other) const {
            return _rows == other._rows;
        }

        bool operator!=(const Matrix &other) const {
            return _rows != other._rows;
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

        Vector<I> operator*(const Vector<I> &v) const {
            throw bad_matrix(); // TODO
//            std::vector<I> result(_width);
//            for (size_t i = 0; i < _height; i++) {
//                result.push_back(_rows[i].dot(v));
//            }
//
//            return Vector<I>(result);
        }

        Matrix operator/(const I &i) const {
            return row_map([&i](const auto &row) { return row / i; });
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix &mx) {
            os << mx._rows[0];
            std::for_each(mx._rows.begin() + 1, mx._rows.end(), [&os](const auto &row) { os << "\n" << row; });
            return os;
        }

        size_t width() { return _width; }

        size_t height() { return _height; }

    private:
        std::vector<Vector<I>> _rows;

        size_t _width;
        size_t _height;

        Matrix(std::vector<Vector<I>> rows) : _rows(rows), _width(rows[0].dimension()), _height(rows.size()) {}

        Matrix combine(const Matrix &other, std::function<Vector<I>(Vector<I>, Vector<I>)> binary_op) const {
            std::vector<Vector<I>> result;
            for (size_t i = 0; i < _rows.size(); i++) {
                result.push_back(binary_op(_rows[i], other._rows[i]));
            }
            return Matrix(result);
        }

        Matrix row_map(std::function<Vector<I>(Vector<I>)> mapper) const {
            std::vector<Vector<I>> result;
            for (size_t i = 0; i < _rows.size(); i++) {
                result.push_back(mapper(_rows[i]));
            }
            return result;
        }
    };

}

#endif //MATRIX_MATRIX_H
