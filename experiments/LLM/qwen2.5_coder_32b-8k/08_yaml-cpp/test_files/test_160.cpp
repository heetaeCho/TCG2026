#include <gtest/gtest.h>

#include "regex_yaml.h"



using namespace YAML;



// Test Fixture for RegEx class

class RegExTest_160 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any, can go here.

    }



    void TearDown() override {

        // Teardown code, if any, can go here.

    }

};



// Test normal operation of the + operator

TEST_F(RegExTest_160, PlusOperatorCombinesTwoRegex_160) {

    RegEx regex1('a');

    RegEx regex2('b');

    RegEx combined = regex1 + regex2;

    EXPECT_TRUE(combined.Matches("ab"));

}



// Test boundary condition with empty regex

TEST_F(RegExTest_160, PlusOperatorWithEmptyRegex_160) {

    RegEx regex1;

    RegEx regex2('a');

    RegEx combined = regex1 + regex2;

    EXPECT_TRUE(combined.Matches("a"));

}



// Test boundary condition with two empty regex

TEST_F(RegExTest_160, PlusOperatorWithTwoEmptyRegex_160) {

    RegEx regex1;

    RegEx regex2;

    RegEx combined = regex1 + regex2;

    EXPECT_TRUE(combined.Matches(""));

}



// Test exceptional case where Matches fails for sequence

TEST_F(RegExTest_160, PlusOperatorMatchesFailsForSequence_160) {

    RegEx regex1('a');

    RegEx regex2('b');

    RegEx combined = regex1 + regex2;

    EXPECT_FALSE(combined.Matches("ac"));

}



// Test boundary condition with single character sequence

TEST_F(RegExTest_160, PlusOperatorSingleCharSequence_160) {

    RegEx regex1('a');

    RegEx combined = regex1 + regex1;

    EXPECT_TRUE(combined.Matches("aa"));

}



// Test normal operation of the + operator with string matching

TEST_F(RegExTest_160, PlusOperatorStringMatching_160) {

    RegEx regex1("abc", REGEX_MATCH);

    RegEx regex2("def", REGEX_MATCH);

    RegEx combined = regex1 + regex2;

    EXPECT_TRUE(combined.Matches("abcdef"));

}



// Test boundary condition with empty string in sequence

TEST_F(RegExTest_160, PlusOperatorEmptyStringInSequence_160) {

    RegEx regex1("");

    RegEx regex2("abc", REGEX_MATCH);

    RegEx combined = regex1 + regex2;

    EXPECT_TRUE(combined.Matches("abc"));

}



// Test exceptional case with non-matching sequence

TEST_F(RegExTest_160, PlusOperatorNonMatchingSequence_160) {

    RegEx regex1("abc", REGEX_MATCH);

    RegEx regex2("def", REGEX_MATCH);

    RegEx combined = regex1 + regex2;

    EXPECT_FALSE(combined.Matches("abcd"));

}
