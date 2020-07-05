#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <vector>
#include <sstream>
#include <functional>

namespace vectors {

    class bad_vector : std::exception {
    };

    class dimension_mismatch : std::exception {
    };

    template<typename I>
    class Vector {
    public:
        Vector() = delete;

        Vector(std::initializer_list<I> &&init) : elements(init), dimension(elements.size()) {
            if (init.size() == 0) {
                throw bad_vector();
            }
        }

        I length() const {
            return sqrt(std::reduce(
                    elements.begin(),
                    elements.end(),
                    0, [](const I &acc, const I &i) { return acc + i * i; }));
        }

        Vector norm() const {
            const auto len = length();
            return map([&len](const I &i) { return i / len; });
        }

        bool operator==(const Vector &other) const {
            return elements == other.elements;
        }

        bool operator!=(const Vector &other) const {
            return elements != other.elements;
        }

        Vector operator+(const Vector &other) const {
            return combine(other, [](const I &i, const I &j) { return i + j; });
        }

        Vector operator-(const Vector other) const {
            return combine(other, [](const I &i, const I &j) { return i - j; });
        }

        Vector operator*(const I i) const {
            return map([&i](const I &e) { return e * i; });
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
            os << "[" << v.elements[0];
            std::for_each(v.elements.begin() + 1, v.elements.end(), [&os](const auto &e) { os << ", " << e; });
            os << "]";
            return os;
        }

    private:

        explicit Vector(std::vector<I> elems) : elements(elems), dimension(elems.size()) {}

        void check_dims_match(const Vector &other) const {
            I our_dim = dimension;
            I their_dim = other.dimension;
            if (their_dim != our_dim) {
                throw dimension_mismatch();
            }
        }

        Vector map(std::function<I(I)> op) const {
            std::vector<I> result(dimension);
            std::transform(elements.begin(), elements.end(), result.begin(), op);
            return Vector(result);
        }

        Vector combine(Vector other, std::function<I(I, I)> binary_op) const {
            check_dims_match(other);
            std::vector<I> result(other.dimension);
            std::transform(elements.begin(), elements.end(), other.elements.begin(), result.begin(), binary_op);
            return Vector(result);
        }

        const std::vector<I> elements;
        const I dimension;
    };

}
#endif //MATRIX_VECTOR_H

