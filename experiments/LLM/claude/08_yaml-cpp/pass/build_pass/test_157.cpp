#include <gtest/gtest.h>
#include <string>
#include "regex_yaml.h"

namespace YAML {

class RegExTest_157 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(RegExTest_157, DefaultConstructor_157) {
    RegEx re;
    // Default constructor creates REGEX_EMPTY, should not match anything meaningful
    // An empty regex behavior: Match on empty string
    std::string empty_str = "";
    // We just verify it doesn't crash
    re.Match(empty_str);
}

TEST_F(RegExTest_157, CharConstructor_MatchesSingleChar_157) {
    RegEx re('a');
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_FALSE(re.Matches('b'));
    EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_157, CharConstructor_MatchesString_157) {
    RegEx re('a');
    EXPECT_TRUE(re.Matches(std::string("a")));
    EXPECT_FALSE(re.Matches(std::string("b")));
}

TEST_F(RegExTest_157, CharConstructor_MatchReturnValue_157) {
    RegEx re('a');
    EXPECT_EQ(1, re.Match(std::string("a")));
    EXPECT_EQ(1, re.Match(std::string("abc")));
    EXPECT_EQ(-1, re.Match(std::string("b")));
}

TEST_F(RegExTest_157, RangeConstructor_MatchesInRange_157) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_TRUE(re.Matches('m'));
    EXPECT_TRUE(re.Matches('z'));
    EXPECT_FALSE(re.Matches('A'));
    EXPECT_FALSE(re.Matches('0'));
}

TEST_F(RegExTest_157, RangeConstructor_BoundaryChars_157) {
    RegEx re('a', 'c');
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_TRUE(re.Matches('b'));
    EXPECT_TRUE(re.Matches('c'));
    EXPECT_FALSE(re.Matches('d'));
    EXPECT_FALSE(re.Matches('`')); // char before 'a'
}

TEST_F(RegExTest_157, RangeConstructor_MatchReturnValue_157) {
    RegEx re('0', '9');
    EXPECT_EQ(1, re.Match(std::string("5")));
    EXPECT_EQ(1, re.Match(std::string("0abc")));
    EXPECT_EQ(-1, re.Match(std::string("abc")));
}

TEST_F(RegExTest_157, StringConstructor_SeqOp_157) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_TRUE(re.Matches(std::string("abc")));
    EXPECT_FALSE(re.Matches(std::string("ab")));
    EXPECT_FALSE(re.Matches(std::string("abd")));
}

TEST_F(RegExTest_157, StringConstructor_SeqOp_MatchReturnValue_157) {
    RegEx re("hello", REGEX_SEQ);
    EXPECT_EQ(5, re.Match(std::string("hello")));
    EXPECT_EQ(5, re.Match(std::string("helloworld")));
    EXPECT_EQ(-1, re.Match(std::string("hell")));
}

TEST_F(RegExTest_157, StringConstructor_OrOp_157) {
    RegEx re("abc", REGEX_OR);
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_TRUE(re.Matches('b'));
    EXPECT_TRUE(re.Matches('c'));
    EXPECT_FALSE(re.Matches('d'));
}

// ==================== Operator Tests ====================

TEST_F(RegExTest_157, NotOperator_NegatesMatch_157) {
    RegEx re('a');
    RegEx notRe = !re;
    EXPECT_FALSE(notRe.Matches('a'));
    EXPECT_TRUE(notRe.Matches('b'));
    EXPECT_TRUE(notRe.Matches('z'));
}

TEST_F(RegExTest_157, NotOperator_NegatesRange_157) {
    RegEx range('a', 'z');
    RegEx notRange = !range;
    EXPECT_FALSE(notRange.Matches('a'));
    EXPECT_FALSE(notRange.Matches('m'));
    EXPECT_FALSE(notRange.Matches('z'));
    EXPECT_TRUE(notRange.Matches('A'));
    EXPECT_TRUE(notRange.Matches('0'));
}

