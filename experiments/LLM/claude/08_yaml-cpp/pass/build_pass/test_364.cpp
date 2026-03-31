#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A simple mock for SignedSignificandBits - just needs to be passable
struct MockSignedSignificandBits {};

// A functor that captures whether it was called with nearest_toward_minus_infinity_t
struct CheckTypeFunctor {
    template <class RoundingTag>
    constexpr bool operator()(RoundingTag) const noexcept {
        return std::is_same<RoundingTag, nearest_toward_minus_infinity_t>::value;
    }
};

// A functor that returns a specific int value
struct ReturnIntFunctor {
    template <class RoundingTag>
    constexpr int operator()(RoundingTag) const noexcept {
        return 42;
    }
};

// A functor that takes additional args and returns their sum
struct SumArgsFunctor {
    template <class RoundingTag>
    constexpr int operator()(RoundingTag, int a, int b) const noexcept {
        return a + b;
    }
};

// A functor that returns its single extra arg
struct PassthroughFunctor {
    template <class RoundingTag>
    constexpr int operator()(RoundingTag, int a) const noexcept {
        return a;
    }
};

// A functor returning a double
struct ReturnDoubleFunctor {
    template <class RoundingTag>
    constexpr double operator()(RoundingTag, double x) const noexcept {
        return x * 2.0;
    }
};

// A functor with no extra args returning a string-like type
struct ReturnCharFunctor {
    template <class RoundingTag>
    constexpr char operator()(RoundingTag) const noexcept {
        return 'A';
    }
};

// Test fixture
class NearestTowardMinusInfinityTest_364 : public ::testing::Test {
protected:
    MockSignedSignificandBits ssb;
};

// Test that delegate calls the functor with nearest_toward_minus_infinity_t
TEST_F(NearestTowardMinusInfinityTest_364, DelegatePassesCorrectRoundingTag_364) {
    bool result = nearest_toward_minus_infinity_t::delegate(ssb, CheckTypeFunctor{});
    EXPECT_TRUE(result);
}

// Test that delegate returns the correct value from the functor with no extra args
TEST_F(NearestTowardMinusInfinityTest_364, DelegateReturnsCorrectValueNoArgs_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, ReturnIntFunctor{});
    EXPECT_EQ(result, 42);
}

// Test that delegate forwards additional arguments correctly
TEST_F(NearestTowardMinusInfinityTest_364, DelegateForwardsAdditionalArgs_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, SumArgsFunctor{}, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test with a single extra argument
TEST_F(NearestTowardMinusInfinityTest_364, DelegateSingleExtraArg_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, PassthroughFunctor{}, 99);
    EXPECT_EQ(result, 99);
}

// Test with double return type
TEST_F(NearestTowardMinusInfinityTest_364, DelegateDoubleReturnType_364) {
    double result = nearest_toward_minus_infinity_t::delegate(ssb, ReturnDoubleFunctor{}, 3.5);
    EXPECT_DOUBLE_EQ(result, 7.0);
}

// Test with char return type
TEST_F(NearestTowardMinusInfinityTest_364, DelegateCharReturnType_364) {
    char result = nearest_toward_minus_infinity_t::delegate(ssb, ReturnCharFunctor{});
    EXPECT_EQ(result, 'A');
}

// Boundary: Test with zero arguments forwarded (sum with 0,0)
TEST_F(NearestTowardMinusInfinityTest_364, DelegateZeroValueArgs_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, SumArgsFunctor{}, 0, 0);
    EXPECT_EQ(result, 0);
}

// Boundary: Test with negative arguments
TEST_F(NearestTowardMinusInfinityTest_364, DelegateNegativeArgs_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, SumArgsFunctor{}, -5, -10);
    EXPECT_EQ(result, -15);
}

// Boundary: Test with large values
TEST_F(NearestTowardMinusInfinityTest_364, DelegateLargeValues_364) {
    int result = nearest_toward_minus_infinity_t::delegate(ssb, SumArgsFunctor{}, 1000000, 2000000);
    EXPECT_EQ(result, 3000000);
}

// Test constexpr capability (compile-time evaluation)
TEST_F(NearestTowardMinusInfinityTest_364, DelegateIsConstexpr_364) {
    constexpr int result = nearest_toward_minus_infinity_t::delegate(
        MockSignedSignificandBits{}, ReturnIntFunctor{});
    EXPECT_EQ(result, 42);
}

// Test noexcept qualification
TEST_F(NearestTowardMinusInfinityTest_364, DelegateIsNoexcept_364) {
    bool is_noexcept = noexcept(
        nearest_toward_minus_infinity_t::delegate(ssb, ReturnIntFunctor{}));
    EXPECT_TRUE(is_noexcept);
}

// Test that the SignedSignificandBits parameter does not affect the result
// (it's not forwarded to the functor)
struct DifferentSSB {
    int value = 999;
};

TEST_F(NearestTowardMinusInfinityTest_364, DelegateIgnoresSSBValue_364) {
    DifferentSSB ssb1;
    ssb1.value = 1;
    DifferentSSB ssb2;
    ssb2.value = 2;
    
    int result1 = nearest_toward_minus_infinity_t::delegate(ssb1, ReturnIntFunctor{});
    int result2 = nearest_toward_minus_infinity_t::delegate(ssb2, ReturnIntFunctor{});
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 42);
}

// Test that delegate works with mixed-type extra args
struct MixedArgsFunctor {
    template <class RoundingTag>
    constexpr double operator()(RoundingTag, int a, double b) const noexcept {
        return static_cast<double>(a) + b;
    }
};

TEST_F(NearestTowardMinusInfinityTest_364, DelegateMixedTypeArgs_364) {
    double result = nearest_toward_minus_infinity_t::delegate(ssb, MixedArgsFunctor{}, 5, 2.5);
    EXPECT_DOUBLE_EQ(result, 7.5);
}

// Test default constructibility of the tag type
TEST_F(NearestTowardMinusInfinityTest_364, TagTypeIsDefaultConstructible_364) {
    EXPECT_TRUE(std::is_default_constructible<nearest_toward_minus_infinity_t>::value);
}

} // namespace
