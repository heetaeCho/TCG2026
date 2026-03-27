#include <gtest/gtest.h>

#include "UTF.cc"  // Assuming the function is in UTF.cc



TEST(UnicodeIsWhitespaceTest_1522, NormalOperation_Space_1522) {

    EXPECT_TRUE(UnicodeIsWhitespace(0x0020));

}



TEST(UnicodeIsWhitespaceTest_1522, NormalOperation_Tab_1522) {

    EXPECT_TRUE(UnicodeIsWhitespace(0x0009));

}



TEST(UnicodeIsWhitespaceTest_1522, NormalOperation_NewLine_1522) {

    EXPECT_TRUE(UnicodeIsWhitespace(0x000A));

}



TEST(UnicodeIsWhitespaceTest_1522, NormalOperation_NoBreakSpace_1522) {

    EXPECT_TRUE(UnicodeIsWhitespace(0x00A0));

}



TEST(UnicodeIsWhitespaceTest_1522, BoundaryCondition_FirstCharBeforeSpaces_1522) {

    EXPECT_FALSE(UnicodeIsWhitespace(0x0008));

}



TEST(UnicodeIsWhitespaceTest_1522, BoundaryCondition_LastCharAfterSpaces_1522) {

    EXPECT_FALSE(UnicodeIsWhitespace(0x3001));

}



TEST(UnicodeIsWhitespaceTest_1522, ExceptionalCase_OutsideUnicodeRange_1522) {

    EXPECT_FALSE(UnicodeIsWhitespace(0x110000));  // Outside valid Unicode range

}



TEST(UnicodeIsWhitespaceTest_1522, ExceptionalCase_NegativeValue_1522) {

    EXPECT_FALSE(UnicodeIsWhitespace(static_cast<Unicode>(-1)));  // Assuming unsigned type, but testing edge case

}
