#include <gtest/gtest.h>
#include "UTF.h"

class UnicodeIsValidTest_1021 : public ::testing::Test {
protected:
};

// Normal operation: Basic ASCII characters should be valid
TEST_F(UnicodeIsValidTest_1021, BasicAsciiIsValid_1021) {
    EXPECT_TRUE(UnicodeIsValid(0x0000));
    EXPECT_TRUE(UnicodeIsValid(0x0041)); // 'A'
    EXPECT_TRUE(UnicodeIsValid(0x007F));
}

// Normal operation: Common Unicode code points
TEST_F(UnicodeIsValidTest_1021, CommonUnicodeCodePointsAreValid_1021) {
    EXPECT_TRUE(UnicodeIsValid(0x00E9));  // é
    EXPECT_TRUE(UnicodeIsValid(0x4E2D));  // 中
    EXPECT_TRUE(UnicodeIsValid(0x1F600)); // 😀 emoji
    EXPECT_TRUE(UnicodeIsValid(0x0100));
    EXPECT_TRUE(UnicodeIsValid(0x2000));
}

// Boundary: Maximum valid code point (U+10FFFF excluding FFFE/FFFF pattern)
TEST_F(UnicodeIsValidTest_1021, MaxValidCodePoint_1021) {
    EXPECT_FALSE(UnicodeIsValid(0x10FFFF)); // ends with 0xFFFE/0xFFFF pattern -> invalid
    EXPECT_FALSE(UnicodeIsValid(0x10FFFE));
    EXPECT_TRUE(UnicodeIsValid(0x10FFFD));
}

// Boundary: Code points at and above 0x110000 are invalid
TEST_F(UnicodeIsValidTest_1021, AboveMaxUnicodeIsInvalid_1021) {
    EXPECT_FALSE(UnicodeIsValid(0x110000));
    EXPECT_FALSE(UnicodeIsValid(0x110001));
    EXPECT_FALSE(UnicodeIsValid(0x200000));
    EXPECT_FALSE(UnicodeIsValid(0xFFFFFFFF));
}

// Surrogate range: U+D800 to U+DFFF are invalid
TEST_F(UnicodeIsValidTest_1021, SurrogateRangeIsInvalid_1021) {
    EXPECT_FALSE(UnicodeIsValid(0xD800)); // start of surrogates
    EXPECT_FALSE(UnicodeIsValid(0xD801));
    EXPECT_FALSE(UnicodeIsValid(0xDB7F));
    EXPECT_FALSE(UnicodeIsValid(0xDB80));
    EXPECT_FALSE(UnicodeIsValid(0xDBFF)); // end of high surrogates
    EXPECT_FALSE(UnicodeIsValid(0xDC00)); // start of low surrogates
    EXPECT_FALSE(UnicodeIsValid(0xDFFF)); // end of low surrogates
}

// Boundary around surrogate range
TEST_F(UnicodeIsValidTest_1021, BoundaryAroundSurrogateRange_1021) {
    EXPECT_TRUE(UnicodeIsValid(0xD7FF));  // just before surrogates
    EXPECT_FALSE(UnicodeIsValid(0xD800)); // start of surrogates
    EXPECT_FALSE(UnicodeIsValid(0xDFFF)); // end of surrogates
    EXPECT_TRUE(UnicodeIsValid(0xE000));  // just after surrogates
}

// Noncharacters: U+FDD0 to U+FDEF are invalid
TEST_F(UnicodeIsValidTest_1021, NoncharactersFDD0toFDEFAreInvalid_1021) {
    EXPECT_FALSE(UnicodeIsValid(0xFDD0));
    EXPECT_FALSE(UnicodeIsValid(0xFDD1));
    EXPECT_FALSE(UnicodeIsValid(0xFDE0));
    EXPECT_FALSE(UnicodeIsValid(0xFDEF));
}

// Boundary around FDD0-FDEF range
TEST_F(UnicodeIsValidTest_1021, BoundaryAroundFDD0FDEFRange_1021) {
    EXPECT_TRUE(UnicodeIsValid(0xFDCF));  // just before
    EXPECT_FALSE(UnicodeIsValid(0xFDD0)); // start
    EXPECT_FALSE(UnicodeIsValid(0xFDEF)); // end
    EXPECT_TRUE(UnicodeIsValid(0xFDF0));  // just after
}

