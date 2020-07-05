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
- [ ] Vector +/- scalar
- [x] Vector +/- Vector
- [ ] Vector * scalar (check 1/x too)
- [ ] Dot product (`.dot()`)
- [ ] Cross product (`.cross()`)
- [ ] Change basis
- [ ] Gram-Schmidt process - make a basis set orthonormal
- [ ] can we make passing `{}` to the ctor a compile error?  

## Matrices
with `Matrix` class
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
