#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

// Test default construction
TEST(Uint128Test_304, DefaultConstruction_304) {
    uint128 val;
    // Default constructed - we just verify it compiles and is usable
    (void)val;
}

// Test parameterized construction and accessors
TEST(Uint128Test_304, ParameterizedConstruction_304) {
    uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    EXPECT_EQ(val.high(), 0x1234567890ABCDEFull);
    EXPECT_EQ(val.low(), 0xFEDCBA0987654321ull);
}

// Test low() returns correct value
TEST(Uint128Test_304, LowReturnsCorrectValue_304) {
    uint128 val(0, 42);
    EXPECT_EQ(val.low(), 42u);
}

// Test high() returns correct value
TEST(Uint128Test_304, HighReturnsCorrectValue_304) {
    uint128 val(42, 0);
    EXPECT_EQ(val.high(), 42u);
}

// Test with zero values
TEST(Uint128Test_304, ZeroValues_304) {
    uint128 val(0, 0);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

// Test with max values
TEST(Uint128Test_304, MaxValues_304) {
    uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

// Test operator+= with simple addition (no carry)
TEST(Uint128Test_304, PlusEqualsSimple_304) {
    uint128 val(0, 10);
    val += 5;
    EXPECT_EQ(val.low(), 15u);
    EXPECT_EQ(val.high(), 0u);
}

// Test operator+= with zero
TEST(Uint128Test_304, PlusEqualsZero_304) {
    uint128 val(100, 200);
    val += 0;
    EXPECT_EQ(val.low(), 200u);
    EXPECT_EQ(val.high(), 100u);
}

// Test operator+= causing carry from low to high
TEST(Uint128Test_304, PlusEqualsWithCarry_304) {
    uint128 val(0, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 1u);
}

// Test operator+= causing carry with existing high value
TEST(Uint128Test_304, PlusEqualsWithCarryExistingHigh_304) {
    uint128 val(5, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 6u);
}

// Test operator+= with large value causing carry
TEST(Uint128Test_304, PlusEqualsLargeValueWithCarry_304) {
    uint128 val(0, UINT64_MAX - 9);
    val += 20;
    EXPECT_EQ(val.low(), 10u);
    EXPECT_EQ(val.high(), 1u);
}

// Test operator+= chaining
TEST(Uint128Test_304, PlusEqualsChaining_304) {
    uint128 val(0, 0);
    val += 10;
    val += 20;
    val += 30;
    EXPECT_EQ(val.low(), 60u);
    EXPECT_EQ(val.high(), 0u);
}

// Test operator+= returns reference (chaining possible)
TEST(Uint128Test_304, PlusEqualsReturnsReference_304) {
    uint128 val(0, 0);
    uint128& ref = (val += 5);
    EXPECT_EQ(&ref, &val);
    EXPECT_EQ(val.low(), 5u);
}

// Test constexpr construction
TEST(Uint128Test_304, ConstexprConstruction_304) {
    constexpr uint128 val(1, 2);
    static_assert(val.high() == 1, "high should be 1");
    static_assert(val.low() == 2, "low should be 2");
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 2u);
}

// Test with power of two boundaries
TEST(Uint128Test_304, PowerOfTwoBoundaries_304) {
    uint128 val(1ull << 63, 1ull << 63);
    EXPECT_EQ(val.high(), 1ull << 63);
    EXPECT_EQ(val.low(), 1ull << 63);
}

// Test operator+= with max uint64 addition near boundary
TEST(Uint128Test_304, PlusEqualsMaxUint64_304) {
    uint128 val(0, 0);
    val += UINT64_MAX;
    EXPECT_EQ(val.low(), UINT64_MAX);
    EXPECT_EQ(val.high(), 0u);
}

// Test multiple carries
TEST(Uint128Test_304, PlusEqualsMultipleCarries_304) {
    uint128 val(0, UINT64_MAX);
    val += 1;  // First carry
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 1u);

    val = uint128(1u, UINT64_MAX);
    val += 1;  // Second scenario
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 2u);
}
