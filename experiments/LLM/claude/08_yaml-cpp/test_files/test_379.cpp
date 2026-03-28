#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// Mock SignedSignificandBits that can be configured as negative or positive
struct MockSignedSignificandBits {
    bool negative;
    constexpr bool is_negative() const noexcept { return negative; }
};

// Tag types to identify which policy was called
struct CalledWithNearestTowardZero {};
struct CalledWithNearestAwayFromZero {};

// A functor that returns different types/values depending on which tag it receives
struct IdentifyPolicyFunc {
    constexpr int operator()(nearest_toward_zero_t) const noexcept {
        return 0; // toward zero
    }
    constexpr int operator()(nearest_away_from_zero_t) const noexcept {
        return 1; // away from zero
    }
};

// A functor that also accepts additional args
struct IdentifyPolicyFuncWithArgs {
    constexpr int operator()(nearest_toward_zero_t, int a, int b) const noexcept {
        return a + b; // toward zero: return sum
    }
    constexpr int operator()(nearest_away_from_zero_t, int a, int b) const noexcept {
        return a * b; // away from zero: return product
    }
};

// Test fixture
class NearestTowardPlusInfinityStaticBoundaryTest_379 : public ::testing::Test {
protected:
    using PolicyT = nearest_toward_plus_infinity_static_boundary_t;
};

// Test: When significand is negative, delegate should call f with nearest_toward_zero
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, NegativeSignificandDelegatesToNearestTowardZero_379) {
    MockSignedSignificandBits s{true}; // negative
    IdentifyPolicyFunc f{};
    auto result = PolicyT::delegate(s, f);
    EXPECT_EQ(result, 0); // 0 means nearest_toward_zero was used
}

// Test: When significand is positive (not negative), delegate should call f with nearest_away_from_zero
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, PositiveSignificandDelegatesToNearestAwayFromZero_379) {
    MockSignedSignificandBits s{false}; // positive
    IdentifyPolicyFunc f{};
    auto result = PolicyT::delegate(s, f);
    EXPECT_EQ(result, 1); // 1 means nearest_away_from_zero was used
}

// Test: Negative significand with additional arguments
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, NegativeSignificandWithAdditionalArgs_379) {
    MockSignedSignificandBits s{true}; // negative
    IdentifyPolicyFuncWithArgs f{};
    auto result = PolicyT::delegate(s, f, 3, 5);
    // toward_zero branch returns a + b = 3 + 5 = 8
    EXPECT_EQ(result, 8);
}

// Test: Positive significand with additional arguments
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, PositiveSignificandWithAdditionalArgs_379) {
    MockSignedSignificandBits s{false}; // positive
    IdentifyPolicyFuncWithArgs f{};
    auto result = PolicyT::delegate(s, f, 3, 5);
    // away_from_zero branch returns a * b = 3 * 5 = 15
    EXPECT_EQ(result, 15);
}

// Test: Boundary - zero significand (is_negative() returns false) should delegate to away_from_zero
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, ZeroSignificandNotNegativeDelegatesToAwayFromZero_379) {
    MockSignedSignificandBits s{false}; // zero is not negative
    IdentifyPolicyFunc f{};
    auto result = PolicyT::delegate(s, f);
    EXPECT_EQ(result, 1); // away from zero
}

// Test: Verify constexpr behavior with negative
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, ConstexprNegative_379) {
    constexpr MockSignedSignificandBits s{true};
    constexpr IdentifyPolicyFunc f{};
    constexpr auto result = PolicyT::delegate(s, f);
    static_assert(result == 0, "Negative should delegate to nearest_toward_zero");
    EXPECT_EQ(result, 0);
}

// Test: Verify constexpr behavior with positive
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, ConstexprPositive_379) {
    constexpr MockSignedSignificandBits s{false};
    constexpr IdentifyPolicyFunc f{};
    constexpr auto result = PolicyT::delegate(s, f);
    static_assert(result == 1, "Positive should delegate to nearest_away_from_zero");
    EXPECT_EQ(result, 1);
}

// Test: Multiple additional arguments with negative
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, NegativeWithBoundaryArgs_379) {
    MockSignedSignificandBits s{true};
    IdentifyPolicyFuncWithArgs f{};
    // Test with zero arguments
    auto result = PolicyT::delegate(s, f, 0, 0);
    EXPECT_EQ(result, 0); // 0 + 0 = 0
}

// Test: Multiple additional arguments with positive
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, PositiveWithBoundaryArgs_379) {
    MockSignedSignificandBits s{false};
    IdentifyPolicyFuncWithArgs f{};
    // Test with zero arguments
    auto result = PolicyT::delegate(s, f, 0, 0);
    EXPECT_EQ(result, 0); // 0 * 0 = 0
}

// Test: Large values with negative significand
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, NegativeWithLargeArgs_379) {
    MockSignedSignificandBits s{true};
    IdentifyPolicyFuncWithArgs f{};
    auto result = PolicyT::delegate(s, f, 1000000, 2000000);
    EXPECT_EQ(result, 3000000); // sum for toward_zero
}

// Test: Large values with positive significand
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, PositiveWithLargeArgs_379) {
    MockSignedSignificandBits s{false};
    IdentifyPolicyFuncWithArgs f{};
    auto result = PolicyT::delegate(s, f, 100, 200);
    EXPECT_EQ(result, 20000); // product for away_from_zero
}

// Test: noexcept specification
TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, DelegateIsNoexcept_379) {
    MockSignedSignificandBits s{true};
    IdentifyPolicyFunc f{};
    EXPECT_TRUE(noexcept(PolicyT::delegate(s, f)));
}
