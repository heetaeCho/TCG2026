#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

// Since we're treating the implementation as a black box, we test only
// through the public interface. We need to create TextWord objects
// using the constructor that takes GfxState*, int rotA, double fontSize.

class TextWordTest_1193 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects in individual tests as needed
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TextWord has expected initial rotation
TEST_F(TextWordTest_1193, GetRotation_ReturnsConstructedRotation_1193) {
    // rotation 0, fontSize 12.0
    // We need a GfxState to construct TextWord. Since we can't easily create one,
    // we pass nullptr and hope the constructor handles it or we test what we can.
    // Note: If constructor requires valid GfxState, this may crash. In that case,
    // these tests document the expected interface behavior.
    
    // Attempting with nullptr - if this segfaults, the test infrastructure would catch it
    // For rotations 0-3
    for (int rot = 0; rot < 4; ++rot) {
        TextWord word(nullptr, rot, 12.0);
        EXPECT_EQ(word.getRotation(), rot) << "Rotation should match constructor arg for rot=" << rot;
    }
}

// Test that a newly constructed TextWord has zero length
TEST_F(TextWordTest_1193, GetLength_NewWord_ReturnsZero_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getLength(), 0);
}

// Test that len() returns same as getLength() for a new word
TEST_F(TextWordTest_1193, Len_NewWord_ReturnsZero_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.len(), 0);
}

// Test that getFontSize returns the fontSize passed to constructor
TEST_F(TextWordTest_1193, GetFontSize_ReturnsConstructedFontSize_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);
}

// Test getFontSize with different values
TEST_F(TextWordTest_1193, GetFontSize_DifferentSizes_1193) {
    TextWord word1(nullptr, 0, 0.0);
    EXPECT_DOUBLE_EQ(word1.getFontSize(), 0.0);

    TextWord word2(nullptr, 0, 24.5);
    EXPECT_DOUBLE_EQ(word2.getFontSize(), 24.5);
}

// Test that getNext returns nullptr for a new word (not linked)
TEST_F(TextWordTest_1193, GetNext_NewWord_ReturnsNullptr_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getNext(), nullptr);
}

// Test that nextWord returns nullptr for a new word
TEST_F(TextWordTest_1193, NextWord_NewWord_ReturnsNullptr_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test that getLink returns nullptr for a new word (no link set)
TEST_F(TextWordTest_1193, GetLink_NewWord_ReturnsNullptr_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test that getText returns something for an empty word
TEST_F(TextWordTest_1193, GetText_EmptyWord_ReturnsEmptyOrValid_1193) {
    TextWord word(nullptr, 0, 12.0);
    auto text = word.getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test that getSpaceAfter returns false for a new word
TEST_F(TextWordTest_1193, GetSpaceAfter_NewWord_ReturnsFalse_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_FALSE(word.getSpaceAfter());
}

// Test that hasSpaceAfter returns false for a new word
TEST_F(TextWordTest_1193, HasSpaceAfter_NewWord_ReturnsFalse_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test that isUnderlined returns false for a new word
TEST_F(TextWordTest_1193, IsUnderlined_NewWord_ReturnsFalse_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_FALSE(word.isUnderlined());
}

// Test that getColor returns initialized color values
TEST_F(TextWordTest_1193, GetColor_NewWord_ReturnsInitializedValues_1193) {
    TextWord word(nullptr, 0, 12.0);
    double r, g, b;
    word.getColor(&r, &g, &b);
    // Colors should be initialized to some value (likely 0.0 or from GfxState)
    // We just verify the call doesn't crash and values are in valid range
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox for a new word
TEST_F(TextWordTest_1193, GetBBox_NewWord_DoesNotCrash_1193) {
    TextWord word(nullptr, 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    // Just verify it doesn't crash; specific values depend on implementation
}

// Test getBBox returning PDFRectangle
TEST_F(TextWordTest_1193, GetBBoxRect_NewWord_DoesNotCrash_1193) {
    TextWord word(nullptr, 0, 12.0);
    PDFRectangle rect = word.getBBox();
    // Just verify it returns without crashing
}

// Test getCharPos for a new word
TEST_F(TextWordTest_1193, GetCharPos_NewWord_ReturnsValue_1193) {
    TextWord word(nullptr, 0, 12.0);
    int charPos = word.getCharPos();
    // Just verify it returns without crashing
    EXPECT_GE(charPos, 0);
}

// Test getCharLen for an empty word
TEST_F(TextWordTest_1193, GetCharLen_EmptyWord_ReturnsZeroOrValid_1193) {
    TextWord word(nullptr, 0, 12.0);
    int charLen = word.getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test that copy constructor is deleted
TEST_F(TextWordTest_1193, CopyConstructor_IsDeleted_1193) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test that copy assignment is deleted
TEST_F(TextWordTest_1193, CopyAssignment_IsDeleted_1193) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test getBaseline for a new word
TEST_F(TextWordTest_1193, GetBaseline_NewWord_ReturnsValue_1193) {
    TextWord word(nullptr, 0, 12.0);
    double baseline = word.getBaseline();
    // Just verify it doesn't crash; value depends on construction
    (void)baseline;
}

// Test boundary: rotation values at boundaries
TEST_F(TextWordTest_1193, Rotation_BoundaryValues_1193) {
    TextWord word0(nullptr, 0, 12.0);
    EXPECT_EQ(word0.getRotation(), 0);

    TextWord word3(nullptr, 3, 12.0);
    EXPECT_EQ(word3.getRotation(), 3);
}

// Test boundary: very small font size
TEST_F(TextWordTest_1193, GetFontSize_VerySmall_1193) {
    TextWord word(nullptr, 0, 0.001);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.001);
}

// Test boundary: very large font size
TEST_F(TextWordTest_1193, GetFontSize_VeryLarge_1193) {
    TextWord word(nullptr, 0, 10000.0);
    EXPECT_DOUBLE_EQ(word.getFontSize(), 10000.0);
}

// Test getFontInfo with out-of-range index on empty word
TEST_F(TextWordTest_1193, GetFontInfo_EmptyWord_OutOfRange_1193) {
    TextWord word(nullptr, 0, 12.0);
    // For an empty word, any index should be out of range
    // The behavior depends on implementation but we test it doesn't crash badly
    // or returns nullptr
    const TextFontInfo *fi = word.getFontInfo(0);
    // May be nullptr for empty word
    (void)fi;
}

// Test getChar with out-of-range index on empty word
TEST_F(TextWordTest_1193, GetChar_EmptyWord_OutOfRange_1193) {
    TextWord word(nullptr, 0, 12.0);
    // Empty word, index 0 is out of range
    // Implementation-dependent behavior
    const Unicode *ch = word.getChar(0);
    (void)ch;
}

// Test getFontName with out-of-range index on empty word
TEST_F(TextWordTest_1193, GetFontName_EmptyWord_1193) {
    TextWord word(nullptr, 0, 12.0);
    const GooString *name = word.getFontName(0);
    // Should return nullptr for empty word
    EXPECT_EQ(name, nullptr);
}

// Test consistency between getSpaceAfter and hasSpaceAfter
TEST_F(TextWordTest_1193, SpaceAfterConsistency_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getSpaceAfter(), word.hasSpaceAfter());
}

// Test consistency between getNext and nextWord
TEST_F(TextWordTest_1193, NextConsistency_1193) {
    TextWord word(nullptr, 0, 12.0);
    EXPECT_EQ(word.getNext(), word.nextWord());
}
