#include <gtest/gtest.h>

// Include the header under test
#include "../TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// We need to understand the unsigned_decimal_fp structure to test properly.
// Based on the interface, it's a template struct with significand, exponent, and a bool parameter.

namespace {

using namespace YAML::jkj::dragonbox;

// Test fixture
class TrailingZeroRemoveTest_338 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test no_trailing_zeros with basic integer types
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosBasicUint32_338) {
    using format_t = float;  // placeholder format type
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(12345u), static_cast<int>(3));
    
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 3);
}

TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosBasicUint64_338) {
    using format_t = double;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned long long>(9876543210ULL), static_cast<int>(-5));
    
    EXPECT_EQ(result.significand, 9876543210ULL);
    EXPECT_EQ(result.exponent, -5);
}

// Test with zero significand
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosZeroSignificand_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(0u), static_cast<int>(0));
    
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with zero exponent
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosZeroExponent_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(42u), static_cast<int>(0));
    
    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with negative exponent
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosNegativeExponent_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(100u), static_cast<int>(-10));
    
    EXPECT_EQ(result.significand, 100u);
    EXPECT_EQ(result.exponent, -10);
}

// Test with large significand
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosLargeSignificand_338) {
    using format_t = double;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned long long>(0xFFFFFFFFFFFFFFFFULL), static_cast<int>(1));
    
    EXPECT_EQ(result.significand, 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result.exponent, 1);
}

// Test with max int exponent
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosMaxExponent_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(1u), static_cast<int>(std::numeric_limits<int>::max()));
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::max());
}

// Test with min int exponent
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosMinExponent_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(1u), static_cast<int>(std::numeric_limits<int>::min()));
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::min());
}

// Test that the result has the correct template parameter (false for trailing zeros indicator)
// This is verified implicitly by the type system - the return type has false as third parameter
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosReturnTypeCorrect_338) {
    using format_t = float;
    using result_type = decltype(policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(0u), static_cast<int>(0)));
    
    // Verify it compiles and the type is unsigned_decimal_fp with false
    static_assert(std::is_same<result_type, 
        unsigned_decimal_fp<unsigned int, int, false>>::value,
        "Return type should be unsigned_decimal_fp with false trailing zeros flag");
    
    SUCCEED();
}

// Test constexpr evaluation
TEST_F(TrailingZeroRemoveTest_338, NoTrailingZerosIsConstexpr_338) {
    using format_t = float;
    constexpr auto result = policy::trailing_zero::remove_t::no_trailing_zeros<format_t>(
        static_cast<unsigned int>(55u), static_cast<int>(7));
    
    static_assert(result.significand == 55u, "Significand should be 55");
    static_assert(result.exponent == 7, "Exponent should be 7");
    
    EXPECT_EQ(result.significand, 55u);
    EXPECT_EQ(result.exponent, 7);
}

// Test on_trailing_zeros method
TEST_F(TrailingZeroRemoveTest_338, OnTrailingZerosBasic_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<format_t>(
        static_cast<unsigned int>(12300u), static_cast<int>(2));
    
    // on_trailing_zeros should remove trailing zeros from significand and adjust exponent
    // The exact behavior depends on implementation, but we can verify the result type
    // and that it produces a valid unsigned_decimal_fp
    // Since the significand 12300 has two trailing zeros, we expect:
    // significand = 123, exponent = 2 + 2 = 4
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, 4);
}

TEST_F(TrailingZeroRemoveTest_338, OnTrailingZerosNoActualTrailingZeros_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<format_t>(
        static_cast<unsigned int>(12345u), static_cast<int>(3));
    
    // No trailing zeros to remove
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 3);
}

TEST_F(TrailingZeroRemoveTest_338, OnTrailingZerosAllZerosExceptFirst_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<format_t>(
        static_cast<unsigned int>(10000u), static_cast<int>(0));
    
    // 10000 has 4 trailing zeros
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 4);
}

TEST_F(TrailingZeroRemoveTest_338, OnTrailingZerosWithZeroSignificand_338) {
    using format_t = float;
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<format_t>(
        static_cast<unsigned int>(0u), static_cast<int>(0));
    
    // Zero significand - behavior might be to just return as-is
    EXPECT_EQ(result.significand, 0u);
}

TEST_F(TrailingZeroRemoveTest_338, OnTrailingZerosUint64_338) {
    using format_t = double;
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<format_t>(
        static_cast<unsigned long long>(123000000ULL), static_cast<int>(-5));
    
    // 123000000 has 6 trailing zeros
    EXPECT_EQ(result.significand, 123ULL);
    EXPECT_EQ(result.exponent, -5 + 6);
}

} // anonymous namespace
