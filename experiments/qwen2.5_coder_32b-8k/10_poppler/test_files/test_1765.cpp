#include <gtest/gtest.h>

#include "Object.h"



// Assuming the function isGlyphOrientationName is part of a class or can be tested independently.

// Since it's static and not part of any class in the provided code, we'll test it directly.



TEST(isGlyphOrientationNameTest_1765, NormalOperation_Auto_1765) {

    Object obj("Auto");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_90_1765) {

    Object obj("90");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_180_1765) {

    Object obj("180");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_270_1765) {

    Object obj("270");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_360_1765) {

    Object obj("360");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_Negative90_1765) {

    Object obj("-90");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, NormalOperation_Negative180_1765) {

    Object obj("-180");

    EXPECT_TRUE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, BoundaryCondition_EmptyString_1765) {

    Object obj("");

    EXPECT_FALSE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, BoundaryCondition_InvalidName_1765) {

    Object obj("Invalid");

    EXPECT_FALSE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, BoundaryCondition_ZeroLengthString_1765) {

    Object obj(std::string_view{});

    EXPECT_FALSE(isGlyphOrientationName(&obj));

}



TEST(isGlyphOrientationNameTest_1765, ExceptionalCase_NullObject_1765) {

    Object* obj = nullptr;

    EXPECT_FALSE(isGlyphOrientationName(obj));

}
