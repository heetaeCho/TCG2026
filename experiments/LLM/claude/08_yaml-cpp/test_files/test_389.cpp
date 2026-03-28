#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using TowardZero = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::toward_zero;

// Test with uint32_t carrier type
TEST(TowardZeroTest_389, PreferRoundDownUint32Zero_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint32_t>(0));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint32One_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint32_t>(1));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint32Max_389) {
    constexpr bool result = TowardZero::prefer_round_down(std::numeric_limits<uint32_t>::max());
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint32Mid_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint32_t>(123456789));
    EXPECT_TRUE(result);
}

// Test with uint64_t carrier type
TEST(TowardZeroTest_389, PreferRoundDownUint64Zero_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint64_t>(0));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint64One_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint64_t>(1));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint64Max_389) {
    constexpr bool result = TowardZero::prefer_round_down(std::numeric_limits<uint64_t>::max());
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint64Large_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint64_t>(0xDEADBEEFCAFEBABE));
    EXPECT_TRUE(result);
}

// Test with uint16_t carrier type
TEST(TowardZeroTest_389, PreferRoundDownUint16Zero_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint16_t>(0));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint16Max_389) {
    constexpr bool result = TowardZero::prefer_round_down(std::numeric_limits<uint16_t>::max());
    EXPECT_TRUE(result);
}

// Test with uint8_t carrier type
TEST(TowardZeroTest_389, PreferRoundDownUint8Zero_389) {
    constexpr bool result = TowardZero::prefer_round_down(static_cast<uint8_t>(0));
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, PreferRoundDownUint8Max_389) {
    constexpr bool result = TowardZero::prefer_round_down(std::numeric_limits<uint8_t>::max());
    EXPECT_TRUE(result);
}

// Test constexpr evaluation
TEST(TowardZeroTest_389, IsConstexpr_389) {
    // Verify the function is usable in constexpr context
    static_assert(TowardZero::prefer_round_down(static_cast<uint32_t>(42)), 
                  "prefer_round_down should return true at compile time");
    static_assert(TowardZero::prefer_round_down(static_cast<uint64_t>(0)),
                  "prefer_round_down should return true at compile time for zero");
    SUCCEED();
}

// Test noexcept guarantee
TEST(TowardZeroTest_389, IsNoexcept_389) {
    EXPECT_TRUE(noexcept(TowardZero::prefer_round_down(static_cast<uint32_t>(0))));
    EXPECT_TRUE(noexcept(TowardZero::prefer_round_down(static_cast<uint64_t>(0))));
    EXPECT_TRUE(noexcept(TowardZero::prefer_round_down(static_cast<uint16_t>(0))));
    EXPECT_TRUE(noexcept(TowardZero::prefer_round_down(static_cast<uint8_t>(0))));
}

// Test that the return value is always true regardless of input
TEST(TowardZeroTest_389, AlwaysReturnsTrueForVariousValues_389) {
    for (uint32_t val : {0u, 1u, 2u, 100u, 1000u, 0xFFFFFFFFu}) {
        EXPECT_TRUE(TowardZero::prefer_round_down(val)) 
            << "Failed for value: " << val;
    }
}

// Test runtime invocation
TEST(TowardZeroTest_389, RuntimeInvocationUint32_389) {
    uint32_t runtime_val = 42;
    bool result = TowardZero::prefer_round_down(runtime_val);
    EXPECT_TRUE(result);
}

TEST(TowardZeroTest_389, RuntimeInvocationUint64_389) {
    uint64_t runtime_val = 9999999999ULL;
    bool result = TowardZero::prefer_round_down(runtime_val);
    EXPECT_TRUE(result);
}

// Test that toward_zero is default constructible
TEST(TowardZeroTest_389, DefaultConstructible_389) {
    TowardZero tz;
    (void)tz;
    SUCCEED();
}

}  // namespace
