#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cstdint>

using namespace YAML::jkj::dragonbox::detail;

// Test: compute_power with k=0 should return 1 for any base
TEST(ComputePowerTest_313, PowerOfZeroReturnsOne_313) {
    EXPECT_EQ((compute_power<0, int>(0)), 1);
    EXPECT_EQ((compute_power<0, int>(1)), 1);
    EXPECT_EQ((compute_power<0, int>(5)), 1);
    EXPECT_EQ((compute_power<0, int>(100)), 1);
    EXPECT_EQ((compute_power<0, int>(-3)), 1);
}

// Test: compute_power with k=1 should return the base itself
TEST(ComputePowerTest_313, PowerOfOneReturnsBase_313) {
    EXPECT_EQ((compute_power<1, int>(0)), 0);
    EXPECT_EQ((compute_power<1, int>(1)), 1);
    EXPECT_EQ((compute_power<1, int>(5)), 5);
    EXPECT_EQ((compute_power<1, int>(10)), 10);
    EXPECT_EQ((compute_power<1, int>(-7)), -7);
}

// Test: compute_power with k=2 should return base squared
TEST(ComputePowerTest_313, PowerOfTwoReturnsSquare_313) {
    EXPECT_EQ((compute_power<2, int>(0)), 0);
    EXPECT_EQ((compute_power<2, int>(1)), 1);
    EXPECT_EQ((compute_power<2, int>(2)), 4);
    EXPECT_EQ((compute_power<2, int>(3)), 9);
    EXPECT_EQ((compute_power<2, int>(10)), 100);
    EXPECT_EQ((compute_power<2, int>(-3)), 9);
}

// Test: compute_power with k=3 should return base cubed
TEST(ComputePowerTest_313, PowerOfThreeReturnsCube_313) {
    EXPECT_EQ((compute_power<3, int>(2)), 8);
    EXPECT_EQ((compute_power<3, int>(3)), 27);
    EXPECT_EQ((compute_power<3, int>(5)), 125);
    EXPECT_EQ((compute_power<3, int>(-2)), -8);
}

// Test: compute_power with larger exponents
TEST(ComputePowerTest_313, LargerExponents_313) {
    EXPECT_EQ((compute_power<4, int>(2)), 16);
    EXPECT_EQ((compute_power<5, int>(2)), 32);
    EXPECT_EQ((compute_power<10, int>(2)), 1024);
    EXPECT_EQ((compute_power<6, int>(3)), 729);
}

// Test: compute_power with base 0 and positive exponent returns 0
TEST(ComputePowerTest_313, BaseZeroWithPositiveExponent_313) {
    EXPECT_EQ((compute_power<1, int>(0)), 0);
    EXPECT_EQ((compute_power<2, int>(0)), 0);
    EXPECT_EQ((compute_power<5, int>(0)), 0);
    EXPECT_EQ((compute_power<10, int>(0)), 0);
}

// Test: compute_power with base 1 always returns 1
TEST(ComputePowerTest_313, BaseOneAlwaysReturnsOne_313) {
    EXPECT_EQ((compute_power<0, int>(1)), 1);
    EXPECT_EQ((compute_power<1, int>(1)), 1);
    EXPECT_EQ((compute_power<5, int>(1)), 1);
    EXPECT_EQ((compute_power<20, int>(1)), 1);
}

// Test: compute_power with negative base and even exponent returns positive
TEST(ComputePowerTest_313, NegativeBaseEvenExponent_313) {
    EXPECT_EQ((compute_power<2, int>(-2)), 4);
    EXPECT_EQ((compute_power<4, int>(-2)), 16);
    EXPECT_EQ((compute_power<2, int>(-5)), 25);
    EXPECT_EQ((compute_power<4, int>(-3)), 81);
}

// Test: compute_power with negative base and odd exponent returns negative
TEST(ComputePowerTest_313, NegativeBaseOddExponent_313) {
    EXPECT_EQ((compute_power<1, int>(-2)), -2);
    EXPECT_EQ((compute_power<3, int>(-2)), -8);
    EXPECT_EQ((compute_power<5, int>(-2)), -32);
    EXPECT_EQ((compute_power<3, int>(-3)), -27);
}

// Test: compute_power with unsigned integer type
TEST(ComputePowerTest_313, UnsignedIntegerType_313) {
    EXPECT_EQ((compute_power<0, unsigned int>(5u)), 1u);
    EXPECT_EQ((compute_power<3, unsigned int>(2u)), 8u);
    EXPECT_EQ((compute_power<10, unsigned int>(2u)), 1024u);
}

// Test: compute_power with uint64_t for larger values
TEST(ComputePowerTest_313, Uint64Type_313) {
    EXPECT_EQ((compute_power<0, uint64_t>(10ULL)), 1ULL);
    EXPECT_EQ((compute_power<1, uint64_t>(10ULL)), 10ULL);
    EXPECT_EQ((compute_power<10, uint64_t>(10ULL)), 10000000000ULL);
    EXPECT_EQ((compute_power<20, uint64_t>(2ULL)), 1048576ULL);
}

// Test: compute_power is constexpr
TEST(ComputePowerTest_313, ConstexprEvaluation_313) {
    constexpr int val0 = compute_power<0, int>(7);
    constexpr int val1 = compute_power<1, int>(7);
    constexpr int val3 = compute_power<3, int>(2);
    constexpr int val10 = compute_power<10, int>(2);

    EXPECT_EQ(val0, 1);
    EXPECT_EQ(val1, 7);
    EXPECT_EQ(val3, 8);
    EXPECT_EQ(val10, 1024);
}

// Test: compute_power with int64_t type
TEST(ComputePowerTest_313, Int64Type_313) {
    EXPECT_EQ((compute_power<15, int64_t>(2LL)), 32768LL);
    EXPECT_EQ((compute_power<3, int64_t>(-10LL)), -1000LL);
    EXPECT_EQ((compute_power<4, int64_t>(-10LL)), 10000LL);
}

// Test: specific known powers of 10
TEST(ComputePowerTest_313, PowersOfTen_313) {
    EXPECT_EQ((compute_power<0, int64_t>(10LL)), 1LL);
    EXPECT_EQ((compute_power<1, int64_t>(10LL)), 10LL);
    EXPECT_EQ((compute_power<2, int64_t>(10LL)), 100LL);
    EXPECT_EQ((compute_power<3, int64_t>(10LL)), 1000LL);
    EXPECT_EQ((compute_power<6, int64_t>(10LL)), 1000000LL);
    EXPECT_EQ((compute_power<9, int64_t>(10LL)), 1000000000LL);
}

// Test: compute_power with base -1
TEST(ComputePowerTest_313, BaseNegativeOne_313) {
    EXPECT_EQ((compute_power<0, int>(-1)), 1);
    EXPECT_EQ((compute_power<1, int>(-1)), -1);
    EXPECT_EQ((compute_power<2, int>(-1)), 1);
    EXPECT_EQ((compute_power<3, int>(-1)), -1);
    EXPECT_EQ((compute_power<4, int>(-1)), 1);
    EXPECT_EQ((compute_power<15, int>(-1)), -1);
    EXPECT_EQ((compute_power<16, int>(-1)), 1);
}
