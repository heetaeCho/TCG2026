#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits - just needs to be a valid type
struct MockSignedSignificandBits {};

// A functor that records it was called with nearest_to_odd_t and returns an int
struct IntReturningFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_odd_t) const noexcept {
        return 42;
    }
};

// A functor that takes nearest_to_odd_t and additional args
struct SumFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_odd_t, int a, int b) const noexcept {
        return a + b;
    }
};

// A functor that returns bool
struct BoolReturningFunc {
    JKJ_FORCEINLINE constexpr bool operator()(nearest_to_odd_t) const noexcept {
        return true;
    }
};

// A functor that takes one additional arg
struct SingleArgFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_odd_t, int x) const noexcept {
        return x * 2;
    }
};

// A functor returning a double
struct DoubleReturningFunc {
    JKJ_FORCEINLINE constexpr double operator()(nearest_to_odd_t, double val) const noexcept {
        return val + 1.0;
    }
};

// A functor that takes many arguments
struct MultiArgFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_odd_t, int a, int b, int c, int d) const noexcept {
        return a + b + c + d;
    }
};

// A functor returning void - we need a special test for this
struct VoidFunc {
    JKJ_FORCEINLINE void operator()(nearest_to_odd_t) const noexcept {
        // No-op
    }
};

// Test fixture
class NearestToOddTest_358 : public ::testing::Test {
protected:
    MockSignedSignificandBits ssb;
};

// Test: delegate with no extra args returns the correct value
TEST_F(NearestToOddTest_358, DelegateNoExtraArgsReturnsCorrectValue_358) {
    auto result = nearest_to_odd_t::delegate(ssb, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: delegate forwards extra arguments correctly
TEST_F(NearestToOddTest_358, DelegateForwardsExtraArguments_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SumFunc{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test: delegate with bool-returning functor
TEST_F(NearestToOddTest_358, DelegateBoolReturnType_358) {
    auto result = nearest_to_odd_t::delegate(ssb, BoolReturningFunc{});
    EXPECT_TRUE(result);
}

// Test: delegate with single extra argument
TEST_F(NearestToOddTest_358, DelegateSingleExtraArg_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SingleArgFunc{}, 7);
    EXPECT_EQ(result, 14);
}

// Test: delegate with double return type
TEST_F(NearestToOddTest_358, DelegateDoubleReturnType_358) {
    auto result = nearest_to_odd_t::delegate(ssb, DoubleReturningFunc{}, 3.5);
    EXPECT_DOUBLE_EQ(result, 4.5);
}

// Test: delegate with multiple extra arguments
TEST_F(NearestToOddTest_358, DelegateMultipleExtraArgs_358) {
    auto result = nearest_to_odd_t::delegate(ssb, MultiArgFunc{}, 1, 2, 3, 4);
    EXPECT_EQ(result, 10);
}

// Test: delegate is noexcept
TEST_F(NearestToOddTest_358, DelegateIsNoexcept_358) {
    bool is_noexcept = noexcept(nearest_to_odd_t::delegate(ssb, IntReturningFunc{}));
    EXPECT_TRUE(is_noexcept);
}

// Test: delegate with zero values for arguments (boundary)
TEST_F(NearestToOddTest_358, DelegateZeroArgValues_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SumFunc{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test: delegate with negative values
TEST_F(NearestToOddTest_358, DelegateNegativeArgValues_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SumFunc{}, -10, -20);
    EXPECT_EQ(result, -30);
}

// Test: delegate with mixed positive and negative values
TEST_F(NearestToOddTest_358, DelegateMixedSignArgValues_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SumFunc{}, 10, -3);
    EXPECT_EQ(result, 7);
}

// Test: delegate with large values (boundary)
TEST_F(NearestToOddTest_358, DelegateLargeArgValues_358) {
    auto result = nearest_to_odd_t::delegate(ssb, SumFunc{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

// Test: return type matches the functor's return type
TEST_F(NearestToOddTest_358, DelegateReturnTypeMatchesFunctor_358) {
    using ReturnType = decltype(nearest_to_odd_t::delegate(ssb, IntReturningFunc{}));
    bool is_int = std::is_same<ReturnType, int>::value;
    EXPECT_TRUE(is_int);

    using ReturnType2 = decltype(nearest_to_odd_t::delegate(ssb, BoolReturningFunc{}));
    bool is_bool = std::is_same<ReturnType2, bool>::value;
    EXPECT_TRUE(is_bool);

    using ReturnType3 = decltype(nearest_to_odd_t::delegate(ssb, DoubleReturningFunc{}, 0.0));
    bool is_double = std::is_same<ReturnType3, double>::value;
    EXPECT_TRUE(is_double);
}

// Test: SignedSignificandBits parameter is ignored (different types work)
struct AnotherSSB {
    int data = 99;
};

TEST_F(NearestToOddTest_358, DelegateIgnoresSSBType_358) {
    AnotherSSB another;
    auto result = nearest_to_odd_t::delegate(another, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: constexpr behavior (compile-time evaluation)
TEST_F(NearestToOddTest_358, DelegateIsConstexprCapable_358) {
    constexpr auto result = nearest_to_odd_t::delegate(MockSignedSignificandBits{}, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: delegate passes nearest_to_odd_t instance to functor
struct TypeCheckFunc {
    JKJ_FORCEINLINE constexpr bool operator()(nearest_to_odd_t) const noexcept {
        return true;
    }

    template <class T>
    JKJ_FORCEINLINE constexpr bool operator()(T) const noexcept {
        return false;
    }
};

TEST_F(NearestToOddTest_358, DelegatePassesNearestToOddTToFunctor_358) {
    auto result = nearest_to_odd_t::delegate(ssb, TypeCheckFunc{});
    EXPECT_TRUE(result);
}

} // namespace
