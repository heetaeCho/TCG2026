#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regeximpl.h"

#include "regex_yaml.h"



using namespace YAML;



class RegExTest_111 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegExTest_111, MatchesSingleChar_111) {

    RegEx regex('a');

    EXPECT_TRUE(regex.Matches("a"));

    EXPECT_FALSE(regex.Matches("b"));

}



TEST_F(RegExTest_111, MatchesCharRange_111) {

    RegEx regex('a', 'z');

    EXPECT_TRUE(regex.Matches("a"));

    EXPECT_TRUE(regex.Matches("m"));

    EXPECT_TRUE(regex.Matches("z"));

    EXPECT_FALSE(regex.Matches("{"));

}



TEST_F(RegExTest_111, MatchesString_111) {

    RegEx regex("abc", REGEX_MATCH);

    EXPECT_TRUE(regex.Matches("abc"));

    EXPECT_FALSE(regex.Matches("abcd"));

    EXPECT_FALSE(regex.Matches("ab"));

}



TEST_F(RegExTest_111, MatchesEmptyRegex_111) {

    RegEx regex;

    EXPECT_TRUE(regex.Matches(""));

    EXPECT_FALSE(regex.Matches("a"));

}



TEST_F(RegExTest_111, NotOperator_111) {

    RegEx regex('a');

    RegEx notRegex = !regex;

    EXPECT_FALSE(notRegex.Matches("a"));

    EXPECT_TRUE(notRegex.Matches("b"));

}



TEST_F(RegExTest_111, OrOperator_111) {

    RegEx regexA('a');

    RegEx regexB('b');

    RegEx orRegex = regexA | regexB;

    EXPECT_TRUE(orRegex.Matches("a"));

    EXPECT_TRUE(orRegex.Matches("b"));

    EXPECT_FALSE(orRegex.Matches("c"));

}



TEST_F(RegExTest_111, AndOperator_111) {

    RegEx regexA('a');

    RegEx regexB('b');

    RegEx andRegex = regexA & regexB;

    // Assuming the behavior of AND operator is a sequence

    EXPECT_TRUE(andRegex.Matches("ab"));

    EXPECT_FALSE(andRegex.Matches("a"));

    EXPECT_FALSE(andRegex.Matches("b"));

}



TEST_F(RegExTest_111, PlusOperator_111) {

    RegEx regexA('a');

    RegEx plusRegex = regexA + regexA;

    EXPECT_TRUE(plusRegex.Matches("aa"));

    EXPECT_FALSE(plusRegex.Matches("a"));

    EXPECT_FALSE(plusRegex.Matches("b"));

}



TEST_F(RegExTest_111, MatchSingleChar_111) {

    RegEx regex('a');

    EXPECT_EQ(regex.Match("a"), 0);

    EXPECT_EQ(regex.Match("b"), -1);

}



TEST_F(RegExTest_111, MatchString_111) {

    RegEx regex("abc", REGEX_MATCH);

    EXPECT_EQ(regex.Match("abc"), 0);

    EXPECT_EQ(regex.Match("abcd"), -1);

    EXPECT_EQ(regex.Match("ab"), -1);

}



TEST_F(RegExTest_111, MatchEmptyRegex_111) {

    RegEx regex;

    EXPECT_EQ(regex.Match(""), 0);

    EXPECT_EQ(regex.Match("a"), -1);

}
