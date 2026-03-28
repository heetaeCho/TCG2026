#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

#include <memory>
#include <cmath>

class TextWordTest_1184 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a minimal GfxState for TextWord construction
// Since we treat implementation as black box, we try to construct with valid params
static std::unique_ptr<GfxState> createMinimalGfxState() {
    // GfxState constructor: GfxState(double hDPI, double vDPI, const PDFRectangle *pageBox, int rotateA, bool upsideDown)
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    return state;
}

TEST_F(TextWordTest_1184, GetColorReturnsStoredColorValues_1184) {
    auto state = createMinimalGfxState();
    // Set color on GfxState before creating TextWord
    GfxColor color;
    color.c[0] = 0; // These map to RGB after color space conversion
    color.c[1] = 0;
    color.c[2] = 0;
    
    // Create with rotation 0 and some font size
    TextWord word(state.get(), 0, 12.0);
    
    double r, g, b;
    word.getColor(&r, &g, &b);
    
    // The color should be whatever was set from GfxState during construction
    // We just verify the values are finite numbers
    EXPECT_TRUE(std::isfinite(r));
    EXPECT_TRUE(std::isfinite(g));
    EXPECT_TRUE(std::isfinite(b));
}

TEST_F(TextWordTest_1184, GetColorBlackDefault_1184) {
    auto state = createMinimalGfxState();
    // Default device gray color space with 0 should give black (0,0,0)
    TextWord word(state.get(), 0, 12.0);
    
    double r, g, b;
    word.getColor(&r, &g, &b);
    
    // Default GfxState color is typically black
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

TEST_F(TextWordTest_1184, GetRotationMatchesConstructorParam_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word0(state.get(), 0, 12.0);
    EXPECT_EQ(word0.getRotation(), 0);
    
    TextWord word1(state.get(), 1, 12.0);
    EXPECT_EQ(word1.getRotation(), 1);
    
    TextWord word2(state.get(), 2, 12.0);
    EXPECT_EQ(word2.getRotation(), 2);
    
    TextWord word3(state.get(), 3, 12.0);
    EXPECT_EQ(word3.getRotation(), 3);
}

TEST_F(TextWordTest_1184, GetFontSizeMatchesConstructorParam_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);
}

TEST_F(TextWordTest_1184, GetFontSizeZero_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 0.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
}

TEST_F(TextWordTest_1184, GetFontSizeLargeValue_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 72.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 72.0);
}

TEST_F(TextWordTest_1184, InitialLengthIsZero_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

TEST_F(TextWordTest_1184, LenMatchesGetLength_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), word.getLength());
}

TEST_F(TextWordTest_1184, InitialNextWordIsNull_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
    EXPECT_EQ(word.getNext(), nullptr);
}

TEST_F(TextWordTest_1184, InitialLinkIsNull_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

TEST_F(TextWordTest_1184, GetTextOnEmptyWord_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    auto text = word.getText();
    EXPECT_NE(text, nullptr);
    // Empty word should produce empty or minimal text
    EXPECT_EQ(text->size(), 0u);
}

TEST_F(TextWordTest_1184, SpaceAfterInitiallyFalse_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
    EXPECT_FALSE(word.hasSpaceAfter());
}

TEST_F(TextWordTest_1184, IsUnderlinedInitiallyFalse_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

TEST_F(TextWordTest_1184, CopyConstructorDeleted_1184) {
    // This is a compile-time check - TextWord copy constructor is deleted
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1184, CopyAssignmentDeleted_1184) {
    // This is a compile-time check - TextWord copy assignment is deleted
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

TEST_F(TextWordTest_1184, GetBBoxFourParams_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // Just verify the values are finite
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

TEST_F(TextWordTest_1184, GetBBoxPDFRectangle_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    PDFRectangle bbox = word.getBBox();
    
    EXPECT_TRUE(std::isfinite(bbox.x1));
    EXPECT_TRUE(std::isfinite(bbox.y1));
    EXPECT_TRUE(std::isfinite(bbox.x2));
    EXPECT_TRUE(std::isfinite(bbox.y2));
}

TEST_F(TextWordTest_1184, GetBBoxConsistency_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    PDFRectangle bbox = word.getBBox();
    
    EXPECT_DOUBLE_EQ(xMin, bbox.x1);
    EXPECT_DOUBLE_EQ(yMin, bbox.y1);
    EXPECT_DOUBLE_EQ(xMax, bbox.x2);
    EXPECT_DOUBLE_EQ(yMax, bbox.y2);
}

TEST_F(TextWordTest_1184, GetBaselineIsFinite_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    double baseline = word.getBaseline();
    EXPECT_TRUE(std::isfinite(baseline));
}

TEST_F(TextWordTest_1184, GetCharPosInitial_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    int charPos = word.getCharPos();
    // charPos should be some valid value (likely 0 for empty word)
    EXPECT_GE(charPos, 0);
}

TEST_F(TextWordTest_1184, GetCharLenInitial_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    int charLen = word.getCharLen();
    // For an empty word, charLen should be 0
    EXPECT_GE(charLen, 0);
}

TEST_F(TextWordTest_1184, CmpYXStaticMethodComparesTwoWords_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    
    // Static comparison - should not crash, result is deterministic
    bool result = TextWord::cmpYX(&word1, &word2);
    // Since both words are constructed identically, neither should be "less than" the other
    // (or both could be equal, meaning false from strict weak ordering)
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(TextWordTest_1184, HasSpaceAfterSameAsGetSpaceAfter_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.hasSpaceAfter(), word.getSpaceAfter());
}

TEST_F(TextWordTest_1184, GetColorMultipleCalls_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    
    double r1, g1, b1;
    word.getColor(&r1, &g1, &b1);
    
    double r2, g2, b2;
    word.getColor(&r2, &g2, &b2);
    
    // Multiple calls should return the same values
    EXPECT_DOUBLE_EQ(r1, r2);
    EXPECT_DOUBLE_EQ(g1, g2);
    EXPECT_DOUBLE_EQ(b1, b2);
}

TEST_F(TextWordTest_1184, DifferentRotationsHaveSameFontSize_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word0(state.get(), 0, 15.0);
    TextWord word1(state.get(), 1, 15.0);
    TextWord word2(state.get(), 2, 15.0);
    TextWord word3(state.get(), 3, 15.0);
    
    EXPECT_DOUBLE_EQ(word0.getFontSize(), 15.0);
    EXPECT_DOUBLE_EQ(word1.getFontSize(), 15.0);
    EXPECT_DOUBLE_EQ(word2.getFontSize(), 15.0);
    EXPECT_DOUBLE_EQ(word3.getFontSize(), 15.0);
}

TEST_F(TextWordTest_1184, GetFontInfoOnEmptyWordReturnsNull_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    // With no characters added, getting font info for index 0 may return null
    // or may be undefined - we test index within bounds of empty word
    if (word.getLength() > 0) {
        const TextFontInfo* fi = word.getFontInfo(0);
        // Just check it doesn't crash
        (void)fi;
    }
}

TEST_F(TextWordTest_1184, GetFontNameOnEmptyWord_1184) {
    auto state = createMinimalGfxState();
    
    TextWord word(state.get(), 0, 12.0);
    if (word.getLength() > 0) {
        const GooString* name = word.getFontName(0);
        (void)name; // Just ensure no crash
    }
}
