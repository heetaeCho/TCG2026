#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// A dummy Info template to satisfy the template template parameter requirement
template <std::size_t N>
struct DummyInfo {};

using namespace YAML::jkj::dragonbox::detail::log;

class IsInRangeTest_317 : public ::testing::Test {
protected:
};

// Test that the fallback overload returns false when min_exponent > max_exponent
TEST_F(IsInRangeTest_317, ReturnsFalseForReversedRange_317) {
    // min_exponent=10 > max_exponent=5, so static_assert passes
    constexpr bool result = is_in_range<DummyInfo, 10, 5, 0>();
    EXPECT_FALSE(result);
}

// Test with different valid reversed ranges
TEST_F(IsInRangeTest_317, ReturnsFalseForLargeReversedRange_317) {
    constexpr bool result = is_in_range<DummyInfo, 1000, -1000, 0>();
    EXPECT_FALSE(result);
}

// Test with min_exponent just above max_exponent (boundary: difference of 1)
TEST_F(IsInRangeTest_317, ReturnsFalseForMinimalReversedRange_317) {
    constexpr bool result = is_in_range<DummyInfo, 1, 0, 0>();
    EXPECT_FALSE(result);
}

// Test with negative exponents where min > max
TEST_F(IsInRangeTest_317, ReturnsFalseForNegativeReversedRange_317) {
    constexpr bool result = is_in_range<DummyInfo, -5, -10, 0>();
    EXPECT_FALSE(result);
}

// Test with different current_tier values
TEST_F(IsInRangeTest_317, ReturnsFalseForDifferentTiers_317) {
    constexpr bool result0 = is_in_range<DummyInfo, 100, 50, 0>();
    constexpr bool result1 = is_in_range<DummyInfo, 100, 50, 1>();
    constexpr bool result2 = is_in_range<DummyInfo, 100, 50, 2>();
    constexpr bool result5 = is_in_range<DummyInfo, 100, 50, 5>();
    EXPECT_FALSE(result0);
    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
    EXPECT_FALSE(result5);
}

// Test with arguments passed (variadic)
TEST_F(IsInRangeTest_317, ReturnsFalseWithArguments_317) {
    constexpr bool result = is_in_range<DummyInfo, 50, 10, 0>(1, 2, 3);
    EXPECT_FALSE(result);
}

// Test constexpr evaluation at compile time
TEST_F(IsInRangeTest_317, IsConstexprEvaluable_317) {
    static_assert(is_in_range<DummyInfo, 10, 5, 0>() == false,
                  "is_in_range fallback should return false at compile time");
    SUCCEED();
}

// Test with large tier value
TEST_F(IsInRangeTest_317, ReturnsFalseForLargeTier_317) {
    constexpr bool result = is_in_range<DummyInfo, 500, 100, 100>();
    EXPECT_FALSE(result);
}

// Test noexcept property
TEST_F(IsInRangeTest_317, IsNoexcept_317) {
    EXPECT_TRUE(noexcept(is_in_range<DummyInfo, 10, 5, 0>()));
}

} // namespace
