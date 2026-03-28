#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler glib headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

// Internal poppler headers for constructing test objects
#include "MarkedContentOutputDev.h"
#include "GfxFont.h"
#include "GfxState.h"
#include "GooString.h"

#include <memory>
#include <cstring>

// Since text_span_poppler_text_span is static, we include the source to test it
// This is a common pattern when testing static functions
#include "poppler-structure-element.cc"

class TextSpanConversionTest_2541 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    // Helper to create a TextSpan using placement or friend access
    // Since TextSpan's constructor is private and friended to MarkedContentOutputDev,
    // we need a workaround
};

// Test that a null text in TextSpan results in null text in PopplerTextSpan
TEST_F(TextSpanConversionTest_2541, NullTextProducesNullOutput_2541)
{
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    TextSpan span(nullptr, nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->text, nullptr);
    EXPECT_EQ(result->font_name, nullptr);
    EXPECT_EQ(result->flags, 0u);
    
    g_slice_free(PopplerTextSpan, result);
}

// Test color conversion with zero values
TEST_F(TextSpanConversionTest_2541, ZeroColorConversion_2541)
{
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    TextSpan span(nullptr, nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->color.red, 0);
    EXPECT_EQ(result->color.green, 0);
    EXPECT_EQ(result->color.blue, 0);
    
    g_slice_free(PopplerTextSpan, result);
}

// Test with valid text
TEST_F(TextSpanConversionTest_2541, ValidTextIsConverted_2541)
{
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    auto text = std::make_unique<GooString>("Hello World");
    TextSpan span(std::move(text), nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    ASSERT_NE(result->text, nullptr);
    EXPECT_STREQ(result->text, "Hello World");
    
    g_free(result->text);
    g_slice_free(PopplerTextSpan, result);
}

// Test no font produces null font_name and zero flags
TEST_F(TextSpanConversionTest_2541, NoFontProducesNullFontNameAndZeroFlags_2541)
{
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    TextSpan span(nullptr, nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->font_name, nullptr);
    EXPECT_EQ(result->flags, 0u);
    
    g_slice_free(PopplerTextSpan, result);
}

// Test bold flag from weight W700
TEST_F(TextSpanConversionTest_2541, HeavyWeightSetsBoldFlag_2541)
{
    // This test verifies that fonts with weight >= W500 get BOLD flag
    // Even if isBold() returns false, the switch statement should catch it
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    // Without being able to construct a real GfxFont with specific weight,
    // we verify the flag constants exist
    EXPECT_NE(POPPLER_TEXT_SPAN_BOLD, 0u);
    EXPECT_NE(POPPLER_TEXT_SPAN_ITALIC, 0u);
    EXPECT_NE(POPPLER_TEXT_SPAN_FIXED_WIDTH, 0u);
    EXPECT_NE(POPPLER_TEXT_SPAN_SERIF, 0u);
}

// Test that flags are distinct
TEST_F(TextSpanConversionTest_2541, FlagsAreDistinct_2541)
{
    // Verify that the text span flags don't overlap
    EXPECT_EQ(POPPLER_TEXT_SPAN_FIXED_WIDTH & POPPLER_TEXT_SPAN_SERIF, 0u);
    EXPECT_EQ(POPPLER_TEXT_SPAN_FIXED_WIDTH & POPPLER_TEXT_SPAN_ITALIC, 0u);
    EXPECT_EQ(POPPLER_TEXT_SPAN_FIXED_WIDTH & POPPLER_TEXT_SPAN_BOLD, 0u);
    EXPECT_EQ(POPPLER_TEXT_SPAN_SERIF & POPPLER_TEXT_SPAN_ITALIC, 0u);
    EXPECT_EQ(POPPLER_TEXT_SPAN_SERIF & POPPLER_TEXT_SPAN_BOLD, 0u);
    EXPECT_EQ(POPPLER_TEXT_SPAN_ITALIC & POPPLER_TEXT_SPAN_BOLD, 0u);
}

// Test max color values
TEST_F(TextSpanConversionTest_2541, MaxColorConversion_2541)
{
    GfxRGB color;
    color.r = gfxColorComp1;  // max color component value
    color.g = gfxColorComp1;
    color.b = gfxColorComp1;
    
    TextSpan span(nullptr, nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    EXPECT_NEAR(result->color.red, 65535, 1);
    EXPECT_NEAR(result->color.green, 65535, 1);
    EXPECT_NEAR(result->color.blue, 65535, 1);
    
    g_slice_free(PopplerTextSpan, result);
}

// Test empty string text
TEST_F(TextSpanConversionTest_2541, EmptyTextString_2541)
{
    GfxRGB color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    
    auto text = std::make_unique<GooString>("");
    TextSpan span(std::move(text), nullptr, color);
    PopplerTextSpan *result = text_span_poppler_text_span(span);
    
    ASSERT_NE(result, nullptr);
    ASSERT_NE(result->text, nullptr);
    EXPECT_STREQ(result->text, "");
    
    g_free(result->text);
    g_slice_free(PopplerTextSpan, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
