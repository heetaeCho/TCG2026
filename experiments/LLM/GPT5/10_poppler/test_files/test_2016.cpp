#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"

// The function under test
extern const char* convertAnnotLineEndingStyle(AnnotLineEndingStyle style);

// Test fixture for AnnotLineEndingStyle
class AnnotTest_2016 : public ::testing::Test {
protected:
    // Test Setup (if needed)
    void SetUp() override {}
    
    // Test Teardown (if needed)
    void TearDown() override {}
};

// Test case for annotLineEndingSquare
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Square_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingSquare), "Square");
}

// Test case for annotLineEndingCircle
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Circle_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingCircle), "Circle");
}

// Test case for annotLineEndingDiamond
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Diamond_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingDiamond), "Diamond");
}

// Test case for annotLineEndingOpenArrow
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_OpenArrow_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingOpenArrow), "OpenArrow");
}

// Test case for annotLineEndingClosedArrow
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_ClosedArrow_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingClosedArrow), "ClosedArrow");
}

// Test case for annotLineEndingButt
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Butt_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingButt), "Butt");
}

// Test case for annotLineEndingROpenArrow
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_ROpenArrow_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingROpenArrow), "ROpenArrow");
}

// Test case for annotLineEndingRClosedArrow
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_RClosedArrow_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingRClosedArrow), "RClosedArrow");
}

// Test case for annotLineEndingSlash
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Slash_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingSlash), "Slash");
}

// Test case for annotLineEndingNone (default case)
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_None_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(annotLineEndingNone), "None");
}

// Test case for invalid AnnotLineEndingStyle (boundary case)
TEST_F(AnnotTest_2016, convertAnnotLineEndingStyle_Invalid_2016) {
    EXPECT_STREQ(convertAnnotLineEndingStyle(static_cast<AnnotLineEndingStyle>(999)), "None");
}