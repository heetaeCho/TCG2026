#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Test fixture for remove_compact_t trailing zero policy
class RemoveCompactTrailingZeroTest_340 : public ::testing::Test {
protected:
    policy::trailing_zero::remove_compact_t policy_;
};

// Test no_trailing_zeros returns correct significand and exponent with basic values
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosBasicValues_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(12345),
        static_cast<int>(-3)
    );
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, -3);
}

// Test no_trailing_zeros with zero significand
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosZeroSignificand_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(0),
        static_cast<int>(0)
    );
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with zero exponent
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosZeroExponent_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(100),
        static_cast<int>(0)
    );
    EXPECT_EQ(result.significand, 100u);
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with negative exponent
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosNegativeExponent_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(999),
        static_cast<int>(-10)
    );
    EXPECT_EQ(result.significand, 999u);
    EXPECT_EQ(result.exponent, -10);
}

// Test no_trailing_zeros with positive exponent
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosPositiveExponent_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(1),
        static_cast<int>(5)
    );
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 5);
}

// Test no_trailing_zeros with large significand
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosLargeSignificand_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(4294967295u),  // max uint32
        static_cast<int>(0)
    );
    EXPECT_EQ(result.significand, 4294967295u);
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with double format
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosDoubleFormat_340) {
    auto result = policy_.no_trailing_zeros<double>(
        static_cast<unsigned long long>(123456789012345ULL),
        static_cast<int>(-15)
    );
    EXPECT_EQ(result.significand, 123456789012345ULL);
    EXPECT_EQ(result.exponent, -15);
}

// Test no_trailing_zeros with significand having trailing zeros (they should be preserved as-is)
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosPreservesTrailingZeros_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(12300),
        static_cast<int>(-5)
    );
    EXPECT_EQ(result.significand, 12300u);
    EXPECT_EQ(result.exponent, -5);
}

// Test on_trailing_zeros basic functionality
TEST_F(RemoveCompactTrailingZeroTest_340, OnTrailingZerosBasicValues_340) {
    auto result = policy_.on_trailing_zeros<float>(
        static_cast<unsigned int>(12300),
        static_cast<int>(-5)
    );
    // on_trailing_zeros for remove_compact_t should remove trailing zeros
    // and adjust exponent accordingly
    // 12300 -> 123, exponent -5 + 2 = -3
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, -3);
}

// Test on_trailing_zeros with no actual trailing zeros
TEST_F(RemoveCompactTrailingZeroTest_340, OnTrailingZerosNoActualTrailingZeros_340) {
    auto result = policy_.on_trailing_zeros<float>(
        static_cast<unsigned int>(12345),
        static_cast<int>(-3)
    );
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, -3);
}

// Test on_trailing_zeros with zero significand
TEST_F(RemoveCompactTrailingZeroTest_340, OnTrailingZerosZeroSignificand_340) {
    auto result = policy_.on_trailing_zeros<float>(
        static_cast<unsigned int>(0),
        static_cast<int>(0)
    );
    EXPECT_EQ(result.significand, 0u);
}

// Test on_trailing_zeros with all trailing zeros except leading 1
TEST_F(RemoveCompactTrailingZeroTest_340, OnTrailingZerosAllTrailing_340) {
    auto result = policy_.on_trailing_zeros<float>(
        static_cast<unsigned int>(10000),
        static_cast<int>(0)
    );
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 4);
}

// Test on_trailing_zeros with single trailing zero
TEST_F(RemoveCompactTrailingZeroTest_340, OnTrailingZerosSingleTrailing_340) {
    auto result = policy_.on_trailing_zeros<float>(
        static_cast<unsigned int>(1230),
        static_cast<int>(-2)
    );
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, -1);
}

// Test return type has may_have_trailing_zeros = false
TEST_F(RemoveCompactTrailingZeroTest_340, NoTrailingZerosReturnType_340) {
    auto result = policy_.no_trailing_zeros<float>(
        static_cast<unsigned int>(42),
        static_cast<int>(1)
    );
    // The return type is unsigned_decimal_fp<..., false>, meaning may_have_trailing_zeros is false
    // We verify the values are correctly passed through
    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.exponent, 1);
}

}  // namespace
