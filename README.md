# x86 Assembly and C LBYARCH Machine Project

Group Members: Tan, Timothy Joshua O. & Recato Dy, John Kieffer L.

### Specification:

**Input:** Scalar variable n (integer) contains the length of the vector; Vectors X and Y are both single precision float. <br>
**Process:** Y[i] = X[i-3] + X[1-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3] <br>
**Example:** X -> 1,2,3,4,5,6,7,8; output Y -> 28, 35 <br>
**Output:** Store result in vector Y. Display the result of 1st ten elements of vector Y for all versions of kernel (i.e. C and x86-64). <be>


# Runtime Comparison

## Debug Mode
Based on our testing the assembly kernel version of the code runs 3 times faster than the C version when in debug mode. This is because in debug mode C has debug features turned on and optimization features turned off. In contrast, the assembly code has no debug features and is already optimized because it is a low-level programming language. <br>  
| Debug Mode  | 2<sup>20</sup> | 2<sup>24</sup> | 2<sup>30</sup> | 
| :--- | :---: | :---: | :---: |
| C | 4.57ms | 74.83ms | 5354.27ms |
| Assembly | 1.47ms | 22.90ms | 1707.53ms |
| Assembly Speed Comparison | 311.36% | 326.78% | 313.57% |

## Release Mode
Based on this testing we can see that when in release mode the assembly kernel version runs ~20% slower than the C version. This is because in release mode C no longer has its debug features turned on and instead has its optimization features. On the other hand, the assembly code is not as well optimized as C code which leads to this speed discrepancy.
| Release Mode  | 2<sup>20</sup> | 2<sup>24</sup> | 2<sup>30</sup> | 
| :--- | :---: | :---: | :---: |
| C | 1.07ms | 17.10ms | 1290.53ms |
| Assembly | 1.33ms | 23.00ms | 1527.83ms |
| Assembly Speed Comparison | 80.00% | 74.35% | 84.47% |

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/4c233b3b-a7c3-4ee6-9836-0a70e6e8cdf9) <br>

### Vector Size 2<sup>24</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/378c6f4e-a269-4d77-9be7-d744cddc7c87) <br>

### Vector Size 2<sup>30</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/35c932a3-de4e-494f-aac5-06dbef5d6cb3) <br>

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/7fb3d3db-a0b2-4dcb-bdca-c360474287b2) <br>
### Vector Size 2<sup>24</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/44bc2a7a-942a-418b-b5a3-d4d55439198f) <br>
### Vector Size 2<sup>30</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/3f73ea43-dace-4d1e-b3e7-95b3468e2362) <br>

# Sample Inputs (with Correctness check)

### Input: 1,2,3,4,5,6,7,8,9,10,11 <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/b01fe6ec-db4f-45b7-8b09-34d2551ee5b5) <br>

### Input: 3,6,9,12,15,18,21,24,27,30 <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/5c00d622-3947-43eb-9c33-25aec91280c0) <br>

### Input: 1,2,3,4,5 (Invalid) <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/e52f8461-36bf-4c2f-967d-e031878a4fba) <br>


