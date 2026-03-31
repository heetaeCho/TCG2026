#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

class TextWordTest_1197 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal GfxState for TextWord construction
        // We need a basic PDF rectangle and CTM
        PDFRectangle pageBox(0, 0, 612, 792);
        auto *state = new GfxState(72.0, 72.0, &pageBox, 0, false);
        gfxState = state;
    }

    void TearDown() override {
        delete gfxState;
    }

    GfxState *gfxState = nullptr;
};

TEST_F(TextWordTest_1197, ConstructionWithRotation0_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.getRotation(), 0);
}

TEST_F(TextWordTest_1197, ConstructionWithRotation1_1197) {
    TextWord word(gfxState, 1, 12.0);
    EXPECT_EQ(word.getRotation(), 1);
}

TEST_F(TextWordTest_1197, ConstructionWithRotation2_1197) {
    TextWord word(gfxState, 2, 12.0);
    EXPECT_EQ(word.getRotation(), 2);
}

TEST_F(TextWordTest_1197, ConstructionWithRotation3_1197) {
    TextWord word(gfxState, 3, 12.0);
    EXPECT_EQ(word.getRotation(), 3);
}

TEST_F(TextWordTest_1197, GetFontSizeReturnsCorrectValue_1197) {
    TextWord word(gfxState, 0, 14.5);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 14.5);
}

TEST_F(TextWordTest_1197, GetFontSizeZero_1197) {
    TextWord word(gfxState, 0, 0.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
}

TEST_F(TextWordTest_1197, InitialLengthIsZero_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

TEST_F(TextWordTest_1197, InitialLenIsZero_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.len(), 0);
}

TEST_F(TextWordTest_1197, GetTextInitiallyEmpty_1197) {
    TextWord word(gfxState, 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

TEST_F(TextWordTest_1197, NextWordInitiallyNull_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
}

TEST_F(TextWordTest_1197, GetNextInitiallyNull_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
}

TEST_F(TextWordTest_1197, NextWordAndGetNextConsistent_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.nextWord(), word.getNext());
}

TEST_F(TextWordTest_1197, GetLinkInitiallyNull_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

TEST_F(TextWordTest_1197, SpaceAfterInitiallyFalse_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
}

TEST_F(TextWordTest_1197, HasSpaceAfterInitiallyFalse_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_FALSE(word.hasSpaceAfter());
}

TEST_F(TextWordTest_1197, SpaceAfterConsistentWithHasSpaceAfter_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_EQ(word.getSpaceAfter(), word.hasSpaceAfter());
}

TEST_F(TextWordTest_1197, IsUnderlinedInitiallyFalse_1197) {
    TextWord word(gfxState, 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

TEST_F(TextWordTest_1197, GetColorReturnsValues_1197) {
    TextWord word(gfxState, 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Color values should be in valid range [0, 1]
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

TEST_F(TextWordTest_1197, GetBBoxFourParams_1197) {
    TextWord word(gfxState, 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // Just verify it doesn't crash and returns some values
    // For an empty word, bounds might be degenerate
    SUCCEED();
}

TEST_F(TextWordTest_1197, GetBBoxReturnsRect_1197) {
    TextWord word(gfxState, 0, 12.0);
    PDFRectangle rect = word.getBBox();
    // Verify the rect version is consistent with the pointer version
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(rect.x1, xMin);
    EXPECT_DOUBLE_EQ(rect.y1, yMin);
    EXPECT_DOUBLE_EQ(rect.x2, xMax);
    EXPECT_DOUBLE_EQ(rect.y2, yMax);
}

TEST_F(TextWordTest_1197, CmpYXStaticComparison_1197) {
    TextWord word1(gfxState, 0, 12.0);
    TextWord word2(gfxState, 0, 12.0);
    // Just verify the static method can be called without crash
    bool result = TextWord::cmpYX(&word1, &word2);
    // Two identically constructed words should have some deterministic comparison
    (void)result;
    SUCCEED();
}

TEST_F(TextWordTest_1197, GetCharPosInitial_1197) {
    TextWord word(gfxState, 0, 12.0);
    int charPos = word.getCharPos();
    // For an empty word, charPos should be some initial value
    (void)charPos;
    SUCCEED();
}

TEST_F(TextWordTest_1197, GetCharLenInitial_1197) {
    TextWord word(gfxState, 0, 12.0);
    int charLen = word.getCharLen();
    // For an empty word with no chars added
    (void)charLen;
    SUCCEED();
}

TEST_F(TextWordTest_1197, LargeFontSize_1197) {
    TextWord word(gfxState, 0, 1000.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 1000.0);
}

TEST_F(TextWordTest_1197, SmallFontSize_1197) {
    TextWord word(gfxState, 0, 0.001);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.001);
}

TEST_F(TextWordTest_1197, NegativeFontSize_1197) {
    TextWord word(gfxState, 0, -1.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), -1.0);
}

TEST_F(TextWordTest_1197, GetFontInfoOnEmptyWord_1197) {
    TextWord word(gfxState, 0, 12.0);
    // No chars added, so fontInfo at index 0 should be nullptr or not crash
    // This might be undefined for empty word, but we test it doesn't crash
    if (word.getLength() > 0) {
        const TextFontInfo *fi = word.getFontInfo(0);
        (void)fi;
    }
    SUCCEED();
}

TEST_F(TextWordTest_1197, GetFontNameOnEmptyWord_1197) {
    TextWord word(gfxState, 0, 12.0);
    if (word.getLength() > 0) {
        const GooString *name = word.getFontName(0);
        (void)name;
    }
    SUCCEED();
}

TEST_F(TextWordTest_1197, PrimaryCompareWithSelf_1197) {
    TextWord word(gfxState, 0, 12.0);
    int cmp = word.primaryCmp(&word);
    // Comparing with self should return 0 (equal)
    EXPECT_EQ(cmp, 0);
}

TEST_F(TextWordTest_1197, PrimaryDeltaWithSelf_1197) {
    TextWord word(gfxState, 0, 12.0);
    double delta = word.primaryDelta(&word);
    // Delta with self should be 0
    EXPECT_DOUBLE_EQ(delta, 0.0);
}

TEST_F(TextWordTest_1197, CopyConstructorDeleted_1197) {
    // Verify copy constructor is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1197, CopyAssignmentDeleted_1197) {
    // Verify copy assignment is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}
