#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

// Since we need to construct TextWord objects but can't access private members,
// we test through the public interface after construction.

class TextWordTest_1192 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TextWord with rotation 0 returns correct rotation
TEST_F(TextWordTest_1192, GetRotation_Rot0_1192) {
    // We need a GfxState to construct TextWord. Since we're treating it as black box,
    // we create a minimal state.
    // TextWord(const GfxState *state, int rotA, double fontSize)
    
    // Create a minimal GfxState - using default PDF coordinate system
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getRotation(), 0);
}

// Test rotation value 1
TEST_F(TextWordTest_1192, GetRotation_Rot1_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 1, 12.0);
    EXPECT_EQ(word.getRotation(), 1);
}

// Test rotation value 2
TEST_F(TextWordTest_1192, GetRotation_Rot2_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 2, 12.0);
    EXPECT_EQ(word.getRotation(), 2);
}

// Test rotation value 3
TEST_F(TextWordTest_1192, GetRotation_Rot3_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 3, 12.0);
    EXPECT_EQ(word.getRotation(), 3);
}

// Test font size
TEST_F(TextWordTest_1192, GetFontSize_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 14.5);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 14.5);
}

// Test that a new word has length 0 (no chars added yet)
TEST_F(TextWordTest_1192, InitialLengthIsZero_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test that getText returns something for empty word
TEST_F(TextWordTest_1192, GetTextEmpty_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test isUnderlined default is false
TEST_F(TextWordTest_1192, IsUnderlinedDefaultFalse_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

// Test getNext returns nullptr for standalone word
TEST_F(TextWordTest_1192, GetNextReturnsNull_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
}

// Test nextWord returns nullptr for standalone word
TEST_F(TextWordTest_1192, NextWordReturnsNull_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test getLink returns nullptr by default
TEST_F(TextWordTest_1192, GetLinkReturnsNull_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test getSpaceAfter default
TEST_F(TextWordTest_1192, GetSpaceAfterDefault_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
}

// Test hasSpaceAfter default
TEST_F(TextWordTest_1192, HasSpaceAfterDefault_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test getColor returns some values
TEST_F(TextWordTest_1192, GetColorDefault_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Colors should be valid (between 0 and 1 typically)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox with 4 double pointers
TEST_F(TextWordTest_1192, GetBBoxPointers_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // Just verify it doesn't crash and returns reasonable values
    // For an empty word, bounds may be degenerate
}

// Test getBBox returning PDFRectangle
TEST_F(TextWordTest_1192, GetBBoxRect_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    PDFRectangle rect = word.getBBox();
    // Verify it returns without crashing
}

// Test len() for empty word
TEST_F(TextWordTest_1192, LenEmpty_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), 0);
}

// Test that len() and getLength() return the same value
TEST_F(TextWordTest_1192, LenEqualsGetLength_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    EXPECT_EQ(word.len(), word.getLength());
}

// Test font size 0
TEST_F(TextWordTest_1192, FontSizeZero_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 0.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
}

// Test very large font size
TEST_F(TextWordTest_1192, FontSizeLarge_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 1000.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 1000.0);
}

// Test cmpYX static comparison with two words at different positions
TEST_F(TextWordTest_1192, CmpYXStaticMethod_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    
    // Just verify it doesn't crash - result depends on internal state
    bool result = TextWord::cmpYX(&word1, &word2);
    // Both words are at same position, so we just check it returns a bool
    (void)result;
}

// Test getCharPos for empty word
TEST_F(TextWordTest_1192, GetCharPosEmpty_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    // Just verify it returns without crashing
    int charPos = word.getCharPos();
    (void)charPos;
}

// Test getCharLen for empty word
TEST_F(TextWordTest_1192, GetCharLenEmpty_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    int charLen = word.getCharLen();
    (void)charLen;
}

// Test getBaseline for empty word
TEST_F(TextWordTest_1192, GetBaselineEmpty_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    double baseline = word.getBaseline();
    // Just verify no crash
    (void)baseline;
}

// Test getFontInfo returns nullptr for empty word at index 0
TEST_F(TextWordTest_1192, GetFontInfoEmptyWord_1192) {
    PDFRectangle box;
    box.x1 = 0;
    box.y1 = 0;
    box.x2 = 612;
    box.y2 = 792;
    
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    // For an empty word, getFontInfo(0) behavior depends on implementation
    // but length is 0, so accessing index 0 may not be valid
    if (word.getLength() > 0) {
        const TextFontInfo *fi = word.getFontInfo(0);
        (void)fi;
    }
}

// Test copy constructor is deleted (compile-time check - just documenting)
// TextWord is non-copyable - this is enforced at compile time

// Test assignment operator is deleted (compile-time check - just documenting)
// TextWord is non-assignable - this is enforced at compile time
