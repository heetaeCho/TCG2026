#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits - just needs to be passable
struct MockSignedSignificandBits {};

// A functor that returns an int and records that it was called with the correct tag type
struct IntReturningFunc {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr int operator()(nearest_toward_zero_t) const noexcept {
        return 42;
    }
};

// A functor that accepts additional args
struct IntReturningFuncWithArgs {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr int operator()(nearest_toward_zero_t, int a, int b) const noexcept {
        return a + b;
    }
};

// A functor returning a different type (bool)
struct BoolReturningFunc {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr bool operator()(nearest_toward_zero_t) const noexcept {
        return true;
    }
};

// A functor with a single additional arg
struct SingleArgFunc {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr int operator()(nearest_toward_zero_t, int x) const noexcept {
        return x * 2;
    }
};

// A functor returning void - we just need it to compile
struct VoidReturningFunc {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr void operator()(nearest_toward_zero_t) const noexcept {
    }
};

// A functor that returns a double
struct DoubleReturningFunc {
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr double operator()(nearest_toward_zero_t, double val) const noexcept {
        return val * 3.14;
    }
};

// Test fixture
class NearestTowardZeroTest_367 : public ::testing::Test {
protected:
    MockSignedSignificandBits signed_bits;
};

// Test: delegate with no extra args returns correct value
TEST_F(NearestTowardZeroTest_367, DelegateNoArgsReturnsExpectedValue_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: delegate with two extra int args forwards them correctly
TEST_F(NearestTowardZeroTest_367, DelegateWithTwoIntArgs_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFuncWithArgs{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test: delegate returns bool type correctly
TEST_F(NearestTowardZeroTest_367, DelegateReturnsBool_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, BoolReturningFunc{});
    EXPECT_TRUE(result);
}

// Test: delegate with single arg forwards correctly
TEST_F(NearestTowardZeroTest_367, DelegateWithSingleArg_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, SingleArgFunc{}, 5);
    EXPECT_EQ(result, 10);
}

// Test: delegate with void return type compiles and runs
TEST_F(NearestTowardZeroTest_367, DelegateVoidReturn_367) {
    // Should compile and not crash
    nearest_toward_zero_t::delegate(signed_bits, VoidReturningFunc{});
    SUCCEED();
}

// Test: delegate with double return type and arg
TEST_F(NearestTowardZeroTest_367, DelegateDoubleReturnWithArg_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, DoubleReturningFunc{}, 1.0);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test: delegate is noexcept
TEST_F(NearestTowardZeroTest_367, DelegateIsNoexcept_367) {
    bool is_noexcept = noexcept(
        nearest_toward_zero_t::delegate(signed_bits, IntReturningFunc{})
    );
    EXPECT_TRUE(is_noexcept);
}

// Test: delegate is constexpr-capable (verify at compile time indirectly)
TEST_F(NearestTowardZeroTest_367, DelegateConstexprCapable_367) {
    // We can test constexpr by using it in a constexpr context
    constexpr auto result = nearest_toward_zero_t::delegate(
        MockSignedSignificandBits{}, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: boundary - zero values for args
TEST_F(NearestTowardZeroTest_367, DelegateWithZeroArgs_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFuncWithArgs{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test: boundary - negative values for args
TEST_F(NearestTowardZeroTest_367, DelegateWithNegativeArgs_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFuncWithArgs{}, -10, -20);
    EXPECT_EQ(result, -30);
}

// Test: boundary - mixed positive and negative args
TEST_F(NearestTowardZeroTest_367, DelegateWithMixedSignArgs_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFuncWithArgs{}, 10, -20);
    EXPECT_EQ(result, -10);
}

// Test: boundary - large values
TEST_F(NearestTowardZeroTest_367, DelegateWithLargeValues_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFuncWithArgs{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

// Test: return type deduction is correct
TEST_F(NearestTowardZeroTest_367, ReturnTypeIsCorrect_367) {
    auto result = nearest_toward_zero_t::delegate(signed_bits, IntReturningFunc{});
    static_assert(std::is_same<decltype(result), int>::value, "Return type should be int");
    
    auto bool_result = nearest_toward_zero_t::delegate(signed_bits, BoolReturningFunc{});
    static_assert(std::is_same<decltype(bool_result), bool>::value, "Return type should be bool");
    
    auto double_result = nearest_toward_zero_t::delegate(signed_bits, DoubleReturningFunc{}, 1.0);
    static_assert(std::is_same<decltype(double_result), double>::value, "Return type should be double");
}

// Test: SignedSignificandBits parameter is ignored (different types should work)
struct AnotherMockBits { int dummy = 99; };

TEST_F(NearestTowardZeroTest_367, DifferentSignedSignificandBitsType_367) {
    AnotherMockBits another_bits;
    auto result = nearest_toward_zero_t::delegate(another_bits, IntReturningFunc{});
    EXPECT_EQ(result, 42);
}

// Test: nearest_toward_zero_t is default constructible
TEST_F(NearestTowardZeroTest_367, IsDefaultConstructible_367) {
    EXPECT_TRUE(std::is_default_constructible<nearest_toward_zero_t>::value);
}

} // namespace
