// File: match_any_of_operator_or_test_164.cpp
#include <gtest/gtest.h>

// Use Catch2 public matcher interfaces only
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp> // declares operator||

using Catch::Matchers::StartsWith;
using Catch::Matchers::EndsWith;
using Catch::Matchers::Equals;

namespace {

// Basic sanity: OR should pass if either matcher matches.
TEST(MatchAnyOfOperatorOrTest_164, MatchesWhenEitherSideMatches_164) {
    auto any = StartsWith(std::string{"pre"}) || EndsWith(std::string{"post"});

    EXPECT_TRUE(any.match(std::string{"prefix"}));      // left side matches
    EXPECT_TRUE(any.match(std::string{"my_post"}));     // right side matches
    EXPECT_FALSE(any.match(std::string{"middle"}));     // neither matches
}

// Chaining check: ((A || B) || C) should consider all 3.
TEST(MatchAnyOfOperatorOrTest_164, ChainingOrAccumulatesMatchers_164) {
    auto m = (StartsWith(std::string{"a"}) || EndsWith(std::string{"z"}))
           || Equals(std::string{"mid"});

    EXPECT_TRUE(m.match(std::string{"alpha"}));         // matches StartsWith("a")
    EXPECT_TRUE(m.match(std::string{"buzz"}));          // matches EndsWith("z")
    EXPECT_TRUE(m.match(std::string{"mid"}));           // matches Equals("mid")
    EXPECT_FALSE(m.match(std::string{"noop"}));         // none match
}

// Symmetry of usefulness: left-false/right-true and left-true/right-false scenarios.
TEST(MatchAnyOfOperatorOrTest_164, OneSideFalseOtherTrueStillMatches_164) {
    auto leftFalse_rightTrue  = StartsWith(std::string{"x"}) || EndsWith(std::string{"ok"});
    auto leftTrue_rightFalse  = StartsWith(std::string{"ok"}) || EndsWith(std::string{"x"});

    EXPECT_TRUE(leftFalse_rightTrue.match(std::string{"is_ok"}));   // only RHS matches
    EXPECT_TRUE(leftTrue_rightFalse.match(std::string{"ok-thing"})); // only LHS matches
    EXPECT_FALSE(leftFalse_rightTrue.match(std::string{"nope"}));    // neither matches
}

// Boundary-ish: include empty-string matcher among OR terms.
TEST(MatchAnyOfOperatorOrTest_164, HandlesEmptyStringBoundary_164) {
    auto m = Equals(std::string{""}) || StartsWith(std::string{"x"});

    EXPECT_TRUE(m.match(std::string{""}));              // equals ""
    EXPECT_TRUE(m.match(std::string{"x-ray"}));         // starts with x
    EXPECT_FALSE(m.match(std::string{"ray"}));          // neither condition
}

// Description should reflect that multiple alternatives are present.
// We do not assert the exact formatting; just presence of both parts.
TEST(MatchAnyOfOperatorOrTest_164, DescribeIncludesBothSubDescriptions_164) {
    auto a = StartsWith(std::string{"pre"});
    auto b = EndsWith(std::string{"post"});
    auto any = a || b;

    const std::string descA = a.describe();
    const std::string descB = b.describe();
    const std::string combined = any.describe();

    // Both sub-descriptions should appear in the combined description.
    EXPECT_NE(combined.find(descA), std::string::npos);
    EXPECT_NE(combined.find(descB), std::string::npos);
    EXPECT_FALSE(combined.empty());
}

// Regression: OR with identical matchers still behaves as "any of" and not crash.
TEST(MatchAnyOfOperatorOrTest_164, OrWithIdenticalMatchersIsSafeAndWorks_164) {
    auto eq = Equals(std::string{"same"});
    auto any = eq || eq;

    EXPECT_TRUE(any.match(std::string{"same"}));
    EXPECT_FALSE(any.match(std::string{"different"}));
}

} // namespace
