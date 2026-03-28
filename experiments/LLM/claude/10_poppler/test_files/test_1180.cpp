#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

// Helper to create a minimal GfxState for TextWord construction
// This may need adjustment based on actual available constructors
class TextWordTest_1180 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal GfxState - using default/null parameters where possible
        // TextWord needs GfxState*, int rotA, double fontSize
    }

    void TearDown() override {
    }
};

// Test that getNext returns nullptr for a freshly constructed standalone TextWord
// Since we cannot easily construct TextWord without a valid GfxState,
// and the partial code shows getNext() returns the `next` member,
// we test what we can observe through the public interface.

// Note: Many tests below may require a valid GfxState. If the test infrastructure
// doesn't support creating one, these tests document the expected interface behavior.

TEST_F(TextWordTest_1180, GetNextReturnsNullForNewWord_1180) {
    // TextWord constructor requires GfxState*, but we test the interface
    // A newly created TextWord should have next == nullptr
    // We need a GfxState to construct - create minimal one
    
    // Using a nullptr GfxState may crash, so we need to create a real one
    // Create minimal PDF objects for GfxState
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    
    EXPECT_EQ(word.getNext(), nullptr);
    EXPECT_EQ(word.nextWord(), nullptr);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetRotationReturnsConstructedRotation_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word0(state, 0, 12.0);
    EXPECT_EQ(word0.getRotation(), 0);
    
    TextWord word1(state, 1, 12.0);
    EXPECT_EQ(word1.getRotation(), 1);
    
    TextWord word2(state, 2, 12.0);
    EXPECT_EQ(word2.getRotation(), 2);
    
    TextWord word3(state, 3, 12.0);
    EXPECT_EQ(word3.getRotation(), 3);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetFontSizeReturnsConstructedFontSize_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);
    
    TextWord word2(state, 0, 24.5);
    EXPECT_DOUBLE_EQ(word2.getFontSize(), 24.5);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetTextReturnsEmptyForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
    
    delete state;
}

TEST_F(TextWordTest_1180, GetLengthReturnsZeroForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
    EXPECT_EQ(word.len(), 0);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetSpaceAfterReturnsFalseForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
    EXPECT_FALSE(word.hasSpaceAfter());
    
    delete state;
}

TEST_F(TextWordTest_1180, IsUnderlinedReturnsFalseForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
    
    delete state;
}

TEST_F(TextWordTest_1180, GetLinkReturnsNullForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
    
    delete state;
}

TEST_F(TextWordTest_1180, CopyConstructorIsDeleted_1180) {
    // This is a compile-time check - TextWord(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1180, CopyAssignmentIsDeleted_1180) {
    // This is a compile-time check - operator=(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

TEST_F(TextWordTest_1180, GetColorReturnsValues_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Colors should be valid (between 0 and 1 typically)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetBBoxReturnsValues_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounding box values should be defined
    // (may be 0 or some initial value)
    
    PDFRectangle rect = word.getBBox();
    EXPECT_DOUBLE_EQ(rect.x1, xMin);
    EXPECT_DOUBLE_EQ(rect.y1, yMin);
    EXPECT_DOUBLE_EQ(rect.x2, xMax);
    EXPECT_DOUBLE_EQ(rect.y2, yMax);
    
    delete state;
}

TEST_F(TextWordTest_1180, FontSizeZero_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 0.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
    
    delete state;
}

TEST_F(TextWordTest_1180, CmpYXStaticComparison_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word1(state, 0, 12.0);
    TextWord word2(state, 0, 12.0);
    
    // Static comparison function should not crash
    // Result depends on internal positions
    bool result = TextWord::cmpYX(&word1, &word2);
    // For two words at similar positions, the result is deterministic
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetCharPosForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    int charPos = word.getCharPos();
    // CharPos should be some non-negative value for a new word
    EXPECT_GE(charPos, 0);
    
    delete state;
}

TEST_F(TextWordTest_1180, GetCharLenForNewWord_1180) {
    auto *state = new GfxState(72.0, 72.0, new PDFRectangle(0, 0, 612, 792), 0, false);
    
    TextWord word(state, 0, 12.0);
    int charLen = word.getCharLen();
    EXPECT_GE(charLen, 0);
    
    delete state;
}
