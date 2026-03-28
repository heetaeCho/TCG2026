#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// Mock SignedSignificandBits that can be configured to return positive or negative
struct MockSignedSignificandBits {
    bool negative;
    constexpr bool is_negative() const noexcept { return negative; }
};

// Tag types to distinguish which policy was called with
struct NearestTowardZeroTag {};
struct NearestAwayFromZeroTag {};

// A callable that records which rounding policy it was invoked with
struct RecordingFunc {
    constexpr int operator()(nearest_toward_zero_t) const noexcept {
        return 0; // 0 means toward_zero
    }
    constexpr int operator()(nearest_away_from_zero_t) const noexcept {
        return 1; // 1 means away_from_zero
    }
};

// A callable that also takes additional args
struct RecordingFuncWithArgs {
    constexpr int operator()(nearest_toward_zero_t, int a, int b) const noexcept {
        return a + b; // toward_zero: return sum
    }
    constexpr int operator()(nearest_away_from_zero_t, int a, int b) const noexcept {
        return a * b; // away_from_zero: return product
    }
};

// Test fixture
class NearestTowardMinusInfinityStaticBoundaryTest_380 : public ::testing::Test {
protected:
    using Policy = nearest_toward_minus_infinity_static_boundary_t;
};

// When the sign is negative, delegate should call f with nearest_away_from_zero
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, NegativeSignDelegatesToAwayFromZero_380) {
    MockSignedSignificandBits s{true}; // negative
    auto result = Policy::delegate(s, RecordingFunc{});
    EXPECT_EQ(result, 1); // 1 means away_from_zero was called
}

// When the sign is positive (not negative), delegate should call f with nearest_toward_zero
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, PositiveSignDelegatesToTowardZero_380) {
    MockSignedSignificandBits s{false}; // positive
    auto result = Policy::delegate(s, RecordingFunc{});
    EXPECT_EQ(result, 0); // 0 means toward_zero was called
}

// Test with additional arguments when negative
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, NegativeSignWithAdditionalArgs_380) {
    MockSignedSignificandBits s{true}; // negative
    // away_from_zero path: returns a * b = 3 * 5 = 15
    auto result = Policy::delegate(s, RecordingFuncWithArgs{}, 3, 5);
    EXPECT_EQ(result, 15);
}

// Test with additional arguments when positive
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, PositiveSignWithAdditionalArgs_380) {
    MockSignedSignificandBits s{false}; // positive
    // toward_zero path: returns a + b = 3 + 5 = 8
    auto result = Policy::delegate(s, RecordingFuncWithArgs{}, 3, 5);
    EXPECT_EQ(result, 8);
}

// Test constexpr evaluation for negative sign
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ConstexprNegativeSign_380) {
    constexpr MockSignedSignificandBits s{true};
    constexpr auto result = Policy::delegate(s, RecordingFunc{});
    EXPECT_EQ(result, 1);
}

// Test constexpr evaluation for positive sign
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ConstexprPositiveSign_380) {
    constexpr MockSignedSignificandBits s{false};
    constexpr auto result = Policy::delegate(s, RecordingFunc{});
    EXPECT_EQ(result, 0);
}

// Boundary: zero is not negative, should delegate to toward_zero
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ZeroIsNotNegative_380) {
    // Zero represented as non-negative
    MockSignedSignificandBits s{false};
    auto result = Policy::delegate(s, RecordingFunc{});
    EXPECT_EQ(result, 0); // toward_zero
}

// Test with args that are zero
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ArgsWithZeroValues_380) {
    MockSignedSignificandBits s_neg{true};
    // away_from_zero: 0 * 0 = 0
    auto result_neg = Policy::delegate(s_neg, RecordingFuncWithArgs{}, 0, 0);
    EXPECT_EQ(result_neg, 0);

    MockSignedSignificandBits s_pos{false};
    // toward_zero: 0 + 0 = 0
    auto result_pos = Policy::delegate(s_pos, RecordingFuncWithArgs{}, 0, 0);
    EXPECT_EQ(result_pos, 0);
}

// Test that return type matches expectation
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ReturnTypeIsCorrect_380) {
    MockSignedSignificandBits s{false};
    auto result = Policy::delegate(s, RecordingFunc{});
    static_assert(std::is_same<decltype(result), int>::value, "Return type should be int");
    EXPECT_TRUE((std::is_same<decltype(result), int>::value));
}

// Test with negative numbers in args
TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, NegativeArgsPositiveSign_380) {
    MockSignedSignificandBits s{false};
    // toward_zero: (-3) + (-5) = -8
    auto result = Policy::delegate(s, RecordingFuncWithArgs{}, -3, -5);
    EXPECT_EQ(result, -8);
}

TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, NegativeArgsNegativeSign_380) {
    MockSignedSignificandBits s{true};
    // away_from_zero: (-3) * (-5) = 15
    auto result = Policy::delegate(s, RecordingFuncWithArgs{}, -3, -5);
    EXPECT_EQ(result, 15);
}
