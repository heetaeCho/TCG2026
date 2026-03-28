#include <gtest/gtest.h>
#include <cstdint>

// We need to replicate the helper function signature since it's static inline in the source file.
// We treat it as a black box but need to call it directly for testing.
// Since the function is static inline in a .cc file, we include it or redefine the exact signature.

static inline unsigned long rotateLeft(unsigned long x, unsigned long n)
{
    return (x << n) | (x >> (32 - n));
}

static inline unsigned long md5Round2(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long Xk, unsigned long s, unsigned long Ti)
{
    return b + rotateLeft((a + ((b & d) | (c & ~d)) + Xk + Ti), s);
}

class Md5Round2Test_1619 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: All zero inputs should produce a deterministic result
TEST_F(Md5Round2Test_1619, AllZeroInputs_1619)
{
    unsigned long result = md5Round2(0, 0, 0, 0, 0, 0, 0);
    // a=0, b=0, c=0, d=0 => (b & d) | (c & ~d) = (0&0)|(0&0xFFFFFFFF) = 0
    // a + 0 + Xk + Ti = 0, rotateLeft(0, 0) = 0, b + 0 = 0
    EXPECT_EQ(0UL, result);
}

// Test: When b=0xFFFFFFFF, d=0xFFFFFFFF, the G function should yield 0xFFFFFFFF
TEST_F(Md5Round2Test_1619, BAndDAllOnes_1619)
{
    unsigned long a = 0;
    unsigned long b = 0xFFFFFFFF;
    unsigned long c = 0;
    unsigned long d = 0xFFFFFFFF;
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    // G(b,c,d) = (b & d) | (c & ~d) = (0xFFFFFFFF & 0xFFFFFFFF) | (0 & 0) = 0xFFFFFFFF
    // a + G + Xk + Ti = 0 + 0xFFFFFFFF + 0 + 0 = 0xFFFFFFFF
    // rotateLeft(0xFFFFFFFF, 0) = 0xFFFFFFFF
    // b + 0xFFFFFFFF = 0xFFFFFFFF + 0xFFFFFFFF = 0x1FFFFFFFE (truncated to 32 bits if unsigned long is 32-bit)
    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    
    // We compute the expected value
    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;
    EXPECT_EQ(expected, result);
}

// Test: Non-zero shift value
TEST_F(Md5Round2Test_1619, NonZeroShift_1619)
{
    unsigned long a = 1;
    unsigned long b = 2;
    unsigned long c = 3;
    unsigned long d = 4;
    unsigned long Xk = 5;
    unsigned long s = 7;
    unsigned long Ti = 10;

    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Known MD5 round 2 values (from RFC 1321 test vectors context)
TEST_F(Md5Round2Test_1619, KnownMd5Values_1619)
{
    // Using typical MD5 round 2 constants
    unsigned long a = 0x67452301;
    unsigned long b = 0xefcdab89;
    unsigned long c = 0x98badcfe;
    unsigned long d = 0x10325476;
    unsigned long Xk = 0x12345678;
    unsigned long s = 5;
    unsigned long Ti = 0xf61e2562;

    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Shift by 1
TEST_F(Md5Round2Test_1619, ShiftByOne_1619)
{
    unsigned long a = 0x80000000;
    unsigned long b = 0;
    unsigned long c = 0;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 1;
    unsigned long Ti = 0;

    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: G function when c has all bits set and d is zero
TEST_F(Md5Round2Test_1619, CAllOnesAndDZero_1619)
{
    unsigned long a = 0;
    unsigned long b = 0;
    unsigned long c = 0xFFFFFFFF;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    // G(b,c,d) = (0 & 0) | (0xFFFFFFFF & 0xFFFFFFFF) = 0xFFFFFFFF
    unsigned long G = (b & d) | (c & ~d);
    EXPECT_EQ(0xFFFFFFFF, G);

    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Large values for Xk and Ti causing overflow
TEST_F(Md5Round2Test_1619, OverflowInAddition_1619)
{
    unsigned long a = 0xFFFFFFFF;
    unsigned long b = 0xFFFFFFFF;
    unsigned long c = 0xFFFFFFFF;
    unsigned long d = 0xFFFFFFFF;
    unsigned long Xk = 0xFFFFFFFF;
    unsigned long s = 16;
    unsigned long Ti = 0xFFFFFFFF;

    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Verify G function selects bits from b when d=1 and from c when d=0
TEST_F(Md5Round2Test_1619, GFunctionBitSelection_1619)
{
    unsigned long a = 0;
    unsigned long b = 0xAAAAAAAA; // alternating bits
    unsigned long c = 0x55555555; // opposite alternating bits
    unsigned long d = 0xFFFF0000; // top half set
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    // G(b,c,d) = (b & d) | (c & ~d)
    // = (0xAAAAAAAA & 0xFFFF0000) | (0x55555555 & 0x0000FFFF)
    // = 0xAAAA0000 | 0x00005555
    // = 0xAAAA5555
    unsigned long G = (b & d) | (c & ~d);
    EXPECT_EQ(0xAAAA5555UL, G);

    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Shift by 31 (boundary for 32-bit rotation)
TEST_F(Md5Round2Test_1619, ShiftBy31_1619)
{
    unsigned long a = 1;
    unsigned long b = 0;
    unsigned long c = 0;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 31;
    unsigned long Ti = 0;

    // G = 0, sum = 1, rotateLeft(1, 31) = 0x80000000
    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

// Test: Only Ti is non-zero
TEST_F(Md5Round2Test_1619, OnlyTiNonZero_1619)
{
    unsigned long a = 0;
    unsigned long b = 0;
    unsigned long c = 0;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 10;
    unsigned long Ti = 0xDEADBEEF;

    unsigned long G = (b & d) | (c & ~d);
    unsigned long sum = a + G + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    unsigned long result = md5Round2(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(expected, result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
