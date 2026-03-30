// File: tests/match_any_of_operator_or_165_tests.cpp

#include <gtest/gtest.h>

#include <string>
#include <utility>

#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

using Catch::Matchers::ContainsSubstring;
using Catch::Matchers::Equals;
using Catch::Matchers::StartsWith;
using Catch::Matchers::Detail::MatchAnyOfGeneric;

// --- Test 1: Basic combination and matching of any element ---
TEST(MatchAnyOfOperatorOr_165, CombinesLhsAndRhs_MatchesAny_165) {
    // LHS matcher: strings starting with "he"
    auto lhs = StartsWith(std::string{"he"});

    // RHS any-of: equals "yo" OR equals "zz"
    auto rhs = MatchAnyOfGeneric{ Equals(std::string{"yo"}), Equals(std::string{"zz"}) };

    // Exercise the operator|| (note rhs is rvalue)
    auto combined = lhs || std::move(rhs);

    // Observable behavior: should match if ANY of [starts-with("he"), "yo", "zz"] is true
    EXPECT_TRUE(combined.match(std::string{"hello"})); // via StartsWith
    EXPECT_TRUE(combined.match(std::string{"yo"}));    // via Equals("yo")
    EXPECT_TRUE(combined.match(std::string{"zz"}));    // via Equals("zz")
    EXPECT_FALSE(combined.match(std::string{"nope"})); // none match
}

// --- Test 2: Chaining multiple times builds a larger "any-of" set ---
TEST(MatchAnyOfOperatorOr_165, ChainingBuildsLargerAnyOf_165) {
    auto lhs1 = Equals(std::string{"alpha"});
    auto first_rhs = MatchAnyOfGeneric{ Equals(std::string{"beta"}) };

    // alpha || (any-of(beta))  -> any-of(alpha, beta)
    auto combined1 = lhs1 || std::move(first_rhs);

    // Now extend again with a new LHS ("gamma") against the current any-of
    auto lhs2 = Equals(std::string{"gamma"});
    auto combined2 = lhs2 || std::move(combined1); // -> any-of(gamma, alpha, beta)

    EXPECT_TRUE(combined2.match(std::string{"alpha"}));
    EXPECT_TRUE(combined2.match(std::string{"beta"}));
    EXPECT_TRUE(combined2.match(std::string{"gamma"}));
    EXPECT_FALSE(combined2.match(std::string{"delta"}));
}

// --- Test 3: Heterogeneous matcher types can coexist in the combined any-of ---
TEST(MatchAnyOfOperatorOr_165, HeterogeneousMatchersCoexist_165) {
    // LHS: Contains substring "core"
    auto lhs = ContainsSubstring(std::string{"core"});

    // RHS any-of contains different matcher types (Equals + StartsWith)
    auto rhs = MatchAnyOfGeneric{
        Equals(std::string{"DONE"}),
        StartsWith(std::string{"pre"})
    };

    auto combined = lhs || std::move(rhs);

    // Matches via different branches
    EXPECT_TRUE(combined.match(std::string{"hardcore mode"})); // via ContainsSubstring("core")
    EXPECT_TRUE(combined.match(std::string{"DONE"}));          // via Equals("DONE")
    EXPECT_TRUE(combined.match(std::string{"prefix"}));        // via StartsWith("pre")
    EXPECT_FALSE(combined.match(std::string{"random"}));       // none of them match
}

// --- Test 4: Result remains a valid matcher usable repeatedly on different inputs ---
TEST(MatchAnyOfOperatorOr_165, CombinedMatcherIsReusable_165) {
    auto lhs = StartsWith(std::string{"cat"});
    auto rhs = MatchAnyOfGeneric{ Equals(std::string{"dog"}), Equals(std::string{"bird"}) };

    auto combined = lhs || std::move(rhs);

    // Reuse on multiple inputs; results should be consistent
    EXPECT_TRUE(combined.match(std::string{"catnip"}));  // LHS path
    EXPECT_TRUE(combined.match(std::string{"dog"}));     // RHS path
    EXPECT_FALSE(combined.match(std::string{"fish"}));   // neither
    EXPECT_TRUE(combined.match(std::string{"bird"}));    // RHS path
}
