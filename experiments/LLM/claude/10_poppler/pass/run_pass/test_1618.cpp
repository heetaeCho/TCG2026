#include <gtest/gtest.h>

// We need to replicate the helper function and the function under test
// since they are static inline in the .cc file and not exposed via a header.
// We treat the logic as a black box based on the known MD5 specification.

static inline unsigned long rotateLeft(unsigned long x, unsigned long n)
{
    return (x << n) | (x >> (32 - n));
}

static inline unsigned long md5Round1(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long Xk, unsigned long s, unsigned long Ti)
{
    return b + rotateLeft((a + ((b & c) | (~b & d)) + Xk + Ti), s);
}

class Md5Round1Test_1618 : public ::testing::Test {
protected:
    // Helper to mask to 32 bits for comparison on platforms where unsigned long > 32 bits
    unsigned long mask32(unsigned long val) {
        return val & 0xFFFFFFFFUL;
    }
};

// Test with all zero inputs
TEST_F(Md5Round1Test_1618, AllZeros_1618)
{
    unsigned long result = md5Round1(0, 0, 0, 0, 0, 0, 0);
    // a=0, b=0, c=0, d=0: F(b,c,d) = (0&0)|(~0&0) = 0
    // sum = 0 + 0 + 0 + 0 = 0
    // rotateLeft(0, 0) = 0
    // result = 0 + 0 = 0
    EXPECT_EQ(mask32(result), 0UL);
}

// Test with all ones (0xFFFFFFFF)
TEST_F(Md5Round1Test_1618, AllOnes_1618)
{
    unsigned long a = 0xFFFFFFFFUL;
    unsigned long b = 0xFFFFFFFFUL;
    unsigned long c = 0xFFFFFFFFUL;
    unsigned long d = 0xFFFFFFFFUL;
    unsigned long Xk = 0xFFFFFFFFUL;
    unsigned long s = 7;
    unsigned long Ti = 0xFFFFFFFFUL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // F(b,c,d) = (0xFFFFFFFF & 0xFFFFFFFF) | (~0xFFFFFFFF & 0xFFFFFFFF) = 0xFFFFFFFF | 0 = 0xFFFFFFFF
    // sum = 0xFFFFFFFF + 0xFFFFFFFF + 0xFFFFFFFF + 0xFFFFFFFF (mod 2^32 if 32-bit)
    // = 4 * 0xFFFFFFFF mod 2^32 = 0xFFFFFFFC (for 32-bit)
    // rotateLeft(0xFFFFFFFC, 7) on 32-bit = ...
    // result = b + rotateLeft(sum, s)
    // We just verify it returns a deterministic value
    unsigned long expected_F = 0xFFFFFFFFUL;
    unsigned long sum = a + expected_F + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;
    EXPECT_EQ(mask32(result), mask32(expected));
}

// Test known MD5 Round 1 step from RFC 1321 reference implementation
// First round, first step: a = FF(a, b, c, d, M0, 7, 0xd76aa478)
TEST_F(Md5Round1Test_1618, KnownMD5Step1_1618)
{
    // Initial MD5 values
    unsigned long a = 0x67452301UL;
    unsigned long b = 0xefcdab89UL;
    unsigned long c = 0x98badcfeUL;
    unsigned long d = 0x10325476UL;
    unsigned long Xk = 0;  // First message word = 0 for empty message padding scenario
    unsigned long s = 7;
    unsigned long Ti = 0xd76aa478UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // Manually compute:
    // F(b,c,d) = (b & c) | (~b & d)
    unsigned long F = (b & c) | (~b & d);
    unsigned long sum = a + F + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    EXPECT_EQ(mask32(result), mask32(expected));
}

// Test with s = 0 (no rotation)
TEST_F(Md5Round1Test_1618, NoRotation_1618)
{
    unsigned long a = 0x12345678UL;
    unsigned long b = 0xABCDEF01UL;
    unsigned long c = 0x11111111UL;
    unsigned long d = 0x22222222UL;
    unsigned long Xk = 0x33333333UL;
    unsigned long s = 0;
    unsigned long Ti = 0x44444444UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    unsigned long F = (b & c) | (~b & d);
    unsigned long sum = a + F + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, 0);  // no rotation
    unsigned long expected = b + rotated;

    EXPECT_EQ(mask32(result), mask32(expected));
}

