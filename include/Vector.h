#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <vector>
#include <sstream>

namespace vectors {

    class bad_vector: std::exception {};

    template<typename I>
    class Vector {
    public:
        Vector() = delete;

        Vector(std::initializer_list<I> &&init) : elements(init), dimension(elements.size()) {
            if (init.size() == 0) {
                throw bad_vector();
            }
        }

        I len() const {
            return sqrt(std::reduce(
                    elements.begin(),
                    elements.end(),
                    0, [](const I &acc, const I &i) { return acc + i * i; }));
        }

        Vector norm() const {
            const auto l = len();
            auto result = elements;
            std::transform(result.begin(), result.end(), result.begin(),
                           [&l](const I &i) { return i / l; });
            return Vector(result);
        }

        bool operator==(Vector other) const {
            return elements == other.elements;
        }

        bool operator!=(Vector other) const {
            return elements != other.elements;
        }

        Vector operator+(Vector other) const {
            auto result = elements;
            std::transform(result.begin(), result.end(), result.begin(), other.elements.begin(),
                           [](const I &i1, const I &i2) { return i1 + i2; });
            return Vector(result);
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
            os << "[" << v.elements[0];
            std::for_each(v.elements.begin() + 1, v.elements.end(), [&os](const auto &e) { os << ", " << e; });
            os << "]";
            return os;
        }

    private:
        explicit Vector(std::vector<I> elems) : elements(elems), dimension(elems.size()) {}

        std::vector<I> elements;
        I dimension;
    };

}
#endif //MATRIX_VECTOR_H

