#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class RegExTest_123 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



// Test normal operation of AlphaNumeric matching with valid characters

TEST_F(RegExTest_123, AlphaNumeric_MatchesValidChars_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_TRUE(alphaNumeric.Matches('a'));

    EXPECT_TRUE(alphaNumeric.Matches('Z'));

    EXPECT_TRUE(alphaNumeric.Matches('0'));

}



// Test normal operation of AlphaNumeric matching with invalid characters

TEST_F(RegExTest_123, AlphaNumeric_MatchesInvalidChars_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_FALSE(alphaNumeric.Matches('@'));

    EXPECT_FALSE(alphaNumeric.Matches('['));

    EXPECT_FALSE(alphaNumeric.Matches(' '));

}



// Test boundary conditions for single character matching

TEST_F(RegExTest_123, AlphaNumeric_MatchesBoundaryChars_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_TRUE(alphaNumeric.Matches('a'));

    EXPECT_TRUE(alphaNumeric.Matches('z'));

    EXPECT_TRUE(alphaNumeric.Matches('A'));

    EXPECT_TRUE(alphaNumeric.Matches('Z'));

    EXPECT_TRUE(alphaNumeric.Matches('0'));

    EXPECT_TRUE(alphaNumeric.Matches('9'));

}



// Test normal operation of AlphaNumeric matching with strings containing valid characters

TEST_F(RegExTest_123, AlphaNumeric_MatchValidString_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_EQ(alphaNumeric.Match("aZ0"), 3);

    EXPECT_EQ(alphaNumeric.Match("abcXYZ123"), 9);

}



// Test normal operation of AlphaNumeric matching with strings containing invalid characters

TEST_F(RegExTest_123, AlphaNumeric_MatchInvalidString_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_EQ(alphaNumeric.Match("aZ0@"), 3);

    EXPECT_EQ(alphaNumeric.Match("abcXYZ!"), 6);

}



// Test boundary conditions for string matching

TEST_F(RegExTest_123, AlphaNumeric_MatchBoundaryString_123) {

    const RegEx& alphaNumeric = AlphaNumeric();

    EXPECT_EQ(alphaNumeric.Match(""), 0); // Empty string

    EXPECT_EQ(alphaNumeric.Match("a"), 1); // Single valid character

    EXPECT_EQ(alphaNumeric.Match("@"), 0); // Single invalid character

}
