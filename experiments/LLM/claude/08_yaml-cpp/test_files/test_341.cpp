#include <gtest/gtest.h>

// We need to include the header that contains the types under test.
// Based on the file structure, we include the dragonbox header.
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// Test fixture for report_t trailing zero policy
class ReportTrailingZeroTest_341 : public ::testing::Test {
protected:
    using report = policy::trailing_zero::report_t;
};

// Test on_trailing_zeros returns correct significand with uint32_t
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosReturnsCorrectSignificand_uint32_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(12345));
}

// Test on_trailing_zeros returns correct exponent with uint32_t
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosReturnsCorrectExponent_uint32_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    EXPECT_EQ(result.exponent, 10);
}

// Test on_trailing_zeros sets may_have_trailing_zeros to true
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosSetsTrailingZerosTrue_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test on_trailing_zeros with zero significand
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosWithZeroSignificand_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(0), static_cast<int>(0));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(0));
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test on_trailing_zeros with negative exponent
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosWithNegativeExponent_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(999), static_cast<int>(-5));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(999));
    EXPECT_EQ(result.exponent, -5);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test on_trailing_zeros with large significand (uint64_t for double)
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosWithUint64Significand_341) {
    auto result = report::on_trailing_zeros<double>(static_cast<uint64_t>(123456789012345ULL), static_cast<int>(100));
    EXPECT_EQ(result.significand, static_cast<uint64_t>(123456789012345ULL));
    EXPECT_EQ(result.exponent, 100);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test on_trailing_zeros with max uint32_t significand
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosMaxUint32Significand_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(0xFFFFFFFF), static_cast<int>(0));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(0xFFFFFFFF));
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test no_trailing_zeros returns correct significand
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosReturnsCorrectSignificand_341) {
    auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(12345));
}

// Test no_trailing_zeros returns correct exponent
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosReturnsCorrectExponent_341) {
    auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    EXPECT_EQ(result.exponent, 10);
}

// Test no_trailing_zeros still sets may_have_trailing_zeros to true (report_t reports both as true)
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosMayHaveTrailingZerosField_341) {
    auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(12345), static_cast<int>(10));
    // report_t returns unsigned_decimal_fp with the third template param as true
    // The may_have_trailing_zeros field value depends on implementation
    // but the return type has the trailing_zeros template parameter set to true
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test no_trailing_zeros with zero significand
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosWithZeroSignificand_341) {
    auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(0), static_cast<int>(0));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(0));
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with negative exponent
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosWithNegativeExponent_341) {
    auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(42), static_cast<int>(-100));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(42));
    EXPECT_EQ(result.exponent, -100);
}

// Test no_trailing_zeros with uint64_t significand
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosWithUint64Significand_341) {
    auto result = report::no_trailing_zeros<double>(static_cast<uint64_t>(999999999999999ULL), static_cast<int>(-50));
    EXPECT_EQ(result.significand, static_cast<uint64_t>(999999999999999ULL));
    EXPECT_EQ(result.exponent, -50);
}

// Test constexpr evaluation of on_trailing_zeros
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosIsConstexpr_341) {
    constexpr auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(100), static_cast<int>(5));
    static_assert(result.significand == 100, "significand should be 100");
    static_assert(result.exponent == 5, "exponent should be 5");
    static_assert(result.may_have_trailing_zeros == true, "may_have_trailing_zeros should be true");
    EXPECT_EQ(result.significand, static_cast<uint32_t>(100));
}

// Test constexpr evaluation of no_trailing_zeros
TEST_F(ReportTrailingZeroTest_341, NoTrailingZerosIsConstexpr_341) {
    constexpr auto result = report::no_trailing_zeros<float>(static_cast<uint32_t>(200), static_cast<int>(-3));
    static_assert(result.significand == 200, "significand should be 200");
    static_assert(result.exponent == -3, "exponent should be -3");
    EXPECT_EQ(result.significand, static_cast<uint32_t>(200));
}

// Test on_trailing_zeros with boundary exponent values
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosWithMaxIntExponent_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(1), static_cast<int>(std::numeric_limits<int>::max()));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(1));
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::max());
    EXPECT_TRUE(result.may_have_trailing_zeros);
}

// Test on_trailing_zeros with min int exponent
TEST_F(ReportTrailingZeroTest_341, OnTrailingZerosWithMinIntExponent_341) {
    auto result = report::on_trailing_zeros<float>(static_cast<uint32_t>(1), static_cast<int>(std::numeric_limits<int>::min()));
    EXPECT_EQ(result.significand, static_cast<uint32_t>(1));
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::min());
    EXPECT_TRUE(result.may_have_trailing_zeros);
}
