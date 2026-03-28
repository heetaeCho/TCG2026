// File: any_match_matcher_test_187.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the header that declares Catch::Matchers::AnyMatch and AnyMatchMatcher
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

namespace {

using Catch::Matchers::AnyMatch;
using Catch::Matchers::AnyMatchMatcher;

// Simple dummy matcher type for deduction tests
struct DummyMatcher {};

// Move-only type to ensure perfect-forwarding supports non-copyable arguments
struct MoveOnlyMatcher {
    MoveOnlyMatcher() = default;
    MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher(MoveOnlyMatcher&&) = default;
    MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) = default;
};

class AnyMatchMatcherTest_187 : public ::testing::Test {};

TEST_F(AnyMatchMatcherTest_187, ReturnsExpectedTypeForLvalue_187) {
    using T = DummyMatcher;
    // When passing an lvalue, template parameter deduces as T&
    using ReturnT = decltype(AnyMatch(std::declval<T&>()));
    using ExpectedT = AnyMatchMatcher<T&>;
    static_assert(std::is_same<ReturnT, ExpectedT>::value,
                  "AnyMatch should return AnyMatchMatcher<T&> for lvalue argument");
    SUCCEED();
}

TEST_F(AnyMatchMatcherTest_187, ReturnsExpectedTypeForConstLvalue_187) {
    using T = DummyMatcher;
    using ReturnT = decltype(AnyMatch(std::declval<const T&>()));
    using ExpectedT = AnyMatchMatcher<const T&>;
    static_assert(std::is_same<ReturnT, ExpectedT>::value,
                  "AnyMatch should return AnyMatchMatcher<const T&> for const lvalue argument");
    SUCCEED();
}

TEST_F(AnyMatchMatcherTest_187, ReturnsExpectedTypeForRvalue_187) {
    using T = DummyMatcher;
    // When passing an rvalue, template parameter deduces as T (not a reference)
    using ReturnT = decltype(AnyMatch(std::declval<T&&>()));
    using ExpectedT = AnyMatchMatcher<T>;
    static_assert(std::is_same<ReturnT, ExpectedT>::value,
                  "AnyMatch should return AnyMatchMatcher<T> for rvalue argument");
    SUCCEED();
}

TEST_F(AnyMatchMatcherTest_187, AcceptsMoveOnlyRvalue_187) {
    using T = MoveOnlyMatcher;
    // Verifies that a move-only type is acceptable in rvalue form
    using ReturnT = decltype(AnyMatch(std::declval<T&&>()));
    using ExpectedT = AnyMatchMatcher<T>;
    static_assert(std::is_same<ReturnT, ExpectedT>::value,
                  "AnyMatch should support move-only rvalue arguments");
    SUCCEED();
}

TEST_F(AnyMatchMatcherTest_187, AcceptsMoveOnlyLvalueWithoutCopy_187) {
    using T = MoveOnlyMatcher;
    // Lvalue forwarding should keep the reference in the template argument
    using ReturnT = decltype(AnyMatch(std::declval<T&>()));
    using ExpectedT = AnyMatchMatcher<T&>;
    static_assert(std::is_same<ReturnT, ExpectedT>::value,
                  "AnyMatch should forward lvalues as references even for move-only types");
    SUCCEED();
}

} // namespace
