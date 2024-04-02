# x86 Assembly and C LBYARCH Programming Project

Group Members: Tan, Timothy Joshua O. & Recato Dy, John Kieffer L.

### Specification:

**Input:** Scalar variable n (integer) contains the length of the vector; Vectors X and Y are both single precision float. <br>
**Process:** Y[i] = X[i-3] + X[1-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3] <br>
**Example:** X -> 1,2,3,4,5,6,7,8; output Y -> 28, 35 <br>
**Output:** Store result in vector Y. Display the result of 1st ten elements of vector Y for all versions of kernel (i.e. C and x86-64). <be>


# Runtime Comparison
## Debug Mode
### Vector Size 2^20 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/f87916bc-e640-435c-b9bf-b547c1141244) <br>

### Vector Size 2^24 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/b48fe461-f1ba-4cf6-8550-253e6eea9804) <br>

### Vector Size 2^30 <br>
![image](https://github.com/kiefferdy/lbyarch-mp/assets/98691592/09a52ea0-32d2-49c9-a7f1-e288be9d9e94) <br>
