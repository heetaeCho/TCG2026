// WildcardPatternTests_561.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_wildcard_pattern.hpp"

// If CaseSensitive is an enum class in Catch2 (as in recent versions),
// bring it into scope for brevity.
using Catch::WildcardPattern;
using Catch::CaseSensitive;

class WildcardPatternTest_561 : public ::testing::Test {};

// ---------- No wildcard (exact match) ----------

TEST_F(WildcardPatternTest_561, ExactMatch_SucceedsWithSameCase_561) {
    WildcardPattern p{"Hello", CaseSensitive::Yes};
    EXPECT_TRUE(p.matches("Hello"));
    EXPECT_FALSE(p.matches("Hello "));   // extra char
    EXPECT_FALSE(p.matches(" Hell o"));  // spacing difference
}

TEST_F(WildcardPatternTest_561, ExactMatch_FailsWithDifferentCase_WhenCaseSensitive_561) {
    WildcardPattern p{"Hello", CaseSensitive::Yes};
    EXPECT_FALSE(p.matches("hello"));
    EXPECT_FALSE(p.matches("HELLO"));
}

TEST_F(WildcardPatternTest_561, ExactMatch_SucceedsIgnoringCase_WhenCaseInsensitive_561) {
    WildcardPattern p{"HeLLo", CaseSensitive::No};
    EXPECT_TRUE(p.matches("hello"));
    EXPECT_TRUE(p.matches("HELLO"));
    EXPECT_FALSE(p.matches("helloo"));   // not exact
}

// ---------- Wildcard at start: "*suffix" (ends-with behavior) ----------

TEST_F(WildcardPatternTest_561, WildcardAtStart_MatchesSuffix_561) {
    WildcardPattern p{"*world", CaseSensitive::Yes};
    EXPECT_TRUE(p.matches("hello world"));
    EXPECT_TRUE(p.matches("world"));
    EXPECT_FALSE(p.matches("worldwide"));  // not ending with "world"
}

TEST_F(WildcardPatternTest_561, WildcardAtStart_CaseInsensitiveSuffix_561) {
    WildcardPattern p{"*WoRLd", CaseSensitive::No};
    EXPECT_TRUE(p.matches("hello world"));
    EXPECT_TRUE(p.matches("WORLD"));
    EXPECT_FALSE(p.matches("worldwide"));
}

// ---------- Wildcard at end: "prefix*" (starts-with behavior) ----------

TEST_F(WildcardPatternTest_561, WildcardAtEnd_MatchesPrefix_561) {
    WildcardPattern p{"abc*", CaseSensitive::Yes};
    EXPECT_TRUE(p.matches("abcdef"));
    EXPECT_TRUE(p.matches("abc"));
    EXPECT_FALSE(p.matches("zabc"));     // does not start with "abc"
}

TEST_F(WildcardPatternTest_561, WildcardAtEnd_CaseInsensitivePrefix_561) {
    WildcardPattern p{"AbC*", CaseSensitive::No};
    EXPECT_TRUE(p.matches("abcdef"));
    EXPECT_TRUE(p.matches("ABC"));
    EXPECT_FALSE(p.matches("zabc"));
}

// ---------- Wildcards at both ends: "*mid*" (contains behavior) ----------

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_MatchesContains_561) {
    WildcardPattern p{"*mid*", CaseSensitive::Yes};
    EXPECT_TRUE(p.matches("pre-mid-suf"));
    EXPECT_TRUE(p.matches("mid"));
    EXPECT_FALSE(p.matches("mi_d"));     // not a simple containment of "mid"
}

TEST_F(WildcardPatternTest_561, WildcardAtBothEnds_CaseInsensitiveContains_561) {
    WildcardPattern p{"*MiD*", CaseSensitive::No};
    EXPECT_TRUE(p.matches("pre-mid-suf"));
    EXPECT_TRUE(p.matches("MID"));
    EXPECT_FALSE(p.matches("mi_d"));
}

// ---------- Boundary: empty pattern (no wildcard) ----------

TEST_F(WildcardPatternTest_561, EmptyPattern_ExactOnly_561) {
    WildcardPattern p{"", CaseSensitive::Yes};
    EXPECT_TRUE(p.matches(""));          // exact empty
    EXPECT_FALSE(p.matches("a"));        // any non-empty should fail
}

// ---------- Negative coverage across wildcards ----------

TEST_F(WildcardPatternTest_561, NegativeCases_DoNotAccidentallyMatch_561) {
    // No wildcard: exact comparison
    {
        WildcardPattern p{"needle", CaseSensitive::No};
        EXPECT_FALSE(p.matches("a needle in a haystack")); // not exact
    }
    // Start wildcard: ends-with comparison
    {
        WildcardPattern p{"*stack", CaseSensitive::No};
        EXPECT_FALSE(p.matches("haystacked"));             // does not end with "stack"
    }
    // End wildcard: starts-with comparison
    {
        WildcardPattern p{"hay*", CaseSensitive::No};
        EXPECT_FALSE(p.matches("a hay"));                  // does not start with "hay"
    }
    // Both ends: contains comparison
    {
        WildcardPattern p{"*xyz*", CaseSensitive::No};
        EXPECT_FALSE(p.matches("x_y_z"));                  // does not contain "xyz" as-is
    }
}
