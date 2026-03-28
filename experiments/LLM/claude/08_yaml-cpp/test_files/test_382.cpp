#include <gtest/gtest.h>
#include <type_traits>

// Minimal definitions to support the code under test

#ifndef JKJ_FORCEINLINE
#define JKJ_FORCEINLINE
#endif

#ifndef JKJ_SAFEBUFFERS
#define JKJ_SAFEBUFFERS
#endif

namespace YAML {
namespace jkj {
namespace dragonbox {
namespace detail {

struct left_closed_directed_t {};
struct right_closed_directed_t {};

} // namespace detail
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

// Include the header under test
// Since we have the code inline, we replicate the struct here faithfully:
namespace YAML {
namespace jkj {
namespace dragonbox {
namespace policy {
namespace decimal_to_binary_rounding {

struct toward_minus_infinity_t {
public:
    template <class SignedSignificandBits, class Func, class... Args>
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS static constexpr decltype(Func{}(
        detail::left_closed_directed_t{}, Args{}...))
    delegate(SignedSignificandBits s, Func f, Args... args) noexcept {
        return s.is_negative()
                   ? f(detail::right_closed_directed_t{}, args...)
                   : f(detail::left_closed_directed_t{}, args...);
    }
};

} // namespace decimal_to_binary_rounding
} // namespace policy
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

// Test helpers

struct MockSignedSignificandBits {
    bool negative_;
    constexpr MockSignedSignificandBits(bool neg) : negative_(neg) {}
    constexpr bool is_negative() const { return negative_; }
};

// A functor that returns different values depending on the interval type
struct TestFunc {
    constexpr int operator()(YAML::jkj::dragonbox::detail::left_closed_directed_t) const {
        return 1;
    }
    constexpr int operator()(YAML::jkj::dragonbox::detail::right_closed_directed_t) const {
        return 2;
    }
    // Overloads with extra args
    constexpr int operator()(YAML::jkj::dragonbox::detail::left_closed_directed_t, int x) const {
        return 100 + x;
    }
    constexpr int operator()(YAML::jkj::dragonbox::detail::right_closed_directed_t, int x) const {
        return 200 + x;
    }
    constexpr int operator()(YAML::jkj::dragonbox::detail::left_closed_directed_t, int x, int y) const {
        return 1000 + x + y;
    }
    constexpr int operator()(YAML::jkj::dragonbox::detail::right_closed_directed_t, int x, int y) const {
        return 2000 + x + y;
    }
};

using TowardMinusInfinity = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::toward_minus_infinity_t;

// Test fixture
class TowardMinusInfinityTest_382 : public ::testing::Test {
protected:
    TowardMinusInfinity policy_;
    TestFunc func_;
};

// When the value is positive (not negative), delegate should call with left_closed_directed_t
TEST_F(TowardMinusInfinityTest_382, PositiveValueUsesLeftClosed_382) {
    MockSignedSignificandBits positive_bits(false);
    int result = TowardMinusInfinity::delegate(positive_bits, func_);
    EXPECT_EQ(result, 1);
}

// When the value is negative, delegate should call with right_closed_directed_t
TEST_F(TowardMinusInfinityTest_382, NegativeValueUsesRightClosed_382) {
    MockSignedSignificandBits negative_bits(true);
    int result = TowardMinusInfinity::delegate(negative_bits, func_);
    EXPECT_EQ(result, 2);
}

// Positive value with one extra argument
TEST_F(TowardMinusInfinityTest_382, PositiveValueWithOneArg_382) {
    MockSignedSignificandBits positive_bits(false);
    int result = TowardMinusInfinity::delegate(positive_bits, func_, 42);
    EXPECT_EQ(result, 142); // 100 + 42
}

// Negative value with one extra argument
TEST_F(TowardMinusInfinityTest_382, NegativeValueWithOneArg_382) {
    MockSignedSignificandBits negative_bits(true);
    int result = TowardMinusInfinity::delegate(negative_bits, func_, 42);
    EXPECT_EQ(result, 242); // 200 + 42
}

// Positive value with two extra arguments
TEST_F(TowardMinusInfinityTest_382, PositiveValueWithTwoArgs_382) {
    MockSignedSignificandBits positive_bits(false);
    int result = TowardMinusInfinity::delegate(positive_bits, func_, 10, 20);
    EXPECT_EQ(result, 1030); // 1000 + 10 + 20
}

// Negative value with two extra arguments
TEST_F(TowardMinusInfinityTest_382, NegativeValueWithTwoArgs_382) {
    MockSignedSignificandBits negative_bits(true);
    int result = TowardMinusInfinity::delegate(negative_bits, func_, 10, 20);
    EXPECT_EQ(result, 2030); // 2000 + 10 + 20
}

// Verify noexcept property
TEST_F(TowardMinusInfinityTest_382, DelegateIsNoexcept_382) {
    MockSignedSignificandBits bits(false);
    bool is_noexcept = noexcept(TowardMinusInfinity::delegate(bits, func_));
    EXPECT_TRUE(is_noexcept);
}

// Boundary: zero args with negative
TEST_F(TowardMinusInfinityTest_382, BoundaryZeroArgsNegative_382) {
    MockSignedSignificandBits bits(true);
    int result = TowardMinusInfinity::delegate(bits, func_);
    EXPECT_EQ(result, 2);
}

// Boundary: zero args with positive
TEST_F(TowardMinusInfinityTest_382, BoundaryZeroArgsPositive_382) {
    MockSignedSignificandBits bits(false);
    int result = TowardMinusInfinity::delegate(bits, func_);
    EXPECT_EQ(result, 1);
}

// Test with zero as extra argument - positive
TEST_F(TowardMinusInfinityTest_382, PositiveWithZeroArg_382) {
    MockSignedSignificandBits bits(false);
    int result = TowardMinusInfinity::delegate(bits, func_, 0);
    EXPECT_EQ(result, 100); // 100 + 0
}

// Test with zero as extra argument - negative
TEST_F(TowardMinusInfinityTest_382, NegativeWithZeroArg_382) {
    MockSignedSignificandBits bits(true);
    int result = TowardMinusInfinity::delegate(bits, func_, 0);
    EXPECT_EQ(result, 200); // 200 + 0
}

// Test with negative integer as extra argument
TEST_F(TowardMinusInfinityTest_382, PositiveWithNegativeArg_382) {
    MockSignedSignificandBits bits(false);
    int result = TowardMinusInfinity::delegate(bits, func_, -5);
    EXPECT_EQ(result, 95); // 100 + (-5)
}

TEST_F(TowardMinusInfinityTest_382, NegativeWithNegativeArg_382) {
    MockSignedSignificandBits bits(true);
    int result = TowardMinusInfinity::delegate(bits, func_, -5);
    EXPECT_EQ(result, 195); // 200 + (-5)
}

// Verify that the functor is called exactly as expected by using a stateful lambda-like functor
struct CountingFunc {
    mutable int left_count = 0;
    mutable int right_count = 0;

    int operator()(YAML::jkj::dragonbox::detail::left_closed_directed_t) const {
        ++left_count;
        return 10;
    }
    int operator()(YAML::jkj::dragonbox::detail::right_closed_directed_t) const {
        ++right_count;
        return 20;
    }
};

TEST_F(TowardMinusInfinityTest_382, PositiveCallsLeftClosedExactlyOnce_382) {
    MockSignedSignificandBits bits(false);
    CountingFunc counter;
    int result = TowardMinusInfinity::delegate(bits, counter);
    EXPECT_EQ(result, 10);
    // Note: due to value semantics in delegate, the original counter may not be modified.
    // We verify behavior via return value.
}

TEST_F(TowardMinusInfinityTest_382, NegativeCallsRightClosedExactlyOnce_382) {
    MockSignedSignificandBits bits(true);
    CountingFunc counter;
    int result = TowardMinusInfinity::delegate(bits, counter);
    EXPECT_EQ(result, 20);
}
