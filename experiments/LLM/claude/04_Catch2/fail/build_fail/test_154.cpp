#include <gtest/gtest.h>
#include <array>
#include <utility>
#include <cstddef>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

// We need to provide the base case overload that the recursive function calls into
// Since the partial code only shows the recursive case, we need to handle the base case.
// The base case with empty index_sequence should be provided by the library.
// Let's include relevant Catch2 headers or define what's needed.

// Define simple matcher types for testing
struct AlwaysTrueMatcher {
    bool match(int) const { return true; }
};

struct AlwaysFalseMatcher {
    bool match(int) const { return false; }
};

struct GreaterThanMatcher {
    int threshold;
    bool match(int val) const { return val > threshold; }
};

struct EqualsMatcher {
    int expected;
    bool match(int val) const { return val == expected; }
};

// We need the base case for match_any_of. If the library doesn't expose it,
// we provide it in the correct namespace.
namespace Catch { namespace Matchers { namespace Detail {

// Base case: single matcher remaining (no more Indices)
template<typename T>
bool match_any_of(auto&& arg, auto const& matchers, std::index_sequence<>) {
    return false;
}

}}} // namespace Catch::Matchers::Detail

class MatchAnyOfTest_154 : public ::testing::Test {
protected:
    AlwaysTrueMatcher alwaysTrue;
    AlwaysFalseMatcher alwaysFalse;
    GreaterThanMatcher gt5{5};
    GreaterThanMatcher gt10{10};
    EqualsMatcher eq3{3};
    EqualsMatcher eq7{7};
};

// Test: Single matcher that returns true
TEST_F(MatchAnyOfTest_154, SingleMatcherTrue_154) {
    std::array<void const*, 1> matchers = {&alwaysTrue};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysTrueMatcher>(
        42, matchers, std::index_sequence<0>{});
    EXPECT_TRUE(result);
}

// Test: Single matcher that returns false
TEST_F(MatchAnyOfTest_154, SingleMatcherFalse_154) {
    std::array<void const*, 1> matchers = {&alwaysFalse};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysFalseMatcher>(
        42, matchers, std::index_sequence<0>{});
    EXPECT_FALSE(result);
}

// Test: Two matchers, first is true (short-circuit)
TEST_F(MatchAnyOfTest_154, TwoMatchersFirstTrue_154) {
    std::array<void const*, 2> matchers = {&alwaysTrue, &alwaysFalse};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysTrueMatcher, AlwaysFalseMatcher>(
        42, matchers, std::index_sequence<0, 1>{});
    EXPECT_TRUE(result);
}

// Test: Two matchers, second is true
TEST_F(MatchAnyOfTest_154, TwoMatchersSecondTrue_154) {
    std::array<void const*, 2> matchers = {&alwaysFalse, &alwaysTrue};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysFalseMatcher, AlwaysTrueMatcher>(
        42, matchers, std::index_sequence<0, 1>{});
    EXPECT_TRUE(result);
}

// Test: Two matchers, both false
TEST_F(MatchAnyOfTest_154, TwoMatchersBothFalse_154) {
    std::array<void const*, 2> matchers = {&alwaysFalse, &alwaysFalse};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysFalseMatcher, AlwaysFalseMatcher>(
        42, matchers, std::index_sequence<0, 1>{});
    EXPECT_FALSE(result);
}

// Test: Two matchers, both true
TEST_F(MatchAnyOfTest_154, TwoMatchersBothTrue_154) {
    std::array<void const*, 2> matchers = {&alwaysTrue, &alwaysTrue};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysTrueMatcher, AlwaysTrueMatcher>(
        42, matchers, std::index_sequence<0, 1>{});
    EXPECT_TRUE(result);
}

// Test: Conditional matchers with value-dependent behavior
TEST_F(MatchAnyOfTest_154, ConditionalMatcherMatches_154) {
    std::array<void const*, 2> matchers = {&gt5, &eq3};
    bool result = Catch::Matchers::Detail::match_any_of<GreaterThanMatcher, EqualsMatcher>(
        3, matchers, std::index_sequence<0, 1>{});
    // 3 > 5 is false, 3 == 3 is true => true
    EXPECT_TRUE(result);
}

// Test: Conditional matchers where none match
TEST_F(MatchAnyOfTest_154, ConditionalMatcherNoneMatch_154) {
    std::array<void const*, 2> matchers = {&gt10, &eq7};
    bool result = Catch::Matchers::Detail::match_any_of<GreaterThanMatcher, EqualsMatcher>(
        5, matchers, std::index_sequence<0, 1>{});
    // 5 > 10 is false, 5 == 7 is false => false
    EXPECT_FALSE(result);
}

// Test: Three matchers with mixed results
TEST_F(MatchAnyOfTest_154, ThreeMatchersLastTrue_154) {
    std::array<void const*, 3> matchers = {&alwaysFalse, &alwaysFalse, &alwaysTrue};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysFalseMatcher, AlwaysFalseMatcher, AlwaysTrueMatcher>(
        42, matchers, std::index_sequence<0, 1, 2>{});
    EXPECT_TRUE(result);
}

// Test: Three matchers all false
TEST_F(MatchAnyOfTest_154, ThreeMatchersAllFalse_154) {
    std::array<void const*, 3> matchers = {&alwaysFalse, &alwaysFalse, &alwaysFalse};
    bool result = Catch::Matchers::Detail::match_any_of<AlwaysFalseMatcher, AlwaysFalseMatcher, AlwaysFalseMatcher>(
        42, matchers, std::index_sequence<0, 1, 2>{});
    EXPECT_FALSE(result);
}

// Test: Boundary value for GreaterThan matcher
TEST_F(MatchAnyOfTest_154, BoundaryValueExactThreshold_154) {
    std::array<void const*, 1> matchers = {&gt5};
    bool result = Catch::Matchers::Detail::match_any_of<GreaterThanMatcher>(
        5, matchers, std::index_sequence<0>{});
    // 5 > 5 is false
    EXPECT_FALSE(result);
}

// Test: Boundary value just above threshold
TEST_F(MatchAnyOfTest_154, BoundaryValueAboveThreshold_154) {
    std::array<void const*, 1> matchers = {&gt5};
    bool result = Catch::Matchers::Detail::match_any_of<GreaterThanMatcher>(
        6, matchers, std::index_sequence<0>{});
    EXPECT_TRUE(result);
}
