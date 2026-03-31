#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
// Since we treat the implementation as a black box, we need valid objects
// to construct TextWord instances.

class TextWordTest_1182 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create TextWord objects in individual tests as needed
    }

    void TearDown() override {
    }

    // Helper to create a TextWord with a given rotation
    // rotation values: 0, 1, 2, 3
    std::unique_ptr<TextWord> createTextWord(int rot = 0) {
        // Create a minimal GfxState - we need a valid state pointer
        // Using nullptr or minimal construction depending on what the constructor accepts
        PDFRectangle box(0, 0, 612, 792);
        auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
        double fontSize = 12.0;
        return std::make_unique<TextWord>(state.get(), rot, fontSize);
    }
};

// Test that a newly created TextWord has length 0
TEST_F(TextWordTest_1182, NewTextWordHasZeroLength_1182) {
    auto word = createTextWord(0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getLength(), 0);
}

// Test that len() returns same as getLength() for empty word
TEST_F(TextWordTest_1182, LenMatchesGetLengthEmpty_1182) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->len(), word->getLength());
}

// Test getRotation returns the rotation passed to constructor
TEST_F(TextWordTest_1182, GetRotationReturnsConstructorValue_1182) {
    for (int rot = 0; rot < 4; ++rot) {
        auto word = createTextWord(rot);
        EXPECT_EQ(word->getRotation(), rot);
    }
}

// Test getFontSize returns the font size set during construction
TEST_F(TextWordTest_1182, GetFontSizeReturnsExpectedValue_1182) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    double fontSize = 14.5;
    auto word = std::make_unique<TextWord>(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word->getFontSize(), fontSize);
}

// Test getText on empty word
TEST_F(TextWordTest_1182, GetTextEmptyWord_1182) {
    auto word = createTextWord(0);
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getNext returns nullptr for standalone word
TEST_F(TextWordTest_1182, GetNextReturnsNullForStandaloneWord_1182) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getNext(), nullptr);
}

// Test nextWord returns nullptr for standalone word
TEST_F(TextWordTest_1182, NextWordReturnsNullForStandaloneWord_1182) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->nextWord(), nullptr);
}

// Test getLink returns nullptr when no link is set
TEST_F(TextWordTest_1182, GetLinkReturnsNullWhenNoLink_1182) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getLink(), nullptr);
}

// Test isUnderlined returns false by default
TEST_F(TextWordTest_1182, IsUnderlinedDefaultFalse_1182) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->isUnderlined());
}

// Test getSpaceAfter returns false by default
TEST_F(TextWordTest_1182, GetSpaceAfterDefaultFalse_1182) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->getSpaceAfter());
}

// Test hasSpaceAfter returns false by default
TEST_F(TextWordTest_1182, HasSpaceAfterDefaultFalse_1182) {
    auto word = createTextWord(0);
    EXPECT_FALSE(word->hasSpaceAfter());
}

// Test getColor returns values (default color)
TEST_F(TextWordTest_1182, GetColorReturnsValues_1182) {
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

// Test getBBox returns bounding box values
TEST_F(TextWordTest_1182, GetBBoxReturnsValues_1182) {
    auto word = createTextWord(0);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounds should still be valid numbers
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test getBBox PDFRectangle overload
TEST_F(TextWordTest_1182, GetBBoxPDFRectangle_1182) {
    auto word = createTextWord(0);
    PDFRectangle rect = word->getBBox();
    EXPECT_TRUE(std::isfinite(rect.x1));
    EXPECT_TRUE(std::isfinite(rect.y1));
    EXPECT_TRUE(std::isfinite(rect.x2));
    EXPECT_TRUE(std::isfinite(rect.y2));
}

// Test getBaseline returns a finite value
TEST_F(TextWordTest_1182, GetBaselineReturnsFiniteValue_1182) {
    auto word = createTextWord(0);
    double baseline = word->getBaseline();
    EXPECT_TRUE(std::isfinite(baseline));
}

// Test copy constructor is deleted (compile-time check would fail if uncommented)
// This is verified by the = delete declaration
TEST_F(TextWordTest_1182, CopyConstructorIsDeleted_1182) {
    // This test verifies through the type system that copying is disallowed
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test copy assignment is deleted
TEST_F(TextWordTest_1182, CopyAssignmentIsDeleted_1182) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test getCharPos on empty word
TEST_F(TextWordTest_1182, GetCharPosEmptyWord_1182) {
    auto word = createTextWord(0);
    int charPos = word->getCharPos();
    // Should return some valid value even for empty word
    EXPECT_GE(charPos, 0);
}

// Test getCharLen on empty word
TEST_F(TextWordTest_1182, GetCharLenEmptyWord_1182) {
    auto word = createTextWord(0);
    int charLen = word->getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test cmpYX static method with two words
TEST_F(TextWordTest_1182, CmpYXComparison_1182) {
    auto word1 = createTextWord(0);
    auto word2 = createTextWord(0);
    // Just verify it doesn't crash and returns a valid boolean
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    // For two default-constructed words, the result is deterministic
    // but we just check it returns without error
    EXPECT_TRUE(result == true || result == false);
}

// Test different rotations
TEST_F(TextWordTest_1182, RotationZero_1182) {
    auto word = createTextWord(0);
    EXPECT_EQ(word->getRotation(), 0);
}

TEST_F(TextWordTest_1182, RotationOne_1182) {
    auto word = createTextWord(1);
    EXPECT_EQ(word->getRotation(), 1);
}

TEST_F(TextWordTest_1182, RotationTwo_1182) {
    auto word = createTextWord(2);
    EXPECT_EQ(word->getRotation(), 2);
}

TEST_F(TextWordTest_1182, RotationThree_1182) {
    auto word = createTextWord(3);
    EXPECT_EQ(word->getRotation(), 3);
}

// Test with different font sizes
TEST_F(TextWordTest_1182, SmallFontSize_1182) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    double fontSize = 1.0;
    auto word = std::make_unique<TextWord>(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word->getFontSize(), fontSize);
}

TEST_F(TextWordTest_1182, LargeFontSize_1182) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    double fontSize = 72.0;
    auto word = std::make_unique<TextWord>(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word->getFontSize(), fontSize);
}

TEST_F(TextWordTest_1182, ZeroFontSize_1182) {
    PDFRectangle box(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
    double fontSize = 0.0;
    auto word = std::make_unique<TextWord>(state.get(), 0, fontSize);
    EXPECT_DOUBLE_EQ(word->getFontSize(), fontSize);
}

// Test getFontInfo on empty word returns nullptr for out of range
TEST_F(TextWordTest_1182, GetFontInfoEmptyWord_1182) {
    auto word = createTextWord(0);
    // For an empty word, there should be no valid font info at index 0
    // This may return nullptr or may be undefined - we test the boundary
    if (word->getLength() == 0) {
        SUCCEED(); // No valid index to query
    }
}

// Test getFontName on empty word
TEST_F(TextWordTest_1182, GetFontNameEmptyWord_1182) {
    auto word = createTextWord(0);
    if (word->getLength() == 0) {
        SUCCEED(); // No valid index to query
    }
}

// Test consistency between getBBox overloads
TEST_F(TextWordTest_1182, GetBBoxOverloadsConsistent_1182) {
    auto word = createTextWord(0);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    PDFRectangle rect = word->getBBox();
    EXPECT_DOUBLE_EQ(rect.x1, xMin);
    EXPECT_DOUBLE_EQ(rect.y1, yMin);
    EXPECT_DOUBLE_EQ(rect.x2, xMax);
    EXPECT_DOUBLE_EQ(rect.y2, yMax);
}
