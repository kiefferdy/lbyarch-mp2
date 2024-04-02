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
| C | 4.57ms | 74.83ms | 5354.27ms |
| Assembly | 1.47ms | 22.90ms | 1707.53ms |
| Assembly Speed Comparison | 311.36% | 326.78% | 313.57% |

## Release Mode
Lorem ipsum dolor sit amet. Sit rerum totam hic quasi voluptas est quae numquam et saepe animi qui quia enim ea veniam dolore. Aut sequi magnam est quae galisum sed soluta sint! 33 dolorem consectetur sit dolores assumenda et similique odit et quos quia sit sequi porro qui tempore repellendus hic quisquam natus. Hic minima laborum ut deserunt impedit id assumenda tempore ut accusantium libero aut ducimus debitis et obcaecati molestiae et consequatur iusto.
| Release Mode  | 2<sup>20</sup> | 2<sup>24</sup> | 2<sup>30</sup> | 
| :--- | :---: | :---: | :---: |
| C | lorem | lorem | lorem |
| Assembly | lorem | lorem | lorem |
| Assembly Speed Comparison | lorem | lorem | lorem |

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/4c233b3b-a7c3-4ee6-9836-0a70e6e8cdf9) <br>

### Vector Size 2<sup>24</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/378c6f4e-a269-4d77-9be7-d744cddc7c87) <br>

### Vector Size 2<sup>30</sup> <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/35c932a3-de4e-494f-aac5-06dbef5d6cb3) <br>

# Outputs (Debug Mode):
### Vector Size 2<sup>20</sup> <br>
image <br>
### Vector Size 2<sup>24</sup> <br>
image <br>
### Vector Size 2<sup>30</sup> <br>
image <be>

# Sample Inputs (with Correctness check)

### Input: 1,2,3,4,5,6,7,8,9,10,11 <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/b01fe6ec-db4f-45b7-8b09-34d2551ee5b5) <br>

### Input: 3,6,9,12,15,18,21,24,27,30 <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/5c00d622-3947-43eb-9c33-25aec91280c0) <br>

### Input: 1,2,3,4,5 (Invalid) <br>
![image](https://github.com/kiefferdy/lbyarch-mp2/assets/98691592/e52f8461-36bf-4c2f-967d-e031878a4fba) <br>


