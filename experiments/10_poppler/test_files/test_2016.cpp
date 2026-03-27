#include <gtest/gtest.h>



// Assuming the function convertAnnotLineEndingStyle is declared in Annot.h

#include "TestProjects/poppler/poppler/Annot.h"



TEST(ConvertAnnotLineEndingStyleTest_2016, SquareReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingSquare), "Square");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, CircleReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingCircle), "Circle");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, DiamondReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingDiamond), "Diamond");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, OpenArrowReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingOpenArrow), "OpenArrow");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, ClosedArrowReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingClosedArrow), "ClosedArrow");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, ButtReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingButt), "Butt");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, ROpenArrowReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingROpenArrow), "ROpenArrow");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, RClosedArrowReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingRClosedArrow), "RClosedArrow");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, SlashReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingSlash), "Slash");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, NoneReturnsCorrectString_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingNone), "None");

}



TEST(ConvertAnnotLineEndingStyleTest_2016, UnknownValueReturnsNone_2016) {

    EXPECT_STREQ(convertAnnotLineEndingStyle(static_cast<AnnotLineEndingStyle>(10)), "None");

}
