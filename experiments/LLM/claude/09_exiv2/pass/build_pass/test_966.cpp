#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
float canonEv(int64_t val);
}
}

using Exiv2::Internal::canonEv;

// Helper for float comparison tolerance
constexpr float kEpsilon = 1e-5f;

// Normal operation tests

TEST(CanonEvTest_966, ZeroValue_966) {
    float result = canonEv(0);
    EXPECT_NEAR(result, 0.0f, kEpsilon);
}

TEST(CanonEvTest_966, PositiveValueNoRemainder_966) {
    // val = 32, remainder = 0, frac = 0
    // result = (32 + 0) / 32 = 1.0
    float result = canonEv(32);
    EXPECT_NEAR(result, 1.0f, kEpsilon);
}

TEST(CanonEvTest_966, PositiveValueMultipleOf32_966) {
    // val = 64, remainder = 0, frac = 0
    // result = (64 + 0) / 32 = 2.0
    float result = canonEv(64);
    EXPECT_NEAR(result, 2.0f, kEpsilon);
}

TEST(CanonEvTest_966, PositiveValue96_966) {
    // val = 96, remainder = 0, frac = 0
    // result = 96 / 32 = 3.0
    float result = canonEv(96);
    EXPECT_NEAR(result, 3.0f, kEpsilon);
}

TEST(CanonEvTest_966, NegativeValueNoRemainder_966) {
    // val = -32, sign = -1, abs_val = 32, remainder = 0
    // result = -1 * (32 + 0) / 32 = -1.0
    float result = canonEv(-32);
    EXPECT_NEAR(result, -1.0f, kEpsilon);
}

TEST(CanonEvTest_966, NegativeValue64_966) {
    // val = -64, sign = -1, abs_val = 64, remainder = 0
    // result = -1 * 64 / 32 = -2.0
    float result = canonEv(-64);
    EXPECT_NEAR(result, -2.0f, kEpsilon);
}

