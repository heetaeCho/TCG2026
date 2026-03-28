// File: match_any_of_generic_test_162.cpp
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the SUT's public interface.
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

using namespace Catch::Matchers::Detail;

// Lightweight collaborator used only to drive observable behavior of the SUT.
// It exposes the minimal surface the SUT relies on (match + describe).
struct DummyMatcher162 {
    bool result;
    std::string desc;

    explicit DummyMatcher162(bool r, std::string d) : result(r), desc(std::move(d)) {}

    template <typename Arg>
    bool match(const Arg&) const {
        return result;
    }

    std::string describe() const {
        return desc;
    }
};

// A simple value type we'll pass through match(); its contents are irrelevant
// because we treat SUT as a black box and our collaborator ignores it.
struct Payload162 { int v = 0; };

// Test fixture (kept empty for clarity/organization).
class MatchAnyOfGenericTest_162 : public ::testing::Test {};

// ---- Normal operation -------------------------------------------------------

TEST_F(MatchAnyOfGenericTest_162, ReturnsTrueIfAnyMatcherMatches_162) {
    DummyMatcher162 m1(false, "d1");
    DummyMatcher162 m2(false, "d2");
    DummyMatcher162 m3(true,  "d3");

    MatchAnyOfGeneric<DummyMatcher162, DummyMatcher162, DummyMatcher162> any(m1, m2, m3);

    Payload162 p{42};
    EXPECT_TRUE(any.match(p));
}

TEST_F(MatchAnyOfGenericTest_162, ReturnsFalseIfNoMatcherMatches_162) {
    DummyMatcher162 m1(false, "never 1");
    DummyMatcher162 m2(false, "never 2");

    MatchAnyOfGeneric<DummyMatcher162, DummyMatcher162> any(m1, m2);

    Payload162 p{};
    EXPECT_FALSE(any.match(p));
}

TEST_F(MatchAnyOfGenericTest_162, SingleMatcherPropagatesResult_162) {
    DummyMatcher162 t(true,  "ok");
    DummyMatcher162 f(false, "nope");

    MatchAnyOfGeneric<DummyMatcher162> any_true(t);
    MatchAnyOfGeneric<DummyMatcher162> any_false(f);

    EXPECT_TRUE(any_true.match(Payload162{1}));
    EXPECT_FALSE(any_false.match(Payload162{2}));
}

// ---- Boundary-ish conditions ------------------------------------------------

// We avoid constructing zero-arity packs (behavior unspecified from interface).
// Instead, validate move semantics & non-copyability, which are explicitly in the interface.

TEST_F(MatchAnyOfGenericTest_162, IsMoveConstructibleAndMoveAssignable_NotCopyable_162) {
    using AnyT = MatchAnyOfGeneric<DummyMatcher162, DummyMatcher162>;

    static_assert(std::is_move_constructible<AnyT>::value, "Should be move-constructible");
    static_assert(std::is_move_assignable<AnyT>::value,    "Should be move-assignable");

    static_assert(!std::is_copy_constructible<AnyT>::value, "Copy-ctor deleted");
    static_assert(!std::is_copy_assignable<AnyT>::value,    "Copy-assign deleted");

    // Also exercise runtime move usage:
    DummyMatcher162 a(false, "a");
    DummyMatcher162 b(true,  "b");
    AnyT original(a, b);

    AnyT moved(std::move(original));
    EXPECT_TRUE(moved.match(Payload162{}));

    DummyMatcher162 c(false, "c");
    DummyMatcher162 d(false, "d");
    AnyT other(c, d);
    other = std::move(moved);  // move-assign should be valid
    EXPECT_TRUE(other.match(Payload162{}));
}

// ---- Description formatting --------------------------------------------------

TEST_F(MatchAnyOfGenericTest_162, Describe_ConcatenatesMatcherDescriptionsWithOr_162) {
    DummyMatcher162 m1(false, "is even");
    DummyMatcher162 m2(true,  "is > 10");
    DummyMatcher162 m3(false, "starts with A");

    MatchAnyOfGeneric<DummyMatcher162, DummyMatcher162, DummyMatcher162> any(m1, m2, m3);
    const std::string d = any.describe();

    // We don't rely on internal implementation details; we check the observable string.
    // The partial code shows " or " as the separator; verify presence and order.
    EXPECT_NE(d.find("is even"), std::string::npos);
    EXPECT_NE(d.find("is > 10"), std::string::npos);
    EXPECT_NE(d.find("starts with A"), std::string::npos);

    // Verify the separator " or " appears between parts.
    // Expect at least two occurrences when 3 descriptions are present.
    size_t count_or = 0, pos = 0;
    while ((pos = d.find(" or ", pos)) != std::string::npos) {
        ++count_or; pos += 4;
    }
    EXPECT_GE(count_or, 2u);
}

TEST_F(MatchAnyOfGenericTest_162, Describe_SingleMatcherIsJustThatDescription_162) {
    DummyMatcher162 m(true, "only one");

    MatchAnyOfGeneric<DummyMatcher162> any(m);
    const std::string d = any.describe();

    EXPECT_EQ(d, "only one");
}

