#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exp.h"

#include "regex_yaml.h"



using namespace YAML;

using namespace testing;



class RegExTest_115 : public ::testing::Test {

protected:

    RegExTest_115() {}

};



TEST_F(RegExTest_115, EmptyConstructorReturnsValidObject_115) {

    const RegEx& emptyRegex = Exp::Empty();

    EXPECT_TRUE(emptyRegex.Matches(""));

}



TEST_F(RegExTest_115, CharConstructorMatchesSingleChar_115) {

    RegEx charRegex('a');

    EXPECT_TRUE(charRegex.Matches("a"));

    EXPECT_FALSE(charRegex.Matches("b"));

}



TEST_F(RegExTest_115, RangeConstructorMatchesInRangeChars_115) {

    RegEx rangeRegex('a', 'z');

    EXPECT_TRUE(rangeRegex.Matches("m"));

    EXPECT_FALSE(rangeRegex.Matches("{"));

}



TEST_F(RegExTest_115, StringConstructorMatchesExactString_115) {

    RegEx stringRegex("abc", REGEX_MATCH);

    EXPECT_TRUE(stringRegex.Matches("abc"));

    EXPECT_FALSE(stringRegex.Matches("abcd"));

}



TEST_F(RegExTest_115, NotOperatorInvertsMatch_115) {

    RegEx charRegex('a');

    RegEx notCharRegex = !charRegex;

    EXPECT_TRUE(notCharRegex.Matches("b"));

    EXPECT_FALSE(notCharRegex.Matches("a"));

}



TEST_F(RegExTest_115, OrOperatorMatchesEitherPattern_115) {

    RegEx charARegex('a');

    RegEx charBRegex('b');

    RegEx orRegex = charARegex | charBRegex;

    EXPECT_TRUE(orRegex.Matches("a"));

    EXPECT_TRUE(orRegex.Matches("b"));

    EXPECT_FALSE(orRegex.Matches("c"));

}



TEST_F(RegExTest_115, AndOperatorMatchesBothPatternsSequentially_115) {

    RegEx charARegex('a');

    RegEx charBRegex('b');

    RegEx andRegex = charARegex & charBRegex;

    EXPECT_TRUE(andRegex.Matches("ab"));

    EXPECT_FALSE(andRegex.Matches("ba"));

    EXPECT_FALSE(andRegex.Matches("abc"));

}



TEST_F(RegExTest_115, PlusOperatorMatchesConcatenationOfPatterns_115) {

    RegEx charARegex('a');

    RegEx charBRegex('b');

    RegEx plusRegex = charARegex + charBRegex;

    EXPECT_TRUE(plusRegex.Matches("ab"));

    EXPECT_FALSE(plusRegex.Matches("ba"));

    EXPECT_FALSE(plusRegex.Matches("abc"));

}



TEST_F(RegExTest_115, MatchFunctionReturnsMatchLength_115) {

    RegEx stringRegex("hello", REGEX_MATCH);

    EXPECT_EQ(stringRegex.Match("hello"), 5);

    EXPECT_EQ(stringRegex.Match("world"), -1);

}



TEST_F(RegExTest_115, MatchesEmptyStringWithEmptyConstructor_115) {

    const RegEx& emptyRegex = Exp::Empty();

    EXPECT_TRUE(emptyRegex.Matches(""));

}



TEST_F(RegExTest_115, MatchFunctionReturnsZeroForEmptyMatch_115) {

    const RegEx& emptyRegex = Exp::Empty();

    EXPECT_EQ(emptyRegex.Match(""), 0);

}