// Remainder == 0x0c (12) => frac = 32/3
TEST(CanonEvTest_966, RemainderIs0x0c_966) {
    // val = 32 + 12 = 44
    // remainder = 44 & 0x1f = 12
    // val_after = 44 - 12 = 32
    // frac = 32/3
    // result = (32 + 32/3) / 32 = (96/3 + 32/3) / 32 = 128/96 = 4/3
    float expected = (32.0f + 32.0f / 3.0f) / 32.0f;
    float result = canonEv(44);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Remainder == 0x14 (20) => frac = 64/3
TEST(CanonEvTest_966, RemainderIs0x14_966) {
    // val = 32 + 20 = 52
    // remainder = 52 & 0x1f = 20
    // val_after = 52 - 20 = 32
    // frac = 64/3
    // result = (32 + 64/3) / 32
    float expected = (32.0f + 64.0f / 3.0f) / 32.0f;
    float result = canonEv(52);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Special case: val == 160 + 8 = 168, remainder == 0x08 => frac = 30/3 = 10
TEST(CanonEvTest_966, SigmaLensSpecialCase_966) {
    // val = 168
    // remainder = 168 & 0x1f = 8
    // val_after = 168 - 8 = 160
    // Since val_after == 160 and frac == 0x08, frac = 30/3 = 10
    // result = (160 + 10) / 32 = 170/32 = 5.3125
    float expected = (160.0f + 30.0f / 3.0f) / 32.0f;
    float result = canonEv(168);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Negative value with remainder 0x0c
TEST(CanonEvTest_966, NegativeRemainderIs0x0c_966) {
    // val = -(32 + 12) = -44
    // sign = -1, abs_val = 44, remainder = 12
    // val_after = 32, frac = 32/3
    // result = -1 * (32 + 32/3) / 32
    float expected = -1.0f * (32.0f + 32.0f / 3.0f) / 32.0f;
    float result = canonEv(-44);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Negative value with remainder 0x14
TEST(CanonEvTest_966, NegativeRemainderIs0x14_966) {
    float expected = -1.0f * (32.0f + 64.0f / 3.0f) / 32.0f;
    float result = canonEv(-52);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Negative Sigma special case: -168
TEST(CanonEvTest_966, NegativeSigmaSpecialCase_966) {
    // val = -168, sign = -1, abs = 168
    // remainder = 8, val_after = 160
    // frac = 30/3 = 10
    // result = -1 * (160 + 10) / 32 = -5.3125
    float expected = -1.0f * (160.0f + 30.0f / 3.0f) / 32.0f;
    float result = canonEv(-168);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Remainder 0x08 but val_after != 160 (should NOT trigger Sigma special case)
TEST(CanonEvTest_966, Remainder0x08NonSigma_966) {
    // val = 64 + 8 = 72
    // remainder = 8, val_after = 64 (not 160)
    // frac stays as 8.0
    // result = (64 + 8) / 32 = 72/32 = 2.25
    float expected = (64.0f + 8.0f) / 32.0f;
    float result = canonEv(72);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Generic remainder (not 0x0c, 0x14, or special 0x08 case)
TEST(CanonEvTest_966, GenericRemainder_966) {
    // val = 32 + 5 = 37
    // remainder = 5, val_after = 32
    // frac = 5.0
    // result = (32 + 5) / 32 = 37/32 = 1.15625
    float expected = 37.0f / 32.0f;
    float result = canonEv(37);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Remainder == 0x1f (31) - maximum remainder
TEST(CanonEvTest_966, MaxRemainder_966) {
    // val = 31
    // remainder = 31, val_after = 0
    // frac = 31.0
    // result = 31 / 32 = 0.96875
    float expected = 31.0f / 32.0f;
    float result = canonEv(31);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// val = 1
TEST(CanonEvTest_966, ValueOne_966) {
    // remainder = 1, val_after = 0
    // frac = 1.0
    // result = 1/32 = 0.03125
    float expected = 1.0f / 32.0f;
    float result = canonEv(1);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// val = -1
TEST(CanonEvTest_966, NegativeValueOne_966) {
    float expected = -1.0f / 32.0f;
    float result = canonEv(-1);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Larger positive value
TEST(CanonEvTest_966, LargePositiveValue_966) {
    // val = 320, remainder = 0, result = 320/32 = 10.0
    float result = canonEv(320);
    EXPECT_NEAR(result, 10.0f, kEpsilon);
}

// Large value with remainder 0x0c
TEST(CanonEvTest_966, LargeValueWithRemainder0x0c_966) {
    // val = 256 + 12 = 268
    // remainder = 12, val_after = 256
    // frac = 32/3
    // result = (256 + 32/3) / 32
    float expected = (256.0f + 32.0f / 3.0f) / 32.0f;
    float result = canonEv(268);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Remainder 0x0c when initial val = just 0x0c = 12
TEST(CanonEvTest_966, OnlyRemainder0x0c_966) {
    // val = 12, remainder = 12, val_after = 0
    // frac = 32/3
    // result = (0 + 32/3) / 32 = 1/3
    float expected = (32.0f / 3.0f) / 32.0f;
    float result = canonEv(12);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Remainder 0x14 when initial val = just 0x14 = 20
TEST(CanonEvTest_966, OnlyRemainder0x14_966) {
    // val = 20, remainder = 20, val_after = 0
    // frac = 64/3
    // result = (0 + 64/3) / 32 = 2/3
    float expected = (64.0f / 3.0f) / 32.0f;
    float result = canonEv(20);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Test symmetry: canonEv(x) == -canonEv(-x)
TEST(CanonEvTest_966, SymmetryProperty_966) {
    for (int64_t val : {0, 1, 12, 20, 31, 32, 44, 52, 72, 100, 168, 320}) {
        float pos = canonEv(val);
        float neg = canonEv(-val);
        EXPECT_NEAR(pos, -neg, kEpsilon) << "Symmetry failed for val=" << val;
    }
}

// Test remainder 0x10 (16) - generic case
TEST(CanonEvTest_966, Remainder0x10_966) {
    // val = 48 (32 + 16)
    // remainder = 16, val_after = 32
    // frac = 16.0
    // result = (32 + 16) / 32 = 1.5
    float result = canonEv(48);
    EXPECT_NEAR(result, 1.5f, kEpsilon);
}

// Sigma special case only triggers when val_after is exactly 160
TEST(CanonEvTest_966, SigmaOnlyAt160_966) {
    // val = 192 + 8 = 200
    // remainder = 8, val_after = 192 (not 160)
    // frac = 8.0 (no special handling)
    // result = (192 + 8) / 32 = 200/32 = 6.25
    float expected = 200.0f / 32.0f;
    float result = canonEv(200);
    EXPECT_NEAR(result, expected, kEpsilon);
}

// Sigma special case: confirm val_after=128+8=136 doesn't trigger
TEST(CanonEvTest_966, NonSigma128Plus8_966) {
    // val = 128 + 8 = 136
    // remainder = 8, val_after = 128
    // frac = 8.0
    // result = (128 + 8) / 32 = 4.25
    float expected = 136.0f / 32.0f;
    float result = canonEv(136);
    EXPECT_NEAR(result, expected, kEpsilon);
}
