# To Do

## Fractions
- [x] `==`
- [x] `*`
- [x] `/`
- [x] `+`
- [x] `-`
- [x] `>`
- [x] `>=`
- [x] `<`
- [x] `<=`
- [x] always handle zero correctly

## Vectors
with `Vector` class
- [x] Calculate length 
- [x] Normalize (set length to 1)
- [x] Vector +/- Vector
- [x] Vector * scalar (check 1/x too)
- [x] Dot product (`.dot(Vector)`)
- [x] Cross product (`.cross(Vector)`) 3d only
- [ ] Vector projection (`.project(Vector)`)
- [ ] Angle between two vectors (`)
- [ ] Change basis (`.to_basis(Matrix)`)
- [ ] Gram-Schmidt process - make a basis set orthonormal

Snags:
- [ ] dimension should be int, not I
- [ ] use I(), not 0, to construct a zero

## Matrices
with `Matrix` class (all square)
- [ ] Compute matrix plus/minus:
  - [ ] scalar
  - [ ] vector
  - [ ] matrix
- Compute matrix times:
  - [ ] scalar (inc 1/x)
  - [ ] vector
  - [ ] matrix
- [ ] Find eigenvalues of a matrix
  - [ ] characteristic polynomail
  - [ ] power rule
- [ ] Test if given vector is an eigenvector of given matrix
- [ ] Change a matrix to its eigenbasis (?)
- [ ] Compute matrix to the power N:
  - [ ] brute-force
  - [ ] by changing to the eigenbasis (with exception if not possible)
- [ ] Compute inverse
  - [ ] with Gaussian elimination
- [ ] Calculate rotation matrix for a given angle
- [ ] Calculate LU-decomposition
- [ ] Calculate determinant
  - [ ] using QR-decomposition
  - [ ] brute-force
- [ ] Calculate null space
  
## Systems
- [ ] Solve a system using Cramer’s rule
- [ ] Solve a system using Gaussian elimination

## Other
- [ ] Can the size parameter be templated?
- [ ] Cross products in other dimensions
- [ ] Support non-square matrices - different class, or generalisation?