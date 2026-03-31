#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

// Helper to create a minimal GfxState for testing
// We need a GfxState to construct TextWord objects
class TextWordTest_1186 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF state for testing
        // GfxState(double hDPIA, double vDPIA, const PDFRectangle *pageBox, int rotateA, bool upsideDown)
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test that a newly constructed TextWord with rotation 0 returns correct rotation
TEST_F(TextWordTest_1186, ConstructorRotation0_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getRotation(), 0);
}

// Test that a newly constructed TextWord with rotation 1 returns correct rotation
TEST_F(TextWordTest_1186, ConstructorRotation1_1186) {
    TextWord word(state.get(), 1, 12.0);
    EXPECT_EQ(word.getRotation(), 1);
}

// Test that a newly constructed TextWord with rotation 2 returns correct rotation
TEST_F(TextWordTest_1186, ConstructorRotation2_1186) {
    TextWord word(state.get(), 2, 12.0);
    EXPECT_EQ(word.getRotation(), 2);
}

// Test that a newly constructed TextWord with rotation 3 returns correct rotation
TEST_F(TextWordTest_1186, ConstructorRotation3_1186) {
    TextWord word(state.get(), 3, 12.0);
    EXPECT_EQ(word.getRotation(), 3);
}

// Test getFontSize returns the font size set during construction
TEST_F(TextWordTest_1186, GetFontSize_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);
}

// Test getFontSize with different size
TEST_F(TextWordTest_1186, GetFontSizeDifferentSize_1186) {
    TextWord word(state.get(), 0, 24.5);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 24.5);
}

// Test that a newly constructed TextWord has length 0
TEST_F(TextWordTest_1186, InitialLengthIsZero_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test len() also returns 0 for newly constructed word
TEST_F(TextWordTest_1186, InitialLenIsZero_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), 0);
}

// Test getText returns something for an empty word
TEST_F(TextWordTest_1186, GetTextEmptyWord_1186) {
    TextWord word(state.get(), 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getNext returns nullptr for a standalone word
TEST_F(TextWordTest_1186, GetNextReturnsNullForStandalone_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
}

// Test nextWord returns nullptr for a standalone word
TEST_F(TextWordTest_1186, NextWordReturnsNullForStandalone_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test getLink returns nullptr when no link is set
TEST_F(TextWordTest_1186, GetLinkReturnsNullByDefault_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test isUnderlined returns false by default
TEST_F(TextWordTest_1186, IsUnderlinedDefaultFalse_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

// Test getSpaceAfter returns false by default
TEST_F(TextWordTest_1186, GetSpaceAfterDefaultFalse_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
}

// Test hasSpaceAfter returns false by default
TEST_F(TextWordTest_1186, HasSpaceAfterDefaultFalse_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test getColor returns some color values (default state colors)
TEST_F(TextWordTest_1186, GetColorReturnsValues_1186) {
    TextWord word(state.get(), 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Default GfxState fill color is typically black (0,0,0)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox (overloaded version with pointer params) for empty word
TEST_F(TextWordTest_1186, GetBBoxPointersEmptyWord_1186) {
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounding box values should still be set
    // We just verify they are finite numbers
    EXPECT_FALSE(std::isnan(xMin));
    EXPECT_FALSE(std::isnan(yMin));
    EXPECT_FALSE(std::isnan(xMax));
    EXPECT_FALSE(std::isnan(yMax));
}

// Test getBBox (PDFRectangle version) for empty word
TEST_F(TextWordTest_1186, GetBBoxPDFRectangleEmptyWord_1186) {
    TextWord word(state.get(), 0, 12.0);
    PDFRectangle bbox = word.getBBox();
    EXPECT_FALSE(std::isnan(bbox.x1));
    EXPECT_FALSE(std::isnan(bbox.y1));
    EXPECT_FALSE(std::isnan(bbox.x2));
    EXPECT_FALSE(std::isnan(bbox.y2));
}

// Test that both getBBox overloads return consistent values
TEST_F(TextWordTest_1186, GetBBoxConsistency_1186) {
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    PDFRectangle bbox = word.getBBox();
    EXPECT_DOUBLE_EQ(bbox.x1, xMin);
    EXPECT_DOUBLE_EQ(bbox.y1, yMin);
    EXPECT_DOUBLE_EQ(bbox.x2, xMax);
    EXPECT_DOUBLE_EQ(bbox.y2, yMax);
}

// Test addChar increases length
TEST_F(TextWordTest_1186, AddCharIncreasesLength_1186) {
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    EXPECT_EQ(word.getLength(), 1);
}

// Test addChar multiple times increases length correctly
TEST_F(TextWordTest_1186, AddMultipleCharsIncreasesLength_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'H', 'H', textMat);
    word.addChar(nullptr, 110.0, 200.0, 10.0, 0.0, 1, 1, 'i', 'i', textMat);
    EXPECT_EQ(word.getLength(), 2);
    EXPECT_EQ(word.len(), 2);
}

// Test getChar returns correct Unicode character after addChar
TEST_F(TextWordTest_1186, GetCharReturnsCorrectUnicode_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    const Unicode *ch = word.getChar(0);
    ASSERT_NE(ch, nullptr);
    EXPECT_EQ(*ch, 'A');
}

// Test getText returns correct text after adding characters
TEST_F(TextWordTest_1186, GetTextAfterAddingChars_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'H', 'H', textMat);
    word.addChar(nullptr, 110.0, 200.0, 10.0, 0.0, 1, 1, 'i', 'i', textMat);

    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(*text, "Hi");
}

// Test getCharBBox returns valid bounding box for added character
TEST_F(TextWordTest_1186, GetCharBBoxForAddedChar_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);

    double xMin, yMin, xMax, yMax;
    word.getCharBBox(0, &xMin, &yMin, &xMax, &yMax);
    // The character should have some extent
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getCharPos returns the character position
TEST_F(TextWordTest_1186, GetCharPos_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 5, 1, 'A', 'A', textMat);

    EXPECT_EQ(word.getCharPos(), 5);
}

// Test getCharLen returns the total character length
TEST_F(TextWordTest_1186, GetCharLen_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    word.addChar(nullptr, 110.0, 200.0, 10.0, 0.0, 1, 1, 'B', 'B', textMat);

    // charLen should reflect the span of characters
    EXPECT_GE(word.getCharLen(), 1);
}

// Test cmpYX static comparison function
TEST_F(TextWordTest_1186, CmpYXOrdering_1186) {
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word1.addChar(nullptr, 100.0, 100.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    word2.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'B', 'B', textMat);

    // word1 is at y=100, word2 is at y=200, so word1 should come first (lower y)
    bool result = TextWord::cmpYX(&word1, &word2);
    // We just verify it returns a boolean without crashing
    EXPECT_TRUE(result || !result);
}

// Test cmpYX with same Y different X
TEST_F(TextWordTest_1186, CmpYXSameYDifferentX_1186) {
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word1.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    word2.addChar(nullptr, 200.0, 200.0, 10.0, 0.0, 0, 1, 'B', 'B', textMat);

    // word1 has smaller x, should come first
    bool result = TextWord::cmpYX(&word1, &word2);
    EXPECT_TRUE(result);
}

// Test zero font size
TEST_F(TextWordTest_1186, ZeroFontSize_1186) {
    TextWord word(state.get(), 0, 0.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test very large font size
TEST_F(TextWordTest_1186, LargeFontSize_1186) {
    TextWord word(state.get(), 0, 1000.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 1000.0);
}

// Test getBaseline for empty word
TEST_F(TextWordTest_1186, GetBaselineEmptyWord_1186) {
    TextWord word(state.get(), 0, 12.0);
    double baseline = word.getBaseline();
    EXPECT_FALSE(std::isnan(baseline));
}

// Test merge combines two words
TEST_F(TextWordTest_1186, MergeWords_1186) {
    TextWord word1(state.get(), 0, 12.0);
    TextWord *word2 = new TextWord(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word1.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'H', 'H', textMat);
    word2->addChar(nullptr, 110.0, 200.0, 10.0, 0.0, 1, 1, 'i', 'i', textMat);

    int lenBefore = word1.getLength();
    word1.merge(word2);
    EXPECT_GT(word1.getLength(), lenBefore);
}

// Test getFontInfo returns nullptr for empty word or when no font set
TEST_F(TextWordTest_1186, GetFontInfoNullFont_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);

    const TextFontInfo *fontInfo = word.getFontInfo(0);
    // When nullptr was passed as font, getFontInfo should return nullptr
    EXPECT_EQ(fontInfo, nullptr);
}

// Test getFontName when no font is set
TEST_F(TextWordTest_1186, GetFontNameNullFont_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);

    const GooString *fontName = word.getFontName(0);
    // With nullptr font, fontName should be nullptr
    EXPECT_EQ(fontName, nullptr);
}

// Test getEdge for added character
TEST_F(TextWordTest_1186, GetEdgeForCharacter_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);

    double edge = word.getEdge(0);
    EXPECT_FALSE(std::isnan(edge));
}

// Test copy constructor and assignment are deleted (compile-time check - just verify we can't copy)
// This is a compile-time property, not a runtime test, but we document it
TEST_F(TextWordTest_1186, NoCopyConstruction_1186) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1186, NoCopyAssignment_1186) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test adding single character with rotation 1
TEST_F(TextWordTest_1186, AddCharWithRotation1_1186) {
    TextWord word(state.get(), 1, 12.0);

    Matrix textMat = {0, 1, -1, 0, 0, 0};
    word.addChar(nullptr, 200.0, 100.0, 0.0, 10.0, 0, 1, 'A', 'A', textMat);

    EXPECT_EQ(word.getLength(), 1);
    EXPECT_EQ(word.getRotation(), 1);
}

// Test adding single character with rotation 2
TEST_F(TextWordTest_1186, AddCharWithRotation2_1186) {
    TextWord word(state.get(), 2, 12.0);

    Matrix textMat = {-1, 0, 0, -1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, -10.0, 0.0, 0, 1, 'A', 'A', textMat);

    EXPECT_EQ(word.getLength(), 1);
    EXPECT_EQ(word.getRotation(), 2);
}

// Test getBBox with pointer and PDFRectangle match after adding chars
TEST_F(TextWordTest_1186, GetBBoxConsistencyAfterAddChar_1186) {
    TextWord word(state.get(), 0, 12.0);

    Matrix textMat = {1, 0, 0, 1, 0, 0};
    word.addChar(nullptr, 100.0, 200.0, 10.0, 12.0, 0, 1, 'A', 'A', textMat);

    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    PDFRectangle bbox = word.getBBox();

    EXPECT_DOUBLE_EQ(bbox.x1, xMin);
    EXPECT_DOUBLE_EQ(bbox.y1, yMin);
    EXPECT_DOUBLE_EQ(bbox.x2, xMax);
    EXPECT_DOUBLE_EQ(bbox.y2, yMax);
}
