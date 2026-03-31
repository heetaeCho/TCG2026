#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cstdint>
#include <limits>

// Test fixture for small_division_by_pow10 tests
class SmallDivisionByPow10Test_326 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Tests for N=1 (division by 10) with uint32_t =====

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Zero_326) {
    // 0 / 10 = 0
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_One_326) {
    // 1 / 10 = 0
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(1);
    EXPECT_EQ(result, 0u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Nine_326) {
    // 9 / 10 = 0
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(9);
    EXPECT_EQ(result, 0u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Ten_326) {
    // 10 / 10 = 1
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(10);
    EXPECT_EQ(result, 1u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Eleven_326) {
    // 11 / 10 = 1
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(11);
    EXPECT_EQ(result, 1u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_NinetyNine_326) {
    // 99 / 10 = 9
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(99);
    EXPECT_EQ(result, 9u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Hundred_326) {
    // 100 / 10 = 10 (boundary: n <= 10^(N+1) = 10^2 = 100)
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(100);
    EXPECT_EQ(result, 10u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Fifty_326) {
    // 50 / 10 = 5
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(50);
    EXPECT_EQ(result, 5u);
}

// ===== Tests for N=2 (division by 100) with uint32_t =====

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Zero_326) {
    // 0 / 100 = 0
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_NinetyNine_326) {
    // 99 / 100 = 0
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(99);
    EXPECT_EQ(result, 0u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Hundred_326) {
    // 100 / 100 = 1
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(100);
    EXPECT_EQ(result, 1u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Thousand_326) {
    // 1000 / 100 = 10 (boundary: n <= 10^(N+1) = 10^3 = 1000)
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(1000);
    EXPECT_EQ(result, 10u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_FiveHundred_326) {
    // 500 / 100 = 5
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(500);
    EXPECT_EQ(result, 5u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_199_326) {
    // 199 / 100 = 1
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(199);
    EXPECT_EQ(result, 1u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_999_326) {
    // 999 / 100 = 9
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(999);
    EXPECT_EQ(result, 9u);
}

// ===== Tests for N=1 (division by 10) with uint64_t =====

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Uint64_Zero_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint64_t>(0ull);
    EXPECT_EQ(result, 0ull);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Uint64_Fifty_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint64_t>(50ull);
    EXPECT_EQ(result, 5ull);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Uint64_Hundred_326) {
    // Boundary: n <= 10^2 = 100
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint64_t>(100ull);
    EXPECT_EQ(result, 10ull);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Uint64_One_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint64_t>(1ull);
    EXPECT_EQ(result, 0ull);
}

// ===== Tests for N=2 (division by 100) with uint64_t =====

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Uint64_Zero_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint64_t>(0ull);
    EXPECT_EQ(result, 0ull);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Uint64_Thousand_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint64_t>(1000ull);
    EXPECT_EQ(result, 10ull);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Uint64_250_326) {
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint64_t>(250ull);
    EXPECT_EQ(result, 2ull);
}

// ===== Tests verifying consecutive values for consistency =====

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_ConsecutiveValues_326) {
    // For values 0..100, verify small_division_by_pow10<1> matches n/10
    for (uint32_t n = 0; n <= 100; ++n) {
        auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(n);
        EXPECT_EQ(result, n / 10u) << "Failed for n=" << n;
    }
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_ConsecutiveValues_326) {
    // For values 0..1000, verify small_division_by_pow10<2> matches n/100
    for (uint32_t n = 0; n <= 1000; ++n) {
        auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(n);
        EXPECT_EQ(result, n / 100u) << "Failed for n=" << n;
    }
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_Uint64_ConsecutiveValues_326) {
    for (uint64_t n = 0; n <= 100; ++n) {
        auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint64_t>(n);
        EXPECT_EQ(result, n / 10ull) << "Failed for n=" << n;
    }
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_Uint64_ConsecutiveValues_326) {
    for (uint64_t n = 0; n <= 1000; ++n) {
        auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint64_t>(n);
        EXPECT_EQ(result, n / 100ull) << "Failed for n=" << n;
    }
}

// ===== Boundary: exact power of 10 at the upper limit =====

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_ExactBoundary_326) {
    // n = 10^(N+1) = 100 is the max allowed
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(100);
    EXPECT_EQ(result, 10u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByHundred_ExactBoundary_326) {
    // n = 10^(N+1) = 1000 is the max allowed
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<2, uint32_t>(1000);
    EXPECT_EQ(result, 10u);
}

// ===== Additional edge: values just below multiples of divisor =====

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_JustBelowMultiple_326) {
    // 19 / 10 = 1
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(19);
    EXPECT_EQ(result, 1u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_ExactMultiple_326) {
    // 20 / 10 = 2
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(20);
    EXPECT_EQ(result, 2u);
}

TEST_F(SmallDivisionByPow10Test_326, DivideByTen_JustAboveMultiple_326) {
    // 21 / 10 = 2
    auto result = YAML::jkj::dragonbox::detail::div::small_division_by_pow10<1, uint32_t>(21);
    EXPECT_EQ(result, 2u);
}
