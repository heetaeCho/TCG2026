#include <gtest/gtest.h>
#include "catch2/internal/catch_case_insensitive_comparisons.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <set>
#include <string>

using Catch::Detail::CaseInsensitiveLess;
using Catch::StringRef;

class CaseInsensitiveLessTest_464 : public ::testing::Test {
protected:
    CaseInsensitiveLess less;
};

// Normal operation tests

TEST_F(CaseInsensitiveLessTest_464, LowercaseLessThanUppercase_464) {
    // "abc" should be equal to "ABC" case-insensitively, so neither should be less
    EXPECT_FALSE(less(StringRef("abc"), StringRef("ABC")));
    EXPECT_FALSE(less(StringRef("ABC"), StringRef("abc")));
}

TEST_F(CaseInsensitiveLessTest_464, DifferentStringsSameCaseCompare_464) {
    // "apple" < "banana" case-insensitively
    EXPECT_TRUE(less(StringRef("apple"), StringRef("banana")));
    EXPECT_FALSE(less(StringRef("banana"), StringRef("apple")));
}

TEST_F(CaseInsensitiveLessTest_464, MixedCaseComparison_464) {
    // "Apple" < "banana" case-insensitively (a < b)
    EXPECT_TRUE(less(StringRef("Apple"), StringRef("banana")));
    EXPECT_FALSE(less(StringRef("banana"), StringRef("Apple")));
}

TEST_F(CaseInsensitiveLessTest_464, MixedCaseComparisonReverse_464) {
    // "BANANA" > "apple" case-insensitively
    EXPECT_FALSE(less(StringRef("BANANA"), StringRef("apple")));
    EXPECT_TRUE(less(StringRef("apple"), StringRef("BANANA")));
}

TEST_F(CaseInsensitiveLessTest_464, SameStringSameCase_464) {
    // Same string should not be less than itself
    EXPECT_FALSE(less(StringRef("hello"), StringRef("hello")));
}

TEST_F(CaseInsensitiveLessTest_464, SameStringDifferentCase_464) {
    // "Hello" and "hELLO" are equal case-insensitively
    EXPECT_FALSE(less(StringRef("Hello"), StringRef("hELLO")));
    EXPECT_FALSE(less(StringRef("hELLO"), StringRef("Hello")));
}

// Boundary condition tests

TEST_F(CaseInsensitiveLessTest_464, EmptyStrings_464) {
    // Two empty strings - neither is less
    EXPECT_FALSE(less(StringRef(""), StringRef("")));
}

TEST_F(CaseInsensitiveLessTest_464, EmptyStringLessThanNonEmpty_464) {
    // Empty string should be less than any non-empty string
    EXPECT_TRUE(less(StringRef(""), StringRef("a")));
    EXPECT_FALSE(less(StringRef("a"), StringRef("")));
}

TEST_F(CaseInsensitiveLessTest_464, SingleCharacterComparison_464) {
    EXPECT_TRUE(less(StringRef("a"), StringRef("b")));
    EXPECT_TRUE(less(StringRef("A"), StringRef("b")));
    EXPECT_TRUE(less(StringRef("a"), StringRef("B")));
    EXPECT_TRUE(less(StringRef("A"), StringRef("B")));
}

TEST_F(CaseInsensitiveLessTest_464, SingleCharacterEqual_464) {
    EXPECT_FALSE(less(StringRef("a"), StringRef("A")));
    EXPECT_FALSE(less(StringRef("A"), StringRef("a")));
}

TEST_F(CaseInsensitiveLessTest_464, PrefixIsLessThanLongerString_464) {
    // "abc" < "abcd" because it's a prefix
    EXPECT_TRUE(less(StringRef("abc"), StringRef("abcd")));
    EXPECT_FALSE(less(StringRef("abcd"), StringRef("abc")));
}

TEST_F(CaseInsensitiveLessTest_464, PrefixMixedCase_464) {
    // "ABC" < "abcd" case-insensitively (prefix)
    EXPECT_TRUE(less(StringRef("ABC"), StringRef("abcd")));
    EXPECT_FALSE(less(StringRef("ABCD"), StringRef("abc")));
}

// Tests with numbers and special characters

TEST_F(CaseInsensitiveLessTest_464, StringsWithNumbers_464) {
    EXPECT_TRUE(less(StringRef("1abc"), StringRef("2abc")));
    EXPECT_FALSE(less(StringRef("2abc"), StringRef("1abc")));
}

