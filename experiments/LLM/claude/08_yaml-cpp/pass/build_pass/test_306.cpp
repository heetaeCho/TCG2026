#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

class Umul64Test_306 : public ::testing::Test {
protected:
};

// Normal operation: basic multiplication of two positive numbers
TEST_F(Umul64Test_306, BasicMultiplication_306) {
    std::uint_least64_t result = umul64(6, 7);
    EXPECT_EQ(result, 42u);
}

// Normal operation: multiplication of larger values
TEST_F(Umul64Test_306, LargerValues_306) {
    std::uint_least64_t result = umul64(1000, 2000);
    EXPECT_EQ(result, 2000000u);
}

// Boundary: multiplication by zero (first operand)
TEST_F(Umul64Test_306, MultiplyByZeroFirst_306) {
    std::uint_least64_t result = umul64(0, 12345);
    EXPECT_EQ(result, 0u);
}

// Boundary: multiplication by zero (second operand)
TEST_F(Umul64Test_306, MultiplyByZeroSecond_306) {
    std::uint_least64_t result = umul64(12345, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: both operands zero
TEST_F(Umul64Test_306, BothZero_306) {
    std::uint_least64_t result = umul64(0, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: multiplication by one (identity, first operand)
TEST_F(Umul64Test_306, MultiplyByOneFirst_306) {
    std::uint_least64_t result = umul64(1, 99999);
    EXPECT_EQ(result, 99999u);
}

// Boundary: multiplication by one (identity, second operand)
TEST_F(Umul64Test_306, MultiplyByOneSecond_306) {
    std::uint_least64_t result = umul64(99999, 1);
    EXPECT_EQ(result, 99999u);
}

// Boundary: maximum uint32 values - result should fit in uint64
TEST_F(Umul64Test_306, MaxUint32Values_306) {
    std::uint_least32_t maxVal = UINT32_MAX;
    std::uint_least64_t result = umul64(maxVal, maxVal);
    // UINT32_MAX * UINT32_MAX = (2^32-1)^2 = 2^64 - 2^33 + 1
    std::uint_least64_t expected = static_cast<std::uint_least64_t>(maxVal) * static_cast<std::uint_least64_t>(maxVal);
    EXPECT_EQ(result, expected);
}

// Boundary: max uint32 multiplied by 1
TEST_F(Umul64Test_306, MaxUint32TimesOne_306) {
    std::uint_least32_t maxVal = UINT32_MAX;
    std::uint_least64_t result = umul64(maxVal, 1);
    EXPECT_EQ(result, static_cast<std::uint_least64_t>(maxVal));
}

// Boundary: max uint32 multiplied by 0
TEST_F(Umul64Test_306, MaxUint32TimesZero_306) {
    std::uint_least32_t maxVal = UINT32_MAX;
    std::uint_least64_t result = umul64(maxVal, 0);
    EXPECT_EQ(result, 0u);
}

// Normal: result exceeds 32-bit range but fits in 64-bit
TEST_F(Umul64Test_306, ResultExceeds32Bits_306) {
    // 100000 * 100000 = 10,000,000,000 which exceeds uint32 max
    std::uint_least64_t result = umul64(100000, 100000);
    EXPECT_EQ(result, 10000000000ULL);
}

// Boundary: power of two multiplication
TEST_F(Umul64Test_306, PowerOfTwoMultiplication_306) {
    std::uint_least64_t result = umul64(65536, 65536); // 2^16 * 2^16 = 2^32
    EXPECT_EQ(result, 4294967296ULL);
}

// Normal: commutativity check
TEST_F(Umul64Test_306, Commutativity_306) {
    std::uint_least64_t result1 = umul64(123, 456);
    std::uint_least64_t result2 = umul64(456, 123);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 56088u);
}

// Boundary: max uint32 multiplied by 2
TEST_F(Umul64Test_306, MaxUint32TimesTwo_306) {
    std::uint_least32_t maxVal = UINT32_MAX;
    std::uint_least64_t result = umul64(maxVal, 2);
    std::uint_least64_t expected = static_cast<std::uint_least64_t>(maxVal) * 2ULL;
    EXPECT_EQ(result, expected);
}

// Normal: small values
TEST_F(Umul64Test_306, SmallValues_306) {
    EXPECT_EQ(umul64(1, 1), 1u);
    EXPECT_EQ(umul64(2, 3), 6u);
    EXPECT_EQ(umul64(10, 10), 100u);
}

// Boundary: one operand is max, other is moderate
TEST_F(Umul64Test_306, MaxTimesModerate_306) {
    std::uint_least32_t maxVal = UINT32_MAX;
    std::uint_least64_t result = umul64(maxVal, 1000);
    std::uint_least64_t expected = static_cast<std::uint_least64_t>(maxVal) * 1000ULL;
    EXPECT_EQ(result, expected);
}
