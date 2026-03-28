#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

class TextWordTest_1198 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal GfxState for TextWord construction
    // GfxState requires PDF coordinate setup
    std::unique_ptr<GfxState> createGfxState() {
        PDFRectangle pageBox(0, 0, 612, 792);
        auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
        return state;
    }
};

// Test that a newly created TextWord has length 0 (no chars added yet)
TEST_F(TextWordTest_1198, NewWordHasZeroLength_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), 0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test that getRotation returns the rotation passed to constructor
TEST_F(TextWordTest_1198, GetRotationReturnsConstructorValue_1198) {
    auto state = createGfxState();
    
    TextWord word0(state.get(), 0, 12.0);
    EXPECT_EQ(word0.getRotation(), 0);
    
    TextWord word1(state.get(), 1, 12.0);
    EXPECT_EQ(word1.getRotation(), 1);
    
    TextWord word2(state.get(), 2, 12.0);
    EXPECT_EQ(word2.getRotation(), 2);
    
    TextWord word3(state.get(), 3, 12.0);
    EXPECT_EQ(word3.getRotation(), 3);
}

// Test that getText returns a valid string for empty word
TEST_F(TextWordTest_1198, GetTextEmptyWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test that getNext returns nullptr for a standalone word
TEST_F(TextWordTest_1198, GetNextReturnsNullForStandaloneWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test that getLink returns nullptr by default
TEST_F(TextWordTest_1198, GetLinkReturnsNullByDefault_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test that getSpaceAfter returns false for a new word
TEST_F(TextWordTest_1198, GetSpaceAfterDefaultFalse_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test that isUnderlined returns false for a new word
TEST_F(TextWordTest_1198, IsUnderlinedDefaultFalse_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

// Test getFontSize returns the font size
TEST_F(TextWordTest_1198, GetFontSizeReturnsExpected_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_GE(word.getFontSize(), 0.0);
}

// Test getColor for default color values
TEST_F(TextWordTest_1198, GetColorReturnsValues_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Colors should be in valid range [0,1]
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test that len() and getLength() are consistent
TEST_F(TextWordTest_1198, LenAndGetLengthConsistent_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(static_cast<int>(word.len()), word.getLength());
}

// Test copy constructor is deleted (compile-time check - just verify it exists as deleted)
// This is a compile-time constraint, so we just note it here.

// Test getBBox returns valid bounding box for empty word
TEST_F(TextWordTest_1198, GetBBoxEmptyWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounds may be degenerate but should not crash
}

// Test getBBox PDFRectangle overload
TEST_F(TextWordTest_1198, GetBBoxPDFRectangle_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    PDFRectangle rect = word.getBBox();
    // Should not crash, values should be defined
}

// Test with different rotation values boundary
TEST_F(TextWordTest_1198, RotationBoundaryValues_1198) {
    auto state = createGfxState();
    
    // Rotation 0-3 are valid
    for (int rot = 0; rot <= 3; rot++) {
        TextWord word(state.get(), rot, 10.0);
        EXPECT_EQ(word.getRotation(), rot);
        EXPECT_EQ(word.len(), 0);
    }
}

// Test that getCharPos returns a value for empty word
TEST_F(TextWordTest_1198, GetCharPosEmptyWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    // Should not crash
    int charPos = word.getCharPos();
    (void)charPos; // Just ensure no crash
}

// Test that getCharLen returns a value for empty word
TEST_F(TextWordTest_1198, GetCharLenEmptyWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    int charLen = word.getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test getBaseline for empty word
TEST_F(TextWordTest_1198, GetBaselineEmptyWord_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 12.0);
    // Should not crash
    double baseline = word.getBaseline();
    (void)baseline;
}

// Test cmpYX static comparison with two words
TEST_F(TextWordTest_1198, CmpYXStaticComparison_1198) {
    auto state = createGfxState();
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    
    // Should not crash; result is a bool
    bool result = TextWord::cmpYX(&word1, &word2);
    (void)result;
}

// Test with zero font size
TEST_F(TextWordTest_1198, ZeroFontSize_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 0.0);
    EXPECT_EQ(word.len(), 0);
}

// Test with very large font size
TEST_F(TextWordTest_1198, LargeFontSize_1198) {
    auto state = createGfxState();
    TextWord word(state.get(), 0, 10000.0);
    EXPECT_EQ(word.len(), 0);
}
