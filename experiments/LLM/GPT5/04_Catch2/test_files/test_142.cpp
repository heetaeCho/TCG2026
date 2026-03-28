// File: tests/match_any_of_or_operator_test.cpp

#include <gtest/gtest.h>
#include "Catch2/src/catch2/matchers/catch_matchers.hpp"

using Catch::Matchers::MatcherBase;
using Catch::Matchers::Detail::MatchAnyOf;

namespace {

// Simple helper matchers used as external collaborators in tests.
// They only define observable behavior via match()/describe().

struct EvenMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct OddMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v % 2 != 0; }
    std::string describe() const override { return "is odd"; }
};

struct NegativeMatcher : MatcherBase<int> {
    bool match(int const& v) const override { return v < 0; }
    std::string describe() const override { return "is negative"; }
};

struct AlwaysFalseMatcher : MatcherBase<int> {
    bool match(int const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

} // namespace

// -------------------------------------------------------------

// 1) Normal operation: `lhs || MatchAnyOf{}` yields a matcher behaving like `lhs`.
TEST(MatchAnyOfOrOperator_142, LhsWithEmptyAnyOfBehavesLikeLhs_142) {
    EvenMatcher lhs;
    auto combined = lhs || MatchAnyOf<int>{};

    EXPECT_TRUE(combined.match(2));   // even -> true
    EXPECT_FALSE(combined.match(3));  // odd  -> false
}

// 2) Combination: `lhs || rhs` acknowledges both sides (either can match).
TEST(MatchAnyOfOrOperator_142, CombinesLhsAndRhsMatchers_142) {
    EvenMatcher lhs;               // matches even
    OddMatcher rhs_part;           // matches odd
    auto rhs = rhs_part || MatchAnyOf<int>{}; // build some rhs AnyOf

    auto combined = lhs || std::move(rhs);

    EXPECT_TRUE(combined.match(4)); // matched by lhs
    EXPECT_TRUE(combined.match(5)); // matched by rhs_part
    EXPECT_FALSE(combined.match(-3 * 2 + 1 + 0)); // sanity: odd path covered above; choose a value neither would fail? (none) -> keep explicit failure check:
    // The above line intentionally kept as comment to avoid redundant assertion.
}

// 3) Chaining / composability with rvalues: `a || (b || MatchAnyOf{})`.
TEST(MatchAnyOfOrOperator_142, SupportsChainingWithRvalues_142) {
    EvenMatcher a;
    NegativeMatcher b;

    auto rhs = b || MatchAnyOf<int>{};
    auto combined = a || std::move(rhs);

    EXPECT_TRUE(combined.match(-7)); // matched by b (negative)
    EXPECT_TRUE(combined.match(10)); // matched by a (even)
    EXPECT_FALSE(combined.match(3)); // neither even nor negative
}

// 4) Edge case: LHS that never matches + RHS that never matches -> overall false.
TEST(MatchAnyOfOrOperator_142, AllConstituentsFailResultsInNoMatch_142) {
    AlwaysFalseMatcher lhs;
    auto rhs = AlwaysFalseMatcher{} || MatchAnyOf<int>{};

    auto combined = lhs || std::move(rhs);

    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(1));
    EXPECT_FALSE(combined.match(-1));
}

// 5) Public description mentions all constituent matchers (order not asserted).
TEST(MatchAnyOfOrOperator_142, DescribeMentionsAllConstituents_142) {
    EvenMatcher a;
    OddMatcher b;
    NegativeMatcher c;

    auto any = b || MatchAnyOf<int>{};         // start with one
    any = c || std::move(any);                 // add another
    auto combined = a || std::move(any);       // prepend via operator||

    const std::string desc = combined.describe();
    // We only verify that each constituent's description text appears;
    // we do NOT assert formatting or ordering.
    EXPECT_NE(desc.find(a.describe()), std::string::npos);
    EXPECT_NE(desc.find(b.describe()), std::string::npos);
    EXPECT_NE(desc.find(c.describe()), std::string::npos);
}

