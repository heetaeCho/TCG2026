#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Mock SignedSignificandBits that can be configured to be negative or not
struct MockSignedSignificandBits {
    bool negative;
    constexpr bool is_negative() const noexcept { return negative; }
};

// A tag to identify which overload was called
enum class DirectionTag {
    Unknown,
    LeftClosed,
    RightClosed
};

// Functor that distinguishes between left_closed_directed_t and right_closed_directed_t
struct TestFunc {
    constexpr DirectionTag operator()(detail::left_closed_directed_t) const noexcept {
        return DirectionTag::LeftClosed;
    }
    constexpr DirectionTag operator()(detail::right_closed_directed_t) const noexcept {
        return DirectionTag::RightClosed;
    }
};

// Functor that also accepts an extra int argument
struct TestFuncWithArg {
    constexpr int operator()(detail::left_closed_directed_t, int val) const noexcept {
        return val + 100;
    }
    constexpr int operator()(detail::right_closed_directed_t, int val) const noexcept {
        return val + 200;
    }
};

// Functor that accepts two extra arguments
struct TestFuncWithTwoArgs {
    constexpr int operator()(detail::left_closed_directed_t, int a, int b) const noexcept {
        return a + b + 1000;
    }
    constexpr int operator()(detail::right_closed_directed_t, int a, int b) const noexcept {
        return a + b + 2000;
    }
};

using TowardPlusInfinity = policy::decimal_to_binary_rounding::toward_plus_infinity_t;

class TowardPlusInfinityTest_381 : public ::testing::Test {};

// When the significand is negative, delegate should call f with left_closed_directed_t
TEST_F(TowardPlusInfinityTest_381, NegativeCallsLeftClosed_381) {
    MockSignedSignificandBits s{true};
    auto result = TowardPlusInfinity::delegate(s, TestFunc{});
    EXPECT_EQ(result, DirectionTag::LeftClosed);
}

// When the significand is not negative, delegate should call f with right_closed_directed_t
TEST_F(TowardPlusInfinityTest_381, PositiveCallsRightClosed_381) {
    MockSignedSignificandBits s{false};
    auto result = TowardPlusInfinity::delegate(s, TestFunc{});
    EXPECT_EQ(result, DirectionTag::RightClosed);
}

// When negative with extra argument, should pass args through to left_closed overload
TEST_F(TowardPlusInfinityTest_381, NegativeWithArgPassesThrough_381) {
    MockSignedSignificandBits s{true};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithArg{}, 42);
    EXPECT_EQ(result, 42 + 100);
}

// When positive with extra argument, should pass args through to right_closed overload
TEST_F(TowardPlusInfinityTest_381, PositiveWithArgPassesThrough_381) {
    MockSignedSignificandBits s{false};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithArg{}, 42);
    EXPECT_EQ(result, 42 + 200);
}

// When negative with two extra arguments
TEST_F(TowardPlusInfinityTest_381, NegativeWithTwoArgs_381) {
    MockSignedSignificandBits s{true};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithTwoArgs{}, 10, 20);
    EXPECT_EQ(result, 10 + 20 + 1000);
}

// When positive with two extra arguments
TEST_F(TowardPlusInfinityTest_381, PositiveWithTwoArgs_381) {
    MockSignedSignificandBits s{false};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithTwoArgs{}, 10, 20);
    EXPECT_EQ(result, 10 + 20 + 2000);
}

// Boundary: zero argument value with negative sign
TEST_F(TowardPlusInfinityTest_381, NegativeWithZeroArg_381) {
    MockSignedSignificandBits s{true};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithArg{}, 0);
    EXPECT_EQ(result, 100);
}

// Boundary: zero argument value with positive sign
TEST_F(TowardPlusInfinityTest_381, PositiveWithZeroArg_381) {
    MockSignedSignificandBits s{false};
    auto result = TowardPlusInfinity::delegate(s, TestFuncWithArg{}, 0);
    EXPECT_EQ(result, 200);
}

// Verify noexcept property - the method is declared noexcept
TEST_F(TowardPlusInfinityTest_381, DelegateIsNoexcept_381) {
    MockSignedSignificandBits s{true};
    EXPECT_TRUE(noexcept(TowardPlusInfinity::delegate(s, TestFunc{})));
}

// Verify constexpr capability (if compiler supports it, this should compile)
TEST_F(TowardPlusInfinityTest_381, ConstexprNegative_381) {
    constexpr MockSignedSignificandBits s{true};
    constexpr auto result = TowardPlusInfinity::delegate(s, TestFunc{});
    EXPECT_EQ(result, DirectionTag::LeftClosed);
}

TEST_F(TowardPlusInfinityTest_381, ConstexprPositive_381) {
    constexpr MockSignedSignificandBits s{false};
    constexpr auto result = TowardPlusInfinity::delegate(s, TestFunc{});
    EXPECT_EQ(result, DirectionTag::RightClosed);
}

} // namespace
