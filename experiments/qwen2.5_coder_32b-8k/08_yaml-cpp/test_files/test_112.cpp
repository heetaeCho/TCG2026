#include <gtest/gtest.h>

#include "regeximpl.h"

#include "stringsource.h"



using namespace YAML;



class RegExTest_112 : public ::testing::Test {

protected:

    RegEx regex;

};



TEST_F(RegExTest_112, Match_EmptyString_ReturnsZero_112) {

    EXPECT_EQ(regex.Match(""), 0);

}



TEST_F(RegExTest_112, Match_SingleCharacterMatch_ReturnsOne_112) {

    RegEx singleCharRegex('a');

    EXPECT_EQ(singleCharRegex.Match("a"), 1);

}



TEST_F(RegExTest_112, Match_SingleCharacterNoMatch_ReturnsZero_112) {

    RegEx singleCharRegex('a');

    EXPECT_EQ(singleCharRegex.Match("b"), 0);

}



TEST_F(RegExTest_112, Match_CharacterRangeMatch_ReturnsOne_112) {

    RegEx rangeRegex('a', 'z');

    EXPECT_EQ(rangeRegex.Match("m"), 1);

}



TEST_F(RegExTest_112, Match_CharacterRangeNoMatch_ReturnsZero_112) {

    RegEx rangeRegex('a', 'z');

    EXPECT_EQ(rangeRegex.Match("A"), 0);

}



TEST_F(RegExTest_112, Match_StringExactMatch_ReturnsStringLength_112) {

    RegEx stringRegex("abc", REGEX_MATCH);

    EXPECT_EQ(stringRegex.Match("abc"), 3);

}



TEST_F(RegExTest_112, Match_StringNoMatch_ReturnsZero_112) {

    RegEx stringRegex("abc", REGEX_MATCH);

    EXPECT_EQ(stringRegex.Match("abcd"), 0);

}



TEST_F(RegExTest_112, Match_SequenceMatch_ReturnsSequenceLength_112) {

    RegEx seqRegex = RegEx('a') + RegEx('b');

    EXPECT_EQ(seqRegex.Match("ab"), 2);

}



TEST_F(RegExTest_112, Match_SequenceNoMatch_ReturnsZero_112) {

    RegEx seqRegex = RegEx('a') + RegEx('b');

    EXPECT_EQ(seqRegex.Match("ba"), 0);

}



TEST_F(RegExTest_112, Match_AlternativeMatchFirstOption_ReturnsOne_112) {

    RegEx altRegex = RegEx('a') | RegEx('b');

    EXPECT_EQ(altRegex.Match("a"), 1);

}



TEST_F(RegExTest_112, Match_AlternativeMatchSecondOption_ReturnsOne_112) {

    RegEx altRegex = RegEx('a') | RegEx('b');

    EXPECT_EQ(altRegex.Match("b"), 1);

}



TEST_F(RegExTest_112, Match_AlternativeNoMatch_ReturnsZero_112) {

    RegEx altRegex = RegEx('a') | RegEx('b');

    EXPECT_EQ(altRegex.Match("c"), 0);

}



TEST_F(RegExTest_112, Match_NegationMatch_ReturnsZero_112) {

    RegEx negRegex = !RegEx('a');

    EXPECT_EQ(negRegex.Match("a"), 0);

}



TEST_F(RegExTest_112, Match_NegationNoMatch_ReturnsOne_112) {

    RegEx negRegex = !RegEx('a');

    EXPECT_EQ(negRegex.Match("b"), 1);

}
