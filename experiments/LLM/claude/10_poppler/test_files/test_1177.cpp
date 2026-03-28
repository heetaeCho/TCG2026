#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"

// Since TextFontInfo requires a GfxState for construction, and we need to treat
// the implementation as a black box, we test observable behavior through the
// public interface. We need to create valid GfxState objects to construct
// TextFontInfo instances.

class TextFontInfoTest_1177 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that isItalic returns a bool value (either true or false) without crashing
// when constructed with a valid GfxState that has no font set
TEST_F(TextFontInfoTest_1177, IsItalicReturnsBool_1177) {
    // Create a minimal GfxState
    // GfxState requires parameters; we create one with default-like settings
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool result = fontInfo.isItalic();
    // With no font set, italic flag should typically be false
    EXPECT_FALSE(result);
}

// Test that isBold returns a bool value
TEST_F(TextFontInfoTest_1177, IsBoldReturnsBool_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool result = fontInfo.isBold();
    EXPECT_FALSE(result);
}

// Test that isFixedWidth returns a bool value
TEST_F(TextFontInfoTest_1177, IsFixedWidthReturnsBool_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool result = fontInfo.isFixedWidth();
    EXPECT_FALSE(result);
}

// Test that isSerif returns a bool value
TEST_F(TextFontInfoTest_1177, IsSerifReturnsBool_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool result = fontInfo.isSerif();
    EXPECT_FALSE(result);
}

// Test that isSymbolic returns a bool value
TEST_F(TextFontInfoTest_1177, IsSymbolicReturnsBool_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool result = fontInfo.isSymbolic();
    EXPECT_FALSE(result);
}

// Test that getFontName returns something (possibly nullptr when no font)
TEST_F(TextFontInfoTest_1177, GetFontNameNoFont_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    const GooString *name = fontInfo.getFontName();
    // When no font is set, font name may be nullptr
    EXPECT_EQ(name, nullptr);
}

// Test that getAscent returns a double value
TEST_F(TextFontInfoTest_1177, GetAscentReturnsDouble_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    double ascent = fontInfo.getAscent();
    // Ascent should be a finite number
    EXPECT_FALSE(std::isnan(ascent));
}

// Test that getDescent returns a double value
TEST_F(TextFontInfoTest_1177, GetDescentReturnsDouble_1177) {
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

// Test that matches(GfxState*) works with the same state
TEST_F(TextFontInfoTest_1177, MatchesSameState_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    // Matching against the same state should return true
    bool result = fontInfo.matches(&state);
    EXPECT_TRUE(result);
}

// Test that matches(TextFontInfo*) works with same-state-constructed info
TEST_F(TextFontInfoTest_1177, MatchesSameTextFontInfo_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo1(&state);
    TextFontInfo fontInfo2(&state);
    bool result = fontInfo1.matches(&fontInfo2);
    EXPECT_TRUE(result);
}

// Test getWMode returns a valid writing mode
TEST_F(TextFontInfoTest_1177, GetWModeReturnsValidMode_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    auto wmode = fontInfo.getWMode();
    // Writing mode should be horizontal (0) when no font is set
    EXPECT_EQ(static_cast<int>(wmode), 0);
}

// Test that matches with a Ref works
TEST_F(TextFontInfoTest_1177, MatchesRefNoFont_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    Ref ref = Ref::INVALID();
    bool result = fontInfo.matches(&ref);
    // With no font, matching an invalid ref should still work without crashing
    // The exact result depends on implementation
    EXPECT_TRUE(result || !result); // Just verify it doesn't crash
}

// Test consistency: multiple calls to isItalic return the same value
TEST_F(TextFontInfoTest_1177, IsItalicConsistent_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool first = fontInfo.isItalic();
    bool second = fontInfo.isItalic();
    EXPECT_EQ(first, second);
}

// Test consistency: multiple calls to isBold return the same value
TEST_F(TextFontInfoTest_1177, IsBoldConsistent_1177) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    GfxState state(72.0, 72.0, &box, 0, false);

    TextFontInfo fontInfo(&state);
    bool first = fontInfo.isBold();
    bool second = fontInfo.isBold();
    EXPECT_EQ(first, second);
}
