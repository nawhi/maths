#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <cmath>
#include <vector>
#include <sstream>
#include <functional>
#include <iostream>

namespace vectors {

    class bad_vector : std::exception {
    };

    class dimension_mismatch : std::exception {
    public:
        explicit dimension_mismatch(const std::string &&message) : msg(message) {}

        [[nodiscard]] const char *what() const noexcept override { return msg.c_str(); }

    private:
        const std::string &msg;
    };

    template<typename I>
    class Vector {
    public:
        Vector() = delete;

        static Vector zero(I dimension) {
            if (dimension <= 0) {
                throw bad_vector();
            }
            std::vector<I> v(dimension);
            v.assign(dimension, 0);
            return Vector(v);
        }

        Vector(std::initializer_list<I> &&init) : _elements(init), _dimension(_elements.size()) {
            if (init.size() == 0) {
                throw bad_vector();
            }
        }

        explicit Vector(std::vector<I> elems) : _elements(elems), _dimension(elems.size()) {}

        size_t dimension() const {
            return _dimension;
        }

        double length() const {
            static_assert(std::is_floating_point_v<I>);
            return sqrt(mapped_sum(square));
        }

        Vector norm() const {
            const double len = length();
            return map([&len](const I &i) { return i / len; });
        }

        I dot(const Vector &other) const {
            return std::inner_product(_elements.begin(), _elements.end(), other._elements.begin(), I());
        }

        Vector cross(const Vector &other) const {
            if (_dimension != 3 || other._dimension != 3) {
                throw dimension_mismatch("cannot take cross product of non-3d vector");
            }

            const auto &u = _elements, &v = other._elements;

            return {
                    u[1] * v[2] - u[2] * v[1],
                    u[2] * v[0] - u[0] * v[2],
                    u[0] * v[1] - u[1] * v[0]
            };
        }

        Vector project(const Vector &onto) const {
            assert_dims_match(onto);
            const auto onto_sum_squares = onto.mapped_sum(square);
            const auto d = dot(onto);
            return onto.map([&](const I &i) {
                return (i * d) / onto_sum_squares;
            });
        }

        I angle_to(const Vector &other) const {
            static_assert(std::is_floating_point_v<I>);
            assert_dims_match(other);
            const auto &cosine = dot(other) / (length() * other.length());
            return acos((double) cosine);
        }

        bool operator==(const Vector &other) const {
            return _elements == other._elements;
        }

        bool operator!=(const Vector &other) const {
            return _elements != other._elements;
        }

        Vector operator+(const Vector &other) const {
            return combine(other, [](const I &i, const I &j) { return i + j; });
        }

        Vector operator-(const Vector other) const {
            return combine(other, [](const I &i, const I &j) { return i - j; });
        }

        Vector operator*(const I i) const {
            return map([&i](const I &elem) { return elem * i; });
        }

        Vector operator/(const I i) const {
            return map([&i](const I &elem) { return elem / i; });
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
            os << "[" << v._elements[0];
            std::for_each(v._elements.begin() + 1, v._elements.end(), [&os](const auto &e) { os << " " << e; });
            os << "]";
            return os;
        }

    private:
        static I square(const I &i) {
            return i * i;
        }

        Vector map(std::function<I(I)> op) const {
            std::vector<I> result(_dimension);
            std::transform(_elements.begin(), _elements.end(), result.begin(), op);
            return Vector(result);
        }

        Vector combine(const Vector &other, std::function<I(I, I)> binary_op) const {
            assert_dims_match(other);

            std::vector<I> result(other._dimension);
            std::transform(_elements.begin(), _elements.end(), other._elements.begin(), result.begin(), binary_op);
            return Vector(result);
        }

        void assert_dims_match(const Vector &other) const {
            if (other._dimension != _dimension) {
                std::ostringstream os;
                os << "Dimensions differ: " << _dimension << " and " << other._dimension;
                throw dimension_mismatch(os.str());
            }
        }

        I mapped_sum(std::function<I(I)> mapper) const {
            return std::reduce(_elements.begin(), _elements.end(), I(),
                               [&mapper](const I &acc, const I &i) { return acc + mapper(i); });
        }

        const std::vector<I> _elements;
        const size_t _dimension;
    };

}
#endif //MATRIX_VECTOR_H

