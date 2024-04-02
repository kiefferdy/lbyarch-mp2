# x86 Assembly and C LBYARCH Programming Project

### Specification:

**Input:** Scalar variable n (integer) contains the length of the vector; Vectors X and Y are both single precision float.
**Process:** Y[i] = X[i-3] + X[1-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]

**Example:** X -> 1,2,3,4,5,6,7,8; output Y -> 28, 35

**Output:** Store result in vector Y. Display the result of 1st ten elements of vector Y for all versions of kernel (i.e. C and x86-64).

Note:
