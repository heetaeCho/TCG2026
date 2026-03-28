#include <gtest/gtest.h>

// Include the header that declares the function and Unicode type
#include "UnicodeTypeTable.h"

// Known constants from the implementation:
// UNICODE_ALPHABETIC_PRESENTATION_BLOCK_BEGIN = 64256 (0xFB00)
// UNICODE_ALPHABETIC_PRESENTATION_BLOCK_END = 64335 (0xFB4F)

class UnicodeTypeTableTest_1873 : public ::testing::Test {
protected:
    static constexpr Unicode BLOCK_BEGIN = 64256; // 0xFB00
    static constexpr Unicode BLOCK_END = 64335;   // 0xFB4F
};

// --- Normal operation tests ---

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_FirstCharInBlock_1873) {
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(BLOCK_BEGIN));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_LastCharInBlock_1873) {
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(BLOCK_END));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_MiddleOfBlock_1873) {
    Unicode mid = (BLOCK_BEGIN + BLOCK_END) / 2;
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(mid));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_SecondCharInBlock_1873) {
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(BLOCK_BEGIN + 1));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_SecondToLastCharInBlock_1873) {
    EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(BLOCK_END - 1));
}

// --- Boundary condition tests ---

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_OneBeforeBlock_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(BLOCK_BEGIN - 1));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_OneAfterBlock_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(BLOCK_END + 1));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_TwoBeforeBlock_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(BLOCK_BEGIN - 2));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_TwoAfterBlock_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(BLOCK_END + 2));
}

// --- Values well outside the block ---

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_Zero_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_One_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(1));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_ASCIIChar_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm('A'));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_BasicLatinRange_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0x0041)); // 'A'
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_LargeValueAboveBlock_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0xFFFF));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_UnicodeMaxBMP_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0x10000));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_HighUnicodeValue_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0x10FFFF));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_HangulBase_1873) {
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0xAC00)); // Hangul S Base
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_ArabicPresentationA_1873) {
    // 0xFB50 is just after the Alphabetic Presentation Forms block
    EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(0xFB50));
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_AllInRange_1873) {
    // Verify every character in the block is recognized
    for (Unicode c = BLOCK_BEGIN; c <= BLOCK_END; ++c) {
        EXPECT_TRUE(unicodeIsAlphabeticPresentationForm(c)) << "Failed for code point: " << c;
    }
}

TEST_F(UnicodeTypeTableTest_1873, AlphabeticPresentationForm_NearbyOutOfRange_1873) {
    // Verify characters just outside the block boundaries are not recognized
    for (Unicode c = BLOCK_BEGIN - 10; c < BLOCK_BEGIN; ++c) {
        EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(c)) << "Should be false for code point: " << c;
    }
    for (Unicode c = BLOCK_END + 1; c <= BLOCK_END + 10; ++c) {
        EXPECT_FALSE(unicodeIsAlphabeticPresentationForm(c)) << "Should be false for code point: " << c;
    }
}
