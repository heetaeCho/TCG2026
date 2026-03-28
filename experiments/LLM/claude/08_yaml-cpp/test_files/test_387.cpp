#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using ToOdd = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::to_odd_t;

// Test with even unsigned int - should prefer round down (return true)
TEST(ToOddTest_387, EvenUintReturnsTrue_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<unsigned int>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<unsigned int>(2)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<unsigned int>(4)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<unsigned int>(100)));
}

// Test with odd unsigned int - should not prefer round down (return false)
TEST(ToOddTest_387, OddUintReturnsFalse_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<unsigned int>(1)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<unsigned int>(3)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<unsigned int>(5)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<unsigned int>(99)));
}

// Test with uint32_t
TEST(ToOddTest_387, Uint32Even_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint32_t>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint32_t>(42)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint32_t>(1000)));
}

TEST(ToOddTest_387, Uint32Odd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint32_t>(1)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint32_t>(43)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint32_t>(999)));
}

// Test with uint64_t
TEST(ToOddTest_387, Uint64Even_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint64_t>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint64_t>(2)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint64_t>(1000000000000ULL)));
}

TEST(ToOddTest_387, Uint64Odd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint64_t>(1)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint64_t>(3)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint64_t>(999999999999ULL)));
}

// Boundary: zero is even
TEST(ToOddTest_387, ZeroIsEven_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint32_t>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint64_t>(0)));
}

// Boundary: max values for uint32_t and uint64_t (both are odd: all bits set)
TEST(ToOddTest_387, MaxUint32IsOdd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(std::numeric_limits<uint32_t>::max()));
}

TEST(ToOddTest_387, MaxUint64IsOdd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(std::numeric_limits<uint64_t>::max()));
}

// Boundary: max value minus 1 is even
TEST(ToOddTest_387, MaxUint32MinusOneIsEven_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(std::numeric_limits<uint32_t>::max() - 1));
}

TEST(ToOddTest_387, MaxUint64MinusOneIsEven_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(std::numeric_limits<uint64_t>::max() - 1));
}

// Test constexpr behavior
TEST(ToOddTest_387, ConstexprEvaluation_387) {
    constexpr bool even_result = ToOdd::prefer_round_down(static_cast<uint32_t>(10));
    constexpr bool odd_result = ToOdd::prefer_round_down(static_cast<uint32_t>(11));
    EXPECT_TRUE(even_result);
    EXPECT_FALSE(odd_result);
}

// Test with uint16_t (smaller carrier type)
TEST(ToOddTest_387, Uint16Even_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint16_t>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint16_t>(2)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint16_t>(256)));
}

TEST(ToOddTest_387, Uint16Odd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint16_t>(1)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint16_t>(255)));
}

// Test with uint8_t
TEST(ToOddTest_387, Uint8Even_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint8_t>(0)));
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint8_t>(254)));
}

TEST(ToOddTest_387, Uint8Odd_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint8_t>(1)));
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint8_t>(255)));
}

// Test with large even and odd numbers
TEST(ToOddTest_387, LargeEvenNumber_387) {
    EXPECT_TRUE(ToOdd::prefer_round_down(static_cast<uint64_t>(0xFFFFFFFFFFFFFFFEULL)));
}

TEST(ToOddTest_387, LargeOddNumber_387) {
    EXPECT_FALSE(ToOdd::prefer_round_down(static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL)));
}

// Noexcept check
TEST(ToOddTest_387, NoexceptGuarantee_387) {
    static_assert(noexcept(ToOdd::prefer_round_down(static_cast<uint32_t>(0))),
                  "prefer_round_down should be noexcept");
    static_assert(noexcept(ToOdd::prefer_round_down(static_cast<uint64_t>(0))),
                  "prefer_round_down should be noexcept");
}
