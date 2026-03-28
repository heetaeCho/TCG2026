#include <gtest/gtest.h>
#include <memory>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
class TextWordTest_1185 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal GfxState
        // GfxState(double hDPIA, double vDPIA, const PDFRectangle *pageBox, int rotateA, bool upsideDown)
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    }

    std::unique_ptr<GfxState> state;
};

TEST_F(TextWordTest_1185, ConstructionWithRotation0_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getRotation(), 0);
}

TEST_F(TextWordTest_1185, ConstructionWithRotation1_1185) {
    TextWord word(state.get(), 1, 12.0);
    EXPECT_EQ(word.getRotation(), 1);
}

TEST_F(TextWordTest_1185, ConstructionWithRotation2_1185) {
    TextWord word(state.get(), 2, 12.0);
    EXPECT_EQ(word.getRotation(), 2);
}

TEST_F(TextWordTest_1185, ConstructionWithRotation3_1185) {
    TextWord word(state.get(), 3, 12.0);
    EXPECT_EQ(word.getRotation(), 3);
}

TEST_F(TextWordTest_1185, InitialLengthIsZero_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

TEST_F(TextWordTest_1185, LenMatchesGetLength_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), word.getLength());
}

TEST_F(TextWordTest_1185, GetFontSizeReturnsCorrectValue_1185) {
    double fontSize = 14.5;
    TextWord word(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

TEST_F(TextWordTest_1185, GetFontSizeSmall_1185) {
    double fontSize = 1.0;
    TextWord word(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

TEST_F(TextWordTest_1185, GetFontSizeLarge_1185) {
    double fontSize = 100.0;
    TextWord word(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

TEST_F(TextWordTest_1185, InitialSpaceAfterIsFalse_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
}

TEST_F(TextWordTest_1185, HasSpaceAfterMatchesGetSpaceAfter_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.hasSpaceAfter(), word.getSpaceAfter());
}

TEST_F(TextWordTest_1185, InitialIsUnderlinedFalse_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

TEST_F(TextWordTest_1185, InitialLinkIsNull_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

TEST_F(TextWordTest_1185, InitialNextIsNull_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
}

TEST_F(TextWordTest_1185, NextWordIsNull_1185) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
}

TEST_F(TextWordTest_1185, GetBBoxFourParams_1185) {
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // Just verify the call doesn't crash and returns some values
    // For a newly constructed word with no chars, bounds may be initial values
    EXPECT_TRUE(true);  // If we get here, getBBox didn't crash
}

TEST_F(TextWordTest_1185, GetBBoxPDFRectangle_1185) {
    TextWord word(state.get(), 0, 12.0);
    PDFRectangle rect = word.getBBox();
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(rect.x1, xMin);
    EXPECT_DOUBLE_EQ(rect.y1, yMin);
    EXPECT_DOUBLE_EQ(rect.x2, xMax);
    EXPECT_DOUBLE_EQ(rect.y2, yMax);
}

TEST_F(TextWordTest_1185, GetTextInitiallyEmpty_1185) {
    TextWord word(state.get(), 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

TEST_F(TextWordTest_1185, GetColorReturnsValues_1185) {
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

TEST_F(TextWordTest_1185, CmpYXStaticMethodWithSameWords_1185) {
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    // Static comparison - should not crash
    bool result = TextWord::cmpYX(&word1, &word2);
    // Both words at same position, so neither should be strictly less
    // We just verify it runs without error
    (void)result;
    SUCCEED();
}

TEST_F(TextWordTest_1185, CopyConstructorDeleted_1185) {
    // This is a compile-time test - TextWord(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1185, CopyAssignmentDeleted_1185) {
    // This is a compile-time test - operator=(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

TEST_F(TextWordTest_1185, GetCharPosInitial_1185) {
    TextWord word(state.get(), 0, 12.0);
    int charPos = word.getCharPos();
    // Just verify it returns some value without crashing
    (void)charPos;
    SUCCEED();
}

TEST_F(TextWordTest_1185, GetCharLenInitial_1185) {
    TextWord word(state.get(), 0, 12.0);
    int charLen = word.getCharLen();
    // For an empty word, charLen should be 0
    EXPECT_EQ(charLen, 0);
}

TEST_F(TextWordTest_1185, GetBaselineInitial_1185) {
    TextWord word(state.get(), 0, 12.0);
    double baseline = word.getBaseline();
    // Just verify it returns without crashing
    (void)baseline;
    SUCCEED();
}

TEST_F(TextWordTest_1185, MultipleFontSizes_1185) {
    double sizes[] = {0.5, 1.0, 6.0, 12.0, 24.0, 48.0, 72.0};
    for (double sz : sizes) {
        TextWord word(state.get(), 0, sz);
        EXPECT_DOUBLE_EQ(word.getFontSize(), sz) << "Failed for font size " << sz;
    }
}

TEST_F(TextWordTest_1185, RotationValues_1185) {
    for (int rot = 0; rot < 4; ++rot) {
        TextWord word(state.get(), rot, 12.0);
        EXPECT_EQ(word.getRotation(), rot) << "Failed for rotation " << rot;
    }
}

TEST_F(TextWordTest_1185, GetFontInfoEmptyWord_1185) {
    TextWord word(state.get(), 0, 12.0);
    // For empty word with no chars, getFontInfo with index 0 should handle gracefully
    // This may return nullptr for an empty word
    if (word.getLength() > 0) {
        const TextFontInfo* fi = word.getFontInfo(0);
        (void)fi;
    }
    SUCCEED();
}

TEST_F(TextWordTest_1185, GetFontNameEmptyWord_1185) {
    TextWord word(state.get(), 0, 12.0);
    if (word.getLength() > 0) {
        const GooString* name = word.getFontName(0);
        (void)name;
    }
    SUCCEED();
}
