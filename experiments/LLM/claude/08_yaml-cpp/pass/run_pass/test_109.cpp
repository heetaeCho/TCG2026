#include "gtest/gtest.h"
#include "regex_yaml.h"
#include "regeximpl.h"

namespace YAML {

// Test fixture for RegEx tests
class RegExTest_109 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(RegExTest_109, DefaultConstructor_MatchesEmptyString_109) {
    RegEx re;
    // REGEX_EMPTY should match empty strings (match length 0)
    EXPECT_TRUE(re.Matches(std::string("")));
}

TEST_F(RegExTest_109, DefaultConstructor_MatchNonEmptyString_109) {
    RegEx re;
    // REGEX_EMPTY on a non-empty string: Match returns 0 (empty match), Matches returns true
    int result = re.Match(std::string("hello"));
    EXPECT_GE(result, 0);
}

// ==================== Single Character Constructor Tests ====================

TEST_F(RegExTest_109, SingleCharConstructor_MatchesSameChar_109) {
    RegEx re('a');
    EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST_F(RegExTest_109, SingleCharConstructor_DoesNotMatchDifferentChar_109) {
    RegEx re('a');
    EXPECT_FALSE(re.Matches(std::string("b")));
}

TEST_F(RegExTest_109, SingleCharConstructor_MatchReturnsOne_109) {
    RegEx re('a');
    EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_109, SingleCharConstructor_MatchReturnNegativeForMismatch_109) {
    RegEx re('a');
    EXPECT_LT(re.Match(std::string("b")), 0);
}

TEST_F(RegExTest_109, SingleCharConstructor_EmptyStringDoesNotMatch_109) {
    RegEx re('a');
    EXPECT_FALSE(re.Matches(std::string("")));
}

TEST_F(RegExTest_109, SingleCharConstructor_MatchesCharVersion_109) {
    RegEx re('x');
    EXPECT_TRUE(re.Matches('x'));
}

TEST_F(RegExTest_109, SingleCharConstructor_DoesNotMatchDifferentCharVersion_109) {
    RegEx re('x');
    EXPECT_FALSE(re.Matches('y'));
}

TEST_F(RegExTest_109, SingleCharConstructor_MatchesFirstCharOfLongerString_109) {
    RegEx re('h');
    int result = re.Match(std::string("hello"));
    EXPECT_EQ(1, result);
}

// ==================== Range Constructor Tests ====================

TEST_F(RegExTest_109, RangeConstructor_MatchesCharInRange_109) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('m'));
}

TEST_F(RegExTest_109, RangeConstructor_MatchesLowerBound_109) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_109, RangeConstructor_MatchesUpperBound_109) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('z'));
}

TEST_F(RegExTest_109, RangeConstructor_DoesNotMatchOutOfRange_109) {
    RegEx re('a', 'z');
    EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_109, RangeConstructor_DoesNotMatchCharAboveRange_109) {
    RegEx re('a', 'f');
    EXPECT_FALSE(re.Matches('g'));
}

TEST_F(RegExTest_109, RangeConstructor_MatchesStringStartingWithInRange_109) {
    RegEx re('0', '9');
    EXPECT_TRUE(re.Matches(std::string("5abc")));
}

TEST_F(RegExTest_109, RangeConstructor_DoesNotMatchStringStartingOutOfRange_109) {
    RegEx re('0', '9');
    EXPECT_FALSE(re.Matches(std::string("abc")));
}

TEST_F(RegExTest_109, RangeConstructor_MatchReturnsOneForValidChar_109) {
    RegEx re('a', 'z');
    EXPECT_EQ(1, re.Match(std::string("m")));
}

TEST_F(RegExTest_109, RangeConstructor_EmptyStringDoesNotMatch_109) {
    RegEx re('a', 'z');
    EXPECT_FALSE(re.Matches(std::string("")));
}

// ==================== String Constructor Tests ====================

TEST_F(RegExTest_109, StringConstructor_SeqMatchesExactString_109) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_TRUE(re.Matches(std::string("abc")));
}

