#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::count_factors;

// ============================================================
// Tests for count_factors<2, ...>
// ============================================================

TEST(CountFactorsTest_314, ZeroFactorsOfTwo_314) {
    // Odd numbers have zero factors of 2
    constexpr int result = count_factors<2, unsigned int>(1u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, OddNumberHasZeroFactorsOfTwo_314) {
    constexpr int result = count_factors<2, unsigned int>(3u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, SingleFactorOfTwo_314) {
    constexpr int result = count_factors<2, unsigned int>(2u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, MultipleFactorsOfTwo_314) {
    constexpr int result = count_factors<2, unsigned int>(8u);
    EXPECT_EQ(result, 3);
}

TEST(CountFactorsTest_314, PowerOfTwo16_314) {
    constexpr int result = count_factors<2, unsigned int>(16u);
    EXPECT_EQ(result, 4);
}

TEST(CountFactorsTest_314, PowerOfTwo1024_314) {
    constexpr int result = count_factors<2, unsigned int>(1024u);
    EXPECT_EQ(result, 10);
}

TEST(CountFactorsTest_314, MixedFactorsOfTwo_314) {
    // 12 = 2^2 * 3
    constexpr int result = count_factors<2, unsigned int>(12u);
    EXPECT_EQ(result, 2);
}

TEST(CountFactorsTest_314, LargeEvenNumber_314) {
    // 48 = 2^4 * 3
    constexpr int result = count_factors<2, unsigned int>(48u);
    EXPECT_EQ(result, 4);
}

// ============================================================
// Tests for count_factors<3, ...>
// ============================================================

TEST(CountFactorsTest_314, ZeroFactorsOfThree_314) {
    constexpr int result = count_factors<3, unsigned int>(1u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, SingleFactorOfThree_314) {
    constexpr int result = count_factors<3, unsigned int>(3u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, MultipleFactorsOfThree_314) {
    // 27 = 3^3
    constexpr int result = count_factors<3, unsigned int>(27u);
    EXPECT_EQ(result, 3);
}

TEST(CountFactorsTest_314, MixedFactorsOfThree_314) {
    // 18 = 2 * 3^2
    constexpr int result = count_factors<3, unsigned int>(18u);
    EXPECT_EQ(result, 2);
}

TEST(CountFactorsTest_314, NoFactorsOfThree_314) {
    constexpr int result = count_factors<3, unsigned int>(4u);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Tests for count_factors<5, ...>
// ============================================================

TEST(CountFactorsTest_314, ZeroFactorsOfFive_314) {
    constexpr int result = count_factors<5, unsigned int>(1u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, SingleFactorOfFive_314) {
    constexpr int result = count_factors<5, unsigned int>(5u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, MultipleFactorsOfFive_314) {
    // 125 = 5^3
    constexpr int result = count_factors<5, unsigned int>(125u);
    EXPECT_EQ(result, 3);
}

TEST(CountFactorsTest_314, MixedFactorsOfFive_314) {
    // 50 = 2 * 5^2
    constexpr int result = count_factors<5, unsigned int>(50u);
    EXPECT_EQ(result, 2);
}

TEST(CountFactorsTest_314, NoFactorsOfFive_314) {
    constexpr int result = count_factors<5, unsigned int>(7u);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Tests for count_factors<10, ...>
// ============================================================

TEST(CountFactorsTest_314, ZeroFactorsOfTen_314) {
    constexpr int result = count_factors<10, unsigned int>(1u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, SingleFactorOfTen_314) {
    constexpr int result = count_factors<10, unsigned int>(10u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, MultipleFactorsOfTen_314) {
    // 1000 = 10^3
    constexpr int result = count_factors<10, unsigned int>(1000u);
    EXPECT_EQ(result, 3);
}

TEST(CountFactorsTest_314, NoFactorsOfTen_314) {
    constexpr int result = count_factors<10, unsigned int>(3u);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Tests with different UInt types
// ============================================================

TEST(CountFactorsTest_314, Uint64SingleFactorOfTwo_314) {
    constexpr int result = count_factors<2, uint64_t>(static_cast<uint64_t>(2));
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, Uint64LargePowerOfTwo_314) {
    // 2^32
    constexpr int result = count_factors<2, uint64_t>(static_cast<uint64_t>(1) << 32);
    EXPECT_EQ(result, 32);
}

TEST(CountFactorsTest_314, Uint16FactorsOfTwo_314) {
    constexpr int result = count_factors<2, uint16_t>(static_cast<uint16_t>(64));
    EXPECT_EQ(result, 6);
}

TEST(CountFactorsTest_314, Uint64LargePowerOfFive_314) {
    // 5^10 = 9765625
    constexpr int result = count_factors<5, uint64_t>(static_cast<uint64_t>(9765625));
    EXPECT_EQ(result, 10);
}

// ============================================================
// Boundary-like tests
// ============================================================

TEST(CountFactorsTest_314, FactorOfTwoForTwo_314) {
    constexpr int result = count_factors<2, unsigned int>(2u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, LargeOddNumber_314) {
    constexpr int result = count_factors<2, unsigned int>(999999937u);
    EXPECT_EQ(result, 0);
}

TEST(CountFactorsTest_314, FactorsOf2In6_314) {
    // 6 = 2 * 3
    constexpr int result = count_factors<2, unsigned int>(6u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, FactorsOf5In3125_314) {
    // 3125 = 5^5
    constexpr int result = count_factors<5, unsigned int>(3125u);
    EXPECT_EQ(result, 5);
}

TEST(CountFactorsTest_314, FactorsOf7In2401_314) {
    // 2401 = 7^4
    constexpr int result = count_factors<7, unsigned int>(2401u);
    EXPECT_EQ(result, 4);
}

TEST(CountFactorsTest_314, FactorsOf7In14_314) {
    // 14 = 2 * 7
    constexpr int result = count_factors<7, unsigned int>(14u);
    EXPECT_EQ(result, 1);
}

TEST(CountFactorsTest_314, FactorsOf2InMaxPowerOf2InUint32_314) {
    // 2^31 = 2147483648
    constexpr int result = count_factors<2, uint32_t>(static_cast<uint32_t>(1) << 31);
    EXPECT_EQ(result, 31);
}

// ============================================================
// Constexpr verification tests
// ============================================================

TEST(CountFactorsTest_314, ConstexprCompileTime_314) {
    // Verify that the function is usable in constexpr context
    static_assert(count_factors<2, unsigned int>(1u) == 0, "1 has 0 factors of 2");
    static_assert(count_factors<2, unsigned int>(8u) == 3, "8 has 3 factors of 2");
    static_assert(count_factors<5, unsigned int>(25u) == 2, "25 has 2 factors of 5");
    static_assert(count_factors<3, unsigned int>(81u) == 4, "81 has 4 factors of 3");
    SUCCEED();
}

} // namespace
