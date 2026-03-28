#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"

// Since we need GfxState to construct TextFontInfo, and we're treating
// the implementation as a black box, we test observable behavior through
// the public interface.

class TextFontInfoTest_1176 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid GfxState to construct TextFontInfo objects.
        // Since constructing GfxState requires complex setup, we'll
        // create minimal state objects where possible.
    }
};

// Helper to create a GfxState with a specific font if possible
// Since we can't easily mock GfxState internals, we test what we can
// with nullptr or minimal state.

// Test that TextFontInfo can be constructed with a GfxState that has no font set
// This tests boundary/null conditions
TEST_F(TextFontInfoTest_1176, ConstructWithNullFontState_1176) {
    // Create a minimal GfxState - this may or may not have a font
    // We test that construction doesn't crash with a basic state
    // GfxState with no font should result in a TextFontInfo with no font info
    
    // Create a basic PDFRectangle and GfxState
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // With no font set, these should return safe defaults
    EXPECT_EQ(fontInfo.getFontName(), nullptr);
}

TEST_F(TextFontInfoTest_1176, IsSymbolicWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // With no font, symbolic flag should be false
    EXPECT_FALSE(fontInfo.isSymbolic());
}

TEST_F(TextFontInfoTest_1176, IsFixedWidthWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    EXPECT_FALSE(fontInfo.isFixedWidth());
}

TEST_F(TextFontInfoTest_1176, IsSerifWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    EXPECT_FALSE(fontInfo.isSerif());
}

TEST_F(TextFontInfoTest_1176, IsItalicWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    EXPECT_FALSE(fontInfo.isItalic());
}

TEST_F(TextFontInfoTest_1176, IsBoldWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    EXPECT_FALSE(fontInfo.isBold());
}

TEST_F(TextFontInfoTest_1176, GetAscentWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // With no font, ascent should be some default value
    double ascent = fontInfo.getAscent();
    // Just verify it returns a finite number
    EXPECT_FALSE(std::isnan(ascent));
}

TEST_F(TextFontInfoTest_1176, GetDescentWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    double descent = fontInfo.getDescent();
    EXPECT_FALSE(std::isnan(descent));
}

TEST_F(TextFontInfoTest_1176, GetWModeWithNoFont_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // Default writing mode should be horizontal
    GfxFont::WritingMode wmode = fontInfo.getWMode();
    // Just test it returns a valid value (0 for horizontal typically)
    EXPECT_GE(static_cast<int>(wmode), 0);
}

TEST_F(TextFontInfoTest_1176, MatchesSameState_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // A TextFontInfo created from the same state should match
    EXPECT_TRUE(fontInfo.matches(&state));
}

TEST_F(TextFontInfoTest_1176, MatchesSelf_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // A TextFontInfo should match itself
    EXPECT_TRUE(fontInfo.matches(&fontInfo));
}

TEST_F(TextFontInfoTest_1176, MatchesDifferentState_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state1(72.0, 72.0, &box, 0, false);
    GfxState state2(72.0, 72.0, &box, 0, false);
    
    TextFontInfo fontInfo1(&state1);
    TextFontInfo fontInfo2(&state2);
    
    // Two TextFontInfo objects from states with no font should match
    // (both have null font)
    EXPECT_TRUE(fontInfo1.matches(&fontInfo2));
}

TEST_F(TextFontInfoTest_1176, CopyConstructorDeleted_1176) {
    // Verify copy constructor is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_constructible<TextFontInfo>::value);
}

TEST_F(TextFontInfoTest_1176, CopyAssignmentDeleted_1176) {
    // Verify copy assignment is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_assignable<TextFontInfo>::value);
}

TEST_F(TextFontInfoTest_1176, MatchesWithRef_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    // Test matching with a Ref - with no font, any ref should not match
    Ref ref = Ref::INVALID();
    // This tests the ref-based matching
    bool result = fontInfo.matches(&ref);
    // With no font set, we can't predict the exact behavior,
    // but it should not crash
    (void)result;
}

TEST_F(TextFontInfoTest_1176, AscentGreaterThanOrEqualDescent_1176) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextFontInfo fontInfo(&state);
    
    double ascent = fontInfo.getAscent();
    double descent = fontInfo.getDescent();
    
    // Ascent should typically be greater than or equal to descent
    // (ascent is positive, descent is negative or zero for most fonts)
    EXPECT_GE(ascent, descent);
}
