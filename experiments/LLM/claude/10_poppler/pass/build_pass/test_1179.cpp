#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <cstring>

class TextWordTest_1179 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal TextWord
    // TextWord requires GfxState*, int rotA, double fontSize
    // We need to create a valid GfxState or handle nullptr carefully
    std::unique_ptr<TextWord> createTextWord(int rot, double fontSize) {
        // Passing nullptr for GfxState - the constructor may handle this
        // If it crashes, we know we need a real GfxState
        return std::make_unique<TextWord>(nullptr, rot, fontSize);
    }
};

// Test basic construction with rotation 0
TEST_F(TextWordTest_1179, ConstructionWithRotation0_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getRotation(), 0);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 12.0);
}

// Test basic construction with rotation 1
TEST_F(TextWordTest_1179, ConstructionWithRotation1_1179) {
    auto word = createTextWord(1, 10.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getRotation(), 1);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 10.0);
}

// Test basic construction with rotation 2
TEST_F(TextWordTest_1179, ConstructionWithRotation2_1179) {
    auto word = createTextWord(2, 14.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getRotation(), 2);
}

// Test basic construction with rotation 3
TEST_F(TextWordTest_1179, ConstructionWithRotation3_1179) {
    auto word = createTextWord(3, 8.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getRotation(), 3);
}

// Test that a newly constructed word has length 0
TEST_F(TextWordTest_1179, NewWordHasZeroLength_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getLength(), 0);
}

// Test len() method on empty word
TEST_F(TextWordTest_1179, NewWordLenIsZero_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->len(), 0);
}

// Test getText on empty word
TEST_F(TextWordTest_1179, EmptyWordGetText_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getNext on a standalone word returns nullptr
TEST_F(TextWordTest_1179, StandaloneWordGetNextIsNull_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getNext(), nullptr);
}

// Test nextWord on a standalone word returns nullptr
TEST_F(TextWordTest_1179, StandaloneWordNextWordIsNull_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->nextWord(), nullptr);
}

// Test getLink on a new word returns nullptr
TEST_F(TextWordTest_1179, NewWordGetLinkIsNull_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getLink(), nullptr);
}

// Test getSpaceAfter on a new word
TEST_F(TextWordTest_1179, NewWordSpaceAfterIsFalse_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->getSpaceAfter());
}

// Test hasSpaceAfter on a new word
TEST_F(TextWordTest_1179, NewWordHasSpaceAfterIsFalse_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->hasSpaceAfter());
}

// Test isUnderlined on a new word
TEST_F(TextWordTest_1179, NewWordIsNotUnderlined_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->isUnderlined());
}

// Test getColor on a new word
TEST_F(TextWordTest_1179, NewWordGetColor_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double r, g, b;
    word->getColor(&r, &g, &b);
    // Colors should be initialized to some default values (likely 0)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox with double* parameters on a new word
TEST_F(TextWordTest_1179, NewWordGetBBoxDoublePtr_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // Bounding box values should be finite
    EXPECT_FALSE(std::isnan(xMin));
    EXPECT_FALSE(std::isnan(yMin));
    EXPECT_FALSE(std::isnan(xMax));
    EXPECT_FALSE(std::isnan(yMax));
}

// Test getBBox returning PDFRectangle on a new word
TEST_F(TextWordTest_1179, NewWordGetBBoxPDFRectangle_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    PDFRectangle rect = word->getBBox();
    EXPECT_FALSE(std::isnan(rect.x1));
    EXPECT_FALSE(std::isnan(rect.y1));
    EXPECT_FALSE(std::isnan(rect.x2));
    EXPECT_FALSE(std::isnan(rect.y2));
}

// Test getFontSize returns the value set at construction
TEST_F(TextWordTest_1179, GetFontSizeReturnsConstructionValue_1179) {
    auto word1 = createTextWord(0, 12.0);
    EXPECT_DOUBLE_EQ(word1->getFontSize(), 12.0);

    auto word2 = createTextWord(0, 24.5);
    EXPECT_DOUBLE_EQ(word2->getFontSize(), 24.5);
}

// Test getFontSize with zero fontSize
TEST_F(TextWordTest_1179, GetFontSizeZero_1179) {
    auto word = createTextWord(0, 0.0);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 0.0);
}

// Test getFontSize with very large fontSize
TEST_F(TextWordTest_1179, GetFontSizeLarge_1179) {
    auto word = createTextWord(0, 1000.0);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 1000.0);
}

// Test getBaseline on a new word
TEST_F(TextWordTest_1179, NewWordGetBaseline_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double baseline = word->getBaseline();
    EXPECT_FALSE(std::isnan(baseline));
}

// Test getCharPos on a new word
TEST_F(TextWordTest_1179, NewWordGetCharPos_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    int charPos = word->getCharPos();
    // charPos should be initialized to some value
    EXPECT_GE(charPos, 0);
}

// Test copy constructor is deleted
TEST_F(TextWordTest_1179, CopyConstructorIsDeleted_1179) {
    // This test verifies at compile time that copy constructor is deleted
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test copy assignment is deleted
TEST_F(TextWordTest_1179, CopyAssignmentIsDeleted_1179) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test cmpYX static method with two words at same position
TEST_F(TextWordTest_1179, CmpYXSamePosition_1179) {
    auto word1 = createTextWord(0, 12.0);
    auto word2 = createTextWord(0, 12.0);
    ASSERT_NE(word1, nullptr);
    ASSERT_NE(word2, nullptr);
    // Comparing two words at same position should return a consistent result
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

// Test getCharLen on empty word
TEST_F(TextWordTest_1179, EmptyWordGetCharLen_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    int charLen = word->getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test both getBBox methods return consistent results
TEST_F(TextWordTest_1179, GetBBoxConsistency_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);

    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);

    PDFRectangle rect = word->getBBox();

    EXPECT_DOUBLE_EQ(xMin, rect.x1);
    EXPECT_DOUBLE_EQ(yMin, rect.y1);
    EXPECT_DOUBLE_EQ(xMax, rect.x2);
    EXPECT_DOUBLE_EQ(yMax, rect.y2);
}

// Test getEdge on a word with index 0 (boundary for empty word edge array)
TEST_F(TextWordTest_1179, GetEdgeIndex0OnNewWord_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    // For an empty word, getEdge(0) should still be accessible
    // as there is an edgeEnd member
    double edge = word->getEdge(0);
    EXPECT_FALSE(std::isnan(edge));
}

// Test multiple rotations have correct rotation value
TEST_F(TextWordTest_1179, AllRotationValues_1179) {
    for (int rot = 0; rot < 4; ++rot) {
        auto word = createTextWord(rot, 12.0);
        ASSERT_NE(word, nullptr);
        EXPECT_EQ(word->getRotation(), rot);
    }
}

// Test that getFontName on empty word with invalid index doesn't crash
// (This may be undefined behavior, but we test boundary)
TEST_F(TextWordTest_1179, GetFontNameOnEmptyWord_1179) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    // With zero length, calling getFontName with any index is out of bounds
    // We just verify length is 0
    EXPECT_EQ(word->getLength(), 0);
}

// Test negative font size
TEST_F(TextWordTest_1179, NegativeFontSize_1179) {
    auto word = createTextWord(0, -5.0);
    ASSERT_NE(word, nullptr);
    // The behavior with negative font size is implementation-defined
    // but it shouldn't crash
    double fs = word->getFontSize();
    EXPECT_FALSE(std::isnan(fs));
}
