#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits - just needs to be a valid type
struct MockSignedSignificandBits {};

// Test functor that takes nearest_away_from_zero_t and returns an int
struct ReturnIntFunc {
    constexpr int operator()(nearest_away_from_zero_t) const noexcept {
        return 42;
    }
};

// Test functor that takes nearest_away_from_zero_t and additional args
struct ReturnSumFunc {
    constexpr int operator()(nearest_away_from_zero_t, int a, int b) const noexcept {
        return a + b;
    }
};

// Test functor that returns void
struct VoidFunc {
    int* target = nullptr;
    constexpr void operator()(nearest_away_from_zero_t) const noexcept {
        // Can't really do side effects in constexpr, but signature is valid
    }
};

// Test functor returning a bool
struct ReturnBoolFunc {
    constexpr bool operator()(nearest_away_from_zero_t) const noexcept {
        return true;
    }
};

// Functor that takes nearest_away_from_zero_t and a single int arg
struct SingleArgFunc {
    constexpr int operator()(nearest_away_from_zero_t, int x) const noexcept {
        return x * 2;
    }
};

// Functor that returns double
struct ReturnDoubleFunc {
    constexpr double operator()(nearest_away_from_zero_t, double x) const noexcept {
        return x + 1.0;
    }
};

// Functor with multiple different argument types
struct MultiTypeArgFunc {
    constexpr long operator()(nearest_away_from_zero_t, int a, long b, short c) const noexcept {
        return static_cast<long>(a) + b + static_cast<long>(c);
    }
};

// ============================
// Test Fixture
// ============================
class NearestAwayFromZeroTest_370 : public ::testing::Test {
protected:
    MockSignedSignificandBits ssb;
};

// Test: delegate with no extra args returns expected value
TEST_F(NearestAwayFromZeroTest_370, DelegateNoExtraArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnIntFunc{});
    EXPECT_EQ(result, 42);
}

// Test: delegate with two extra int args forwards them correctly
TEST_F(NearestAwayFromZeroTest_370, DelegateWithTwoIntArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnSumFunc{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test: delegate returns bool correctly
TEST_F(NearestAwayFromZeroTest_370, DelegateReturnsBool_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnBoolFunc{});
    EXPECT_TRUE(result);
}

// Test: delegate with single int argument
TEST_F(NearestAwayFromZeroTest_370, DelegateWithSingleArg_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, SingleArgFunc{}, 5);
    EXPECT_EQ(result, 10);
}

// Test: delegate with double argument and return type
TEST_F(NearestAwayFromZeroTest_370, DelegateWithDoubleArg_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnDoubleFunc{}, 3.14);
    EXPECT_DOUBLE_EQ(result, 4.14);
}

// Test: delegate with multiple different argument types
TEST_F(NearestAwayFromZeroTest_370, DelegateWithMultiTypeArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, MultiTypeArgFunc{}, 1, 2L, static_cast<short>(3));
    EXPECT_EQ(result, 6L);
}

// Test: delegate is noexcept
TEST_F(NearestAwayFromZeroTest_370, DelegateIsNoexcept_370) {
    bool is_noexcept = noexcept(nearest_away_from_zero_t::delegate(ssb, ReturnIntFunc{}));
    EXPECT_TRUE(is_noexcept);
}

// Test: delegate is constexpr (compile-time evaluation)
TEST_F(NearestAwayFromZeroTest_370, DelegateIsConstexpr_370) {
    constexpr auto result = nearest_away_from_zero_t::delegate(MockSignedSignificandBits{}, ReturnIntFunc{});
    EXPECT_EQ(result, 42);
}

// Test: boundary - delegate with zero values
TEST_F(NearestAwayFromZeroTest_370, DelegateWithZeroArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnSumFunc{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test: boundary - delegate with negative values
TEST_F(NearestAwayFromZeroTest_370, DelegateWithNegativeArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnSumFunc{}, -10, -20);
    EXPECT_EQ(result, -30);
}

// Test: boundary - delegate with max int values
TEST_F(NearestAwayFromZeroTest_370, DelegateWithMaxIntArgs_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, SingleArgFunc{}, 0);
    EXPECT_EQ(result, 0);
}

// Test: return type correctness
TEST_F(NearestAwayFromZeroTest_370, DelegateReturnTypeIsCorrect_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnIntFunc{});
    static_assert(std::is_same<decltype(result), int>::value, "Return type should be int");
    EXPECT_EQ(result, 42);
}

// Test: return type for double functor
TEST_F(NearestAwayFromZeroTest_370, DelegateReturnTypeDouble_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, ReturnDoubleFunc{}, 0.0);
    static_assert(std::is_same<decltype(result), double>::value, "Return type should be double");
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: The SignedSignificandBits parameter does not affect the result
// (it's not forwarded to the functor)
TEST_F(NearestAwayFromZeroTest_370, DifferentSSBSameResult_370) {
    MockSignedSignificandBits ssb1;
    MockSignedSignificandBits ssb2;
    auto result1 = nearest_away_from_zero_t::delegate(ssb1, ReturnIntFunc{});
    auto result2 = nearest_away_from_zero_t::delegate(ssb2, ReturnIntFunc{});
    EXPECT_EQ(result1, result2);
}

// Test with a lambda-like callable wrapped in a struct
struct LambdaLikeFunc {
    constexpr int operator()(nearest_away_from_zero_t, int val) const noexcept {
        return val + 100;
    }
};

TEST_F(NearestAwayFromZeroTest_370, DelegateWithLambdaLikeFunc_370) {
    auto result = nearest_away_from_zero_t::delegate(ssb, LambdaLikeFunc{}, 5);
    EXPECT_EQ(result, 105);
}

} // anonymous namespace
