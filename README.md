# x86 Assembly and C LBYARCH Programming Project

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
| C | 4.7000ms | 85.0667ms | 88382.1333ms |
| Assembly | 1.4333ms | 24.7333ms | 82178.7333ms |
| Assembly Speed Comparison | 327.91% | 343.94% | 107.55% |

## Release Mode

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/f87916bc-e640-435c-b9bf-b547c1141244) <br>

### Vector Size 2<sup>24</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/b48fe461-f1ba-4cf6-8550-253e6eea9804) <br>

### Vector Size 2<sup>30</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/09a52ea0-32d2-49c9-a7f1-e288be9d9e94) <be>

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <be>
image <br>
### Vector Size 2<sup>24</sup> <be>
image <br>
### Vector Size 2<sup>30</sup> <br>
image <be>

# Sample Inputs (with Correctness check)

### Input: 1,2,3,4,5,6,7,8,9,10,11 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/075c91a7-f858-4e25-9cdd-cdd86ab586fb) <br>

### Input: 1,2,3,4,5,6,7,8,9,10,11 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/66907f76-1d3e-4b65-8875-654d2ddafc57) <br>

### Input: 1,2,3,4,5 (Invalid) <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/ac44932c-7521-46e5-a54d-4d2158ae4e79) <br>