TEST_F(RegExTest_157, NotOperator_DoubleNegation_157) {
    RegEx re('x');
    RegEx doubleNot = !(!re);
    EXPECT_TRUE(doubleNot.Matches('x'));
    EXPECT_FALSE(doubleNot.Matches('y'));
}

TEST_F(RegExTest_157, NotOperator_MatchReturnValue_157) {
    RegEx re('a');
    RegEx notRe = !re;
    EXPECT_EQ(1, notRe.Match(std::string("b")));
    EXPECT_EQ(-1, notRe.Match(std::string("a")));
}

TEST_F(RegExTest_157, OrOperator_MatchesEither_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx orRe = a | b;
    EXPECT_TRUE(orRe.Matches('a'));
    EXPECT_TRUE(orRe.Matches('b'));
    EXPECT_FALSE(orRe.Matches('c'));
}

TEST_F(RegExTest_157, OrOperator_MatchReturnValue_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx orRe = a | b;
    EXPECT_EQ(1, orRe.Match(std::string("a")));
    EXPECT_EQ(1, orRe.Match(std::string("b")));
    EXPECT_EQ(-1, orRe.Match(std::string("c")));
}

TEST_F(RegExTest_157, AndOperator_MatchesBoth_157) {
    RegEx range('a', 'z');
    RegEx specific('m');
    RegEx andRe = range & specific;
    EXPECT_TRUE(andRe.Matches('m'));
    EXPECT_FALSE(andRe.Matches('a'));
    EXPECT_FALSE(andRe.Matches('A'));
}

TEST_F(RegExTest_157, AndOperator_NoOverlap_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx andRe = a & b;
    EXPECT_FALSE(andRe.Matches('a'));
    EXPECT_FALSE(andRe.Matches('b'));
    EXPECT_FALSE(andRe.Matches('c'));
}

