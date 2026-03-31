#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits
struct MockSignedSignificandBits {};

// A functor that returns an int when called with nearest_to_even_t
struct IntReturningFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_even_t) const noexcept {
        return 42;
    }
};

// A functor that takes nearest_to_even_t and additional args
struct SumFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_even_t, int a, int b) const noexcept {
        return a + b;
    }
};

// A functor that returns a bool
struct BoolReturningFunc {
    JKJ_FORCEINLINE constexpr bool operator()(nearest_to_even_t) const noexcept {
        return true;
    }
};

// A functor that takes one additional argument
struct SingleArgFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_even_t, int x) const noexcept {
        return x * 2;
    }
};

// A functor that returns void-like (we use int to keep it simple)
struct IdentityFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_even_t, int x) const noexcept {
        return x;
    }
};

// A functor that takes many arguments
struct MultiArgFunc {
    JKJ_FORCEINLINE constexpr int operator()(nearest_to_even_t, int a, int b, int c, int d) const noexcept {
        return a + b + c + d;
    }
};

// A functor returning a different type (double)
struct DoubleReturningFunc {
    JKJ_FORCEINLINE constexpr double operator()(nearest_to_even_t, double x) const noexcept {
        return x * 3.14;
    }
};

// Test fixture
class NearestToEvenTest_355 : public ::testing::Test {
protected:
    nearest_to_even_t policy;
    MockSignedSignificandBits bits;
};

// Test: delegate with no extra args returns correct value
TEST_F(NearestToEvenTest_355, DelegateNoArgs_ReturnsExpectedValue_355) {
    auto result = nearest_to_even_t::delegate(bits, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: delegate with two extra int args forwards them correctly
TEST_F(NearestToEvenTest_355, DelegateTwoArgs_ReturnsSumOfArgs_355) {
    auto result = nearest_to_even_t::delegate(bits, SumFunc{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test: delegate with bool-returning functor
TEST_F(NearestToEvenTest_355, DelegateBoolReturn_ReturnsTrue_355) {
    auto result = nearest_to_even_t::delegate(bits, BoolReturningFunc{});
    EXPECT_TRUE(result);
}

// Test: delegate with a single extra argument
TEST_F(NearestToEvenTest_355, DelegateSingleArg_ReturnsDoubledValue_355) {
    auto result = nearest_to_even_t::delegate(bits, SingleArgFunc{}, 7);
    EXPECT_EQ(result, 14);
}

// Test: delegate with identity function
TEST_F(NearestToEvenTest_355, DelegateIdentity_ReturnsOriginalValue_355) {
    auto result = nearest_to_even_t::delegate(bits, IdentityFunc{}, 99);
    EXPECT_EQ(result, 99);
}

// Test: delegate with many arguments
TEST_F(NearestToEvenTest_355, DelegateMultipleArgs_ReturnsSumOfAll_355) {
    auto result = nearest_to_even_t::delegate(bits, MultiArgFunc{}, 1, 2, 3, 4);
    EXPECT_EQ(result, 10);
}

// Test: delegate with double return type
TEST_F(NearestToEvenTest_355, DelegateDoubleReturn_ReturnsCorrectDouble_355) {
    auto result = nearest_to_even_t::delegate(bits, DoubleReturningFunc{}, 2.0);
    EXPECT_DOUBLE_EQ(result, 2.0 * 3.14);
}

// Test: boundary - zero args passed to sum func
TEST_F(NearestToEvenTest_355, DelegateSumWithZeros_ReturnsZero_355) {
    auto result = nearest_to_even_t::delegate(bits, SumFunc{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test: boundary - negative values
TEST_F(NearestToEvenTest_355, DelegateSumWithNegatives_ReturnsCorrectSum_355) {
    auto result = nearest_to_even_t::delegate(bits, SumFunc{}, -10, 5);
    EXPECT_EQ(result, -5);
}

// Test: boundary - large values
TEST_F(NearestToEvenTest_355, DelegateSumWithLargeValues_ReturnsCorrectSum_355) {
    auto result = nearest_to_even_t::delegate(bits, SumFunc{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

// Test: constexpr evaluation (compile-time check at runtime)
TEST_F(NearestToEvenTest_355, DelegateIsConstexpr_355) {
    constexpr auto result = nearest_to_even_t::delegate(MockSignedSignificandBits{}, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: noexcept property
TEST_F(NearestToEvenTest_355, DelegateIsNoexcept_355) {
    bool is_noexcept = noexcept(nearest_to_even_t::delegate(bits, IntReturningFunc{}));
    EXPECT_TRUE(is_noexcept);
}

// Test: The SignedSignificandBits parameter does not affect the result
TEST_F(NearestToEvenTest_355, DelegateIgnoresSignedSignificandBits_355) {
    MockSignedSignificandBits bits1;
    MockSignedSignificandBits bits2;
    auto result1 = nearest_to_even_t::delegate(bits1, IntReturningFunc{});
    auto result2 = nearest_to_even_t::delegate(bits2, IntReturningFunc{});
    EXPECT_EQ(result1, result2);
}

// Test: return type deduction works correctly
TEST_F(NearestToEvenTest_355, DelegateReturnTypeIsCorrect_355) {
    auto result = nearest_to_even_t::delegate(bits, IntReturningFunc{});
    static_assert(std::is_same<decltype(result), int>::value, "Return type should be int");
    EXPECT_EQ(result, 42);
}

// Test: double return type deduction
TEST_F(NearestToEvenTest_355, DelegateDoubleReturnTypeIsCorrect_355) {
    auto result = nearest_to_even_t::delegate(bits, DoubleReturningFunc{}, 1.0);
    static_assert(std::is_same<decltype(result), double>::value, "Return type should be double");
    EXPECT_DOUBLE_EQ(result, 3.14);
}

} // namespace
