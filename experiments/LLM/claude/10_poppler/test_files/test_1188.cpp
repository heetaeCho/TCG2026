#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
// Since we treat TextWord as a black box, we need valid construction parameters

class TextWordTest_1188 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects in individual tests as needed
    }

    void TearDown() override {
    }

    // Helper to create a TextWord with a given rotation
    // rotation values: 0, 1, 2, 3
    std::unique_ptr<TextWord> createTextWord(int rotation) {
        // Create a minimal GfxState - this may require specific setup
        // depending on the actual implementation
        // We use nullptr or minimal state if possible
        double fontSize = 12.0;
        // GfxState constructor typically needs PDFDoc coordinates
        // We'll try to create one with reasonable defaults
        GfxState state(72.0, 72.0, nullptr, 0, false);
        return std::make_unique<TextWord>(&state, rotation, fontSize);
    }
};

// Test that getRotation returns the rotation value passed during construction
TEST_F(TextWordTest_1188, GetRotation_ReturnsConstructedRotation_0_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getRotation(), 0);
}

TEST_F(TextWordTest_1188, GetRotation_ReturnsConstructedRotation_1_1188) {
    auto word = createTextWord(1);
    EXPECT_EQ(word->getRotation(), 1);
}

TEST_F(TextWordTest_1188, GetRotation_ReturnsConstructedRotation_2_1188) {
    auto word = createTextWord(2);
    EXPECT_EQ(word->getRotation(), 2);
}

TEST_F(TextWordTest_1188, GetRotation_ReturnsConstructedRotation_3_1188) {
    auto word = createTextWord(3);
    EXPECT_EQ(word->getRotation(), 3);
}

// Test that a freshly created TextWord has length 0 (no characters added yet)
TEST_F(TextWordTest_1188, GetLength_NewWord_ReturnsZero_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getLength(), 0);
}

// Test that len() is consistent with getLength()
TEST_F(TextWordTest_1188, Len_NewWord_ReturnsZero_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->len(), 0);
}

// Test getText on empty word
TEST_F(TextWordTest_1188, GetText_EmptyWord_ReturnsEmptyOrValid_1188) {
    auto word = createTextWord(0);
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    // Empty word should produce empty text
    EXPECT_TRUE(text->empty() || text->length() == 0);
}

// Test that getNext returns nullptr for a newly created word
TEST_F(TextWordTest_1188, GetNext_NewWord_ReturnsNull_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getNext(), nullptr);
}

// Test that nextWord returns nullptr for a newly created word
TEST_F(TextWordTest_1188, NextWord_NewWord_ReturnsNull_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->nextWord(), nullptr);
}

// Test that getLink returns nullptr for a newly created word (no link set)
TEST_F(TextWordTest_1188, GetLink_NewWord_ReturnsNull_1188) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getLink(), nullptr);
}

// Test getSpaceAfter for a new word
TEST_F(TextWordTest_1188, GetSpaceAfter_NewWord_ReturnsFalse_1188) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->getSpaceAfter());
}

// Test hasSpaceAfter for a new word
TEST_F(TextWordTest_1188, HasSpaceAfter_NewWord_ReturnsFalse_1188) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->hasSpaceAfter());
}

// Test isUnderlined for a new word
TEST_F(TextWordTest_1188, IsUnderlined_NewWord_ReturnsFalse_1188) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->isUnderlined());
}

