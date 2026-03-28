#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "UnicodeTypeTable.h"  // Include the appropriate header file for the Unicode class

// TEST_ID: 1873
// Test the unicodeIsAlphabeticPresentationForm function with a character within the valid range
TEST_F(UnicodeTest_1873, unicodeIsAlphabeticPresentationForm_ValidCharacter_1873) {
    Unicode validChar = 64256;  // A valid character within the Unicode Alphabetic Presentation Block
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(validChar));
}

// TEST_ID: 1874
// Test the unicodeIsAlphabeticPresentationForm function with a character outside the valid range
TEST_F(UnicodeTest_1874, unicodeIsAlphabeticPresentationForm_InvalidCharacter_1874) {
    Unicode invalidChar = 65000;  // A character outside the valid range
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(invalidChar));
}

// TEST_ID: 1875
// Test the unicodeIsAlphabeticPresentationForm function with a character at the lower boundary of the valid range
TEST_F(UnicodeTest_1875, unicodeIsAlphabeticPresentationForm_LowerBoundary_1875) {
    Unicode lowerBoundaryChar = 64256;  // The lower boundary of the valid range
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(lowerBoundaryChar));
}

// TEST_ID: 1876
// Test the unicodeIsAlphabeticPresentationForm function with a character at the upper boundary of the valid range
TEST_F(UnicodeTest_1876, unicodeIsAlphabeticPresentationForm_UpperBoundary_1876) {
    Unicode upperBoundaryChar = 64335;  // The upper boundary of the valid range
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(upperBoundaryChar));
}

// TEST_ID: 1877
// Test the unicodeIsAlphabeticPresentationForm function with a character just outside the upper boundary
TEST_F(UnicodeTest_1877, unicodeIsAlphabeticPresentationForm_AboveUpperBoundary_1877) {
    Unicode charAboveUpper = 64336;  // A character just outside the upper boundary
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(charAboveUpper));
}

// TEST_ID: 1878
// Test the unicodeIsAlphabeticPresentationForm function with a character just outside the lower boundary
TEST_F(UnicodeTest_1878, unicodeIsAlphabeticPresentationForm_BelowLowerBoundary_1878) {
    Unicode charBelowLower = 64255;  // A character just outside the lower boundary
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(charBelowLower));
}

// TEST_ID: 1879
// Test the unicodeIsAlphabeticPresentationForm function with a non-alphabetic character
TEST_F(UnicodeTest_1879, unicodeIsAlphabeticPresentationForm_NonAlphabeticCharacter_1879) {
    Unicode nonAlphabeticChar = 1000;  // A non-alphabetic character
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(nonAlphabeticChar));
}

// TEST_ID: 1880
// Test the boundary values for Hangul letters
TEST_F(UnicodeTest_1880, HangulBoundaryTest_1880) {
    Unicode hangulBase = 0xAC00;  // The first Hangul syllabic block
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(hangulBase));

    Unicode hangulLast = 0xD7A3;  // The last Hangul syllabic block
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(hangulLast));
}

// TEST_ID: 1881
// Test a character inside the Hangul block but outside the specified ranges
TEST_F(UnicodeTest_1881, HangulOutsideRangeTest_1881) {
    Unicode hangulOutsideRange = 0xAE00;  // A Hangul syllable outside the valid range
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(hangulOutsideRange));
}