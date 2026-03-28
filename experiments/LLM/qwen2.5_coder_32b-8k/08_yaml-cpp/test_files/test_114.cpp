#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regex_yaml.h"



using namespace YAML;



// Test fixture for RegEx class tests.

class RegExTest_114 : public ::testing::Test {

protected:

    RegEx regex;

};



// Test normal operation with a matching single character.

TEST_F(RegExTest_114, MatchSingleCharSuccess_114) {

    RegEx regex('a');

    EXPECT_EQ(regex.Match("a"), 0);

}



// Test normal operation with a non-matching single character.

TEST_F(RegExTest_114, MatchSingleCharFailure_114) {

    RegEx regex('b');

    EXPECT_EQ(regex.Match("a"), -1);

}



// Test normal operation with a matching range of characters.

TEST_F(RegExTest_114, MatchRangeSuccess_114) {

    RegEx regex('a', 'z');

    EXPECT_EQ(regex.Match("m"), 0);

}



// Test normal operation with a non-matching range of characters.

TEST_F(RegExTest_114, MatchRangeFailure_114) {

    RegEx regex('a', 'z');

    EXPECT_EQ(regex.Match("A"), -1);

}



// Test boundary condition with an empty string and empty regex.

TEST_F(RegExTest_114, MatchEmptyStringSuccess_114) {

    RegEx regex;

    EXPECT_EQ(regex.Match(""), 0);

}



// Test boundary condition with an empty string and non-empty regex.

TEST_F(RegExTest_114, MatchEmptyStringFailure_114) {

    RegEx regex('a');

    EXPECT_EQ(regex.Match(""), -1);

}



// Test exceptional case with invalid source (using a null pointer).

TEST_F(RegExTest_114, MatchInvalidSource_114) {

    const char* nullStr = nullptr;

    EXPECT_EQ(regex.Match(nullStr), -1);

}



// Test normal operation with an OR regex.

TEST_F(RegExTest_114, MatchOrSuccess_114) {

    RegEx regex1('a');

    RegEx regex2('b');

    RegEx orRegex = regex1 | regex2;

    EXPECT_EQ(orRegex.Match("a"), 0);

    EXPECT_EQ(orRegex.Match("b"), 0);

}



// Test normal operation with an AND regex.

TEST_F(RegExTest_114, MatchAndSuccess_114) {

    RegEx regex1('a');

    RegEx regex2('b');

    RegEx andRegex = regex1 & regex2;

    EXPECT_EQ(andRegex.Match("ab"), 0);

}



// Test normal operation with a NOT regex.

TEST_F(RegExTest_114, MatchNotSuccess_114) {

    RegEx regex('a');

    RegEx notRegex = !regex;

    EXPECT_EQ(notRegex.Match("b"), 0);

}



// Test exceptional case with a NOT regex matching the character.

TEST_F(RegExTest_114, MatchNotFailure_114) {

    RegEx regex('a');

    RegEx notRegex = !regex;

    EXPECT_EQ(notRegex.Match("a"), -1);

}