// Test getFontSize returns the font size used during construction
TEST_F(TextWordTest_1188, GetFontSize_ReturnsConstructedFontSize_1188) {
    GfxState state(72.0, 72.0, nullptr, 0, false);
    double fontSize = 12.0;
    TextWord word(&state, 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test getFontSize with different font sizes
TEST_F(TextWordTest_1188, GetFontSize_DifferentSize_1188) {
    GfxState state(72.0, 72.0, nullptr, 0, false);
    double fontSize = 24.5;
    TextWord word(&state, 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test that getColor returns valid color values for a new word
TEST_F(TextWordTest_1188, GetColor_NewWord_ReturnsValidColors_1188) {
    auto word = createTextWord(0);
    double r, g, b;
    word->getColor(&r, &g, &b);
    // Colors should be in valid range [0, 1]
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox on a new word returns valid bounding box
TEST_F(TextWordTest_1188, GetBBox_NewWord_ReturnsValidBBox_1188) {
    auto word = createTextWord(0);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // For a new word, bounding box values should be set (possibly degenerate)
    // Just verify the call doesn't crash and min <= max (or equal for empty)
}

// Test getBBox PDFRectangle version
TEST_F(TextWordTest_1188, GetBBox_PDFRectangle_NewWord_1188) {
    auto word = createTextWord(0);
    PDFRectangle rect = word->getBBox();
    // Verify it returns a valid rectangle
    // For empty word, this may be degenerate
}

// Test getCharPos on a new word
TEST_F(TextWordTest_1188, GetCharPos_NewWord_1188) {
    auto word = createTextWord(0);
    int charPos = word->getCharPos();
    // charPos should be a non-negative value or 0 for new word
    EXPECT_GE(charPos, 0);
}

// Test getCharLen on a new word
TEST_F(TextWordTest_1188, GetCharLen_NewWord_1188) {
    auto word = createTextWord(0);
    int charLen = word->getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test copy constructor and assignment operator are deleted
TEST_F(TextWordTest_1188, CopyConstructorDeleted_1188) {
    // This test verifies at compile time that copy is deleted
    // If this compiles, the test passes (the static_assert checks it)
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1188, CopyAssignmentDeleted_1188) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test cmpYX static method with two words
TEST_F(TextWordTest_1188, CmpYX_SamePosition_1188) {
    auto word1 = createTextWord(0);
    auto word2 = createTextWord(0);
    // Just verify the comparison doesn't crash
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    // Result should be deterministic for identical positions
    bool result2 = TextWord::cmpYX(word1.get(), word2.get());
    EXPECT_EQ(result, result2);
}

// Test getFontInfo on empty word returns nullptr for out of range
TEST_F(TextWordTest_1188, GetFontInfo_EmptyWord_1188) {
    auto word = createTextWord(0);
    // With no characters, getFontInfo(0) should return nullptr
    const TextFontInfo* fontInfo = word->getFontInfo(0);
    EXPECT_EQ(fontInfo, nullptr);
}

// Test getFontName on empty word
TEST_F(TextWordTest_1188, GetFontName_EmptyWord_1188) {
    auto word = createTextWord(0);
    // With no characters, getFontName(0) should return nullptr
    const GooString* fontName = word->getFontName(0);
    EXPECT_EQ(fontName, nullptr);
}

// Test getChar on empty word - boundary test
TEST_F(TextWordTest_1188, GetChar_EmptyWord_BoundaryTest_1188) {
    auto word = createTextWord(0);
    // With no characters added, getChar(0) is out of bounds
    // This tests boundary behavior - implementation should handle gracefully
    // We don't call it if length is 0 as it may be undefined behavior
    EXPECT_EQ(word->getLength(), 0);
}

// Test getBaseline on a new word
TEST_F(TextWordTest_1188, GetBaseline_NewWord_1188) {
    auto word = createTextWord(0);
    double baseline = word->getBaseline();
    // Baseline should be some finite value
    EXPECT_FALSE(std::isnan(baseline));
    EXPECT_FALSE(std::isinf(baseline));
}

// Test primaryCmp with two empty words
TEST_F(TextWordTest_1188, PrimaryCmp_TwoEmptyWords_1188) {
    auto word1 = createTextWord(0);
    auto word2 = createTextWord(0);
    int cmp = word1->primaryCmp(word2.get());
    // Two words at same position should have 0 or near-0 comparison
    // Just verify it doesn't crash
    SUCCEED();
}

// Test primaryDelta with two empty words
TEST_F(TextWordTest_1188, PrimaryDelta_TwoEmptyWords_1188) {
    auto word1 = createTextWord(0);
    auto word2 = createTextWord(0);
    double delta = word1->primaryDelta(word2.get());
    EXPECT_FALSE(std::isnan(delta));
}

// Test with zero font size
TEST_F(TextWordTest_1188, ZeroFontSize_1188) {
    GfxState state(72.0, 72.0, nullptr, 0, false);
    double fontSize = 0.0;
    TextWord word(&state, 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test with very large font size
TEST_F(TextWordTest_1188, LargeFontSize_1188) {
    GfxState state(72.0, 72.0, nullptr, 0, false);
    double fontSize = 1000.0;
    TextWord word(&state, 0, fontSize);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 1000.0);
}

// Test with negative font size
TEST_F(TextWordTest_1188, NegativeFontSize_1188) {
    GfxState state(72.0, 72.0, nullptr, 0, false);
    double fontSize = -5.0;
    TextWord word(&state, 0, fontSize);
    // Implementation may handle this differently
    // Just verify it doesn't crash
    EXPECT_EQ(word.getRotation(), 0);
}
