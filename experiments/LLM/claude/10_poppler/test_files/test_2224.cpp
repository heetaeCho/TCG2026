#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-document.h"
}

#include "FontInfo.h"

// We need to work with the internal structure of PopplerFontsIter
// Based on the partial code, iter->items[iter->index] returns FontInfo*
// and the struct has items (array/vector of FontInfo*) and index

// Forward declare the function under test
extern "C" {
PopplerFontType poppler_fonts_iter_get_font_type(PopplerFontsIter *iter);
}

class PopplerFontsIterGetFontTypeTest_2224 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns POPPLER_FONT_TYPE_UNKNOWN
TEST_F(PopplerFontsIterGetFontTypeTest_2224, NullIterReturnsUnknown_2224)
{
    PopplerFontType result = poppler_fonts_iter_get_font_type(nullptr);
    EXPECT_EQ(result, POPPLER_FONT_TYPE_UNKNOWN);
}

// Test that a valid iterator with a valid FontInfo returns the correct font type
// Since we can't easily construct FontInfo without GfxFont/XRef, we test what we can
// The null case is the primary testable boundary condition through the public interface

TEST_F(PopplerFontsIterGetFontTypeTest_2224, NullIterReturnsUnknownType_2224)
{
    // Verify the return value is specifically POPPLER_FONT_TYPE_UNKNOWN (0)
    PopplerFontType result = poppler_fonts_iter_get_font_type(NULL);
    EXPECT_EQ(result, POPPLER_FONT_TYPE_UNKNOWN);
    EXPECT_EQ(static_cast<int>(result), 0);
}

// Verify enum values are as expected for completeness
TEST_F(PopplerFontsIterGetFontTypeTest_2224, EnumValuesAreCorrect_2224)
{
    EXPECT_EQ(POPPLER_FONT_TYPE_UNKNOWN, 0);
    EXPECT_EQ(POPPLER_FONT_TYPE_TYPE1, 1);
    EXPECT_EQ(POPPLER_FONT_TYPE_TYPE1C, 2);
    EXPECT_EQ(POPPLER_FONT_TYPE_TYPE1COT, 3);
    EXPECT_EQ(POPPLER_FONT_TYPE_TYPE3, 4);
    EXPECT_EQ(POPPLER_FONT_TYPE_TRUETYPE, 5);
    EXPECT_EQ(POPPLER_FONT_TYPE_TRUETYPEOT, 6);
    EXPECT_EQ(POPPLER_FONT_TYPE_CID_TYPE0, 7);
    EXPECT_EQ(POPPLER_FONT_TYPE_CID_TYPE0C, 8);
    EXPECT_EQ(POPPLER_FONT_TYPE_CID_TYPE0COT, 9);
    EXPECT_EQ(POPPLER_FONT_TYPE_CID_TYPE2, 10);
    EXPECT_EQ(POPPLER_FONT_TYPE_CID_TYPE2OT, 11);
}

// Test multiple consecutive calls with nullptr to ensure consistent behavior
TEST_F(PopplerFontsIterGetFontTypeTest_2224, MultipleNullCallsReturnSameResult_2224)
{
    PopplerFontType result1 = poppler_fonts_iter_get_font_type(nullptr);
    PopplerFontType result2 = poppler_fonts_iter_get_font_type(nullptr);
    PopplerFontType result3 = poppler_fonts_iter_get_font_type(nullptr);
    EXPECT_EQ(result1, POPPLER_FONT_TYPE_UNKNOWN);
    EXPECT_EQ(result2, POPPLER_FONT_TYPE_UNKNOWN);
    EXPECT_EQ(result3, POPPLER_FONT_TYPE_UNKNOWN);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
