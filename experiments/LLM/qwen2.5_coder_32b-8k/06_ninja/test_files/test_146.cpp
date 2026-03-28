#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace testing;



extern std::string StripAnsiEscapeCodes(const std::string& in);



class StripAnsiEscapeCodesTest_146 : public ::testing::Test {

protected:

    // Setup code, if needed

};



TEST_F(StripAnsiEscapeCodesTest_146, NormalOperation_NoEscapes_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("Hello World"), "Hello World");

}



TEST_F(StripAnsiEscapeCodesTest_146, NormalOperation_WithEscapes_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("\33[31mRed\33[0m Text"), "Red Text");

}



TEST_F(StripAnsiEscapeCodesTest_146, BoundaryCondition_EmptyString_146) {

    EXPECT_EQ(StripAnsiEscapeCodes(""), "");

}



TEST_F(StripAnsiEscapeCodesTest_146, BoundaryCondition_SingleNonEscapeCharacter_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("A"), "A");

}



TEST_F(StripAnsiEscapeCodesTest_146, BoundaryCondition_SingleEscapeCharacter_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("\33"), "");

}



TEST_F(StripAnsiEscapeCodesTest_146, BoundaryCondition_EscapeAtEndOfString_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("Hello \33"), "Hello ");

}



TEST_F(StripAnsiEscapeCodesTest_146, BoundaryCondition_EscapeSequenceIncomplete_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("\33["), "");

}



TEST_F(StripAnsiEscapeCodesTest_146, ExceptionalCase_NoClosingBracket_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("\33[31mRed\330m Text"), "Red\330m Text");

}



TEST_F(StripAnsiEscapeCodesTest_146, ExceptionalCase_EscapeFollowedByNonAlpha_146) {

    EXPECT_EQ(StripAnsiEscapeCodes("\33[31;mText"), ";Text");

}
