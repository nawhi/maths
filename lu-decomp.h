#include "matrix.h"

/**
 * Perform an LU-decomposition on a matrix.
 * @param mx an invertible Matrix with nonzero pivots
 * @return a pair p where p.first is a lower diagonal 
 *        matrix, p.second is an upper diagonal matrix, and
 *        p.first * p.second = mx
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T>> lu_decomp(Matrix<T> mx);

