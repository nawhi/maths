#include "matrix.h"

const Matrix<int> IDENTITY = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

/**
 * @param mx input matrix
 * @param r_from the row to add from
 * @param r_to the row to add to
 * @param factor number by which to multiply r_from 
 *        before adding it to r_to
 * @return a new matrix formed by adding f times 
 *         the row with index r_from to the row 
 *         with index r_to
 */
template<typename T>
Matrix<T> add_row_multiple(const Matrix<T>& mx, int r_from, int r_to, T factor)
{
    auto res = mx;
    for (int col=0; col<4; col++)
    {
        res.set(
            r_to, col,
            mx(r_to, col) + factor * mx(r_from, col)
        );
    }
    return res;
}


/**
 * Perform an LU-decomposition on a matrix.
 * @param mx an invertible Matrix with nonzero pivots
 * @return a pair p where p.first is a lower diagonal 
 *        matrix with ones on the diagonal, p.second 
 *        is an upper diagonal matrix which may have
 *        anything on the diagnonal, and 
 *        p.first * p.second = mx
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T>> lu_decomp(Matrix<T> mx)
{
    // Begin with I * mx
    Matrix<T> l = IDENTITY;
    Matrix<T> u = mx;

    for (int c = 0; c < 3 /* stop before final row */; c++)
    {
        for (int k = c+1; k < 4; k++)
        {
            // What's needed to eliminate position (c+k, c)?
            T factor = u(k, c) / u(c, c);

            // Eliminate
            u = add_row_multiple(u, c, k, -factor);

            // Update L
            l.set(k, c, factor);
        }
    }
    return std::make_pair(l, u);
}

