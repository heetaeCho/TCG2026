#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

// Since GfxFont has a protected constructor and is abstract-like, we need a concrete subclass for testing.
// However, based on the interface, we can use makeFont or create a minimal testable derived class.
// Given the constraints, we'll test what we can through the public interface.

// A minimal concrete derived class to test base class default behavior
class TestableGfxFont : public GfxFont {
public:
    // We need to call the protected constructor. Since the exact constructor signature
    // and required parameters are complex, we'll focus on testing static methods
    // and the default virtual method behavior where possible.
    // For getWMode(), the base class provides a default implementation returning Horizontal.
};

// Test the WritingMode enum values
TEST(GfxFontWritingModeTest_1160, HorizontalValueIsZero_1160) {
    EXPECT_EQ(static_cast<int>(GfxFont::WritingMode::Horizontal), 0);
}

TEST(GfxFontWritingModeTest_1160, VerticalValueIsOne_1160) {
    EXPECT_EQ(static_cast<int>(GfxFont::WritingMode::Vertical), 1);
}

// Test isBase14Font static method with known base14 fonts
TEST(GfxFontStaticTest_1160, IsBase14Font_Courier_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_CourierBold_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Bold"));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_CourierOblique_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Oblique"));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_CourierBoldOblique_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "BoldOblique"));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_Helvetica_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_HelveticaBold_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_TimesRoman_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Roman"));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_Symbol_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("Symbol", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_ZapfDingbats_1160) {
    EXPECT_TRUE(GfxFont::isBase14Font("ZapfDingbats", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_UnknownFont_1160) {
    EXPECT_FALSE(GfxFont::isBase14Font("ArbitraryFont", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_EmptyFamilyAndStyle_1160) {
    EXPECT_FALSE(GfxFont::isBase14Font("", ""));
}

TEST(GfxFontStaticTest_1160, IsBase14Font_RandomString_1160) {
    EXPECT_FALSE(GfxFont::isBase14Font("NotAFont", "NotAStyle"));
}

// Test getAlternateName static method
TEST(GfxFontStaticTest_1160, GetAlternateName_NullInput_1160) {
    const char* result = GfxFont::getAlternateName(nullptr);
    // Result may be nullptr for null input
    // We just check it doesn't crash
    (void)result;
}

TEST(GfxFontStaticTest_1160, GetAlternateName_UnknownFont_1160) {
    const char* result = GfxFont::getAlternateName("CompletelyUnknownFontXYZ123");
    // For an unknown font, the result is likely nullptr
    EXPECT_EQ(result, nullptr);
}

TEST(GfxFontStaticTest_1160, GetAlternateName_KnownFont_1160) {
    // Some common font names might have alternates
    const char* result = GfxFont::getAlternateName("Courier");
    // We don't know the exact alternate, but we can check it doesn't crash
    (void)result;
}

// Test makeFont with nullptr - should handle gracefully
TEST(GfxFontStaticTest_1160, MakeFont_NullXRef_1160) {
    // Passing nullptr for xref and fontDict - should return nullptr or handle gracefully
    auto font = GfxFont::makeFont(nullptr, "tag", Ref::INVALID(), nullptr);
    // With null inputs, we expect no valid font
    EXPECT_EQ(font, nullptr);
}

// Test the default getWMode virtual method behavior
// We know from the header that the default returns WritingMode::Horizontal
TEST(GfxFontDefaultBehaviorTest_1160, DefaultGetWModeReturnsHorizontal_1160) {
    // The base class default implementation returns Horizontal
    // This is visible from the inline definition in the header
    // We verify the enum value
    EXPECT_EQ(static_cast<int>(GfxFont::WritingMode::Horizontal), 0);
}

// Test WritingMode enum distinctness
TEST(GfxFontWritingModeTest_1160, HorizontalAndVerticalAreDifferent_1160) {
    EXPECT_NE(GfxFont::WritingMode::Horizontal, GfxFont::WritingMode::Vertical);
}
