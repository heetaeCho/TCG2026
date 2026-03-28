// RegexMatcher_tests_223.cpp
#include <gtest/gtest.h>
#include <regex>
#include <string>

// Headers from the provided codebase
#include "catch2/catch_case_sensitive.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

using Catch::CaseSensitive;
using Catch::Matchers::RegexMatcher;

// Normal operation: exact full-string match (case-sensitive by default)
TEST(RegexMatcherTest_223, MatchExact_CaseSensitive_223) {
    RegexMatcher m("^hello$", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("hello"));
    EXPECT_FALSE(m.match("Hello"));  // different case should not match
}

// Boundary: full-string vs partial-string match requirement
TEST(RegexMatcherTest_223, FullMatchRequired_NotPartial_223) {
    RegexMatcher m("world", CaseSensitive::Yes);
    EXPECT_FALSE(m.match("hello world")); // regex_match requires full-string match
    EXPECT_TRUE(RegexMatcher(".*world.*", CaseSensitive::Yes).match("hello world")); // explicit full match pattern
}

// Case handling: case-insensitive should match regardless of case
TEST(RegexMatcherTest_223, Match_IgnoresCase_WhenCaseSensitiveNo_223) {
    RegexMatcher m("^hello$", CaseSensitive::No);
    EXPECT_TRUE(m.match("HELLO"));
    EXPECT_TRUE(m.match("HeLLo"));
    EXPECT_TRUE(m.match("hello"));
}

// Boundary: empty pattern behavior with full match
TEST(RegexMatcherTest_223, EmptyPattern_MatchesOnlyEmptyString_223) {
    RegexMatcher m("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(""));          // empty pattern matches empty string
    EXPECT_FALSE(m.match("anything")); // but not non-empty strings for full match
}

// Exceptional case: invalid regex should surface as std::regex_error on match
TEST(RegexMatcherTest_223, InvalidRegex_ThrowsOnMatch_223) {
    RegexMatcher m("(", CaseSensitive::Yes); // invalid pattern
    EXPECT_THROW(m.match(""), std::regex_error);
    EXPECT_THROW(m.match("anything"), std::regex_error);
}

// Normal operation: anchors and wildcards with ECMAScript syntax
TEST(RegexMatcherTest_223, AnchorsAndWildcard_ECMAScript_223) {
    RegexMatcher anchored("^ab.c$", CaseSensitive::Yes);
    EXPECT_TRUE(anchored.match("abxc"));
    EXPECT_FALSE(anchored.match("zabxc"));
    EXPECT_FALSE(anchored.match("abxcz"));

    // Verify repeated calls are consistent (stateless observable behavior)
    EXPECT_TRUE(anchored.match("abxc"));
    EXPECT_TRUE(RegexMatcher("^a.*c$", CaseSensitive::No).match("A---C"));
}

// Mixed case & anchors under case-insensitive mode
TEST(RegexMatcherTest_223, AnchoredCaseInsensitive_223) {
    RegexMatcher m("^TeSt[0-9]+$", CaseSensitive::No);
    EXPECT_TRUE(m.match("test123"));
    EXPECT_TRUE(m.match("TEST9"));
    EXPECT_FALSE(m.match("preTEST9post"));  // must be full-string match
}
