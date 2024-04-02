# x86 Assembly and C LBYARCH Programming Project

### Specification:

**Input:** Scalar variable n (integer) contains the length of the vector; Vectors X and Y are both single precision float. <br>
**Process:** Y[i] = X[i-3] + X[1-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3] <br>
**Example:** X -> 1,2,3,4,5,6,7,8; output Y -> 28, 35 <br>
**Output:** Store result in vector Y. Display the result of 1st ten elements of vector Y for all versions of kernel (i.e. C and x86-64). <be>


# Runtime Comparison
## Debug Mode
### Vector 2^20 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/85b13245-e386-4cc6-a6ec-2abf155bd17f) <br>

### Vector 2^24 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/d5efbf7b-0930-446a-9e78-0971994ba3c3) <br>

### Vector 2^30 <be>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/1326421b-480d-466c-9657-ede5e8adc5ab) <br>
