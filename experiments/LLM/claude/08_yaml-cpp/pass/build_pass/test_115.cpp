#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {

// Test fixture for Exp::Empty tests
class ExpEmptyTest_115 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for RegEx tests
class RegExTest_115 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Exp::Empty() Tests =====

TEST_F(ExpEmptyTest_115, EmptyReturnsSameReference_115) {
    // The static instance should return the same reference each time
    const RegEx& ref1 = Exp::Empty();
    const RegEx& ref2 = Exp::Empty();
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(ExpEmptyTest_115, EmptyRegExDoesNotMatchCharacter_115) {
    const RegEx& empty = Exp::Empty();
    // An empty regex should not match any character
    EXPECT_FALSE(empty.Matches('a'));
    EXPECT_FALSE(empty.Matches('z'));
    EXPECT_FALSE(empty.Matches('\0'));
}

TEST_F(ExpEmptyTest_115, EmptyRegExMatchesEmptyString_115) {
    const RegEx& empty = Exp::Empty();
    // An empty regex should match an empty string (zero-length match)
    EXPECT_TRUE(empty.Matches(std::string("")));
}

TEST_F(ExpEmptyTest_115, EmptyRegExMatchReturnsZeroForEmptyString_115) {
    const RegEx& empty = Exp::Empty();
    // Match on empty string should return 0 (zero-length match)
    EXPECT_EQ(0, empty.Match(std::string("")));
}

TEST_F(ExpEmptyTest_115, EmptyRegExMatchReturnsZeroForNonEmptyString_115) {
    const RegEx& empty = Exp::Empty();
    // Match on non-empty string should still return 0 (matches zero chars)
    EXPECT_EQ(0, empty.Match(std::string("hello")));
}

// ===== RegEx Constructor Tests =====

TEST_F(RegExTest_115, DefaultConstructor_115) {
    RegEx r;
    // Default (empty) regex
    EXPECT_TRUE(r.Matches(std::string("")));
    EXPECT_FALSE(r.Matches('a'));
}

TEST_F(RegExTest_115, CharConstructorMatchesSameChar_115) {
    RegEx r('a');
    EXPECT_TRUE(r.Matches('a'));
    EXPECT_FALSE(r.Matches('b'));
    EXPECT_FALSE(r.Matches('A'));
}

TEST_F(RegExTest_115, CharConstructorMatchesString_115) {
    RegEx r('a');
    EXPECT_TRUE(r.Matches(std::string("a")));
    EXPECT_FALSE(r.Matches(std::string("b")));
    EXPECT_FALSE(r.Matches(std::string("")));
}

TEST_F(RegExTest_115, CharConstructorMatchReturnsOne_115) {
    RegEx r('a');
    EXPECT_EQ(1, r.Match(std::string("a")));
    EXPECT_EQ(1, r.Match(std::string("abc")));
}

TEST_F(RegExTest_115, CharConstructorMatchReturnsNegativeOnMismatch_115) {
    RegEx r('a');
    EXPECT_EQ(-1, r.Match(std::string("b")));
    EXPECT_EQ(-1, r.Match(std::string("")));
}

TEST_F(RegExTest_115, RangeConstructorMatchesWithinRange_115) {
    RegEx r('a', 'z');
    EXPECT_TRUE(r.Matches('a'));
    EXPECT_TRUE(r.Matches('m'));
    EXPECT_TRUE(r.Matches('z'));
    EXPECT_FALSE(r.Matches('A'));
    EXPECT_FALSE(r.Matches('0'));
}

TEST_F(RegExTest_115, RangeConstructorBoundaryChars_115) {
    RegEx r('a', 'c');
    EXPECT_TRUE(r.Matches('a'));
    EXPECT_TRUE(r.Matches('b'));
    EXPECT_TRUE(r.Matches('c'));
    EXPECT_FALSE(r.Matches('d'));
    EXPECT_FALSE(r.Matches('`')); // char before 'a'
}

TEST_F(RegExTest_115, RangeConstructorMatchReturnsOne_115) {
    RegEx r('0', '9');
    EXPECT_EQ(1, r.Match(std::string("5")));
    EXPECT_EQ(1, r.Match(std::string("0abc")));
    EXPECT_EQ(-1, r.Match(std::string("abc")));
}

// ===== Operator Tests =====

TEST_F(RegExTest_115, OrOperatorMatchesEither_115) {
    RegEx a('a');
    RegEx b('b');
    RegEx combined = a | b;
    EXPECT_TRUE(combined.Matches('a'));
    EXPECT_TRUE(combined.Matches('b'));
    EXPECT_FALSE(combined.Matches('c'));
}

TEST_F(RegExTest_115, OrOperatorMatchReturnValue_115) {
    RegEx a('a');
    RegEx b('b');
    RegEx combined = a | b;
    EXPECT_EQ(1, combined.Match(std::string("a")));
    EXPECT_EQ(1, combined.Match(std::string("b")));
    EXPECT_EQ(-1, combined.Match(std::string("c")));
}

TEST_F(RegExTest_115, AndOperatorMatchesBoth_115) {
    RegEx range('a', 'z');
    RegEx specific('m');
    RegEx combined = range & specific;
    EXPECT_TRUE(combined.Matches('m'));
    EXPECT_FALSE(combined.Matches('a'));
    EXPECT_FALSE(combined.Matches('A'));
}

TEST_F(RegExTest_115, NotOperatorNegatesMatch_115) {
    RegEx a('a');
    RegEx notA = !a;
    EXPECT_FALSE(notA.Matches('a'));
    EXPECT_TRUE(notA.Matches('b'));
    EXPECT_TRUE(notA.Matches('z'));
}

TEST_F(RegExTest_115, NotOperatorMatchReturnValue_115) {
    RegEx a('a');
    RegEx notA = !a;
    EXPECT_EQ(-1, notA.Match(std::string("a")));
    EXPECT_EQ(1, notA.Match(std::string("b")));
}

TEST_F(RegExTest_115, SequenceOperator_115) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_TRUE(seq.Matches(std::string("ab")));
    EXPECT_FALSE(seq.Matches(std::string("a")));
    EXPECT_FALSE(seq.Matches(std::string("ba")));
    EXPECT_FALSE(seq.Matches(std::string("")));
}

