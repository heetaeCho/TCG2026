#include <gtest/gtest.h>

// Include the necessary headers for the function under test
#include "./TestProjects/exiv2/xmpsdk/src/UnicodeInlines.incl_cpp"

// Test case to check for the character '·' (0xB7)
TEST_F(UnicodeInlinesTest_1878, IsOtherChar_NonASCII_BulletChar_1878) {
    XMP_Uns32 cp = 0xB7;  // '·' character code point
    EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Character 0xB7 should be identified as non-ASCII.";
}

// Test case to check for character code points within the range 0x300 to 0x36F
TEST_F(UnicodeInlinesTest_1879, IsOtherChar_NonASCII_Range300to36F_1879) {
    XMP_Uns32 cp = 0x300;  // First character code in the range
    EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Character 0x300 should be identified as non-ASCII.";
    
    cp = 0x36F;  // Last character code in the range
    EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Character 0x36F should be identified as non-ASCII.";
}

// Test case to check for character code points within the range 0x203F to 0x2040
TEST_F(UnicodeInlinesTest_1880, IsOtherChar_NonASCII_Range203Fto2040_1880) {
    XMP_Uns32 cp = 0x203F;  // First character code in the range
    EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Character 0x203F should be identified as non-ASCII.";
    
    cp = 0x2040;  // Last character code in the range
    EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Character 0x2040 should be identified as non-ASCII.";
}

// Test case to check for a non-matching character (character code point outside the specified ranges)
TEST_F(UnicodeInlinesTest_1881, IsOtherChar_NonASCII_OutsideRanges_1881) {
    XMP_Uns32 cp = 0x41;  // 'A' character code point
    EXPECT_FALSE(IsOtherChar_NonASCII(cp)) << "Character 0x41 should not be identified as non-ASCII.";
}

// Test case to check for boundary conditions
TEST_F(UnicodeInlinesTest_1882, IsOtherChar_NonASCII_BoundaryConditions_1882) {
    XMP_Uns32 cp = 0x2FF;  // Boundary value just before the 0x300 range
    EXPECT_FALSE(IsOtherChar_NonASCII(cp)) << "Character 0x2FF should not be identified as non-ASCII.";
    
    cp = 0x370;  // Boundary value just after the 0x36F range
    EXPECT_FALSE(IsOtherChar_NonASCII(cp)) << "Character 0x370 should not be identified as non-ASCII.";
}

// Test case to check for exceptional cases, like invalid character code point
TEST_F(UnicodeInlinesTest_1883, IsOtherChar_NonASCII_InvalidChar_1883) {
    XMP_Uns32 cp = 0xFFFFFFFF;  // Invalid character code point
    EXPECT_FALSE(IsOtherChar_NonASCII(cp)) << "Character 0xFFFFFFFF should not be identified as non-ASCII.";
}