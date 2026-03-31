#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cstdint>

namespace {

using namespace YAML::jkj::dragonbox::detail;

// Test fixture for check_divisibility_and_divide_by_pow10 tests
class CheckDivisibilityAndDivideByPow10Test_325 : public ::testing::Test {
protected:
};

// =====================================================================
// Tests for N=1 with uint32_t
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_DivisibleByTen_325) {
    // 20 is divisible by 10, so result should be true, and n should become 2
    uint32_t n = 20;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 2u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_NotDivisibleByTen_325) {
    // 21 is not divisible by 10, so result should be false, and n should become 2 (floor(21/10))
    uint32_t n = 21;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 2u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_Zero_325) {
    // 0 is divisible by 10
    uint32_t n = 0;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 0u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_Ten_325) {
    // 10 is divisible by 10
    uint32_t n = 10;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 1u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_One_325) {
    // 1 is not divisible by 10
    uint32_t n = 1;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 0u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_Ninety_325) {
    // 90 is divisible by 10
    uint32_t n = 90;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 9u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_NinetyNine_325) {
    // 99 is not divisible by 10
    uint32_t n = 99;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 9u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_Fifty_325) {
    // 50 is divisible by 10
    uint32_t n = 50;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 5u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_FiftyFive_325) {
    // 55 is not divisible by 10
    uint32_t n = 55;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 5u);
}

// =====================================================================
// Tests for N=2 with uint32_t (divide by 100)
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_DivisibleByHundred_325) {
    // 200 is divisible by 100
    uint32_t n = 200;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 2u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_NotDivisibleByHundred_325) {
    // 201 is not divisible by 100
    uint32_t n = 201;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 2u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_Zero_325) {
    uint32_t n = 0;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 0u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_Hundred_325) {
    uint32_t n = 100;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 1u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_NineHundredNinetyNine_325) {
    // 999 is not divisible by 100, floor(999/100) = 9
    uint32_t n = 999;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 9u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_FiveHundred_325) {
    uint32_t n = 500;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 5u);
}

// =====================================================================
// Tests for N=1 with uint64_t
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt64_DivisibleByTen_325) {
    uint64_t n = 30;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 3u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt64_NotDivisibleByTen_325) {
    uint64_t n = 37;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 3u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt64_Zero_325) {
    uint64_t n = 0;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 0u);
}

// =====================================================================
// Tests for boundary: max value within the constraint n <= 10^(N+1)
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_MaxBoundaryValue_325) {
    // For N=1, n <= 10^2 = 100
    uint32_t n = 100;
    bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 10u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_MaxBoundaryValue_325) {
    // For N=2, n <= 10^3 = 1000
    uint32_t n = 1000;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 10u);
}

// =====================================================================
// Tests for various small values with N=1
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_AllSingleDigits_325) {
    // Test all values 0-9; only 0 is divisible by 10
    for (uint32_t i = 0; i <= 9; ++i) {
        uint32_t n = i;
        bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
        if (i == 0) {
            EXPECT_TRUE(result) << "Failed for n=" << i;
        } else {
            EXPECT_FALSE(result) << "Failed for n=" << i;
        }
        EXPECT_EQ(n, 0u) << "Failed for n=" << i;
    }
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_MultiplesOfTenUpToHundred_325) {
    // All multiples of 10 from 0 to 100 should be divisible
    for (uint32_t i = 0; i <= 100; i += 10) {
        uint32_t n = i;
        bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
        EXPECT_TRUE(result) << "Failed for n=" << i;
        EXPECT_EQ(n, i / 10) << "Failed for n=" << i;
    }
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N1_UInt32_NonMultiplesOfTen_325) {
    // Non-multiples of 10 should not be divisible
    for (uint32_t i = 1; i <= 99; ++i) {
        if (i % 10 == 0) continue;
        uint32_t n = i;
        bool result = div::check_divisibility_and_divide_by_pow10<1>(n);
        EXPECT_FALSE(result) << "Failed for n=" << i;
        EXPECT_EQ(n, i / 10) << "Failed for n=" << i;
    }
}

// =====================================================================
// Tests for N=2 with uint64_t
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt64_DivisibleByHundred_325) {
    uint64_t n = 700;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_TRUE(result);
    EXPECT_EQ(n, 7u);
}

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt64_NotDivisibleByHundred_325) {
    uint64_t n = 750;
    bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
    EXPECT_FALSE(result);
    EXPECT_EQ(n, 7u);
}

// =====================================================================
// Comprehensive test for N=2 with uint32_t: all values 0..1000
// =====================================================================

TEST_F(CheckDivisibilityAndDivideByPow10Test_325, N2_UInt32_AllValuesUpToThousand_325) {
    for (uint32_t i = 0; i <= 1000; ++i) {
        uint32_t n = i;
        bool result = div::check_divisibility_and_divide_by_pow10<2>(n);
        bool expected_divisible = (i % 100 == 0);
        EXPECT_EQ(result, expected_divisible) << "Divisibility check failed for n=" << i;
        EXPECT_EQ(n, i / 100) << "Division result failed for n=" << i;
    }
}

} // anonymous namespace
