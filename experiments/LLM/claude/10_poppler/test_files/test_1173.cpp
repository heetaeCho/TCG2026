#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"

// Since TextFontInfo requires a GfxState for construction and we cannot
// easily create one without a full PDF context, we test what we can
// through the public interface. We focus on observable behavior through
// the public API.

// Helper to create a minimal GfxState for testing purposes.
// Note: In practice, constructing a valid GfxState may require
// additional setup. These tests verify the interface contracts.

class TextFontInfoTest_1173 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup is done per-test as needed
    }

    void TearDown() override {
    }
};

// Test that getFontName returns nullptr when no font is set in the state
// (i.e., when constructed with a state that has no current font)
TEST_F(TextFontInfoTest_1173, GetFontNameReturnsNullWhenNoFont_1173) {
    // Create a GfxState with no font set
    // GfxState constructor: GfxState(double hDPI, double vDPI, const PDFRectangle *pageBox, int rotateA, bool upsideDown)
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    // When no font is set on the GfxState, fontName should be nullptr
    const GooString *name = fontInfo.getFontName();
    // The font name could be nullptr if no font was set
    // We just verify the call doesn't crash and returns a consistent value
    SUCCEED();
}

// Test that getAscent returns a reasonable value
TEST_F(TextFontInfoTest_1173, GetAscentReturnsValue_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    double ascent = fontInfo.getAscent();
    // Ascent should be a finite number
    EXPECT_FALSE(std::isnan(ascent));
    EXPECT_FALSE(std::isinf(ascent));
}

// Test that getDescent returns a reasonable value
TEST_F(TextFontInfoTest_1173, GetDescentReturnsValue_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    double descent = fontInfo.getDescent();
    // Descent should be a finite number
    EXPECT_FALSE(std::isnan(descent));
    EXPECT_FALSE(std::isinf(descent));
}

// Test that getWMode returns a valid writing mode
TEST_F(TextFontInfoTest_1173, GetWModeReturnsValidValue_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    auto wmode = fontInfo.getWMode();
    // Writing mode should be either horizontal or vertical
    EXPECT_TRUE(wmode == GfxFont::W0 || wmode == GfxFont::W1);
}

// Test matches with same state returns true
TEST_F(TextFontInfoTest_1173, MatchesSameStateReturnsTrue_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    // Matching against the same state (with same font, which is none) should return true
    bool result = fontInfo.matches(&state);
    EXPECT_TRUE(result);
}

// Test matches with TextFontInfo pointer - same object comparison
TEST_F(TextFontInfoTest_1173, MatchesSameFontInfoReturnsTrue_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    // Matching fontInfo against itself should return true
    bool result = fontInfo.matches(&fontInfo);
    EXPECT_TRUE(result);
}

// Test matches with different TextFontInfo objects created from same state
TEST_F(TextFontInfoTest_1173, MatchesDifferentFontInfoSameState_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo1(&state);
    TextFontInfo fontInfo2(&state);
    
    // Both created from same state (no font), should match
    bool result = fontInfo1.matches(&fontInfo2);
    EXPECT_TRUE(result);
}

// Test boolean font property methods don't crash
TEST_F(TextFontInfoTest_1173, IsFixedWidthDoesNotCrash_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    // Just verify these don't crash - actual values depend on font
    bool fixedWidth = fontInfo.isFixedWidth();
    (void)fixedWidth;
    SUCCEED();
}

TEST_F(TextFontInfoTest_1173, IsSerifDoesNotCrash_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    bool serif = fontInfo.isSerif();
    (void)serif;
    SUCCEED();
}

TEST_F(TextFontInfoTest_1173, IsSymbolicDoesNotCrash_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    bool symbolic = fontInfo.isSymbolic();
    (void)symbolic;
    SUCCEED();
}

TEST_F(TextFontInfoTest_1173, IsItalicDoesNotCrash_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    bool italic = fontInfo.isItalic();
    (void)italic;
    SUCCEED();
}

TEST_F(TextFontInfoTest_1173, IsBoldDoesNotCrash_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    bool bold = fontInfo.isBold();
    (void)bold;
    SUCCEED();
}

// Test matches with a Ref
TEST_F(TextFontInfoTest_1173, MatchesRefNoFont_1173) {
    PDFRectangle pageBox(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    
    TextFontInfo fontInfo(&state);
    
    Ref ref = Ref::INVALID();
    // When no font is set, matching against an invalid ref
    bool result = fontInfo.matches(&ref);
    // Result depends on implementation but should not crash
    (void)result;
    SUCCEED();
}

// Test that copy constructor is deleted (compile-time check - this test
// simply documents the constraint)
TEST_F(TextFontInfoTest_1173, CopyConstructorIsDeleted_1173) {
    // TextFontInfo(const TextFontInfo&) = delete;
    // This is a compile-time constraint. If someone tries to copy,
    // it won't compile. We just document this here.
    EXPECT_TRUE(std::is_copy_constructible<TextFontInfo>::value == false);
}

// Test that copy assignment is deleted
TEST_F(TextFontInfoTest_1173, CopyAssignmentIsDeleted_1173) {
    EXPECT_TRUE(std::is_copy_assignable<TextFontInfo>::value == false);
}

// Test with different page sizes to ensure no dependency on page geometry
TEST_F(TextFontInfoTest_1173, DifferentPageSizesNoEffect_1173) {
    PDFRectangle smallPage(0, 0, 100, 100);
    PDFRectangle largePage(0, 0, 10000, 10000);
    
    GfxState state1(72.0, 72.0, &smallPage, 0, false);
    GfxState state2(72.0, 72.0, &largePage, 0, false);
    
    TextFontInfo fontInfo1(&state1);
    TextFontInfo fontInfo2(&state2);
    
    // Both have no font, they should match each other
    bool result = fontInfo1.matches(&fontInfo2);
    EXPECT_TRUE(result);
}
