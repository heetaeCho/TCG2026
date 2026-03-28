#include <gtest/gtest.h>
#include "Annot.h"

// Since convertAnnotLineEndingStyle is a static function in the .cc file,
// we need to either include the .cc file or declare it extern.
// For testing purposes, we'll include the implementation file to access the static function.
// This is a common technique for testing static functions.

// Forward declaration won't work for static functions, so we include the source
// or use a wrapper. Since the function is static, we need to access it differently.
// One approach: include the .cc to get the static function in our translation unit.

// However, a cleaner approach for testing: we'll declare the function signature
// and rely on linkage. Since it's static, we must include the source file.

// We include just enough to get the static function:
namespace {
#include "Annot.cc"
}

// If the above doesn't work due to other dependencies in Annot.cc,
// we can copy just the function for testing. But per constraints,
// we test the interface as-is.

class ConvertAnnotLineEndingStyleTest_2016 : public ::testing::Test {
protected:
    const char* convert(AnnotLineEndingStyle style) {
        return convertAnnotLineEndingStyle(style);
    }
};

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsSquare_2016) {
    EXPECT_STREQ("Square", convert(annotLineEndingSquare));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsCircle_2016) {
    EXPECT_STREQ("Circle", convert(annotLineEndingCircle));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsDiamond_2016) {
    EXPECT_STREQ("Diamond", convert(annotLineEndingDiamond));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsOpenArrow_2016) {
    EXPECT_STREQ("OpenArrow", convert(annotLineEndingOpenArrow));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsClosedArrow_2016) {
    EXPECT_STREQ("ClosedArrow", convert(annotLineEndingClosedArrow));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsButt_2016) {
    EXPECT_STREQ("Butt", convert(annotLineEndingButt));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsROpenArrow_2016) {
    EXPECT_STREQ("ROpenArrow", convert(annotLineEndingROpenArrow));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsRClosedArrow_2016) {
    EXPECT_STREQ("RClosedArrow", convert(annotLineEndingRClosedArrow));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsSlash_2016) {
    EXPECT_STREQ("Slash", convert(annotLineEndingSlash));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsNoneForAnnotLineEndingNone_2016) {
    EXPECT_STREQ("None", convert(annotLineEndingNone));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsNoneForDefaultCase_2016) {
    // Test with a value that doesn't match any defined enum case
    EXPECT_STREQ("None", convert(static_cast<AnnotLineEndingStyle>(100)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnsNoneForNegativeValue_2016) {
    EXPECT_STREQ("None", convert(static_cast<AnnotLineEndingStyle>(-1)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, SquareEnumValueIsZero_2016) {
    EXPECT_STREQ("Square", convert(static_cast<AnnotLineEndingStyle>(0)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, CircleEnumValueIsOne_2016) {
    EXPECT_STREQ("Circle", convert(static_cast<AnnotLineEndingStyle>(1)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, DiamondEnumValueIsTwo_2016) {
    EXPECT_STREQ("Diamond", convert(static_cast<AnnotLineEndingStyle>(2)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, OpenArrowEnumValueIsThree_2016) {
    EXPECT_STREQ("OpenArrow", convert(static_cast<AnnotLineEndingStyle>(3)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ClosedArrowEnumValueIsFour_2016) {
    EXPECT_STREQ("ClosedArrow", convert(static_cast<AnnotLineEndingStyle>(4)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, NoneEnumValueIsFive_2016) {
    // annotLineEndingNone = 5 falls through to default case
    EXPECT_STREQ("None", convert(static_cast<AnnotLineEndingStyle>(5)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ButtEnumValueIsSix_2016) {
    EXPECT_STREQ("Butt", convert(static_cast<AnnotLineEndingStyle>(6)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ROpenArrowEnumValueIsSeven_2016) {
    EXPECT_STREQ("ROpenArrow", convert(static_cast<AnnotLineEndingStyle>(7)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, RClosedArrowEnumValueIsEight_2016) {
    EXPECT_STREQ("RClosedArrow", convert(static_cast<AnnotLineEndingStyle>(8)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, SlashEnumValueIsNine_2016) {
    EXPECT_STREQ("Slash", convert(static_cast<AnnotLineEndingStyle>(9)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, LargeEnumValueReturnsNone_2016) {
    EXPECT_STREQ("None", convert(static_cast<AnnotLineEndingStyle>(9999)));
}

TEST_F(ConvertAnnotLineEndingStyleTest_2016, ReturnValueIsNotNull_2016) {
    // Verify that no enum value produces a null return
    for (int i = -1; i <= 15; i++) {
        const char* result = convert(static_cast<AnnotLineEndingStyle>(i));
        EXPECT_NE(nullptr, result) << "Null returned for value " << i;
    }
}