TEST_F(RegExTest_109, StringConstructor_SeqMatchReturnsLength_109) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_EQ(3, re.Match(std::string("abcdef")));
}

TEST_F(RegExTest_109, StringConstructor_SeqDoesNotMatchPartial_109) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_FALSE(re.Matches(std::string("ab")));
}

TEST_F(RegExTest_109, StringConstructor_SeqDoesNotMatchDifferent_109) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_FALSE(re.Matches(std::string("xyz")));
}

TEST_F(RegExTest_109, StringConstructor_OrMatchesAnyChar_109) {
    RegEx re("abc", REGEX_OR);
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_TRUE(re.Matches('b'));
    EXPECT_TRUE(re.Matches('c'));
}

TEST_F(RegExTest_109, StringConstructor_OrDoesNotMatchOtherChar_109) {
    RegEx re("abc", REGEX_OR);
    EXPECT_FALSE(re.Matches('d'));
}

// ==================== Operator Tests ====================

TEST_F(RegExTest_109, OrOperator_MatchesEither_109) {
    RegEx re1('a');
    RegEx re2('b');
    RegEx combined = re1 | re2;
    EXPECT_TRUE(combined.Matches('a'));
    EXPECT_TRUE(combined.Matches('b'));
    EXPECT_FALSE(combined.Matches('c'));
}

TEST_F(RegExTest_109, AndOperator_MatchesBoth_109) {
    RegEx re1('a', 'z');
    RegEx re2('a', 'f');
    RegEx combined = re1 & re2;
    EXPECT_TRUE(combined.Matches('c'));
    EXPECT_FALSE(combined.Matches('g'));
}

TEST_F(RegExTest_109, NotOperator_InvertsMatch_109) {
    RegEx re('a');
    RegEx notRe = !re;
    EXPECT_FALSE(notRe.Matches('a'));
    EXPECT_TRUE(notRe.Matches('b'));
}

TEST_F(RegExTest_109, SequenceOperator_MatchesConcatenation_109) {
    RegEx re1('a');
    RegEx re2('b');
    RegEx combined = re1 + re2;
    EXPECT_TRUE(combined.Matches(std::string("ab")));
    EXPECT_EQ(2, combined.Match(std::string("ab")));
}

TEST_F(RegExTest_109, SequenceOperator_DoesNotMatchPartial_109) {
    RegEx re1('a');
    RegEx re2('b');
    RegEx combined = re1 + re2;
    EXPECT_FALSE(combined.Matches(std::string("a")));
    EXPECT_FALSE(combined.Matches(std::string("ac")));
}

TEST_F(RegExTest_109, SequenceOperator_MatchPrefixOfLongerString_109) {
    RegEx re1('a');
    RegEx re2('b');
    RegEx combined = re1 + re2;
    int result = combined.Match(std::string("abcd"));
    EXPECT_EQ(2, result);
}

// ==================== Complex Combination Tests ====================

TEST_F(RegExTest_109, ComplexOr_MultipleOptions_109) {
    RegEx re1('a');
    RegEx re2('b');
    RegEx re3('c');
    RegEx combined = re1 | re2 | re3;
    EXPECT_TRUE(combined.Matches('a'));
    EXPECT_TRUE(combined.Matches('b'));
    EXPECT_TRUE(combined.Matches('c'));
    EXPECT_FALSE(combined.Matches('d'));
}

TEST_F(RegExTest_109, NotOperator_EmptyStringBehavior_109) {
    RegEx re('a');
    RegEx notRe = !re;
    // Not operator on empty string
    EXPECT_FALSE(notRe.Matches(std::string("")));
}

TEST_F(RegExTest_109, SequenceOperator_ThreeChars_109) {
    RegEx re1('x');
    RegEx re2('y');
    RegEx re3('z');
    RegEx combined = re1 + re2 + re3;
    EXPECT_TRUE(combined.Matches(std::string("xyz")));
    EXPECT_EQ(3, combined.Match(std::string("xyz")));
    EXPECT_FALSE(combined.Matches(std::string("xy")));
}

