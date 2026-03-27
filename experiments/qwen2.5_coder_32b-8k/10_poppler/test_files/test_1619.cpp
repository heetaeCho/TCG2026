#include <gtest/gtest.h>



// Assuming the function md5Round2 is part of a class or can be tested in isolation.

// Since it's a static inline function, we will create a simple wrapper class for testing purposes.



class MD5Wrapper {

public:

    static unsigned long md5Round2(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long Xk, unsigned long s, unsigned long Ti) {

        return ::md5Round2(a, b, c, d, Xk, s, Ti);

    }

};



// Test fixture for MD5Wrapper

class MD5WrapperTest : public ::testing::Test {};



// Normal operation test

TEST_F(MD5WrapperTest_1619, NormalOperation_1619) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9abcdef0;

    unsigned long c = 0x23456789;

    unsigned long d = 0xabcd1234;

    unsigned long Xk = 0xfedcba09;

    unsigned long s = 5;

    unsigned long Ti = 0x76543210;



    unsigned long expected = b + ((a + ((b & d) | (c & ~d)) + Xk + Ti) << s);

    EXPECT_EQ(MD5Wrapper::md5Round2(a, b, c, d, Xk, s, Ti), expected);

}



// Boundary condition test: zero values

TEST_F(MD5WrapperTest_1619, ZeroValues_1619) {

    unsigned long a = 0;

    unsigned long b = 0;

    unsigned long c = 0;

    unsigned long d = 0;

    unsigned long Xk = 0;

    unsigned long s = 0;

    unsigned long Ti = 0;



    EXPECT_EQ(MD5Wrapper::md5Round2(a, b, c, d, Xk, s, Ti), b);

}



// Boundary condition test: max values

TEST_F(MD5WrapperTest_1619, MaxValues_1619) {

    unsigned long a = 0xFFFFFFFF;

    unsigned long b = 0xFFFFFFFF;

    unsigned long c = 0xFFFFFFFF;

    unsigned long d = 0xFFFFFFFF;

    unsigned long Xk = 0xFFFFFFFF;

    unsigned long s = 31; // Max shift value for 32-bit

    unsigned long Ti = 0xFFFFFFFF;



    unsigned long expected = b + ((a + ((b & d) | (c & ~d)) + Xk + Ti) << s);

    EXPECT_EQ(MD5Wrapper::md5Round2(a, b, c, d, Xk, s, Ti), expected);

}



// Boundary condition test: shift value zero

TEST_F(MD5WrapperTest_1619, ShiftZero_1619) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9abcdef0;

    unsigned long c = 0x23456789;

    unsigned long d = 0xabcd1234;

    unsigned long Xk = 0xfedcba09;

    unsigned long s = 0;

    unsigned long Ti = 0x76543210;



    unsigned long expected = b + (a + ((b & d) | (c & ~d)) + Xk + Ti);

    EXPECT_EQ(MD5Wrapper::md5Round2(a, b, c, d, Xk, s, Ti), expected);

}



// Boundary condition test: shift value max

TEST_F(MD5WrapperTest_1619, ShiftMax_1619) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9abcdef0;

    unsigned long c = 0x23456789;

    unsigned long d = 0xabcd1234;

    unsigned long Xk = 0xfedcba09;

    unsigned long s = 31; // Max shift value for 32-bit

    unsigned long Ti = 0x76543210;



    unsigned long expected = b + ((a + ((b & d) | (c & ~d)) + Xk + Ti) << s);

    EXPECT_EQ(MD5Wrapper::md5Round2(a, b, c, d, Xk, s, Ti), expected);

}

```


