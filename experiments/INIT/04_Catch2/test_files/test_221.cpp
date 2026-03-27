// File: starts_with_matcher_test_221.cpp

#include <gtest/gtest.h>

// Include the public Catch2 matcher headers that declare the interfaces
#include "catch2/matchers/catch_matchers_string.hpp"

using Catch::CaseSensitive;
using Catch::Matchers::CasedString;
using Catch::Matchers::StartsWithMatcher;

//
// Normal operation
//

TEST(StartsWithMatcherTest_221, MatchesWhenSourceStartsWithPrefix_CaseSensitive_221) {
    CasedString cmp("He", CaseSensitive::Yes);
    StartsWithMatcher m(cmp);

    EXPECT_TRUE(m.match(std::string("Hello")));
    EXPECT_TRUE(m.match(std::string("He")));
    EXPECT_FALSE(m.match(std::string("hello")));  // case differs
}

TEST(StartsWithMatcherTest_221, MatchesWhenSourceStartsWithPrefix_CaseInsensitive_221) {
    CasedString cmp("he", CaseSensitive::No);
    StartsWithMatcher m(cmp);

    EXPECT_TRUE(m.match(std::string("hello")));
    EXPECT_TRUE(m.match(std::string("Hello")));
    EXPECT_TRUE(m.match(std::string("HEy")));
    EXPECT_FALSE(m.match(std::string("ahero")));   // not at the start
}

//
// Boundary conditions
//

TEST(StartsWithMatcherTest_221, EmptyPrefixMatchesAnySource_221) {
    CasedString cmp("", CaseSensitive::Yes);
    StartsWithMatcher m(cmp);

    EXPECT_TRUE(m.match(std::string("anything")));
    EXPECT_TRUE(m.match(std::string("")));
}

TEST(StartsWithMatcherTest_221, EmptySourceOnlyMatchesEmptyPrefix_221) {
    {
        CasedString cmp("", CaseSensitive::Yes);
        StartsWithMatcher m(cmp);
        EXPECT_TRUE(m.match(std::string("")));
    }
    {
        CasedString cmp("x", CaseSensitive::Yes);
        StartsWithMatcher m(cmp);
        EXPECT_FALSE(m.match(std::string("")));
    }
}

TEST(StartsWithMatcherTest_221, PrefixEqualToWholeSource_221) {
    CasedString cmp("abc", CaseSensitive::Yes);
    StartsWithMatcher m(cmp);

    EXPECT_TRUE(m.match(std::string("abc")));   // exact match counts as starting with
}

TEST(StartsWithMatcherTest_221, PrefixLongerThanSourceDoesNotMatch_221) {
    CasedString cmp("abcd", CaseSensitive::No);
    StartsWithMatcher m(cmp);

    EXPECT_FALSE(m.match(std::string("abc")));
}

//
// Additional observable cases
//

TEST(StartsWithMatcherTest_221, NonMatchingDifferentFirstChar_221) {
    CasedString cmp("z", CaseSensitive::No);
    StartsWithMatcher m(cmp);

    EXPECT_FALSE(m.match(std::string("apple")));
}

TEST(StartsWithMatcherTest_221, CaseSensitivityRespectedOnFirstChar_221) {
    {
        CasedString cmp("A", CaseSensitive::Yes);
        StartsWithMatcher m(cmp);
        EXPECT_TRUE(m.match(std::string("Apple")));
        EXPECT_FALSE(m.match(std::string("apple")));
    }
    {
        CasedString cmp("A", CaseSensitive::No);
        StartsWithMatcher m(cmp);
        EXPECT_TRUE(m.match(std::string("apple")));
    }
}
