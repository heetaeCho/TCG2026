#include <gtest/gtest.h>

// Include necessary type definitions
#include <cstdint>

// Define XMP_Uns32 if not already defined
typedef uint32_t XMP_Uns32;

// Include the inline function
#define BanAllEntityUsage 0
static inline bool IsStartChar_NonASCII(XMP_Uns32 cp) {
    if (((0xC0 <= cp) && (cp <= 0xD6)) || ((0xD8 <= cp) && (cp <= 0xF6))) return true;
    if (((0xF8 <= cp) && (cp <= 0x2FF)) || ((0x370 <= cp) && (cp <= 0x37D))) return true;
    if (((0x37F <= cp) && (cp <= 0x1FFF)) || ((0x200C <= cp) && (cp <= 0x200D))) return true;
    if (((0x2070 <= cp) && (cp <= 0x218F)) || ((0x2C00 <= cp) && (cp <= 0x2FEF))) return true;
    if (((0x3001 <= cp) && (cp <= 0xD7FF)) || ((0xF900 <= cp) && (cp <= 0xFDCF))) return true;
    if (((0xFDF0 <= cp) && (cp <= 0xFFFD)) || ((0x10000 <= cp) && (cp <= 0xEFFFF))) return true;
    return false;
}

class IsStartCharNonASCIITest_1876 : public ::testing::Test {
protected:
};

// ============================================================
// Range 1: 0xC0 - 0xD6
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_C0_D6_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xC0));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_C0_D6_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xD6));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_C0_D6_Middle_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xC5));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_C0_D6_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xBF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_C0_D6_AboveUpper_1876) {
    // 0xD7 is the gap between the two sub-ranges
    EXPECT_FALSE(IsStartChar_NonASCII(0xD7));
}

// ============================================================
// Range 2: 0xD8 - 0xF6
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_D8_F6_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xD8));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_D8_F6_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xF6));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_D8_F6_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xF7));
}

// ============================================================
// Range 3: 0xF8 - 0x2FF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_F8_2FF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xF8));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F8_2FF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x2FF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F8_2FF_Middle_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x1FF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F8_2FF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x300));
}

// ============================================================
// Range 4: 0x370 - 0x37D
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_370_37D_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x370));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_370_37D_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x37D));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_370_37D_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x36F));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_370_37D_GapAbove_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x37E));
}

// ============================================================
// Range 5: 0x37F - 0x1FFF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_37F_1FFF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x37F));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_37F_1FFF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x1FFF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_37F_1FFF_Middle_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x1000));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_37F_1FFF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2000));
}

// ============================================================
// Range 6: 0x200C - 0x200D
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_200C_200D_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x200C));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_200C_200D_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x200D));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_200C_200D_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x200B));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_200C_200D_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x200E));
}

// ============================================================
// Range 7: 0x2070 - 0x218F
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_2070_218F_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x2070));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2070_218F_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x218F));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2070_218F_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x206F));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2070_218F_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2190));
}

// ============================================================
// Range 8: 0x2C00 - 0x2FEF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_2C00_2FEF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x2C00));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2C00_2FEF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x2FEF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2C00_2FEF_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2BFF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_2C00_2FEF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2FF0));
}

// ============================================================
// Range 9: 0x3001 - 0xD7FF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_3001_D7FF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x3001));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_3001_D7FF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xD7FF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_3001_D7FF_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x3000));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_3001_D7FF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xD800));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_3001_D7FF_Middle_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x5000));
}

// ============================================================
// Range 10: 0xF900 - 0xFDCF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_F900_FDCF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xF900));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F900_FDCF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xFDCF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F900_FDCF_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xF8FF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_F900_FDCF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFDD0));
}

// ============================================================
// Range 11: 0xFDF0 - 0xFFFD
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_FDF0_FFFD_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xFDF0));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_FDF0_FFFD_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xFFFD));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_FDF0_FFFD_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFDEF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_FDF0_FFFD_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFE));
}

// ============================================================
// Range 12: 0x10000 - 0xEFFFF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Range_10000_EFFFF_LowerBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x10000));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_10000_EFFFF_UpperBound_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0xEFFFF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_10000_EFFFF_Middle_1876) {
    EXPECT_TRUE(IsStartChar_NonASCII(0x50000));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_10000_EFFFF_BelowLower_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFF));
}

TEST_F(IsStartCharNonASCIITest_1876, Range_10000_EFFFF_AboveUpper_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xF0000));
}

// ============================================================
// Values clearly outside all ranges
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, Zero_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x00));
}

TEST_F(IsStartCharNonASCIITest_1876, ASCIIRange_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x41));  // 'A'
}

TEST_F(IsStartCharNonASCIITest_1876, BelowFirstRange_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x01));
}

TEST_F(IsStartCharNonASCIITest_1876, JustBelowC0_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xBF));
}

TEST_F(IsStartCharNonASCIITest_1876, GapBetween300And36F_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x350));
}

TEST_F(IsStartCharNonASCIITest_1876, GapBetween200EAnd206F_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2050));
}

TEST_F(IsStartCharNonASCIITest_1876, GapBetween2190And2BFF_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0x2500));
}

TEST_F(IsStartCharNonASCIITest_1876, GapBetweenD800AndF8FF_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xE000));
}

TEST_F(IsStartCharNonASCIITest_1876, VeryLargeValue_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFFFFFF));
}

TEST_F(IsStartCharNonASCIITest_1876, MaxUns32_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(UINT32_MAX));
}

// ============================================================
// Gap between 0x2000-0x200B (between range 5 end and range 6 start)
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, GapBetween2000And200B_ReturnsFalse_1876) {
    for (XMP_Uns32 cp = 0x2000; cp <= 0x200B; ++cp) {
        EXPECT_FALSE(IsStartChar_NonASCII(cp)) << "Failed for cp=0x" << std::hex << cp;
    }
}

// ============================================================
// Gap between 0xFDD0 and 0xFDEF
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, GapFDD0_FDEF_ReturnsFalse_1876) {
    for (XMP_Uns32 cp = 0xFDD0; cp <= 0xFDEF; ++cp) {
        EXPECT_FALSE(IsStartChar_NonASCII(cp)) << "Failed for cp=0x" << std::hex << cp;
    }
}

// ============================================================
// Verify entire gap 0xFFFE-0xFFFF returns false
// ============================================================
TEST_F(IsStartCharNonASCIITest_1876, FFFE_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFE));
}

TEST_F(IsStartCharNonASCIITest_1876, FFFF_ReturnsFalse_1876) {
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFF));
}
