#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// We need to work with the types referenced in the code.
// Since we're treating the implementation as a black box, we'll create
// minimal types that satisfy the template requirements.

namespace {

// A minimal SignedSignificandBits type for testing
struct MockSignedSignificandBits {};

// A tag type that matches what detail::right_closed_directed_t should be
// We need to reference the actual type from the namespace
using RightClosedDirectedTag = YAML::jkj::dragonbox::detail::right_closed_directed_t;

// A functor that records whether it was called and with what tag
struct TestFunc {
    // Overload that accepts right_closed_directed_t
    constexpr int operator()(RightClosedDirectedTag) const noexcept {
        return 42;
    }
};

// A functor that accepts right_closed_directed_t and additional args
struct TestFuncWithArgs {
    constexpr int operator()(RightClosedDirectedTag, int a, int b) const noexcept {
        return a + b;
    }
};

// A functor that returns a different type
struct TestFuncReturnsDouble {
    constexpr double operator()(RightClosedDirectedTag) const noexcept {
        return 3.14;
    }
};

// A functor with one extra arg
struct TestFuncOneArg {
    constexpr int operator()(RightClosedDirectedTag, int x) const noexcept {
        return x * 2;
    }
};

// A functor that returns bool
struct TestFuncReturnsBool {
    constexpr bool operator()(RightClosedDirectedTag) const noexcept {
        return true;
    }
};

// A functor with three extra args
struct TestFuncThreeArgs {
    constexpr int operator()(RightClosedDirectedTag, int a, int b, int c) const noexcept {
        return a + b + c;
    }
};

using AwayFromZero = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::away_from_zero;

} // anonymous namespace

// Test fixture
class AwayFromZeroTest_384 : public ::testing::Test {
protected:
    MockSignedSignificandBits ssb;
};

// Test that delegate calls the functor with right_closed_directed_t tag and no extra args
TEST_F(AwayFromZeroTest_384, DelegateNoArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFunc{});
    EXPECT_EQ(result, 42);
}

// Test that delegate forwards additional arguments correctly
TEST_F(AwayFromZeroTest_384, DelegateWithTwoArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncWithArgs{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test that delegate works with a single extra argument
TEST_F(AwayFromZeroTest_384, DelegateWithOneArg_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncOneArg{}, 5);
    EXPECT_EQ(result, 10);
}

// Test that delegate returns the correct type (double)
TEST_F(AwayFromZeroTest_384, DelegateReturnsDouble_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncReturnsDouble{});
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test that delegate returns bool correctly
TEST_F(AwayFromZeroTest_384, DelegateReturnsBool_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncReturnsBool{});
    EXPECT_TRUE(result);
}

// Test with three extra arguments
TEST_F(AwayFromZeroTest_384, DelegateWithThreeArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncThreeArgs{}, 1, 2, 3);
    EXPECT_EQ(result, 6);
}

// Test that the SignedSignificandBits parameter is ignored (any value works)
TEST_F(AwayFromZeroTest_384, DelegateIgnoresSignedSignificandBits_384) {
    MockSignedSignificandBits ssb1;
    MockSignedSignificandBits ssb2;
    auto result1 = AwayFromZero::delegate(ssb1, TestFunc{});
    auto result2 = AwayFromZero::delegate(ssb2, TestFunc{});
    EXPECT_EQ(result1, result2);
}

// Test boundary: zero arguments forwarded
TEST_F(AwayFromZeroTest_384, DelegateWithZeroExtraArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFunc{});
    EXPECT_EQ(result, 42);
}

// Test that delegate with negative arguments works correctly
TEST_F(AwayFromZeroTest_384, DelegateWithNegativeArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncWithArgs{}, -5, -10);
    EXPECT_EQ(result, -15);
}

// Test with zero values as arguments
TEST_F(AwayFromZeroTest_384, DelegateWithZeroValueArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncWithArgs{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test constexpr behavior (compile-time evaluation)
TEST_F(AwayFromZeroTest_384, DelegateIsConstexpr_384) {
    constexpr auto result = AwayFromZero::delegate(MockSignedSignificandBits{}, TestFunc{});
    static_assert(result == 42, "delegate should be constexpr evaluable");
    EXPECT_EQ(result, 42);
}

// Test constexpr with args
TEST_F(AwayFromZeroTest_384, DelegateIsConstexprWithArgs_384) {
    constexpr auto result = AwayFromZero::delegate(MockSignedSignificandBits{}, TestFuncWithArgs{}, 7, 8);
    static_assert(result == 15, "delegate should be constexpr evaluable with args");
    EXPECT_EQ(result, 15);
}

// Test noexcept property
TEST_F(AwayFromZeroTest_384, DelegateIsNoexcept_384) {
    bool is_noexcept = noexcept(AwayFromZero::delegate(ssb, TestFunc{}));
    EXPECT_TRUE(is_noexcept);
}

// Test with large integer arguments
TEST_F(AwayFromZeroTest_384, DelegateWithLargeArgs_384) {
    auto result = AwayFromZero::delegate(ssb, TestFuncWithArgs{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}
