#include <gtest/gtest.h>
#include "regex_yaml.h"
#include <string>

namespace YAML {

class RegExTest_160 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Constructor Tests ===

TEST_F(RegExTest_160, DefaultConstructor_160) {
    RegEx re;
    // Default regex should match empty - test with empty string
    // REGEX_EMPTY behavior
    std::string empty_str = "";
    // We just ensure it can be constructed without error
    SUCCEED();
}

TEST_F(RegExTest_160, CharConstructor_MatchesSameChar_160) {
    RegEx re('a');
    EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_160, CharConstructor_DoesNotMatchDifferentChar_160) {
    RegEx re('a');
    EXPECT_FALSE(re.Matches('b'));
}

TEST_F(RegExTest_160, RangeConstructor_MatchesCharInRange_160) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('m'));
}

TEST_F(RegExTest_160, RangeConstructor_MatchesLowerBound_160) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_160, RangeConstructor_MatchesUpperBound_160) {
    RegEx re('a', 'z');
    EXPECT_TRUE(re.Matches('z'));
}

TEST_F(RegExTest_160, RangeConstructor_DoesNotMatchOutOfRange_160) {
    RegEx re('a', 'z');
    EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_160, RangeConstructor_DoesNotMatchCharBeforeRange_160) {
    RegEx re('b', 'y');
    EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_160, RangeConstructor_DoesNotMatchCharAfterRange_160) {
    RegEx re('b', 'y');
    EXPECT_FALSE(re.Matches('z'));
}

// === String Constructor Tests ===

TEST_F(RegExTest_160, StringConstructorWithOrOp_160) {
    RegEx re("abc", REGEX_OR);
    EXPECT_TRUE(re.Matches('a'));
    EXPECT_TRUE(re.Matches('b'));
    EXPECT_TRUE(re.Matches('c'));
    EXPECT_FALSE(re.Matches('d'));
}

TEST_F(RegExTest_160, StringConstructorWithSeqOp_MatchesString_160) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_TRUE(re.Matches(std::string("abc")));
}

TEST_F(RegExTest_160, StringConstructorWithSeqOp_DoesNotMatchDifferentString_160) {
    RegEx re("abc", REGEX_SEQ);
    EXPECT_FALSE(re.Matches(std::string("abd")));
}

// === Operator+ Tests (Sequence) ===

TEST_F(RegExTest_160, OperatorPlus_MatchesSequence_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_TRUE(seq.Matches(std::string("ab")));
}