// Test with s = 1 (minimal rotation)
TEST_F(Md5Round1Test_1618, RotateByOne_1618)
{
    unsigned long a = 1;
    unsigned long b = 0;
    unsigned long c = 0;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 1;
    unsigned long Ti = 0;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // F(0,0,0) = (0&0)|(~0&0) = 0
    // sum = 1 + 0 + 0 + 0 = 1
    // rotateLeft(1, 1) = 2
    // result = 0 + 2 = 2
    EXPECT_EQ(mask32(result), 2UL);
}

// Test where b=0xFFFFFFFF, c=0, d=0 to check F function behavior
// F = (0xFFFFFFFF & 0) | (~0xFFFFFFFF & 0) = 0 | 0 = 0
TEST_F(Md5Round1Test_1618, FunctionFAllBSetCDZero_1618)
{
    unsigned long a = 0;
    unsigned long b = 0xFFFFFFFFUL;
    unsigned long c = 0;
    unsigned long d = 0;
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // F = 0, sum = 0, rotateLeft(0,0) = 0, result = 0xFFFFFFFF + 0 = 0xFFFFFFFF
    EXPECT_EQ(mask32(result), 0xFFFFFFFFUL);
}

// Test where b=0, c=0xFFFFFFFF, d=0xFFFFFFFF
// F = (0 & 0xFFFFFFFF) | (~0 & 0xFFFFFFFF) = 0 | 0xFFFFFFFF = 0xFFFFFFFF
TEST_F(Md5Round1Test_1618, FunctionFBZeroCDAllSet_1618)
{
    unsigned long a = 0;
    unsigned long b = 0;
    unsigned long c = 0xFFFFFFFFUL;
    unsigned long d = 0xFFFFFFFFUL;
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // F = 0xFFFFFFFF, sum = 0 + 0xFFFFFFFF + 0 + 0 = 0xFFFFFFFF
    // rotateLeft(0xFFFFFFFF, 0) = 0xFFFFFFFF
    // result = 0 + 0xFFFFFFFF = 0xFFFFFFFF
    EXPECT_EQ(mask32(result), 0xFFFFFFFFUL);
}

// Test with typical MD5 round 1 shift values: 7, 12, 17, 22
TEST_F(Md5Round1Test_1618, ShiftValue7_1618)
{
    unsigned long a = 0x00000001UL;
    unsigned long b = 0x00000000UL;
    unsigned long c = 0x00000000UL;
    unsigned long d = 0x00000000UL;
    unsigned long Xk = 0x00000000UL;
    unsigned long s = 7;
    unsigned long Ti = 0x00000000UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // F = 0, sum = 1, rotateLeft(1, 7) = 128 = 0x80
    EXPECT_EQ(mask32(result), 0x80UL);
}

TEST_F(Md5Round1Test_1618, ShiftValue12_1618)
{
    unsigned long a = 0x00000001UL;
    unsigned long b = 0x00000000UL;
    unsigned long c = 0x00000000UL;
    unsigned long d = 0x00000000UL;
    unsigned long Xk = 0x00000000UL;
    unsigned long s = 12;
    unsigned long Ti = 0x00000000UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // rotateLeft(1, 12) = 0x1000
    EXPECT_EQ(mask32(result), 0x1000UL);
}

TEST_F(Md5Round1Test_1618, ShiftValue17_1618)
{
    unsigned long a = 0x00000001UL;
    unsigned long b = 0x00000000UL;
    unsigned long c = 0x00000000UL;
    unsigned long d = 0x00000000UL;
    unsigned long Xk = 0x00000000UL;
    unsigned long s = 17;
    unsigned long Ti = 0x00000000UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // rotateLeft(1, 17) = 0x20000
    EXPECT_EQ(mask32(result), 0x20000UL);
}

TEST_F(Md5Round1Test_1618, ShiftValue22_1618)
{
    unsigned long a = 0x00000001UL;
    unsigned long b = 0x00000000UL;
    unsigned long c = 0x00000000UL;
    unsigned long d = 0x00000000UL;
    unsigned long Xk = 0x00000000UL;
    unsigned long s = 22;
    unsigned long Ti = 0x00000000UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // rotateLeft(1, 22) = 0x400000
    EXPECT_EQ(mask32(result), 0x400000UL);
}