TEST_F(RegExTest_115, SequenceOperatorMatchReturnsTwo_115) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_EQ(2, seq.Match(std::string("ab")));
    EXPECT_EQ(2, seq.Match(std::string("abc")));
    EXPECT_EQ(-1, seq.Match(std::string("a")));
    EXPECT_EQ(-1, seq.Match(std::string("ba")));
}

// ===== Complex Combination Tests =====

TEST_F(RegExTest_115, OrOfRanges_115) {
    RegEx lower('a', 'z');
    RegEx upper('A', 'Z');
    RegEx alpha = lower | upper;
    EXPECT_TRUE(alpha.Matches('a'));
    EXPECT_TRUE(alpha.Matches('Z'));
    EXPECT_FALSE(alpha.Matches('0'));
}

TEST_F(RegExTest_115, SequenceOfThreeChars_115) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx seq = a + b + c;
    EXPECT_TRUE(seq.Matches(std::string("abc")));
    EXPECT_EQ(3, seq.Match(std::string("abc")));
    EXPECT_EQ(3, seq.Match(std::string("abcd")));
    EXPECT_EQ(-1, seq.Match(std::string("ab")));
}

TEST_F(RegExTest_115, NotOfRange_115) {
    RegEx digit('0', '9');
    RegEx nonDigit = !digit;
    EXPECT_TRUE(nonDigit.Matches('a'));
    EXPECT_FALSE(nonDigit.Matches('5'));
}

TEST_F(RegExTest_115, AndWithRange_115) {
    RegEx lower('a', 'z');
    RegEx vowel_a('a');
    RegEx vowel_e('e');
    RegEx vowels = vowel_a | vowel_e;
    RegEx lowerVowels = lower & vowels;
    EXPECT_TRUE(lowerVowels.Matches('a'));
    EXPECT_TRUE(lowerVowels.Matches('e'));
    EXPECT_FALSE(lowerVowels.Matches('b'));
    EXPECT_FALSE(lowerVowels.Matches('A'));
}

// ===== Edge Cases =====

TEST_F(RegExTest_115, MatchOnEmptyStringWithCharRegEx_115) {
    RegEx a('a');
    EXPECT_EQ(-1, a.Match(std::string("")));
    EXPECT_FALSE(a.Matches(std::string("")));
}

TEST_F(RegExTest_115, MatchOnEmptyStringWithEmptyRegEx_115) {
    RegEx empty;
    EXPECT_EQ(0, empty.Match(std::string("")));
    EXPECT_TRUE(empty.Matches(std::string("")));
}

TEST_F(RegExTest_115, SpecialCharsMatch_115) {
    RegEx tab('\t');
    EXPECT_TRUE(tab.Matches('\t'));
    EXPECT_FALSE(tab.Matches(' '));
    EXPECT_EQ(1, tab.Match(std::string("\t")));
}

TEST_F(RegExTest_115, NullCharMatch_115) {
    RegEx null_char('\0');
    EXPECT_TRUE(null_char.Matches('\0'));
    EXPECT_FALSE(null_char.Matches('a'));
}

TEST_F(RegExTest_115, SingleCharRangeMatchesExactly_115) {
    RegEx r('m', 'm');
    EXPECT_TRUE(r.Matches('m'));
    EXPECT_FALSE(r.Matches('l'));
    EXPECT_FALSE(r.Matches('n'));
}

TEST_F(RegExTest_115, CharMatchInLongerString_115) {
    RegEx a('a');
    // Match should return 1 even if string is longer (matches first char)
    EXPECT_EQ(1, a.Match(std::string("abcdef")));
}

TEST_F(RegExTest_115, MatchesStringExactLength_115) {
    RegEx a('a');
    // Matches checks if the entire string matches (single char matches single char string)
    EXPECT_TRUE(a.Matches(std::string("a")));
    // Multi-char string should not be considered a full match for single char regex
    EXPECT_FALSE(a.Matches(std::string("aa")));
}

TEST_F(RegExTest_115, DoubleNegation_115) {
    RegEx a('a');
    RegEx notNotA = !(!a);
    EXPECT_TRUE(notNotA.Matches('a'));
    EXPECT_FALSE(notNotA.Matches('b'));
}

TEST_F(RegExTest_115, OrWithSelf_115) {
    RegEx a('a');
    RegEx aOrA = a | a;
    EXPECT_TRUE(aOrA.Matches('a'));
    EXPECT_FALSE(aOrA.Matches('b'));
}

TEST_F(RegExTest_115, SequenceWithEmpty_115) {
    RegEx a('a');
    RegEx empty;
    RegEx seq = empty + a;
    EXPECT_EQ(1, seq.Match(std::string("a")));
    EXPECT_TRUE(seq.Matches(std::string("a")));
}

}  // namespace YAML
