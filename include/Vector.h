#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <vector>
#include <sstream>
#include <functional>

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

        Vector(std::initializer_list<I> &&init) : elements(init), dimension(elements.size()) {
            if (init.size() == 0) {
                throw bad_vector();
            }
        }

        explicit Vector(std::vector<I> elems) : elements(elems), dimension(elems.size()) {}

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

        I dot(const Vector &other) const {
            return std::inner_product(elements.begin(), elements.end(), other.elements.begin(), 0);
        }

        Vector cross(const Vector& other) const {
            if (dimension != 3 || other.dimension != 3) {
                throw dimension_mismatch("cannot take cross product of non-3d vector");
            }

            const auto& a = elements, b = other.elements;

            return Vector{
                a[1]*b[2] - b[1]*a[2],
                a[0]*b[2] - b[0]*a[2],
                a[0]*b[1] - b[0]*a[1]
            };
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
            std::for_each(v.elements.begin() + 1, v.elements.end(), [&os](const auto &e) { os << " " << e; });
            os << "]";
            return os;
        }

    private:

        Vector map(std::function<I(I)> op) const {
            std::vector<I> result(dimension);
            std::transform(elements.begin(), elements.end(), result.begin(), op);
            return Vector(result);
        }

        Vector combine(Vector other, std::function<I(I, I)> binary_op) const {
            if (other.dimension != dimension) {
                std::ostringstream os;
                os << "Dimensions differ: " << dimension << " and " << other.dimension;
                throw dimension_mismatch(os.str());
            }

            std::vector<I> result(other.dimension);
            std::transform(elements.begin(), elements.end(), other.elements.begin(), result.begin(), binary_op);
            return Vector(result);
        }

        const std::vector<I> elements;
        const I dimension;
    };

}
#endif //MATRIX_VECTOR_H

