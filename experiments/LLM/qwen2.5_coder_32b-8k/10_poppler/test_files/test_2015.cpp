#include <gtest/gtest.h>

#include "Object.h"

#include "Annot.h"



using namespace poppler;



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_Square_2015) {

    Object obj("Square");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingSquare);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_Circle_2015) {

    Object obj("Circle");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingCircle);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_Diamond_2015) {

    Object obj("Diamond");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingDiamond);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_OpenArrow_2015) {

    Object obj("OpenArrow");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingOpenArrow);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_ClosedArrow_2015) {

    Object obj("ClosedArrow");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingClosedArrow);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_Butt_2015) {

    Object obj("Butt");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingButt);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_ROpenArrow_2015) {

    Object obj("ROpenArrow");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingROpenArrow);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_RClosedArrow_2015) {

    Object obj("RClosedArrow");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingRClosedArrow);

}



TEST(parseAnnotLineEndingStyleTest_2015, NormalOperation_Slash_2015) {

    Object obj("Slash");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingSlash);

}



TEST(parseAnnotLineEndingStyleTest_2015, BoundaryCondition_EmptyString_2015) {

    Object obj("");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);

}



TEST(parseAnnotLineEndingStyleTest_2015, BoundaryCondition_UnrecognizedName_2015) {

    Object obj("Unknown");

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);

}



TEST(parseAnnotLineEndingStyleTest_2015, ExceptionalCase_NotAName_2015) {

    Object obj(42); // Assuming 42 is an integer and not a name

    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);

}
