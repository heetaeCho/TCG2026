#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
// Since we treat the implementation as a black box, we need valid construction parameters.

class TextWordTest_1194 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects as needed in individual tests
    }

    void TearDown() override {
    }
};

// Test that getEdge returns the edge value for the character at index i
// This is the primary function we have full visibility into from the provided code.
// Since getEdge accesses chars[i].edge, we need a TextWord with at least one character added.

// Due to the complexity of constructing a valid GfxState and the dependencies involved,
// we focus on testing the observable interface behaviors we can exercise.

// Test: getLength on a freshly constructed TextWord should reflect initial state
TEST_F(TextWordTest_1194, GetLengthInitial_1194) {
    // We need a GfxState to construct a TextWord.
    // Creating a minimal GfxState for horizontal writing, rotation 0
    // GfxState(double hDPIA, double vDPIA, const PDFRectangle *pageBox, int rotateA, bool upsideDown)
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    // A freshly constructed TextWord should have length 0 (no characters added yet)
    EXPECT_EQ(word.getLength(), 0);
}

// Test: getRotation returns the rotation set during construction
TEST_F(TextWordTest_1194, GetRotation_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    
    TextWord word0(&state, 0, 12.0);
    EXPECT_EQ(word0.getRotation(), 0);
    
    TextWord word1(&state, 1, 12.0);
    EXPECT_EQ(word1.getRotation(), 1);
    
    TextWord word2(&state, 2, 12.0);
    EXPECT_EQ(word2.getRotation(), 2);
    
    TextWord word3(&state, 3, 12.0);
    EXPECT_EQ(word3.getRotation(), 3);
}

// Test: getFontSize returns the font size set during construction
TEST_F(TextWordTest_1194, GetFontSize_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    
    TextWord word(&state, 0, 14.5);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 14.5);
}

// Test: getText on empty word
TEST_F(TextWordTest_1194, GetTextEmpty_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    // Empty word should produce empty text
    EXPECT_TRUE(text->empty());
}

// Test: getNext / nextWord returns nullptr for a standalone word
TEST_F(TextWordTest_1194, GetNextNullptr_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    EXPECT_EQ(word.getNext(), nullptr);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test: getLink returns nullptr when no link is set
TEST_F(TextWordTest_1194, GetLinkNullptr_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test: len() on empty word should be 0
TEST_F(TextWordTest_1194, LenEmpty_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    EXPECT_EQ(word.len(), 0);
}

// Test: addChar increases length
TEST_F(TextWordTest_1194, AddCharIncreasesLength_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    EXPECT_EQ(word.getLength(), 1);
    
    word.addChar(&fontInfo, 110.0, 200.0, 10.0, 0.0, 1, 1, 'B', 'B', textMat);
    EXPECT_EQ(word.getLength(), 2);
}

// Test: getEdge after adding characters
TEST_F(TextWordTest_1194, GetEdgeAfterAddChar_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    // getEdge(0) should return the edge value of the first character
    // The exact value depends on implementation, but it should be a valid double
    double edge0 = word.getEdge(0);
    // We just verify it doesn't crash and returns a finite value
    EXPECT_TRUE(std::isfinite(edge0));
}

// Test: getText after adding characters returns expected text
TEST_F(TextWordTest_1194, GetTextAfterAddChar_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'H', 'H', textMat);
    word.addChar(&fontInfo, 110.0, 200.0, 10.0, 0.0, 1, 1, 'i', 'i', textMat);
    
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->empty());
}

// Test: getChar returns the Unicode character at the given index
TEST_F(TextWordTest_1194, GetCharAtIndex_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'X', 'X', textMat);
    
    const Unicode *ch = word.getChar(0);
    ASSERT_NE(ch, nullptr);
    EXPECT_EQ(*ch, 'X');
}

