#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::uint128;

// ==================== uint128 Tests ====================

TEST(Uint128Test_403, DefaultConstruction_403) {
    uint128 val;
    // Default constructed - just verify it compiles and doesn't crash
    (void)val;
}

TEST(Uint128Test_403, ParameterizedConstruction_403) {
    constexpr uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    EXPECT_EQ(val.high(), 0x1234567890ABCDEFull);
    EXPECT_EQ(val.low(), 0xFEDCBA0987654321ull);
}

TEST(Uint128Test_403, HighAccessor_403) {
    constexpr uint128 val(42, 100);
    EXPECT_EQ(val.high(), 42u);
}

TEST(Uint128Test_403, LowAccessor_403) {
    constexpr uint128 val(42, 100);
    EXPECT_EQ(val.low(), 100u);
}

TEST(Uint128Test_403, ZeroValues_403) {
    constexpr uint128 val(0, 0);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

TEST(Uint128Test_403, MaxValues_403) {
    constexpr uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

TEST(Uint128Test_403, PlusEqualsNoCarry_403) {
    uint128 val(10, 20);
    val += 5;
    EXPECT_EQ(val.low(), 25u);
    EXPECT_EQ(val.high(), 10u);
}

TEST(Uint128Test_403, PlusEqualsZero_403) {
    uint128 val(10, 20);
    val += 0;
    EXPECT_EQ(val.low(), 20u);
    EXPECT_EQ(val.high(), 10u);
}

TEST(Uint128Test_403, PlusEqualsWithCarry_403) {
    uint128 val(10, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 11u);
}

TEST(Uint128Test_403, PlusEqualsWithCarryLargeAddend_403) {
    uint128 val(5, UINT64_MAX - 9);
    val += 10;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 6u);
}

TEST(Uint128Test_403, PlusEqualsWithCarryMaxHigh_403) {
    uint128 val(UINT64_MAX, UINT64_MAX);
    val += 1;
    // Overflow in high part wraps around
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 0u);
}

TEST(Uint128Test_403, PlusEqualsLargeNumber_403) {
    uint128 val(0, UINT64_MAX - 99);
    val += 100;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 1u);
}

TEST(Uint128Test_403, PlusEqualsChaining_403) {
    uint128 val(0, 0);
    val += 10;
    val += 20;
    EXPECT_EQ(val.low(), 30u);
    EXPECT_EQ(val.high(), 0u);
}

TEST(Uint128Test_403, ConstexprAccessors_403) {
    constexpr uint128 val(123456789ull, 987654321ull);
    static_assert(val.high() == 123456789ull, "high() should be constexpr");
    static_assert(val.low() == 987654321ull, "low() should be constexpr");
    EXPECT_EQ(val.high(), 123456789ull);
    EXPECT_EQ(val.low(), 987654321ull);
}

}  // namespace
