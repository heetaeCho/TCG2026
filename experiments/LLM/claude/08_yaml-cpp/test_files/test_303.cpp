#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

// Test default construction
TEST(Uint128Test_303, DefaultConstruction_303) {
    uint128 val;
    // Default constructed - we just verify it compiles and is usable
    (void)val;
}

// Test parameterized construction and high() accessor
TEST(Uint128Test_303, ConstructWithHighAndLow_High_303) {
    constexpr uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    constexpr auto h = val.high();
    EXPECT_EQ(h, 0x1234567890ABCDEFull);
}

// Test parameterized construction and low() accessor
TEST(Uint128Test_303, ConstructWithHighAndLow_Low_303) {
    constexpr uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    constexpr auto l = val.low();
    EXPECT_EQ(l, 0xFEDCBA0987654321ull);
}

// Test with zero values
TEST(Uint128Test_303, ZeroValues_303) {
    constexpr uint128 val(0, 0);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

// Test with max values
TEST(Uint128Test_303, MaxValues_303) {
    constexpr uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

// Test high is zero, low is non-zero
TEST(Uint128Test_303, HighZeroLowNonZero_303) {
    constexpr uint128 val(0, 42);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 42u);
}

// Test high is non-zero, low is zero
TEST(Uint128Test_303, HighNonZeroLowZero_303) {
    constexpr uint128 val(42, 0);
    EXPECT_EQ(val.high(), 42u);
    EXPECT_EQ(val.low(), 0u);
}

// Test operator+= with no carry
TEST(Uint128Test_303, PlusEqualsNoCarry_303) {
    uint128 val(10, 20);
    val += 5;
    EXPECT_EQ(val.low(), 25u);
    EXPECT_EQ(val.high(), 10u);
}

// Test operator+= with zero
TEST(Uint128Test_303, PlusEqualsZero_303) {
    uint128 val(10, 20);
    val += 0;
    EXPECT_EQ(val.low(), 20u);
    EXPECT_EQ(val.high(), 10u);
}

// Test operator+= with carry (overflow of low part)
TEST(Uint128Test_303, PlusEqualsWithCarry_303) {
    uint128 val(10, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 11u);
}

// Test operator+= with carry and larger addition
TEST(Uint128Test_303, PlusEqualsWithCarryLarger_303) {
    uint128 val(10, UINT64_MAX - 9);
    val += 10;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 11u);
}

// Test operator+= with carry and large n
TEST(Uint128Test_303, PlusEqualsWithCarryLargeN_303) {
    uint128 val(5, UINT64_MAX - 99);
    val += 200;
    EXPECT_EQ(val.low(), 100u);
    EXPECT_EQ(val.high(), 6u);
}

// Test operator+= chaining
TEST(Uint128Test_303, PlusEqualsChaining_303) {
    uint128 val(0, 0);
    val += 10;
    val += 20;
    val += 30;
    EXPECT_EQ(val.low(), 60u);
    EXPECT_EQ(val.high(), 0u);
}

// Test constexpr high() and low()
TEST(Uint128Test_303, ConstexprAccessors_303) {
    constexpr uint128 val(100, 200);
    static_assert(val.high() == 100, "high() should be 100");
    static_assert(val.low() == 200, "low() should be 200");
    EXPECT_EQ(val.high(), 100u);
    EXPECT_EQ(val.low(), 200u);
}

// Test with power of two values
TEST(Uint128Test_303, PowerOfTwoValues_303) {
    constexpr uint128 val(1ull << 63, 1ull << 63);
    EXPECT_EQ(val.high(), 1ull << 63);
    EXPECT_EQ(val.low(), 1ull << 63);
}

// Test operator+= max value added to near-max low
TEST(Uint128Test_303, PlusEqualsMaxAddition_303) {
    uint128 val(0, 1);
    val += UINT64_MAX;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 1u);
}

// Test operator+= returns reference to self
TEST(Uint128Test_303, PlusEqualsReturnsReference_303) {
    uint128 val(0, 0);
    uint128& ref = (val += 5);
    EXPECT_EQ(&ref, &val);
    EXPECT_EQ(val.low(), 5u);
}