TEST_F(CaseInsensitiveLessTest_464, NumbersAndLetters_464) {
    // '0' (48) < 'A' (65) < 'a' (97), but toLower('A') = 'a' (97)
    // So '0' < toLower('A') = 'a'
    EXPECT_TRUE(less(StringRef("0"), StringRef("A")));
    EXPECT_TRUE(less(StringRef("0"), StringRef("a")));
}

TEST_F(CaseInsensitiveLessTest_464, SpecialCharacters_464) {
    // Special characters are compared as-is (toLower has no effect on non-alpha)
    EXPECT_FALSE(less(StringRef("!"), StringRef("!")));
}

// Transitivity and strict weak ordering tests

TEST_F(CaseInsensitiveLessTest_464, Irreflexivity_464) {
    EXPECT_FALSE(less(StringRef("test"), StringRef("test")));
    EXPECT_FALSE(less(StringRef("TEST"), StringRef("TEST")));
    EXPECT_FALSE(less(StringRef("TeSt"), StringRef("TeSt")));
}

TEST_F(CaseInsensitiveLessTest_464, Asymmetry_464) {
    // If a < b, then !(b < a)
    StringRef a("alpha");
    StringRef b("beta");
    if (less(a, b)) {
        EXPECT_FALSE(less(b, a));
    }
}

TEST_F(CaseInsensitiveLessTest_464, Transitivity_464) {
    // a < b and b < c implies a < c
    StringRef a("alpha");
    StringRef b("beta");
    StringRef c("gamma");
    EXPECT_TRUE(less(a, b));
    EXPECT_TRUE(less(b, c));
    EXPECT_TRUE(less(a, c));
}

// Use as comparator in std::set

TEST_F(CaseInsensitiveLessTest_464, UsableAsSetComparator_464) {
    std::set<std::string, CaseInsensitiveLess> s;
    s.insert("Hello");
    s.insert("hello");
    s.insert("HELLO");
    // All should be considered equivalent, so set size should be 1
    EXPECT_EQ(s.size(), 1u);
}

TEST_F(CaseInsensitiveLessTest_464, SetComparatorMultipleDistinctEntries_464) {
    std::set<std::string, CaseInsensitiveLess> s;
    s.insert("apple");
    s.insert("Banana");
    s.insert("CHERRY");
    s.insert("APPLE");
    s.insert("banana");
    // Should have 3 distinct entries
    EXPECT_EQ(s.size(), 3u);
}

// Edge case: strings differing only at the last character

TEST_F(CaseInsensitiveLessTest_464, DifferAtLastCharacter_464) {
    EXPECT_TRUE(less(StringRef("testa"), StringRef("testb")));
    EXPECT_TRUE(less(StringRef("testA"), StringRef("testB")));
    EXPECT_FALSE(less(StringRef("testA"), StringRef("testA")));
    EXPECT_FALSE(less(StringRef("testa"), StringRef("testA")));
}

// Longer strings

TEST_F(CaseInsensitiveLessTest_464, LongStringsComparison_464) {
    std::string longA(1000, 'a');
    std::string longB(1000, 'b');
    EXPECT_TRUE(less(StringRef(longA), StringRef(longB)));
    EXPECT_FALSE(less(StringRef(longB), StringRef(longA)));
}

TEST_F(CaseInsensitiveLessTest_464, LongStringsCaseInsensitiveEqual_464) {
    std::string longLower(1000, 'a');
    std::string longUpper(1000, 'A');
    EXPECT_FALSE(less(StringRef(longLower), StringRef(longUpper)));
    EXPECT_FALSE(less(StringRef(longUpper), StringRef(longLower)));
}

TEST_F(CaseInsensitiveLessTest_464, LongStringsDifferAtEnd_464) {
    std::string base(999, 'a');
    std::string strA = base + "a";
    std::string strB = base + "b";
    EXPECT_TRUE(less(StringRef(strA), StringRef(strB)));
    EXPECT_FALSE(less(StringRef(strB), StringRef(strA)));
}

// Z vs a boundary

TEST_F(CaseInsensitiveLessTest_464, ZvsAComparison_464) {
    EXPECT_FALSE(less(StringRef("z"), StringRef("a")));
    EXPECT_FALSE(less(StringRef("Z"), StringRef("a")));
    EXPECT_FALSE(less(StringRef("Z"), StringRef("A")));
    EXPECT_TRUE(less(StringRef("a"), StringRef("z")));
    EXPECT_TRUE(less(StringRef("A"), StringRef("z")));
    EXPECT_TRUE(less(StringRef("A"), StringRef("Z")));
}