// Noncharacters: U+xFFFE and U+xFFFF for each plane are invalid
TEST_F(UnicodeIsValidTest_1021, FFFEandFFFFPerPlaneAreInvalid_1021) {
    // BMP
    EXPECT_FALSE(UnicodeIsValid(0xFFFE));
    EXPECT_FALSE(UnicodeIsValid(0xFFFF));

    // Plane 1
    EXPECT_FALSE(UnicodeIsValid(0x1FFFE));
    EXPECT_FALSE(UnicodeIsValid(0x1FFFF));

    // Plane 2
    EXPECT_FALSE(UnicodeIsValid(0x2FFFE));
    EXPECT_FALSE(UnicodeIsValid(0x2FFFF));

    // Plane 3
    EXPECT_FALSE(UnicodeIsValid(0x3FFFE));
    EXPECT_FALSE(UnicodeIsValid(0x3FFFF));

    // Plane 14
    EXPECT_FALSE(UnicodeIsValid(0xEFFFE));
    EXPECT_FALSE(UnicodeIsValid(0xEFFFF));

    // Plane 15
    EXPECT_FALSE(UnicodeIsValid(0xFFFFE));
    EXPECT_FALSE(UnicodeIsValid(0xFFFFF));

    // Plane 16
    EXPECT_FALSE(UnicodeIsValid(0x10FFFE));
    EXPECT_FALSE(UnicodeIsValid(0x10FFFF));
}

// Valid code points just before FFFE/FFFF in each plane
TEST_F(UnicodeIsValidTest_1021, ValidCodePointsBeforeFFFEPerPlane_1021) {
    EXPECT_TRUE(UnicodeIsValid(0xFFFD));
    EXPECT_TRUE(UnicodeIsValid(0x1FFFD));
    EXPECT_TRUE(UnicodeIsValid(0x2FFFD));
    EXPECT_TRUE(UnicodeIsValid(0x10FFFD));
}

// Zero is a valid Unicode code point
TEST_F(UnicodeIsValidTest_1021, ZeroIsValid_1021) {
    EXPECT_TRUE(UnicodeIsValid(0));
}

// Various valid code points from different blocks
TEST_F(UnicodeIsValidTest_1021, VariousValidCodePoints_1021) {
    EXPECT_TRUE(UnicodeIsValid(0x0001));
    EXPECT_TRUE(UnicodeIsValid(0x007E));
    EXPECT_TRUE(UnicodeIsValid(0x0080));
    EXPECT_TRUE(UnicodeIsValid(0x07FF));
    EXPECT_TRUE(UnicodeIsValid(0x0800));
    EXPECT_TRUE(UnicodeIsValid(0xFDC0)); // just before noncharacter range but not in it
    EXPECT_TRUE(UnicodeIsValid(0xFDF0)); // just after noncharacter range
    EXPECT_TRUE(UnicodeIsValid(0xE000)); // Private Use Area start
    EXPECT_TRUE(UnicodeIsValid(0xF8FF)); // Private Use Area end
}

// Large invalid values
TEST_F(UnicodeIsValidTest_1021, LargeInvalidValues_1021) {
    EXPECT_FALSE(UnicodeIsValid(0x7FFFFFFF));
    EXPECT_FALSE(UnicodeIsValid(0x80000000));
}

// All noncharacters in FDD0-FDEF range
TEST_F(UnicodeIsValidTest_1021, AllNoncharactersInFDRange_1021) {
    for (Unicode cp = 0xFDD0; cp <= 0xFDEF; ++cp) {
        EXPECT_FALSE(UnicodeIsValid(cp)) << "Code point U+" << std::hex << cp << " should be invalid";
    }
}

// All FFFE/FFFF noncharacters across planes
TEST_F(UnicodeIsValidTest_1021, AllFFFENoncharactersAcrossPlanes_1021) {
    for (int plane = 0; plane <= 16; ++plane) {
        Unicode fffe = (plane << 16) | 0xFFFE;
        Unicode ffff = (plane << 16) | 0xFFFF;
        EXPECT_FALSE(UnicodeIsValid(fffe)) << "Code point U+" << std::hex << fffe << " should be invalid";
        EXPECT_FALSE(UnicodeIsValid(ffff)) << "Code point U+" << std::hex << ffff << " should be invalid";
    }
}

// Surrogate range exhaustive boundary check
TEST_F(UnicodeIsValidTest_1021, SurrogateExhaustiveBoundary_1021) {
    // Every value from D800 to DFFF should be invalid
    for (Unicode cp = 0xD800; cp <= 0xDFFF; ++cp) {
        EXPECT_FALSE(UnicodeIsValid(cp)) << "Surrogate U+" << std::hex << cp << " should be invalid";
    }
}
