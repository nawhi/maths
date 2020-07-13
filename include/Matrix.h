

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>

#include "Vector.h"

namespace matrices {

    using vectors::Vector;

    template<typename I>
    class Matrix {
    public:
        Matrix(const std::initializer_list<std::initializer_list<I>>&& init): rows(init.size()) {
            auto i = std::move(init);
            for (const std::initializer_list<I>& row: i) {
                Vector<I> v{row};
                rows.push_back(v);
            }
        }

        friend std::ostream& operator << (std::ostream& os, const Matrix& mx) {
            os << "todo";
            return os;
        }

    private:
        std::vector<Vector<I>> rows;
    };

}

#endif //MATRIX_MATRIX_H
