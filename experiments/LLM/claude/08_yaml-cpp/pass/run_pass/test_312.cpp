#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::umul96_lower64;

// Test normal multiplication of small values
TEST(Umul96Lower64Test_312, SmallValues_312) {
    // 2 * 3 = 6
    EXPECT_EQ(umul96_lower64(2, 3), UINT64_C(6));
}

// Test multiplication by zero (x = 0)
TEST(Umul96Lower64Test_312, XIsZero_312) {
    EXPECT_EQ(umul96_lower64(0, 12345), UINT64_C(0));
}

// Test multiplication by zero (y = 0)
TEST(Umul96Lower64Test_312, YIsZero_312) {
    EXPECT_EQ(umul96_lower64(12345, 0), UINT64_C(0));
}

// Test both operands zero
TEST(Umul96Lower64Test_312, BothZero_312) {
    EXPECT_EQ(umul96_lower64(0, 0), UINT64_C(0));
}

// Test multiplication by one (x = 1)
TEST(Umul96Lower64Test_312, XIsOne_312) {
    EXPECT_EQ(umul96_lower64(1, UINT64_C(0xFFFFFFFFFFFFFFFF)), UINT64_C(0xFFFFFFFFFFFFFFFF));
}

// Test multiplication by one (y = 1)
TEST(Umul96Lower64Test_312, YIsOne_312) {
    EXPECT_EQ(umul96_lower64(42, 1), UINT64_C(42));
}

// Test with maximum uint32 value and small y
TEST(Umul96Lower64Test_312, MaxUint32TimesSmallY_312) {
    // 0xFFFFFFFF * 2 = 0x1FFFFFFFE, lower 64 bits = 0x1FFFFFFFE
    uint32_t x = UINT32_C(0xFFFFFFFF);
    uint64_t y = UINT64_C(2);
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0x1FFFFFFFE));
}

// Test with maximum uint32 and maximum uint64
TEST(Umul96Lower64Test_312, MaxUint32TimesMaxUint64_312) {
    // 0xFFFFFFFF * 0xFFFFFFFFFFFFFFFF
    // The full 96-bit result would be 0xFFFFFFFE_FFFFFFFF_00000001 (conceptually)
    // But the function masks with 0xFFFFFFFFFFFFFFFF, so we get lower 64 bits
    // Let's compute: 0xFFFFFFFF * 0xFFFFFFFFFFFFFFFF
    // = (2^32 - 1) * (2^64 - 1)
    // = 2^96 - 2^64 - 2^32 + 1
    // Lower 64 bits: (-2^32 + 1) mod 2^64 = 2^64 - 2^32 + 1 = 0xFFFFFFFF00000001
    uint32_t x = UINT32_C(0xFFFFFFFF);
    uint64_t y = UINT64_C(0xFFFFFFFFFFFFFFFF);
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0xFFFFFFFF00000001));
}

// Test with x = max uint32, y = max uint32
TEST(Umul96Lower64Test_312, MaxUint32TimesMaxUint32AsY_312) {
    // 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
    uint32_t x = UINT32_C(0xFFFFFFFF);
    uint64_t y = UINT64_C(0xFFFFFFFF);
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0xFFFFFFFE00000001));
}

// Test with power of two values
TEST(Umul96Lower64Test_312, PowerOfTwoValues_312) {
    // 2^16 * 2^48 = 2^64, lower 64 bits should be 0
    uint32_t x = UINT32_C(0x10000);       // 2^16
    uint64_t y = UINT64_C(0x1000000000000); // 2^48
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0));
}

// Test constexpr nature
TEST(Umul96Lower64Test_312, ConstexprEvaluation_312) {
    constexpr uint64_t result = umul96_lower64(10, 20);
    EXPECT_EQ(result, UINT64_C(200));
}

// Test with large y value that causes overflow past 64 bits
TEST(Umul96Lower64Test_312, OverflowMasking_312) {
    // 2 * 0x8000000000000000 = 0x10000000000000000, lower 64 bits = 0
    uint32_t x = 2;
    uint64_t y = UINT64_C(0x8000000000000000);
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0));
}

// Test with 3 * large y
TEST(Umul96Lower64Test_312, ThreeTimesLargeY_312) {
    // 3 * 0x8000000000000000 = 0x18000000000000000
    // Lower 64 bits = 0x8000000000000000
    uint32_t x = 3;
    uint64_t y = UINT64_C(0x8000000000000000);
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(0x8000000000000000));
}

// Test with typical non-trivial values
TEST(Umul96Lower64Test_312, TypicalValues_312) {
    uint32_t x = 1000000;
    uint64_t y = UINT64_C(1000000000000);
    // 1000000 * 1000000000000 = 10^18 = 0xDE0B6B3A7640000
    uint64_t result = umul96_lower64(x, y);
    EXPECT_EQ(result, UINT64_C(1000000000000000000));
}

// Test commutativity-like behavior when y fits in 32 bits
TEST(Umul96Lower64Test_312, CommutativeSmallValues_312) {
    uint32_t a = 123;
    uint64_t b = 456;
    uint32_t c = 456;
    uint64_t d = 123;
    EXPECT_EQ(umul96_lower64(a, b), umul96_lower64(c, d));
}

// Test with x = 1 and y = 0x8000000000000000 (high bit set)
TEST(Umul96Lower64Test_312, OneTimesHighBitY_312) {
    uint64_t result = umul96_lower64(1, UINT64_C(0x8000000000000000));
    EXPECT_EQ(result, UINT64_C(0x8000000000000000));
}

} // namespace