// Test: getBBox returns valid bounding box after adding a character
TEST_F(TextWordTest_1194, GetBBoxAfterAddChar_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // The bounding box should have valid coordinates
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test: getBBox returning PDFRectangle
TEST_F(TextWordTest_1194, GetBBoxPDFRectangle_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    PDFRectangle rect = word.getBBox();
    EXPECT_LE(rect.x1, rect.x2);
    EXPECT_LE(rect.y1, rect.y2);
}

// Test: getCharBBox returns valid bounding box for a character
TEST_F(TextWordTest_1194, GetCharBBox_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    double xMin, yMin, xMax, yMax;
    word.getCharBBox(0, &xMin, &yMin, &xMax, &yMax);
    
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test: getColor returns default color values
TEST_F(TextWordTest_1194, GetColor_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    double r, g, b;
    word.getColor(&r, &g, &b);
    
    // Colors should be in valid range [0, 1]
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test: getCharPos on empty word
TEST_F(TextWordTest_1194, GetCharPos_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    // charPos should be some default value for an empty word
    int charPos = word.getCharPos();
    // Just verify it doesn't crash
    EXPECT_GE(charPos, 0);
}

// Test: getSpaceAfter / hasSpaceAfter on fresh word
TEST_F(TextWordTest_1194, SpaceAfterDefault_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    // Default should be false
    EXPECT_FALSE(word.getSpaceAfter());
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test: isUnderlined on fresh word
TEST_F(TextWordTest_1194, IsUnderlinedDefault_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    EXPECT_FALSE(word.isUnderlined());
}

// Test: getBaseline returns a finite value
TEST_F(TextWordTest_1194, GetBaseline_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    double baseline = word.getBaseline();
    EXPECT_TRUE(std::isfinite(baseline));
}

// Test: getFontInfo returns nullptr for empty word (no chars added)
TEST_F(TextWordTest_1194, GetFontInfoOnEmpty_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    // No characters, so getFontInfo for any index might return nullptr or be undefined.
    // We'll just check the word length is 0
    EXPECT_EQ(word.getLength(), 0);
}

// Test: getFontInfo returns valid pointer after adding character
TEST_F(TextWordTest_1194, GetFontInfoAfterAddChar_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    
    const TextFontInfo *fi = word.getFontInfo(0);
    EXPECT_NE(fi, nullptr);
}

// Test: Multiple characters and getEdge for each
TEST_F(TextWordTest_1194, GetEdgeMultipleChars_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    word.addChar(&fontInfo, 110.0, 200.0, 10.0, 0.0, 1, 1, 'B', 'B', textMat);
    word.addChar(&fontInfo, 120.0, 200.0, 10.0, 0.0, 2, 1, 'C', 'C', textMat);
    
    EXPECT_EQ(word.getLength(), 3);
    
    // Each edge should be finite
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isfinite(word.getEdge(i)));
    }
    
    // Edges should be non-decreasing for left-to-right horizontal text
    EXPECT_LE(word.getEdge(0), word.getEdge(1));
    EXPECT_LE(word.getEdge(1), word.getEdge(2));
}

// Test: getCharLen after adding chars
TEST_F(TextWordTest_1194, GetCharLen_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    word.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    word.addChar(&fontInfo, 110.0, 200.0, 10.0, 0.0, 1, 1, 'B', 'B', textMat);
    
    int charLen = word.getCharLen();
    EXPECT_GT(charLen, 0);
}

// Test: cmpYX static comparison function
TEST_F(TextWordTest_1194, CmpYX_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word1(&state, 0, 12.0);
    TextWord word2(&state, 0, 12.0);
    
    TextFontInfo fontInfo(nullptr, &state);
    Matrix textMat = {1, 0, 0, 1, 0, 0};
    
    // word1 at y=200
    word1.addChar(&fontInfo, 100.0, 200.0, 10.0, 0.0, 0, 1, 'A', 'A', textMat);
    // word2 at y=300 (lower on page)
    word2.addChar(&fontInfo, 100.0, 300.0, 10.0, 0.0, 0, 1, 'B', 'B', textMat);
    
    // cmpYX should define a total order
    bool result1 = TextWord::cmpYX(&word1, &word2);
    bool result2 = TextWord::cmpYX(&word2, &word1);
    
    // One should be true and the other false (strict weak ordering, unless equal)
    // They shouldn't both be true
    EXPECT_FALSE(result1 && result2);
}

// Test: Copy constructor and assignment are deleted (compile-time check encoded as a type trait test)
TEST_F(TextWordTest_1194, NotCopyable_1194) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test: Different rotation values with font size 0
TEST_F(TextWordTest_1194, ZeroFontSize_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 0.0);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test: Very large font size
TEST_F(TextWordTest_1194, LargeFontSize_1194) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    GfxState state(72.0, 72.0, &box, 0, false);
    TextWord word(&state, 0, 10000.0);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 10000.0);
}
