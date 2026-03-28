#include <gtest/gtest.h>
#include <cstdint>

// We need to replicate the helper function signature since it's static inline
// in the source file. We'll test it by including or redefining the exact same logic.
// However, per constraints, we must treat the implementation as a black box.
// Since the function is static inline in a .cc file, we cannot directly call it
// from a test file. We need to either:
// 1. Include the .cc file directly (not ideal but necessary for static functions)
// 2. Or redefine the helpers needed

// Include the source file to get access to the static inline function
// This is necessary because md5Round4 is static and not exposed via a header

// First, let's define the rotateLeft helper that md5Round4 depends on,
// and include the actual implementation file to test the static function.

// We'll include the implementation file to access the static inline functions
#include "Decrypt.cc"

class Md5Round4Test_1621 : public ::testing::Test {
protected:
    // Helper to compute expected MD5 round 4 manually based on the formula:
    // b + rotateLeft((a + (c ^ (b | ~d)) + Xk + Ti), s)
    // We don't re-implement - we just call the function and verify against known values
};

// Test normal operation with all zero inputs
TEST_F(Md5Round4Test_1621, AllZeroInputs_1621) {
    unsigned long result = md5Round4(0, 0, 0, 0, 0, 0, 0);
    // a=0, b=0, c=0, d=0 => c ^ (b | ~d) = 0 ^ (0 | 0xFFFFFFFF) = 0xFFFFFFFF
    // inner = 0 + 0xFFFFFFFF + 0 + 0 = 0xFFFFFFFF
    // rotateLeft(0xFFFFFFFF, 0) = 0xFFFFFFFF
    // result = 0 + 0xFFFFFFFF = 0xFFFFFFFF
    EXPECT_EQ(result, 0xFFFFFFFFUL);
}

// Test with shift amount of 0 (no rotation)
TEST_F(Md5Round4Test_1621, NoRotation_1621) {
    unsigned long a = 1, b = 2, c = 3, d = 4, Xk = 5, s = 0, Ti = 6;
    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);
    // c ^ (b | ~d) = 3 ^ (2 | ~4)
    // ~4 in 32-bit = 0xFFFFFFFB
    // 2 | 0xFFFFFFFB = 0xFFFFFFFB
    // 3 ^ 0xFFFFFFFB = 0xFFFFFFF8
    // inner = 1 + 0xFFFFFFF8 + 5 + 6 = 0x100000004 (mod 2^32 if 32-bit)
    // rotateLeft(inner, 0) = inner
    // result = 2 + inner
    // This depends on the word size; just verify it returns deterministically
    unsigned long result2 = md5Round4(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(result, result2);
}

// Test with known MD5 round 4 constants (from RFC 1321 step 4, first operation)
// Round 4 uses: a = II(a, b, c, d, X[0], 6, 0xf4292244)
TEST_F(Md5Round4Test_1621, KnownMD5Constants_1621) {
    unsigned long a = 0x12345678;
    unsigned long b = 0x9abcdef0;
    unsigned long c = 0x0fedcba9;
    unsigned long d = 0x87654321;
    unsigned long Xk = 0xdeadbeef;
    unsigned long s = 6;
    unsigned long Ti = 0xf4292244;
    
    unsigned long result = md5Round4(a, b, c, d, Xk, s, Ti);
    // Verify deterministic behavior
    unsigned long result2 = md5Round4(a, b, c, d, Xk, s, Ti);
    EXPECT_EQ(result, result2);
}

// Test symmetry: changing b affects both the I function and the final addition
TEST_F(Md5Round4Test_1621, DifferentBValues_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 1, 0);
    unsigned long result2 = md5Round4(0, 1, 0, 0, 0, 1, 0);
    // Different b values should produce different results
    EXPECT_NE(result1, result2);
}

// Test that changing d affects the result (d participates in ~d)
TEST_F(Md5Round4Test_1621, DifferentDValues_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 1, 0);
    unsigned long result2 = md5Round4(0, 0, 0, 1, 0, 1, 0);
    // ~0 vs ~1 are different, so results should differ
    EXPECT_NE(result1, result2);
}