TEST_F(RegExTest_157, PlusOperator_Sequence_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_TRUE(seq.Matches(std::string("ab")));
    EXPECT_FALSE(seq.Matches(std::string("a")));
    EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST_F(RegExTest_157, PlusOperator_SequenceMatchReturnValue_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_EQ(2, seq.Match(std::string("ab")));
    EXPECT_EQ(2, seq.Match(std::string("abc")));
    EXPECT_EQ(-1, seq.Match(std::string("a")));
    EXPECT_EQ(-1, seq.Match(std::string("ba")));
}

TEST_F(RegExTest_157, PlusOperator_ThreeCharSequence_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx seq = a + b + c;
    EXPECT_EQ(3, seq.Match(std::string("abc")));
    EXPECT_EQ(3, seq.Match(std::string("abcd")));
    EXPECT_EQ(-1, seq.Match(std::string("ab")));
    EXPECT_EQ(-1, seq.Match(std::string("abd")));
}

// ==================== Empty String / Edge Cases ====================

TEST_F(RegExTest_157, MatchOnEmptyString_157) {
    RegEx re('a');
    EXPECT_EQ(-1, re.Match(std::string("")));
    EXPECT_FALSE(re.Matches(std::string("")));
}

TEST_F(RegExTest_157, RangeMatchOnEmptyString_157) {
    RegEx re('a', 'z');
    EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST_F(RegExTest_157, NotOperator_OnEmptyString_157) {
    RegEx re('a');
    RegEx notRe = !re;
    // Empty string - no character to match against
    EXPECT_EQ(-1, notRe.Match(std::string("")));
}

// ==================== Complex Combinations ====================

TEST_F(RegExTest_157, ComplexOrWithRange_157) {
    RegEx digits('0', '9');
    RegEx letters('a', 'z');
    RegEx alphanumLower = digits | letters;
    EXPECT_TRUE(alphanumLower.Matches('5'));
    EXPECT_TRUE(alphanumLower.Matches('m'));
    EXPECT_FALSE(alphanumLower.Matches('A'));
    EXPECT_FALSE(alphanumLower.Matches('!'));
}

TEST_F(RegExTest_157, NotWithOr_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx orRe = a | b;
    RegEx notOrRe = !orRe;
    EXPECT_FALSE(notOrRe.Matches('a'));
    EXPECT_FALSE(notOrRe.Matches('b'));
    EXPECT_TRUE(notOrRe.Matches('c'));
}

TEST_F(RegExTest_157, SequenceWithRange_157) {
    RegEx letter('a', 'z');
    RegEx digit('0', '9');
    RegEx seq = letter + digit;
    EXPECT_EQ(2, seq.Match(std::string("a1")));
    EXPECT_EQ(2, seq.Match(std::string("z9")));
    EXPECT_EQ(-1, seq.Match(std::string("1a")));
    EXPECT_EQ(-1, seq.Match(std::string("aa")));
}

TEST_F(RegExTest_157, AndWithRange_157) {
    RegEx lowerRange('a', 'f');
    RegEx upperRange('d', 'z');
    RegEx andRe = lowerRange & upperRange;
    // Overlap is d, e, f
    EXPECT_TRUE(andRe.Matches('d'));
    EXPECT_TRUE(andRe.Matches('e'));
    EXPECT_TRUE(andRe.Matches('f'));
    EXPECT_FALSE(andRe.Matches('a'));
    EXPECT_FALSE(andRe.Matches('g'));
}

TEST_F(RegExTest_157, CharConstructor_SpecialChars_157) {
    RegEx re('\n');
    EXPECT_TRUE(re.Matches('\n'));
    EXPECT_FALSE(re.Matches('\t'));
    EXPECT_FALSE(re.Matches(' '));
}

TEST_F(RegExTest_157, CharConstructor_NullChar_157) {
    RegEx re('\0');
    EXPECT_TRUE(re.Matches('\0'));
    EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_157, RangeConstructor_SingleCharRange_157) {
    RegEx re('m', 'm');
    EXPECT_TRUE(re.Matches('m'));
    EXPECT_FALSE(re.Matches('l'));
    EXPECT_FALSE(re.Matches('n'));
}

TEST_F(RegExTest_157, StringConstructor_SingleCharSeq_157) {
    RegEx re("x", REGEX_SEQ);
    EXPECT_TRUE(re.Matches(std::string("x")));
    EXPECT_FALSE(re.Matches(std::string("y")));
    EXPECT_EQ(1, re.Match(std::string("x")));
}

TEST_F(RegExTest_157, StringConstructor_EmptyString_157) {
    RegEx re("", REGEX_SEQ);
    // Empty sequence - should match with length 0
    EXPECT_EQ(0, re.Match(std::string("anything")));
}

TEST_F(RegExTest_157, MatchReturnsLongestForOr_157) {
    RegEx ab("ab", REGEX_SEQ);
    RegEx abc("abc", REGEX_SEQ);
    RegEx orRe = ab | abc;
    // Or should return the longer match if both match
    int result = orRe.Match(std::string("abcd"));
    EXPECT_GE(result, 2); // At least 2
}

TEST_F(RegExTest_157, OrOperator_MultipleChained_157) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx orRe = a | b | c;
    EXPECT_TRUE(orRe.Matches('a'));
    EXPECT_TRUE(orRe.Matches('b'));
    EXPECT_TRUE(orRe.Matches('c'));
    EXPECT_FALSE(orRe.Matches('d'));
}

TEST_F(RegExTest_157, MatchesStringLongerThanPattern_157) {
    RegEx re('a');
    // Matches checks if the entire source matches starting from beginning
    // For a single char regex, "ab" should not "Match" fully but Match returns 1
    EXPECT_EQ(1, re.Match(std::string("ab")));
    // Matches should check if the regex matches exactly
    EXPECT_FALSE(re.Matches(std::string("ab")));
}

TEST_F(RegExTest_157, SeqStringConstructor_PartialMatch_157) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_EQ(-1, re.Match(std::string("ab")));
    EXPECT_EQ(-1, re.Match(std::string("abd")));
    EXPECT_EQ(3, re.Match(std::string("abcdef")));
}

}  // namespace YAML
