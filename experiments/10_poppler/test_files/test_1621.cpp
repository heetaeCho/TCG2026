#include <gtest/gtest.h>



// Mocking external collaborators if needed would happen here.

// Since there are no external collaborators in this case, we proceed with just Google Test.



// The function to test

static inline unsigned long md5Round4(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long Xk, unsigned long s, unsigned long Ti) {

    return b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

}



// Utility function rotateLeft as it is not provided

static inline unsigned long rotateLeft(unsigned long x, int n) {

    return (x << n) | (x >> (32 - n));

}



// Test fixture for md5Round4 tests

class Md5Round4Test_1621 : public ::testing::Test {};



// Normal operation test case

TEST_F(Md5Round4Test_1621, NormalOperation_1621) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9ABCDEF0;

    unsigned long c = 0xFEDCBA98;

    unsigned long d = 0x76543210;

    unsigned long Xk = 0xDEADBEEF;

    unsigned long s = 5;

    unsigned long Ti = 0xCAFECAFE;



    unsigned long expected = b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);



    EXPECT_EQ(result, expected);

}



// Boundary conditions test case with zero values

TEST_F(Md5Round4Test_1621, ZeroValues_1621) {

    unsigned long a = 0;

    unsigned long b = 0;

    unsigned long c = 0;

    unsigned long d = 0;

    unsigned long Xk = 0;

    unsigned long s = 0;

    unsigned long Ti = 0;



    unsigned long expected = b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);



    EXPECT_EQ(result, expected);

}



// Boundary conditions test case with maximum values

TEST_F(Md5Round4Test_1621, MaxValues_1621) {

    unsigned long a = 0xFFFFFFFF;

    unsigned long b = 0xFFFFFFFF;

    unsigned long c = 0xFFFFFFFF;

    unsigned long d = 0xFFFFFFFF;

    unsigned long Xk = 0xFFFFFFFF;

    unsigned long s = 31; // Maximum shift value

    unsigned long Ti = 0xFFFFFFFF;



    unsigned long expected = b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);



    EXPECT_EQ(result, expected);

}



// Test case for shift value being zero

TEST_F(Md5Round4Test_1621, ShiftZero_1621) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9ABCDEF0;

    unsigned long c = 0xFEDCBA98;

    unsigned long d = 0x76543210;

    unsigned long Xk = 0xDEADBEEF;

    unsigned long s = 0; // Shift value is zero

    unsigned long Ti = 0xCAFECAFE;



    unsigned long expected = b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);



    EXPECT_EQ(result, expected);

}



// Test case for shift value being 32 (full rotation)

TEST_F(Md5Round4Test_1621, ShiftFullRotation_1621) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9ABCDEF0;

    unsigned long c = 0xFEDCBA98;

    unsigned long d = 0x76543210;

    unsigned long Xk = 0xDEADBEEF;

    unsigned long s = 32; // Full rotation

    unsigned long Ti = 0xCAFECAFE;



    unsigned long expected = b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s);

    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);



    EXPECT_EQ(result, expected);

}
