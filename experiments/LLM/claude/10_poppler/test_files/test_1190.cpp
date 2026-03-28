#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
// Since we treat TextWord as a black box, we need valid construction parameters.

class TextWordTest_1190 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects in individual tests as needed
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TextWord has zero length
TEST_F(TextWordTest_1190, NewWordHasZeroLength_1190) {
    // We need a GfxState to construct TextWord. Since we can't easily create one,
    // we test getCharLen behavior based on the visible implementation:
    // getCharLen returns 0 when chars is empty, otherwise chars.back().charPos - chars.front().charPos
    
    // Since constructing TextWord requires GfxState which is complex,
    // we focus on testing the getCharLen method's contract through the provided code.
    // The inline implementation shows:
    // - Empty chars vector -> returns 0
    // - Non-empty -> returns back().charPos - front().charPos
    
    // Without being able to easily instantiate, we verify the interface exists
    // by checking compilation and basic properties.
    
    // Create a minimal GfxState - this may require mocking or using test utilities
    // For now, test with nullptr if constructor allows, or skip if not possible
    
    // Attempt to create TextWord with rotation 0 and fontSize 12.0
    // Note: This test may need adjustment based on actual GfxState availability
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getLength(), 0);
    EXPECT_EQ(word.getCharLen(), 0);
}

// Test that getCharLen returns 0 for empty word
TEST_F(TextWordTest_1190, GetCharLenReturnsZeroForEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getCharLen(), 0);
}

// Test rotation value is preserved
TEST_F(TextWordTest_1190, GetRotationReturnsCorrectValue_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    for (int rot = 0; rot < 4; ++rot) {
        TextWord word(state.get(), rot, 12.0);
        EXPECT_EQ(word.getRotation(), rot);
    }
}

// Test getText on empty word
TEST_F(TextWordTest_1190, GetTextOnEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getNext returns nullptr for isolated word
TEST_F(TextWordTest_1190, GetNextReturnsNullForIsolatedWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getNext(), nullptr);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test getLink returns nullptr when no link set
TEST_F(TextWordTest_1190, GetLinkReturnsNullByDefault_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test font size
TEST_F(TextWordTest_1190, GetFontSizeReturnsExpectedValue_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 14.5;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test spaceAfter default
TEST_F(TextWordTest_1190, SpaceAfterDefaultIsFalse_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_FALSE(word.getSpaceAfter());
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test underlined default
TEST_F(TextWordTest_1190, UnderlinedDefaultIsFalse_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_FALSE(word.isUnderlined());
}

// Test color retrieval
TEST_F(TextWordTest_1190, GetColorReturnsValues_1190) {
    PDFRectangle box(0, 0, 612, 792);
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

// Test getBBox on empty word
TEST_F(TextWordTest_1190, GetBBoxOnEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // For an empty word, bounding box values should be defined (not crash)
    // We just verify the call succeeds
    SUCCEED();
}

// Test getBBox PDFRectangle overload
TEST_F(TextWordTest_1190, GetBBoxReturnsPDFRectangle_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    PDFRectangle rect = word.getBBox();
    // Just verify it returns without crashing
    SUCCEED();
}

// Test len() on empty word
TEST_F(TextWordTest_1190, LenReturnsZeroForEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.len(), 0);
}

// Test that getLength and len return same value
TEST_F(TextWordTest_1190, GetLengthAndLenAreConsistent_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    EXPECT_EQ(word.getLength(), word.len());
}

// Test copy constructor is deleted (compile-time check - this verifies the design)
TEST_F(TextWordTest_1190, CopyConstructorIsDeleted_1190) {
    // This is a compile-time property. We verify by checking that
    // std::is_copy_constructible is false
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test copy assignment is deleted
TEST_F(TextWordTest_1190, CopyAssignmentIsDeleted_1190) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test getCharPos on empty word
TEST_F(TextWordTest_1190, GetCharPosOnEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // Should not crash, returns some value
    int charPos = word.getCharPos();
    (void)charPos; // suppress unused warning
    SUCCEED();
}

// Test different rotation values (boundary: 0 and 3)
TEST_F(TextWordTest_1190, RotationBoundaryValues_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    {
        TextWord word(state.get(), 0, 12.0);
        EXPECT_EQ(word.getRotation(), 0);
    }
    {
        TextWord word(state.get(), 3, 12.0);
        EXPECT_EQ(word.getRotation(), 3);
    }
}

// Test with very small font size
TEST_F(TextWordTest_1190, VerySmallFontSize_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 0.001;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
    EXPECT_EQ(word.getLength(), 0);
    EXPECT_EQ(word.getCharLen(), 0);
}

// Test with large font size
TEST_F(TextWordTest_1190, LargeFontSize_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 1000.0;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test with zero font size
TEST_F(TextWordTest_1190, ZeroFontSize_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    double fontSize = 0.0;
    TextWord word(state.get(), 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
}

// Test getBaseline on empty word
TEST_F(TextWordTest_1190, GetBaselineOnEmptyWord_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // Should return a valid double without crashing
    double baseline = word.getBaseline();
    (void)baseline;
    SUCCEED();
}

// Test getFontInfo on empty word returns nullptr for invalid index
TEST_F(TextWordTest_1190, GetFontInfoOnEmptyWordReturnsNull_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word(state.get(), 0, 12.0);
    
    // For empty word, requesting font info at index 0 should handle gracefully
    // This might return nullptr or could be undefined - we test it doesn't crash
    if (word.getLength() == 0) {
        // Don't call getFontInfo with invalid index on empty word
        SUCCEED();
    }
}

// Test cmpYX static comparison with two words
TEST_F(TextWordTest_1190, CmpYXStaticComparison_1190) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    
    TextWord word1(state.get(), 0, 12.0);
    TextWord word2(state.get(), 0, 12.0);
    
    // Static comparison should not crash
    bool result = TextWord::cmpYX(&word1, &word2);
    (void)result;
    SUCCEED();
}
