#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::binary_to_decimal_rounding;

// Test fixture
class DoNotCareTTest_385 : public ::testing::Test {
protected:
    do_not_care_t policy;
};

// Test that prefer_round_down returns false for uint32_t with value 0
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint32Zero_385) {
    uint32_t carrier = 0;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint32_t with value 1
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint32One_385) {
    uint32_t carrier = 1;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint32_t max value
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint32Max_385) {
    uint32_t carrier = std::numeric_limits<uint32_t>::max();
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint64_t with value 0
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint64Zero_385) {
    uint64_t carrier = 0;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint64_t with value 1
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint64One_385) {
    uint64_t carrier = 1;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint64_t max value
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint64Max_385) {
    uint64_t carrier = std::numeric_limits<uint64_t>::max();
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint16_t
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint16_385) {
    uint16_t carrier = 12345;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down returns false for uint8_t
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForUint8_385) {
    uint8_t carrier = 255;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that prefer_round_down is a constexpr function
TEST_F(DoNotCareTTest_385, PreferRoundDownIsConstexpr_385) {
    constexpr bool result = do_not_care_t::prefer_round_down(uint32_t(42));
    EXPECT_FALSE(result);
}

// Test that prefer_round_down is noexcept
TEST_F(DoNotCareTTest_385, PreferRoundDownIsNoexcept_385) {
    EXPECT_TRUE(noexcept(policy.prefer_round_down(uint32_t(0))));
    EXPECT_TRUE(noexcept(policy.prefer_round_down(uint64_t(0))));
}

// Test that prefer_round_down can be called statically
TEST_F(DoNotCareTTest_385, PreferRoundDownCanBeCalledStatically_385) {
    EXPECT_FALSE(do_not_care_t::prefer_round_down(uint32_t(100)));
    EXPECT_FALSE(do_not_care_t::prefer_round_down(uint64_t(100)));
}

// Test with a large uint64_t value (boundary-like)
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForLargeUint64_385) {
    uint64_t carrier = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_FALSE(policy.prefer_round_down(carrier));
}

// Test that do_not_care_t is default constructible
TEST_F(DoNotCareTTest_385, IsDefaultConstructible_385) {
    EXPECT_TRUE(std::is_default_constructible<do_not_care_t>::value);
}

// Test with mid-range values
TEST_F(DoNotCareTTest_385, PreferRoundDownReturnsFalseForMidRangeValues_385) {
    uint32_t mid32 = std::numeric_limits<uint32_t>::max() / 2;
    uint64_t mid64 = std::numeric_limits<uint64_t>::max() / 2;
    EXPECT_FALSE(policy.prefer_round_down(mid32));
    EXPECT_FALSE(policy.prefer_round_down(mid64));
}

// Test constexpr with uint64_t
TEST_F(DoNotCareTTest_385, PreferRoundDownIsConstexprUint64_385) {
    constexpr bool result = do_not_care_t::prefer_round_down(uint64_t(999999999999ULL));
    EXPECT_FALSE(result);
}

} // namespace
