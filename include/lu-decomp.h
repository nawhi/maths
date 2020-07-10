#include "MatrixOld.h"

namespace matrices::old {

    template<typename T, int size>
    MatrixOld<T, size> add_row_multiple(const MatrixOld<T, size>& mx, int r_from, int r_to, T factor)
    {
        auto res = mx;
        for (int col=0; col<size; col++)
        {
            res.set(
                r_to, col,
                mx(r_to, col) + factor * mx(r_from, col)
            );
        }
        return res;
    }


    template <typename T, int size>
    std::pair<MatrixOld < T, size>, MatrixOld<T, size>> lu_decomp(MatrixOld<T, size> mx)
    {
        // Begin with I * mx
        MatrixOld<T, size> l = MatrixOld < T, size>::identity();
        MatrixOld<T, size> u = mx;

        for (int c = 0; c < size-1 /* stop before final row */; c++)
        {
            for (int k = c+1; k < size; k++)
            {
                // What's needed to eliminate position (k, c)?
                T factor = u(k, c) / u(c, c);

                // Eliminate
                u = add_row_multiple(u, c, k, -factor);

                // Update L
                l.set(k, c, factor);
            }
        }
        return std::make_pair(l, u);
    }

}