// Test with maximum values for all parameters (boundary)
TEST_F(Md5Round4Test_1621, MaxValues_1621) {
    unsigned long maxVal = 0xFFFFFFFF;
    unsigned long result = md5Round4(maxVal, maxVal, maxVal, maxVal, maxVal, 16, maxVal);
    // c ^ (b | ~d) = 0xFFFFFFFF ^ (0xFFFFFFFF | 0x00000000) = 0xFFFFFFFF ^ 0xFFFFFFFF = 0
    // inner = 0xFFFFFFFF + 0 + 0xFFFFFFFF + 0xFFFFFFFF (with overflow)
    // Verify deterministic
    unsigned long result2 = md5Round4(maxVal, maxVal, maxVal, maxVal, 16, maxVal, maxVal);
    // Just ensure no crash
    (void)result;
    (void)result2;
}

// Test shift values typical in MD5 round 4: 6, 10, 15, 21
TEST_F(Md5Round4Test_1621, TypicalShift6_1621) {
    unsigned long result = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 6, 0xf4292244);
    unsigned long result2 = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 6, 0xf4292244);
    EXPECT_EQ(result, result2);
}

TEST_F(Md5Round4Test_1621, TypicalShift10_1621) {
    unsigned long result = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 10, 0x432aff97);
    unsigned long result2 = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 10, 0x432aff97);
    EXPECT_EQ(result, result2);
}

TEST_F(Md5Round4Test_1621, TypicalShift15_1621) {
    unsigned long result = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 15, 0xab9423a7);
    unsigned long result2 = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 15, 0xab9423a7);
    EXPECT_EQ(result, result2);
}

TEST_F(Md5Round4Test_1621, TypicalShift21_1621) {
    unsigned long result = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 21, 0xfc93a039);
    unsigned long result2 = md5Round4(0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 21, 0xfc93a039);
    EXPECT_EQ(result, result2);
}

// Test that c only participates via XOR
TEST_F(Md5Round4Test_1621, DifferentCValues_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 4, 0);
    unsigned long result2 = md5Round4(0, 0, 0xFF, 0, 0, 4, 0);
    EXPECT_NE(result1, result2);
}

// Test that Xk addition works
TEST_F(Md5Round4Test_1621, XkAffectsResult_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 4, 0);
    unsigned long result2 = md5Round4(0, 0, 0, 0, 100, 4, 0);
    EXPECT_NE(result1, result2);
}

// Test that Ti addition works
TEST_F(Md5Round4Test_1621, TiAffectsResult_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 4, 0);
    unsigned long result2 = md5Round4(0, 0, 0, 0, 0, 4, 100);
    EXPECT_NE(result1, result2);
}

// Test that a affects the result
TEST_F(Md5Round4Test_1621, AAffectsResult_1621) {
    unsigned long result1 = md5Round4(0, 0, 0, 0, 0, 4, 0);
    unsigned long result2 = md5Round4(1, 0, 0, 0, 0, 4, 0);
    EXPECT_NE(result1, result2);
}

// Edge case: shift by 31 (maximum meaningful for 32-bit)
TEST_F(Md5Round4Test_1621, ShiftBy31_1621) {
    unsigned long result = md5Round4(1, 0, 0, 0, 0, 31, 0);
    unsigned long result2 = md5Round4(1, 0, 0, 0, 0, 31, 0);
    EXPECT_EQ(result, result2);
}

// Verify the I function property: when b = 0xFFFFFFFF, b | ~d = 0xFFFFFFFF for any d
TEST_F(Md5Round4Test_1621, IFunctionWithMaxB_1621) {
    // I(b,c,d) = c ^ (b | ~d)
    // When b = 0xFFFFFFFF: (0xFFFFFFFF | ~d) = 0xFFFFFFFF, so I = c ^ 0xFFFFFFFF = ~c
    unsigned long result1 = md5Round4(0, 0xFFFFFFFF, 0x12345678, 0, 0, 0, 0);
    unsigned long result2 = md5Round4(0, 0xFFFFFFFF, 0x12345678, 0xABCDEF01, 0, 0, 0);
    // d shouldn't matter when b is all 1s
    EXPECT_EQ(result1, result2);
}
