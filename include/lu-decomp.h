#include "Matrix.h"
/**
 * @param mx input matrix
 * @param r_from the row to add from
 * @param r_to the row to add to
 * @param factor number by which to multiply r_from 
 *        before adding it to r_to
 * @return a new matrix formed by adding factor times 
 *         the row with index r_from to the row 
 *         with index r_to
 */
template<typename T, int size>
Matrix<T, size> add_row_multiple(const Matrix<T, size>& mx, int r_from, int r_to, T factor)
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


/**
 * Perform an LU-decomposition on a matrix.
 * @param mx an invertible Matrix with nonzero pivots
 * @return a pair p where p.first is a lower diagonal 
 *        matrix with ones on the diagonal, p.second 
 *        is an upper diagonal matrix with any numbers
 *        on the diagonal, and p.first * p.second == mx
 */
template <typename T, int size>
std::pair<Matrix<T, size>, Matrix<T, size>> lu_decomp(Matrix<T, size> mx)
{
    // Begin with I * mx
    Matrix<T, size> l = Matrix<T, size>::identity();
    Matrix<T, size> u = mx;

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

