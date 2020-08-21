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
- [x] no-args constructor produces zero fraction
- [x] enforce integral constraint for template (or remove it)

## Vectors
- [x] Calculate length 
- [x] Normalize (set length to 1)
- [x] Vector +/- Vector
- [x] Vector * scalar (check 1/x too)
- [x] Dot product (`.dot(Vector)`)
- [x] Cross product (`.cross(Vector)`) 3d only
- [x] Vector projection (`.project(Vector)`)
- [x] Angle between two vectors

## Matrices
with `Matrix` class (all square)
- [x] Matrix string repr
- [x] Matrix plus Matrix
- [ ] Matrix minus Matrix
- Matrix times:
  - [ ] scalar (inc 1/x)
  - [ ] vector
  - [ ] matrix
- [ ] Find eigenvalues of a matrix
  - [ ] characteristic polynomial
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

## Bases
- [ ] Change a vector to a given basis
- [ ] Make basis vectors orthonormal using Gram-Schmidt
  
## Systems
- [ ] Solve a system using Cramer’s rule
- [ ] Solve a system using Gaussian elimination

## Other
- [ ] Replace static_asserts for operations requiring floating point with templates
- [ ] Can the size parameter be templated?
- [ ] Cross products in other dimensions
- [ ] Support non-square matrices - different class, or generalisation?
- [ ] optimisations? what's really slow? 
