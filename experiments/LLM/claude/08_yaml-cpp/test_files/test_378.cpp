#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal definitions needed to compile the code under test

#ifndef JKJ_FORCEINLINE
#define JKJ_FORCEINLINE inline
#endif

#ifndef JKJ_SAFEBUFFERS
#define JKJ_SAFEBUFFERS
#endif

namespace YAML {
namespace jkj {
namespace dragonbox {
namespace detail {

struct nearest_always_closed_t {};
struct nearest_always_open_t {};

} // namespace detail

namespace policy {
namespace decimal_to_binary_rounding {

struct nearest_to_odd_static_boundary_t {
public:
    template <class SignedSignificandBits, class Func, class... Args>
    JKJ_FORCEINLINE JKJ_SAFEBUFFERS static constexpr decltype(Func{}(
        detail::nearest_always_closed_t{}, Args{}...))
    delegate(SignedSignificandBits s, Func f, Args... args) noexcept {
        return s.has_even_significand_bits()
                   ? f(detail::nearest_always_open_t{}, args...)
                   : f(detail::nearest_always_closed_t{}, args...);
    }
};

} // namespace decimal_to_binary_rounding
} // namespace policy
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

// Test helpers

struct EvenSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return true; }
};

struct OddSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return false; }
};

// A functor that returns different values depending on which tag type is passed
struct TestFunc {
    int operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t) const noexcept {
        return 1; // open path
    }
    int operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t) const noexcept {
        return 2; // closed path
    }
};

// A functor that accepts extra arguments
struct TestFuncWithArgs {
    int operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t, int a, int b) const noexcept {
        return a + b + 100; // open path
    }
    int operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t, int a, int b) const noexcept {
        return a + b + 200; // closed path
    }
};

// A functor that returns a string-like identifier
struct TestFuncString {
    const char* operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t) const noexcept {
        return "open";
    }
    const char* operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t) const noexcept {
        return "closed";
    }
};

using NearestToOdd = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd_static_boundary_t;

// Test fixture
class NearestToOddStaticBoundaryTest_378 : public ::testing::Test {
protected:
};

// Test: Even significand bits should delegate to the open path
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandDelegatesToOpen_378) {
    EvenSignificandBits s;
    TestFunc f;
    int result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 1); // open path returns 1
}

// Test: Odd significand bits should delegate to the closed path
TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandDelegatesToClosed_378) {
    OddSignificandBits s;
    TestFunc f;
    int result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 2); // closed path returns 2
}

// Test: Even significand with additional arguments - open path
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandWithArgsDelegatesToOpen_378) {
    EvenSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, 3, 7);
    EXPECT_EQ(result, 3 + 7 + 100); // open path: a + b + 100
}

// Test: Odd significand with additional arguments - closed path
TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandWithArgsDelegatesToClosed_378) {
    OddSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, 3, 7);
    EXPECT_EQ(result, 3 + 7 + 200); // closed path: a + b + 200
}

// Test: Return type is correctly deduced (const char*)
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandReturnsOpenString_378) {
    EvenSignificandBits s;
    TestFuncString f;
    const char* result = NearestToOdd::delegate(s, f);
    EXPECT_STREQ(result, "open");
}

TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandReturnsClosedString_378) {
    OddSignificandBits s;
    TestFuncString f;
    const char* result = NearestToOdd::delegate(s, f);
    EXPECT_STREQ(result, "closed");
}

// Test: Boundary - zero args beyond the tag
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandNoExtraArgs_378) {
    EvenSignificandBits s;
    TestFunc f;
    auto result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 1);
}

TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandNoExtraArgs_378) {
    OddSignificandBits s;
    TestFunc f;
    auto result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 2);
}

// Test: constexpr behavior (compile-time evaluation)
TEST_F(NearestToOddStaticBoundaryTest_378, ConstexprEvenSignificand_378) {
    // Verify that the function can be evaluated at compile time
    constexpr EvenSignificandBits s{};
    constexpr TestFunc f{};
    constexpr int result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 1);
}

TEST_F(NearestToOddStaticBoundaryTest_378, ConstexprOddSignificand_378) {
    constexpr OddSignificandBits s{};
    constexpr TestFunc f{};
    constexpr int result = NearestToOdd::delegate(s, f);
    EXPECT_EQ(result, 2);
}

// Test: noexcept property
TEST_F(NearestToOddStaticBoundaryTest_378, DelegateIsNoexcept_378) {
    EvenSignificandBits es;
    OddSignificandBits os;
    TestFunc f;
    EXPECT_TRUE(noexcept(NearestToOdd::delegate(es, f)));
    EXPECT_TRUE(noexcept(NearestToOdd::delegate(os, f)));
}

// Test with arguments that are zero (boundary value for int args)
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandZeroArgs_378) {
    EvenSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, 0, 0);
    EXPECT_EQ(result, 100); // 0 + 0 + 100
}

TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandZeroArgs_378) {
    OddSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, 0, 0);
    EXPECT_EQ(result, 200); // 0 + 0 + 200
}

// Test with negative arguments
TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandNegativeArgs_378) {
    EvenSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, -5, -3);
    EXPECT_EQ(result, -5 + -3 + 100);
}

TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandNegativeArgs_378) {
    OddSignificandBits s;
    TestFuncWithArgs f;
    int result = NearestToOdd::delegate(s, f, -5, -3);
    EXPECT_EQ(result, -5 + -3 + 200);
}
