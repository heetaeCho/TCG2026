#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// A dummy type to use as SignedSignificandBits
struct DummySignedSignificandBits {};

// A functor that accepts left_closed_directed_t and returns an int
struct IntReturningFunc {
    constexpr int operator()(detail::left_closed_directed_t) const noexcept {
        return 42;
    }
};

// A functor that accepts left_closed_directed_t and one int arg
struct IntArgFunc {
    constexpr int operator()(detail::left_closed_directed_t, int x) const noexcept {
        return x * 2;
    }
};

// A functor that accepts left_closed_directed_t and two int args
struct TwoIntArgFunc {
    constexpr int operator()(detail::left_closed_directed_t, int x, int y) const noexcept {
        return x + y;
    }
};

// A functor that returns a bool
struct BoolReturningFunc {
    constexpr bool operator()(detail::left_closed_directed_t) const noexcept {
        return true;
    }
};

// A functor that accepts left_closed_directed_t and a double arg
struct DoubleArgFunc {
    constexpr double operator()(detail::left_closed_directed_t, double d) const noexcept {
        return d + 1.0;
    }
};

// A functor returning zero to test boundary
struct ZeroReturningFunc {
    constexpr int operator()(detail::left_closed_directed_t, int x) const noexcept {
        return 0;
    }
};

using TowardZero = policy::decimal_to_binary_rounding::toward_zero;

class TowardZeroTest_383 : public ::testing::Test {};

TEST_F(TowardZeroTest_383, DelegateNoArgs_ReturnsExpectedValue_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

TEST_F(TowardZeroTest_383, DelegateOneIntArg_ReturnsDoubledValue_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, IntArgFunc{}, 5);
    EXPECT_EQ(result, 10);
}

TEST_F(TowardZeroTest_383, DelegateTwoIntArgs_ReturnsSumOfArgs_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, TwoIntArgFunc{}, 3, 7);
    EXPECT_EQ(result, 10);
}

TEST_F(TowardZeroTest_383, DelegateBoolReturn_ReturnsTrue_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, BoolReturningFunc{});
    EXPECT_TRUE(result);
}

TEST_F(TowardZeroTest_383, DelegateDoubleArg_ReturnsIncrementedValue_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, DoubleArgFunc{}, 2.5);
    EXPECT_DOUBLE_EQ(result, 3.5);
}

TEST_F(TowardZeroTest_383, DelegateWithZeroArg_ReturnsZero_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, IntArgFunc{}, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(TowardZeroTest_383, DelegateWithNegativeArg_ReturnsNegativeDoubled_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, IntArgFunc{}, -3);
    EXPECT_EQ(result, -6);
}

TEST_F(TowardZeroTest_383, DelegateWithLargeValues_ReturnsCorrectSum_383) {
    auto result = TowardZero::delegate(DummySignedSignificandBits{}, TwoIntArgFunc{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

TEST_F(TowardZeroTest_383, DelegateIsConstexpr_383) {
    constexpr auto result = TowardZero::delegate(DummySignedSignificandBits{}, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

TEST_F(TowardZeroTest_383, DelegateIsNoexcept_383) {
    EXPECT_TRUE(noexcept(TowardZero::delegate(DummySignedSignificandBits{}, IntReturningFunc{})));
}

TEST_F(TowardZeroTest_383, DelegateIgnoresSignedSignificandBits_383) {
    // The first parameter should be ignored; different instances yield same result
    auto result1 = TowardZero::delegate(DummySignedSignificandBits{}, IntArgFunc{}, 7);
    auto result2 = TowardZero::delegate(DummySignedSignificandBits{}, IntArgFunc{}, 7);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 14);
}

} // namespace