// ==================== Boundary and Edge Case Tests ====================

TEST_F(RegExTest_109, SingleChar_NullCharacter_109) {
    RegEx re('\0');
    EXPECT_TRUE(re.Matches('\0'));
    EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_109, Range_SingleCharRange_109) {
    RegEx re('m', 'm');
    EXPECT_TRUE(re.Matches('m'));
    EXPECT_FALSE(re.Matches('l'));
    EXPECT_FALSE(re.Matches('n'));
}

TEST_F(RegExTest_109, Match_ReturnsNegativeForNoMatch_109) {
    RegEx re('z');
    EXPECT_LT(re.Match(std::string("abc")), 0);
}

TEST_F(RegExTest_109, Match_EmptyStringReturnsNegative_109) {
    RegEx re('a');
    EXPECT_LT(re.Match(std::string("")), 0);
}

TEST_F(RegExTest_109, StringConstructor_EmptyStringSeq_109) {
    RegEx re("", REGEX_SEQ);
    // Empty sequence should match (0 length match)
    EXPECT_TRUE(re.Matches(std::string("")));
    EXPECT_EQ(0, re.Match(std::string("abc")));
}

TEST_F(RegExTest_109, OrOperator_WithRange_109) {
    RegEx digits('0', '9');
    RegEx underscore('_');
    RegEx combined = digits | underscore;
    EXPECT_TRUE(combined.Matches('5'));
    EXPECT_TRUE(combined.Matches('_'));
    EXPECT_FALSE(combined.Matches('a'));
}

TEST_F(RegExTest_109, AndOperator_RangeIntersection_109) {
    RegEx range1('a', 'm');
    RegEx range2('f', 'z');
    RegEx combined = range1 & range2;
    // Intersection is 'f' to 'm'
    EXPECT_TRUE(combined.Matches('f'));
    EXPECT_TRUE(combined.Matches('m'));
    EXPECT_FALSE(combined.Matches('a'));
    EXPECT_FALSE(combined.Matches('z'));
}

TEST_F(RegExTest_109, NotOperator_DoubleNegation_109) {
    RegEx re('a');
    RegEx doubleNot = !(!re);
    EXPECT_TRUE(doubleNot.Matches('a'));
    EXPECT_FALSE(doubleNot.Matches('b'));
}

TEST_F(RegExTest_109, SequenceWithOr_CombinedPattern_109) {
    RegEx vowel("aeiou", REGEX_OR);
    RegEx consonant('b');
    RegEx combined = consonant + vowel;
    EXPECT_TRUE(combined.Matches(std::string("ba")));
    EXPECT_TRUE(combined.Matches(std::string("be")));
    EXPECT_FALSE(combined.Matches(std::string("bc")));
}

TEST_F(RegExTest_109, MatchString_ConsistentWithMatches_109) {
    RegEx re('h');
    std::string test = "hello";
    bool matches = re.Matches(test);
    int matchLen = re.Match(test);
    // Matches should be true iff Match >= 0
    EXPECT_EQ(matches, matchLen >= 0);
}

TEST_F(RegExTest_109, Range_DigitRange_109) {
    RegEx re('0', '9');
    for (char c = '0'; c <= '9'; ++c) {
        EXPECT_TRUE(re.Matches(c)) << "Should match digit: " << c;
    }
    EXPECT_FALSE(re.Matches('/'));  // char before '0'
    EXPECT_FALSE(re.Matches(':'));  // char after '9'
}

TEST_F(RegExTest_109, SingleChar_SpecialCharacters_109) {
    RegEx re('\n');
    EXPECT_TRUE(re.Matches('\n'));
    EXPECT_FALSE(re.Matches('\t'));
}

TEST_F(RegExTest_109, SingleChar_SpaceCharacter_109) {
    RegEx re(' ');
    EXPECT_TRUE(re.Matches(' '));
    EXPECT_FALSE(re.Matches('\t'));
}

}  // namespace YAML