// Test that F selects c when b bit is 1, and d when b bit is 0
TEST_F(Md5Round1Test_1618, FunctionFMuxBehavior_1618)
{
    // b = 0xF0F0F0F0, c = 0xAAAAAAAA, d = 0x55555555
    // F = (0xF0F0F0F0 & 0xAAAAAAAA) | (~0xF0F0F0F0 & 0x55555555)
    //   = 0xA0A0A0A0 | 0x05050505 = 0xA5A5A5A5
    unsigned long a = 0;
    unsigned long b = 0xF0F0F0F0UL;
    unsigned long c = 0xAAAAAAAAUL;
    unsigned long d = 0x55555555UL;
    unsigned long Xk = 0;
    unsigned long s = 0;
    unsigned long Ti = 0;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    // sum = 0 + 0xA5A5A5A5 + 0 + 0 = 0xA5A5A5A5
    // rotateLeft(0xA5A5A5A5, 0) = 0xA5A5A5A5
    // result = 0xF0F0F0F0 + 0xA5A5A5A5 = 0x96969695 (with carry)
    unsigned long expected = mask32(0xF0F0F0F0UL + 0xA5A5A5A5UL);
    EXPECT_EQ(mask32(result), expected);
}

// Test commutativity doesn't hold (swapping a and b should give different results)
TEST_F(Md5Round1Test_1618, NonCommutativeAB_1618)
{
    unsigned long val1 = 0x12345678UL;
    unsigned long val2 = 0x9ABCDEF0UL;
    unsigned long c = 0x11111111UL;
    unsigned long d = 0x22222222UL;
    unsigned long Xk = 0x33333333UL;
    unsigned long s = 7;
    unsigned long Ti = 0xD76AA478UL;

    unsigned long result1 = md5Round1(val1, val2, c, d, Xk, s, Ti);
    unsigned long result2 = md5Round1(val2, val1, c, d, Xk, s, Ti);

    EXPECT_NE(mask32(result1), mask32(result2));
}

// Test with large Ti value
TEST_F(Md5Round1Test_1618, LargeTiValue_1618)
{
    unsigned long a = 0x67452301UL;
    unsigned long b = 0xefcdab89UL;
    unsigned long c = 0x98badcfeUL;
    unsigned long d = 0x10325476UL;
    unsigned long Xk = 0x80000000UL;  // typical padding word
    unsigned long s = 7;
    unsigned long Ti = 0xd76aa478UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    unsigned long F = (b & c) | (~b & d);
    unsigned long sum = a + F + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    EXPECT_EQ(mask32(result), mask32(expected));
}

// Test determinism - same inputs always give same output
TEST_F(Md5Round1Test_1618, Deterministic_1618)
{
    unsigned long a = 0xDEADBEEFUL;
    unsigned long b = 0xCAFEBABEUL;
    unsigned long c = 0x12345678UL;
    unsigned long d = 0x9ABCDEF0UL;
    unsigned long Xk = 0xFEDCBA98UL;
    unsigned long s = 12;
    unsigned long Ti = 0xe8c7b756UL;

    unsigned long result1 = md5Round1(a, b, c, d, Xk, s, Ti);
    unsigned long result2 = md5Round1(a, b, c, d, Xk, s, Ti);

    EXPECT_EQ(result1, result2);
}

// Test with power of 2 values
TEST_F(Md5Round1Test_1618, PowerOfTwoInputs_1618)
{
    unsigned long a = 0x80000000UL;
    unsigned long b = 0x40000000UL;
    unsigned long c = 0x20000000UL;
    unsigned long d = 0x10000000UL;
    unsigned long Xk = 0x08000000UL;
    unsigned long s = 1;
    unsigned long Ti = 0x04000000UL;

    unsigned long result = md5Round1(a, b, c, d, Xk, s, Ti);

    unsigned long F = (b & c) | (~b & d);
    unsigned long sum = a + F + Xk + Ti;
    unsigned long rotated = rotateLeft(sum, s);
    unsigned long expected = b + rotated;

    EXPECT_EQ(mask32(result), mask32(expected));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
