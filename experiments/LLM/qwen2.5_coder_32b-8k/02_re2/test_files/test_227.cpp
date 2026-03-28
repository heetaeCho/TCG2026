#include <gtest/gtest.h>

#include <string>



namespace re2 {



void AppendLiteral(std::string *t, Rune r, bool foldcase);



class ToStringTest_227 : public ::testing::Test {

protected:

    std::string result;

};



TEST_F(ToStringTest_227, NormalOperation_SpecialCharacterWithoutFoldCase_227) {

    result.clear();

    AppendLiteral(&result, '(', false);

    EXPECT_EQ(result, "\\(");

}



TEST_F(ToStringTest_227, NormalOperation_LowercaseLetterWithFoldCase_227) {

    result.clear();

    AppendLiteral(&result, 'a', true);

    EXPECT_EQ(result, "[Aa]");

}



TEST_F(ToStringTest_227, NormalOperation_UppercaseLetterWithoutFoldCase_227) {

    result.clear();

    AppendLiteral(&result, 'B', false);

    EXPECT_EQ(result, "B");

}



TEST_F(ToStringTest_227, BoundaryCondition_ZeroRune_227) {

    result.clear();

    AppendLiteral(&result, 0, true);

    EXPECT_EQ(result, "");

}



TEST_F(ToStringTest_227, BoundaryCondition_AsciiMaxWithoutSpecialChars_227) {

    result.clear();

    AppendLiteral(&result, 'z', false);

    EXPECT_EQ(result, "z");

}



TEST_F(ToStringTest_227, ExceptionalCase_OutOfAsciiRange_227) {

    result.clear();

    AppendLiteral(&result, 0x80, false);

    // Assuming AppendCCRange handles this case internally and we can't observe it directly.

    EXPECT_NE(result, "");

}



}  // namespace re2