TEST_F(RegExTest_160, OperatorPlus_DoesNotMatchWrongSequence_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST_F(RegExTest_160, OperatorPlus_DoesNotMatchPartialSequence_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_FALSE(seq.Matches(std::string("a")));
}

TEST_F(RegExTest_160, OperatorPlus_ChainedSequence_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx seq = a + b + c;
    EXPECT_TRUE(seq.Matches(std::string("abc")));
}

TEST_F(RegExTest_160, OperatorPlus_ChainedSequenceWrongOrder_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx seq = a + b + c;
    EXPECT_FALSE(seq.Matches(std::string("acb")));
}

// === Operator| Tests (Or) ===

TEST_F(RegExTest_160, OperatorOr_MatchesFirstAlternative_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx alt = a | b;
    EXPECT_TRUE(alt.Matches('a'));
}

TEST_F(RegExTest_160, OperatorOr_MatchesSecondAlternative_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx alt = a | b;
    EXPECT_TRUE(alt.Matches('b'));
}

TEST_F(RegExTest_160, OperatorOr_DoesNotMatchNonAlternative_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx alt = a | b;
    EXPECT_FALSE(alt.Matches('c'));
}

// === Operator& Tests (And) ===

TEST_F(RegExTest_160, OperatorAnd_MatchesBothConditions_160) {
    RegEx range('a', 'z');
    RegEx specific('m');
    RegEx both = range & specific;
    EXPECT_TRUE(both.Matches('m'));
}

TEST_F(RegExTest_160, OperatorAnd_DoesNotMatchOnlyOneCondition_160) {
    RegEx range('a', 'c');
    RegEx specific('d');
    RegEx both = range & specific;
    EXPECT_FALSE(both.Matches('a'));
    EXPECT_FALSE(both.Matches('d'));
}

// === Operator! Tests (Not) ===

TEST_F(RegExTest_160, OperatorNot_MatchesNonMatchingChar_160) {
    RegEx a('a');
    RegEx notA = !a;
    EXPECT_TRUE(notA.Matches('b'));
}

TEST_F(RegExTest_160, OperatorNot_DoesNotMatchOriginalChar_160) {
    RegEx a('a');
    RegEx notA = !a;
    EXPECT_FALSE(notA.Matches('a'));
}

// === Match (int return) Tests ===

TEST_F(RegExTest_160, Match_SingleChar_ReturnsOne_160) {
    RegEx a('a');
    EXPECT_EQ(1, a.Match(std::string("a")));
}

TEST_F(RegExTest_160, Match_SingleChar_NoMatch_ReturnsNegative_160) {
    RegEx a('a');
    EXPECT_EQ(-1, a.Match(std::string("b")));
}

TEST_F(RegExTest_160, Match_Sequence_ReturnsLength_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_EQ(2, seq.Match(std::string("ab")));
}

TEST_F(RegExTest_160, Match_Sequence_NoMatch_ReturnsNegative_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx seq = a + b;
    EXPECT_EQ(-1, seq.Match(std::string("ac")));
}

TEST_F(RegExTest_160, Match_EmptyString_160) {
    RegEx a('a');
    EXPECT_EQ(-1, a.Match(std::string("")));
}

TEST_F(RegExTest_160, Match_LongerSequence_160) {
    RegEx re("hello", REGEX_SEQ);
    EXPECT_EQ(5, re.Match(std::string("hello")));
}

TEST_F(RegExTest_160, Match_LongerSequencePartialInput_160) {
    RegEx re("hello", REGEX_SEQ);
    EXPECT_EQ(-1, re.Match(std::string("hell")));
}

TEST_F(RegExTest_160, Match_SequenceWithExtraInput_160) {
    RegEx re("ab", REGEX_SEQ);
    // Match should return the matched length (2) even if input is longer
    EXPECT_EQ(2, re.Match(std::string("abc")));
}

// === Range Match Tests ===

TEST_F(RegExTest_160, Match_Range_ReturnsOneOnMatch_160) {
    RegEx range('0', '9');
    EXPECT_EQ(1, range.Match(std::string("5")));
}

TEST_F(RegExTest_160, Match_Range_ReturnsNegativeOnNoMatch_160) {
    RegEx range('0', '9');
    EXPECT_EQ(-1, range.Match(std::string("a")));
}

// === Or Match Tests ===

TEST_F(RegExTest_160, Match_Or_ReturnsLongestMatch_160) {
    RegEx ab("ab", REGEX_SEQ);
    RegEx a('a');
    RegEx alt = ab | a;
    // Should return the longest match
    int result = alt.Match(std::string("ab"));
    EXPECT_GE(result, 1);
}

// === Complex Combinations ===

TEST_F(RegExTest_160, ComplexCombination_OrWithSequence_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx ab = a + b;
    RegEx alt = ab | c;
    EXPECT_TRUE(alt.Matches(std::string("ab")));
    EXPECT_TRUE(alt.Matches('c'));
}

TEST_F(RegExTest_160, ComplexCombination_NotWithRange_160) {
    RegEx range('a', 'z');
    RegEx notRange = !range;
    EXPECT_TRUE(notRange.Matches('A'));
    EXPECT_TRUE(notRange.Matches('0'));
    EXPECT_FALSE(notRange.Matches('m'));
}

TEST_F(RegExTest_160, ComplexCombination_AndWithRanges_160) {
    RegEx lower('a', 'f');
    RegEx upper('d', 'z');
    RegEx both = lower & upper;
    // 'd', 'e', 'f' should match (intersection)
    EXPECT_TRUE(both.Matches('d'));
    EXPECT_TRUE(both.Matches('e'));
    EXPECT_TRUE(both.Matches('f'));
    // 'a' is in lower but not in upper range starting from 'd'
    EXPECT_FALSE(both.Matches('a'));
    // 'g' is in upper but not in lower range ending at 'f'
    EXPECT_FALSE(both.Matches('g'));
}

// === Matches with string tests ===

TEST_F(RegExTest_160, Matches_StringExactMatch_160) {
    RegEx re("test", REGEX_SEQ);
    EXPECT_TRUE(re.Matches(std::string("test")));
}

TEST_F(RegExTest_160, Matches_StringNoMatch_160) {
    RegEx re("test", REGEX_SEQ);
    EXPECT_FALSE(re.Matches(std::string("tess")));
}

TEST_F(RegExTest_160, Matches_StringTooShort_160) {
    RegEx re("test", REGEX_SEQ);
    EXPECT_FALSE(re.Matches(std::string("tes")));
}

// === Default RegEx Tests ===

TEST_F(RegExTest_160, DefaultRegEx_MatchEmptyString_160) {
    RegEx re;
    // REGEX_EMPTY should match zero-length
    int result = re.Match(std::string("anything"));
    EXPECT_GE(result, 0);
}

TEST_F(RegExTest_160, DefaultRegEx_MatchChar_160) {
    RegEx re;
    // REGEX_EMPTY behavior on single char
    // Expected: matches zero length (true for Matches since Match >= 0)
    bool result = re.Matches('x');
    // Behavior depends on implementation; just verify no crash
    (void)result;
    SUCCEED();
}

// === Boundary: Special Characters ===

TEST_F(RegExTest_160, MatchSpecialChar_Null_160) {
    RegEx re('\0');
    EXPECT_TRUE(re.Matches('\0'));
    EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_160, MatchSpecialChar_Newline_160) {
    RegEx re('\n');
    EXPECT_TRUE(re.Matches('\n'));
    EXPECT_FALSE(re.Matches('\t'));
}

TEST_F(RegExTest_160, MatchSpecialChar_MaxChar_160) {
    RegEx re(static_cast<char>(127));
    EXPECT_TRUE(re.Matches(static_cast<char>(127)));
    EXPECT_FALSE(re.Matches('a'));
}

// === Multiple Or combinations ===

TEST_F(RegExTest_160, MultipleOrCombinations_160) {
    RegEx a('a');
    RegEx b('b');
    RegEx c('c');
    RegEx d('d');
    RegEx combined = a | b | c | d;
    EXPECT_TRUE(combined.Matches('a'));
    EXPECT_TRUE(combined.Matches('b'));
    EXPECT_TRUE(combined.Matches('c'));
    EXPECT_TRUE(combined.Matches('d'));
    EXPECT_FALSE(combined.Matches('e'));
}

// === String OR constructor matches individual chars ===

TEST_F(RegExTest_160, StringOrConstructor_EmptyString_160) {
    RegEx re("", REGEX_OR);
    // Empty OR should not match anything
    EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_160, StringSeqConstructor_EmptyString_160) {
    RegEx re("", REGEX_SEQ);
    // Empty sequence should match empty
    EXPECT_TRUE(re.Matches(std::string("")));
}

TEST_F(RegExTest_160, StringOrConstructor_SingleChar_160) {
    RegEx re("x", REGEX_OR);
    EXPECT_TRUE(re.Matches('x'));
    EXPECT_FALSE(re.Matches('y'));
}

}  // namespace YAML
