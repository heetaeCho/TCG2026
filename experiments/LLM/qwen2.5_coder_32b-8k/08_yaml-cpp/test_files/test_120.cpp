#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



// Test Fixture for RegEx tests with TEST_ID 120

class RegExTest_120 : public ::testing::Test {

protected:

    const RegEx& blankOrBreakRegex = BlankOrBreak();

};



// Normal operation: Test if the regex matches a space character - TEST_ID 120

TEST_F(RegExTest_120, MatchesSpaceCharacter_120) {

    EXPECT_TRUE(blankOrBreakRegex.Matches(' '));

}



// Normal operation: Test if the regex matches a newline character - TEST_ID 120

TEST_F(RegExTest_120, MatchesNewlineCharacter_120) {

    EXPECT_TRUE(blankOrBreakRegex.Matches('\n'));

}



// Boundary condition: Test if the regex does not match a non-space and non-newline character - TEST_ID 120

TEST_F(RegExTest_120, DoesNotMatchNonSpaceCharacter_120) {

    EXPECT_FALSE(blankOrBreakRegex.Matches('a'));

}



// Normal operation: Test if the regex matches an empty string - TEST_ID 120

TEST_F(RegExTest_120, MatchesEmptyString_120) {

    EXPECT_TRUE(blankOrBreakRegex.Matches(""));

}



// Boundary condition: Test if the regex does not match a non-empty string without spaces or newlines - TEST_ID 120

TEST_F(RegExTest_120, DoesNotMatchNonEmptyStringWithoutSpaces_120) {

    EXPECT_FALSE(blankOrBreakRegex.Matches("abc"));

}



// Normal operation: Test if the regex matches a string with only spaces and newlines - TEST_ID 120

TEST_F(RegExTest_120, MatchesStringWithSpacesAndNewlines_120) {

    EXPECT_TRUE(blankOrBreakRegex.Matches(" \n\n  "));

}



// Exceptional case: Test if the regex does not match a null character - TEST_ID 120

TEST_F(RegExTest_120, DoesNotMatchNullCharacter_120) {

    EXPECT_FALSE(blankOrBreakRegex.Matches('\0'));

}
