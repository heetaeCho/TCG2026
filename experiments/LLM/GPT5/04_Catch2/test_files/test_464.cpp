// File: case_insensitive_less_tests_464.cpp

#include <gtest/gtest.h>
#include <set>
#include <string>

// Headers under test (paths taken from the prompt)
#include "catch2/internal/catch_case_insensitive_comparisons.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;
using Catch::Detail::CaseInsensitiveLess;

// Fixture kept minimal as we only need the comparator object
class CaseInsensitiveLessTest_464 : public ::testing::Test {
protected:
    CaseInsensitiveLess comp;
};

TEST_F(CaseInsensitiveLessTest_464, EqualIgnoringCase_ReturnsFalseBothWays_464) {
    StringRef a("AbC");
    StringRef b("aBc");

    // If strings are equal case-insensitively, neither is less than the other
    EXPECT_FALSE(comp(a, b));
    EXPECT_FALSE(comp(b, a));
}

TEST_F(CaseInsensitiveLessTest_464, Lexicographical_OrderDifferentCase_464) {
    // 'a' < 'b' even with mixed case
    StringRef apple("Apple");
    StringRef banana("bAnAnA");

    EXPECT_TRUE(comp(apple, banana));
    EXPECT_FALSE(comp(banana, apple));
}

TEST_F(CaseInsensitiveLessTest_464, DiffersLaterInString_LessIfEarlierCharIsSmaller_464) {
    // Compare proceeds lexicographically; first differing char decides
    StringRef lhs("abCxyz");
    StringRef rhs("aBd000");

    // 'c' < 'd' (ignoring case), so lhs < rhs
    EXPECT_TRUE(comp(lhs, rhs));
    EXPECT_FALSE(comp(rhs, lhs));
}

TEST_F(CaseInsensitiveLessTest_464, PrefixComparison_ShorterPrefixIsLess_464) {
    // When one is a prefix of the other (case-insensitive equal prefix), the shorter is less
    StringRef shortS("ab");
    StringRef longS("aBc");

    EXPECT_TRUE(comp(shortS, longS));
    EXPECT_FALSE(comp(longS, shortS));
}

TEST_F(CaseInsensitiveLessTest_464, EmptyStringBehavior_464) {
    StringRef empty("");
    StringRef nonEmpty("A");

    // empty !< empty, and empty < nonEmpty
    EXPECT_FALSE(comp(empty, empty));
    EXPECT_TRUE(comp(empty, nonEmpty));
    EXPECT_FALSE(comp(nonEmpty, empty));
}

TEST_F(CaseInsensitiveLessTest_464, NonAlphabeticCharacters_AreComparedNormally_464) {
    // Digits/punctuation are not affected by case; standard lexicographical behavior should apply
    StringRef s1("a1");
    StringRef s2("A2");

    // Compare at second char: '1' < '2'
    EXPECT_TRUE(comp(s1, s2));
    EXPECT_FALSE(comp(s2, s1));
}

TEST_F(CaseInsensitiveLessTest_464, SetTreatsCaseInsensitiveEqualsAsSameKey_464) {
    // In ordered associative containers, two keys are equivalent if
    // !comp(a, b) && !comp(b, a). Insert both "abc" and "AbC": only one element should remain.
    std::set<StringRef, CaseInsensitiveLess> s;

    s.insert(StringRef("abc"));
    s.insert(StringRef("AbC"));
    s.insert(StringRef("aBc"));
    s.insert(StringRef("ABC"));

    // All are case-insensitively equal, so only one key is stored
    EXPECT_EQ(s.size(), 1u);

    // Also check that a different key (case-insensitively) can be added
    s.insert(StringRef("abd"));
    EXPECT_EQ(s.size(), 2u);
}

TEST_F(CaseInsensitiveLessTest_464, OrderingAcrossMultipleValues_StableAndTransitive_464) {
    // Basic sanity: a < b < c under the comparator
    StringRef a("a");
    StringRef b("B");  // same as 'b' ignoring case
    StringRef c("c");

    EXPECT_TRUE(comp(a, b));
    EXPECT_TRUE(comp(b, c));
    EXPECT_TRUE(comp(a, c));

    // And not the other way
    EXPECT_FALSE(comp(b, a));
    EXPECT_FALSE(comp(c, b));
    EXPECT_FALSE(comp(c, a));
}
