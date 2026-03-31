#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits - just needs to be a valid type
struct MockSignedSignificandBits {};

// Test functor that takes nearest_toward_plus_infinity_t and returns an int
struct ReturnIntFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_toward_plus_infinity_t) const noexcept {
        return 42;
    }
};

// Test functor that takes nearest_toward_plus_infinity_t and additional args
struct ReturnSumFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_toward_plus_infinity_t, int a, int b) const noexcept {
        return a + b;
    }
};

// Test functor that returns a different type (double)
struct ReturnDoubleFunc {
    JKJ_FORCEINLINE constexpr double operator()(nearest_toward_plus_infinity_t) const noexcept {
        return 3.14;
    }
};

// Test functor that takes nearest_toward_plus_infinity_t and a single arg
struct ReturnArgFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_toward_plus_infinity_t, int a) const noexcept {
        return a;
    }
};

// Test functor returning bool
struct ReturnBoolFunc {
    JKJ_FORCEINLINE constexpr bool operator()(nearest_toward_plus_infinity_t) const noexcept {
        return true;
    }
};

// Test functor that takes three extra arguments
struct ThreeArgsFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_toward_plus_infinity_t, int a, int b, int c) const noexcept {
        return a * b * c;
    }
};

// =============================================================================
// Tests
// =============================================================================

class NearestTowardPlusInfinityTest_361 : public ::testing::Test {
protected:
    nearest_toward_plus_infinity_t policy_;
    MockSignedSignificandBits ssb_;
};

// Test that delegate calls the functor with no extra args and returns correct value
TEST_F(NearestTowardPlusInfinityTest_361, DelegateNoExtraArgs_ReturnsExpectedInt_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnIntFunc{});
    EXPECT_EQ(result, 42);
}

// Test that delegate forwards extra arguments correctly
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithTwoExtraArgs_ReturnsSumOfArgs_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnSumFunc{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test that delegate works with a functor returning double
TEST_F(NearestTowardPlusInfinityTest_361, DelegateReturnsDouble_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnDoubleFunc{});
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test that delegate correctly passes a single extra argument
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithSingleExtraArg_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnArgFunc{}, 99);
    EXPECT_EQ(result, 99);
}

// Test that delegate works with a bool return type
TEST_F(NearestTowardPlusInfinityTest_361, DelegateReturnsBool_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnBoolFunc{});
    EXPECT_TRUE(result);
}

// Test boundary: zero values as extra arguments
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithZeroArgs_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnSumFunc{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test with negative values
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithNegativeArgs_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnSumFunc{}, -5, -10);
    EXPECT_EQ(result, -15);
}

// Test with three extra arguments
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithThreeExtraArgs_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ThreeArgsFunc{}, 2, 3, 4);
    EXPECT_EQ(result, 24);
}

// Test that delegate is constexpr-compatible (compile time check via static_assert proxy)
TEST_F(NearestTowardPlusInfinityTest_361, DelegateIsNoexcept_361) {
    // Verify noexcept specification
    bool is_noexcept = noexcept(
        nearest_toward_plus_infinity_t::delegate(ssb_, ReturnIntFunc{})
    );
    EXPECT_TRUE(is_noexcept);
}

// Test that the type nearest_toward_plus_infinity_t is default constructible
TEST_F(NearestTowardPlusInfinityTest_361, TypeIsDefaultConstructible_361) {
    EXPECT_TRUE(std::is_default_constructible<nearest_toward_plus_infinity_t>::value);
}

// Test mixed positive and negative args
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithMixedSignArgs_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnSumFunc{}, 100, -50);
    EXPECT_EQ(result, 50);
}

// Test with large values
TEST_F(NearestTowardPlusInfinityTest_361, DelegateWithLargeValues_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ReturnSumFunc{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

// Test that delegate with ThreeArgsFunc and zeros returns zero
TEST_F(NearestTowardPlusInfinityTest_361, DelegateThreeArgsWithZero_361) {
    auto result = nearest_toward_plus_infinity_t::delegate(ssb_, ThreeArgsFunc{}, 0, 5, 10);
    EXPECT_EQ(result, 0);
}

} // namespace
