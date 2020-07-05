# To Do

## Fractions
- [x] `==`
- [x] `*`
- [x] `/`
- [x] `+`
- [x] `-`
- [ ] `>`
- [ ] `>=`
- [ ] `<`
- [ ] `<=`
- [ ] always handle zero correctly
- [ ] power (?)
- [ ] `*=`, `+=`, `/=` (?)
- [ ] cast to floating point (?)
- [ ] cast to int(?)
- [ ] optimisations (?) e.g. the comparison methods

## Vectors
with `Vector` class
- [ ] Calculate length 
- [ ] Normalize (set length to 1)
- [ ] Vector +/- scalar
- [ ] Vector +/- Vector
- [ ] Vector * scalar (inc 1/x)
- [ ] Dot product (`.dot()`)
- [ ] Cross product (`.cross()`)
- [ ] Change basis
- [ ] Gram-Schmidt process - make a basis set orthonormal  

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
