

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

namespace matrices {

    template<typename I>
    class Matrix {
    public:
        explicit Matrix(const std::initializer_list<std::initializer_list<I>>&& elems) {}

        friend std::ostream& operator << (std::ostream& os, const Matrix mx) {
            os << "todo";
            return os;
        }

    private:
//        std::vector<Vector<I>>
    };

}

#endif //MATRIX_MATRIX_H
