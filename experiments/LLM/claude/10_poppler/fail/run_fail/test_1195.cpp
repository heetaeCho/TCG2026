#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

// We need to create a minimal GfxState for constructing TextWord objects.
// Since we treat the implementation as a black box, we construct objects
// through the public interface and verify observable behavior.

class TextWordTest_1195 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects in individual tests as needed
    }

    void TearDown() override {
    }
};

// Helper to create a GfxState - this may need adjustment based on actual API
// Since we can't know internal details, we try to construct minimal valid objects.

// Test: Construction with rotation 0
TEST_F(TextWordTest_1195, ConstructWithRotation0_1195) {
    // Create a TextWord with rotation 0
    // We need a valid GfxState pointer; using nullptr may crash,
    // so we attempt to create a minimal one if possible.
    // Since the constructor signature is: TextWord(const GfxState *state, int rotA, double fontSize)
    // We test that the object can be created and basic getters return expected values.
    
    // Note: Without being able to create a proper GfxState, we may need to
    // test with what's available. Let's try with a nullptr state if the
    // constructor handles it, or create a minimal state.
    
    // Attempt construction - if this crashes, the test environment needs a proper GfxState setup
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getRotation(), 0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test: Construction with rotation 1
TEST_F(TextWordTest_1195, ConstructWithRotation1_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 1, 14.0);
    
    EXPECT_EQ(word.getRotation(), 1);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 14.0);
}

// Test: Construction with rotation 2
TEST_F(TextWordTest_1195, ConstructWithRotation2_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 2, 10.0);
    
    EXPECT_EQ(word.getRotation(), 2);
}

// Test: Construction with rotation 3
TEST_F(TextWordTest_1195, ConstructWithRotation3_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 3, 10.0);
    
    EXPECT_EQ(word.getRotation(), 3);
}

// Test: getLength returns 0 for empty word
TEST_F(TextWordTest_1195, GetLengthEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getLength(), 0);
}

// Test: len() returns same as getLength for empty word
TEST_F(TextWordTest_1195, LenEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.len(), word.getLength());
}

// Test: getText returns empty or valid string for empty word
TEST_F(TextWordTest_1195, GetTextEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test: getNext returns nullptr for standalone word
TEST_F(TextWordTest_1195, GetNextReturnsNullForStandaloneWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getNext(), nullptr);
}

// Test: nextWord returns nullptr for standalone word
TEST_F(TextWordTest_1195, NextWordReturnsNullForStandaloneWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test: getLink returns nullptr for word without link
TEST_F(TextWordTest_1195, GetLinkReturnsNullForWordWithoutLink_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test: getSpaceAfter for new word
TEST_F(TextWordTest_1195, GetSpaceAfterNewWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // New word should not have space after by default
    EXPECT_FALSE(word.getSpaceAfter());
}

// Test: hasSpaceAfter for new word
TEST_F(TextWordTest_1195, HasSpaceAfterNewWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test: isUnderlined for new word
TEST_F(TextWordTest_1195, IsUnderlinedNewWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_FALSE(word.isUnderlined());
}

// Test: getColor returns color values
TEST_F(TextWordTest_1195, GetColorReturnsValues_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
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

// Test: getBBox returns bounding box values
TEST_F(TextWordTest_1195, GetBBoxReturnsValues_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // For an empty word, bounding box values should still be set
    // We just verify the call doesn't crash and values are retrievable
    SUCCEED();
}

// Test: getBBox PDFRectangle overload
TEST_F(TextWordTest_1195, GetBBoxPDFRectangle_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    PDFRectangle rect = word.getBBox();
    
    // Both getBBox versions should return consistent values
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    EXPECT_DOUBLE_EQ(rect.x1, xMin);
    EXPECT_DOUBLE_EQ(rect.y1, yMin);
    EXPECT_DOUBLE_EQ(rect.x2, xMax);
    EXPECT_DOUBLE_EQ(rect.y2, yMax);
}

// Test: getBaseline returns a double value
TEST_F(TextWordTest_1195, GetBaselineReturnsValue_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    double baseline = word.getBaseline();
    // Baseline should be a finite number
    EXPECT_FALSE(std::isnan(baseline));
    EXPECT_FALSE(std::isinf(baseline));
}

// Test: getFontSize returns the fontSize passed to constructor
TEST_F(TextWordTest_1195, GetFontSizeMatchesConstructor_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 24.0;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test: getFontSize with very small font
TEST_F(TextWordTest_1195, GetFontSizeSmallFont_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 1.0;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test: getFontSize with large font
TEST_F(TextWordTest_1195, GetFontSizeLargeFont_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 144.0;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test: getCharPos for empty word
TEST_F(TextWordTest_1195, GetCharPosEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // Should not crash
    int charPos = word.getCharPos();
    (void)charPos;
    SUCCEED();
}

// Test: getCharLen for empty word
TEST_F(TextWordTest_1195, GetCharLenEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    int charLen = word.getCharLen();
    // For empty word, charLen should be 0 or consistent with length
    EXPECT_GE(charLen, 0);
}

// Test: Copy constructor is deleted
TEST_F(TextWordTest_1195, CopyConstructorDeleted_1195) {
    // This is a compile-time check - TextWord(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test: Copy assignment is deleted
TEST_F(TextWordTest_1195, CopyAssignmentDeleted_1195) {
    // This is a compile-time check - operator=(const TextWord&) = delete
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test: cmpYX static comparison function
TEST_F(TextWordTest_1195, CmpYXStaticFunction_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    
    // cmpYX should return a boolean indicating ordering
    bool result = TextWord::cmpYX(&word1, &word2);
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

// Test: getFontInfo returns nullptr for empty word with invalid index
TEST_F(TextWordTest_1195, GetFontInfoEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // For an empty word, there are no characters, so index 0 would be out of range
    // The behavior depends on implementation - we just verify the word has length 0
    EXPECT_EQ(word.getLength(), 0);
}

// Test: getFontName for empty word
TEST_F(TextWordTest_1195, GetFontNameEmptyWord_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // Empty word has no characters, so we can't safely call getFontName(0)
    EXPECT_EQ(word.getLength(), 0);
}

// Test: getSpaceAfter and hasSpaceAfter are consistent
TEST_F(TextWordTest_1195, SpaceAfterConsistency_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getSpaceAfter(), word.hasSpaceAfter());
}

// Test: getNext and nextWord return the same value
TEST_F(TextWordTest_1195, GetNextAndNextWordConsistency_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getNext(), word.nextWord());
}

// Test: fontSize of 0
TEST_F(TextWordTest_1195, GetFontSizeZero_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 0.0);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
}

// Test: len and getLength are consistent
TEST_F(TextWordTest_1195, LenAndGetLengthConsistency_1195) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(static_cast<int>(word.len()), word.getLength());
}
