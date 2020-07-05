#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <vector>

template <typename I>
class Vector {
public:
    Vector(std::initializer_list<I>&& init): elems(init), dims(elems.size()) {}

    bool operator==(Vector other) const {
        return elems == other.elems;
    }

    bool operator!=(Vector other) const {
        return elems != other.elems;
    }

    I len() const {
        return sqrt(std::reduce(
                elems.begin(),
                elems.end(),
                0, [](const I &acc, const I &prev) { return acc + prev * prev; }));
    }

    Vector norm() const {
        const auto l = len();
        auto result = elems;
        std::transform(result.begin(), result.end(), result.begin(),
                       [&l](const I &i) { return i / l; });
        return Vector(result);
    }

private:
    explicit Vector(std::vector<I> elems): elems(elems), dims(elems.size()) {}

    std::vector<I> elems;
    I dims;
};

#endif //MATRIX_VECTOR_H
