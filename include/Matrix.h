

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
        Matrix(const std::initializer_list<std::initializer_list<I>>&& init) {
            if (init.size() == 0)
                throw bad_matrix();
            auto i = std::move(init);
            for (const std::initializer_list<I>& row: i) {
                Vector<I> v{row};
                rows.push_back(v);
            }
        }

        friend std::ostream& operator << (std::ostream& os, const Matrix& mx) {
            os << mx.rows[0];
            std::for_each(mx.rows.begin() + 1, mx.rows.end(), [&os](const auto& row) { os << "\n" << row; });
            return os;
        }

    private:
        std::vector<Vector<I>> rows;
    };

}

#endif //MATRIX_MATRIX_H
