#include <gtest/gtest.h>

#include <cctype> // For std::tolower



namespace Catch {

    char toLower(char c);

}



class StringManipTest_591 : public ::testing::Test {};



TEST_F(StringManipTest_591, LowercaseCharacter_ReturnsSameCharacter_591) {

    EXPECT_EQ(Catch::toLower('a'), 'a');

}



TEST_F(StringManipTest_591, UppercaseCharacter_ReturnsLowercaseEquivalent_591) {

    EXPECT_EQ(Catch::toLower('A'), 'a');

}



TEST_F(StringManipTest_591, NonAlphabeticCharacter_ReturnsSameCharacter_591) {

    EXPECT_EQ(Catch::toLower('0'), '0');

    EXPECT_EQ(Catch::toLower('#'), '#');

    EXPECT_EQ(Catch::toLower(' '), ' ');

}



TEST_F(StringManipTest_591, EdgeCase_LowercaseA_ReturnsSameCharacter_591) {

    EXPECT_EQ(Catch::toLower('a'), 'a');

}



TEST_F(StringManipTest_591, EdgeCase_UppercaseZ_ReturnsLowercaseEquivalent_591) {

    EXPECT_EQ(Catch::toLower('Z'), 'z');

}
