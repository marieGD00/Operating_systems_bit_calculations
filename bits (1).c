/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif

/************************************************ 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
	int y = (x >>31);
  return (x ^ y) + (1+~y);
}

/************************************************ 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
	 // overflow occurs when
   //two numbers with the same sign are added and result has opposite sign
  //if a and b have different signs, you cannot get overflow. 
  // if they are the same, then there was no overflow.
  int z=x+y;
  int a=x>>31;
  int b=y>>31;
  int c=z>>31;
  return !!((a^b)|(!(a^c)&!(b^c)));
  
}

/************************************************ 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
	  x  = x & (x >> 16);
	  x  = x & (x >> 8);
	  x  = x & (x >> 4);
	  x  = x & (x >> 2);
	 
    return x&0x1;
}

/************************************************
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int negative_x = ~x+1;
	int bits = (negative_x | x) >> 31;
  return bits + 1;
}

/************************************************
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int c = 0;
	int ones = 0x55 + (0x55 << 8) + (0x55 << 16) + (0x55 << 24); // 01010101...
  int twos = 0x33 + (0x33 << 8) + (0x33 << 16) + (0x33 << 24); // 00110011...
  int fours = 0x0f + (0x0f << 8) + (0x0f << 16) + (0x0f << 24); // 00001111...
  int eights = 0xff + (0xff << 16); // 0000000011111111...
  int sixteens = 0xff + (0xff << 8); // 00000000000000001111111111111111

  c = (x & ones) + ((x >> 1) & ones);
  c = (c & twos) + ((c >> 2) & twos);
  c = (c + ( c >> 4 )) & fours ;
  c = (c + ( c >> 8 )) & eights ;
  c = (c + ( c >> 16 )) & sixteens ;
//c = (c & 0x0F0F0F0F) + ((c >> 4) & 0x0F0F0F0F);
//c = (c & 0x00FF00FF) + ((c >> 8) & 0x00FF00FF);
//c = (c & 0x0000FFFF) + ((c >> 16)& 0x0000FFFF);
return c;
}

/************************************************
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  return (~x & ~y);
}

/************************************************
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int n_shift3 = n << 3;
  int m_shift3 = m << 3;
  int pull_m = 0xFF & (x >> m_shift3);
  int pull_n = 0xFF & (x >> n_shift3);

  x = x ^ (pull_m << m_shift3) ^ (pull_n << n_shift3);
  return x | (pull_m << n_shift3) | (pull_n << m_shift3);

}

/************************************************ 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
 /* if x != 0, subtract 1 from 0 => 0xffffffff
   * else if x = 0, subtract 1 from 1 => 0x00000000
   */
  int mask = (!x + ~0x00);

  /* if x was non-zero, mask out z, 
   * if it was zero, mask out y 
   */
  return ((~mask) & z) | ((mask) & y);
}

/************************************************
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  int multiply_3 = x + x + x;
  int check_sign = multiply_3 >> 31;

  return ((multiply_3>>2) & (~check_sign)) + ((((multiply_3+3)>>2)&check_sign));
}

/************************************************ 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  return !((x << (32+(1+~n)) >> (32+(1+~n))) ^ x);
  
 
}

/************************************************
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return 0xff & (x >> (n << 3));
  
}

/************************************************ 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
 int m = x;
 
  m = m | m >> 1;
  m = m | m >> 2;
  m = m | m >> 4;
  m = m | m >> 8;
  m = m | m >> 16;
  m = m & ((~m >> 1)^(0x1 << 31));//0x80000000);
    return m;
}

/************************************************
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
  return y | !(x^y);
}

/************************************************ 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int sign = 1 << 31;
   int upperBound = ~(sign | 0x39); /*if > 0x39 is added, result goes negative*/
   int lowerBound = ~0x30;/*when < 0x30 is added, result is negative*/

   /*now add x and check the sign bit for each*/
   upperBound = sign & (upperBound+x) >> 31;
   lowerBound = sign & (lowerBound+1+x) >> 31; 
   /*if either result is negative, it is not in desired range*/
   return !(upperBound | lowerBound); 
}

/************************************************ 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x^y);
}

/************************************************
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  //check for overflow
  //overflow will happen if x and y are different sign
  int check_sign = ((x >>31) ^ (y >> 31)) & 0x1; //different = 1 all else = false
  int y_positive = (y>>31) & 0x1;//check y positive //1 if negative
  int subtract = x + (1 + ~y);
  int subtract_sign = (subtract >> 31) & 0x1;//check if subtract is negative
  return (check_sign & (!y_positive)) | ((!check_sign) & subtract_sign);
  
}

/************************************************
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  return !((x >> 31)&0x1);
}

/************************************************
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {

   int ispositive= ! ( (x>>31) ^ 0) & !!(x^0);         
    int temp= !((x & ~x+1) ^ x);
    return temp & ispositive;
 
}

/************************************************
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  //Tmin = -Tmax - 1
  //int Tmax = 0x7f;
  //int Tmin = ~Tmax;
  //tmin+tmin=0
  
  return !(x+x)^ !x;
}

/************************************************
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {

//There are 2 integers between 1 and -2: 0 and -1
//1   in binary is 00000000000000000000000000000001
//0   in binary is 00000000000000000000000000000000
//-1 in binary is 11111111111111111111111111111111
//-2 in binary is 11111111111111111111111111111110
  return ~0;
}

/************************************************
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
    int high_mask = ~0 << (32+(~n+1));
    int low_mask = ~(~0 << n);
    int save_bits = ((x & high_mask) >> (32+(~n+1))) & low_mask;
    return (x<<n) | save_bits;

  //int unsignedmask = (0x1<<31)+(~0); 
  //int save_bits = x >> (32 + (~n+1));
  //return (x << n) | save_bits & unsignedmask;
  //return (x << n) | (n << (32 -n));
}

/************************************************
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  //it will only overflow if positive becomes negative or if negative becomes positive
  //Tmax = ~Tmin
  //1 overflow?
  //2 negative or positive
  //saturate
  //Tmin= 10000000000
  //Tmax= 01111111
  int multiply_2 = x << 1;
  int Tmin = 0x1  << 31;
  int a = (x>>31); // fills the integer with the sign bit 
  int b = (x<<1) >> 31; // fills the integer with the MSB 
  x <<= 1; // multiplies by 2
  x ^= (a^b)&(x^b^(0x1 << 31)); // saturate
  return x;
}

