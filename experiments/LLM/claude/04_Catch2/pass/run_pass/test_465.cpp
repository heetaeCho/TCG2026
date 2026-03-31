#include <gtest/gtest.h>
#include "catch2/internal/catch_case_insensitive_comparisons.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::Detail::CaseInsensitiveEqualTo;
using Catch::StringRef;

class CaseInsensitiveEqualToTest_465 : public ::testing::Test {
protected:
    CaseInsensitiveEqualTo equalTo;
};

// Normal operation tests

TEST_F(CaseInsensitiveEqualToTest_465, SameStringReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("hello"), StringRef("hello")));
}

TEST_F(CaseInsensitiveEqualToTest_465, DifferentCaseReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("Hello"), StringRef("hello")));
}

TEST_F(CaseInsensitiveEqualToTest_465, AllUpperVsAllLowerReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("HELLO"), StringRef("hello")));
}

TEST_F(CaseInsensitiveEqualToTest_465, MixedCaseReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("HeLLo"), StringRef("hEllO")));
}

TEST_F(CaseInsensitiveEqualToTest_465, DifferentStringsReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("hello"), StringRef("world")));
}

TEST_F(CaseInsensitiveEqualToTest_465, DifferentLengthsReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("hello"), StringRef("hell")));
}

TEST_F(CaseInsensitiveEqualToTest_465, DifferentLengthsReversedReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("hell"), StringRef("hello")));
}

// Boundary condition tests

TEST_F(CaseInsensitiveEqualToTest_465, EmptyStringsReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef(""), StringRef("")));
}

TEST_F(CaseInsensitiveEqualToTest_465, EmptyVsNonEmptyReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef(""), StringRef("a")));
}

TEST_F(CaseInsensitiveEqualToTest_465, NonEmptyVsEmptyReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("a"), StringRef("")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SingleCharSameCaseReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("a"), StringRef("a")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SingleCharDifferentCaseReturnsTrue_465) {
    EXPECT_TRUE(equalTo(StringRef("a"), StringRef("A")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SingleCharDifferentReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("a"), StringRef("b")));
}

// Non-alphabetic characters

TEST_F(CaseInsensitiveEqualToTest_465, NumbersCompareEqual_465) {
    EXPECT_TRUE(equalTo(StringRef("12345"), StringRef("12345")));
}

TEST_F(CaseInsensitiveEqualToTest_465, NumbersDifferReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("12345"), StringRef("12346")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SpecialCharactersCompareEqual_465) {
    EXPECT_TRUE(equalTo(StringRef("!@#$%"), StringRef("!@#$%")));
}

TEST_F(CaseInsensitiveEqualToTest_465, MixedAlphaNumericCaseInsensitive_465) {
    EXPECT_TRUE(equalTo(StringRef("Hello123"), StringRef("HELLO123")));
}

TEST_F(CaseInsensitiveEqualToTest_465, MixedAlphaNumericDifferentReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("Hello123"), StringRef("HELLO124")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SpacesCompareEqual_465) {
    EXPECT_TRUE(equalTo(StringRef("hello world"), StringRef("HELLO WORLD")));
}

TEST_F(CaseInsensitiveEqualToTest_465, StringWithSpaceVsWithout_465) {
    EXPECT_FALSE(equalTo(StringRef("hello world"), StringRef("helloworld")));
}

// Symmetry tests

TEST_F(CaseInsensitiveEqualToTest_465, SymmetricComparison_465) {
    EXPECT_TRUE(equalTo(StringRef("ABC"), StringRef("abc")));
    EXPECT_TRUE(equalTo(StringRef("abc"), StringRef("ABC")));
}

TEST_F(CaseInsensitiveEqualToTest_465, SymmetricComparisonFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("abc"), StringRef("abd")));
    EXPECT_FALSE(equalTo(StringRef("abd"), StringRef("abc")));
}

// Edge cases with similar prefixes

TEST_F(CaseInsensitiveEqualToTest_465, PrefixSubstringReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("abc"), StringRef("abcd")));
}

TEST_F(CaseInsensitiveEqualToTest_465, LongerLhsReturnsFalse_465) {
    EXPECT_FALSE(equalTo(StringRef("abcd"), StringRef("abc")));
}

// Longer strings

TEST_F(CaseInsensitiveEqualToTest_465, LongerStringsCaseInsensitive_465) {
    EXPECT_TRUE(equalTo(
        StringRef("The Quick Brown Fox Jumps Over The Lazy Dog"),
        StringRef("the quick brown fox jumps over the lazy dog")
    ));
}

TEST_F(CaseInsensitiveEqualToTest_465, LongerStringsDiffer_465) {
    EXPECT_FALSE(equalTo(
        StringRef("The Quick Brown Fox Jumps Over The Lazy Dog"),
        StringRef("the quick brown fox jumps over the lazy cat")
    ));
}

// Using std::string as source

TEST_F(CaseInsensitiveEqualToTest_465, StdStringInputs_465) {
    std::string s1 = "Hello";
    std::string s2 = "HELLO";
    EXPECT_TRUE(equalTo(StringRef(s1), StringRef(s2)));
}

TEST_F(CaseInsensitiveEqualToTest_465, DefaultConstructedStringRefs_465) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(equalTo(a, b));
}
