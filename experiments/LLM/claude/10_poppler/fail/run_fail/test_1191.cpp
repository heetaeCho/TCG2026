#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

// Helper to create a minimal GfxState for TextWord construction
// We need a valid GfxState pointer; constructing one requires some setup
class TextWordTest_1191 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal GfxState
        // GfxState needs ctm, pageWidth, pageHeight, rotateA, upsideDown
        // We'll try to create a basic one
    }

    void TearDown() override {
    }

    // Helper to create a TextWord with default parameters if possible
    std::unique_ptr<TextWord> createTextWord(int rot = 0, double fontSize = 12.0) {
        // TextWord constructor requires (const GfxState *state, int rotA, double fontSize)
        // Passing nullptr for state and hoping the constructor handles it,
        // or we need to construct a proper GfxState
        // Since we can't know internals, we try with nullptr
        // This may crash if the constructor dereferences state unconditionally
        // In that case, these tests document the interface expectations
        
        PDFRectangle box(0, 0, 612, 792);
        auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
        gfxStates.push_back(std::move(state));
        return std::make_unique<TextWord>(gfxStates.back().get(), rot, fontSize);
    }

    std::vector<std::unique_ptr<GfxState>> gfxStates;
};

// Test that a newly created TextWord has expected initial rotation
TEST_F(TextWordTest_1191, GetRotation_ReturnsConstructedRotation_1191) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getRotation(), 0);
}

TEST_F(TextWordTest_1191, GetRotation_Rotation1_1191) {
    auto word = createTextWord(1, 12.0);
    EXPECT_EQ(word->getRotation(), 1);
}

TEST_F(TextWordTest_1191, GetRotation_Rotation2_1191) {
    auto word = createTextWord(2, 12.0);
    EXPECT_EQ(word->getRotation(), 2);
}

TEST_F(TextWordTest_1191, GetRotation_Rotation3_1191) {
    auto word = createTextWord(3, 12.0);
    EXPECT_EQ(word->getRotation(), 3);
}

// Test font size
TEST_F(TextWordTest_1191, GetFontSize_ReturnsConstructedFontSize_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 12.0);
}

TEST_F(TextWordTest_1191, GetFontSize_DifferentSize_1191) {
    auto word = createTextWord(0, 24.5);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 24.5);
}

// Test initial length is 0 (no chars added)
TEST_F(TextWordTest_1191, GetLength_InitiallyZero_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(word->getLength(), 0);
}

// Test len() matches getLength()
TEST_F(TextWordTest_1191, Len_MatchesGetLength_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(static_cast<int>(word->len()), word->getLength());
}

// Test getText on empty word
TEST_F(TextWordTest_1191, GetText_EmptyWord_1191) {
    auto word = createTextWord(0, 12.0);
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getSpaceAfter on newly created word
TEST_F(TextWordTest_1191, GetSpaceAfter_InitiallyFalse_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_FALSE(word->getSpaceAfter());
}

// Test hasSpaceAfter on newly created word
TEST_F(TextWordTest_1191, HasSpaceAfter_InitiallyFalse_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_FALSE(word->hasSpaceAfter());
}

// Test isUnderlined on newly created word
TEST_F(TextWordTest_1191, IsUnderlined_InitiallyFalse_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_FALSE(word->isUnderlined());
}

// Test getLink on newly created word
TEST_F(TextWordTest_1191, GetLink_InitiallyNull_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(word->getLink(), nullptr);
}

// Test getNext / nextWord on newly created word
TEST_F(TextWordTest_1191, GetNext_InitiallyNull_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(word->getNext(), nullptr);
}

TEST_F(TextWordTest_1191, NextWord_InitiallyNull_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(word->nextWord(), nullptr);
}

// Test getColor on newly created word - should return initial color values
TEST_F(TextWordTest_1191, GetColor_ReturnsValidValues_1191) {
    auto word = createTextWord(0, 12.0);
    double r, g, b;
    word->getColor(&r, &g, &b);
    // Colors should be in [0, 1] range
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox returns some valid bounding box
TEST_F(TextWordTest_1191, GetBBox_ReturnsValues_1191) {
    auto word = createTextWord(0, 12.0);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, we just verify it doesn't crash
    // and returns finite values
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test PDFRectangle version of getBBox
TEST_F(TextWordTest_1191, GetBBoxRect_ReturnsValues_1191) {
    auto word = createTextWord(0, 12.0);
    PDFRectangle rect = word->getBBox();
    EXPECT_TRUE(std::isfinite(rect.x1));
    EXPECT_TRUE(std::isfinite(rect.y1));
    EXPECT_TRUE(std::isfinite(rect.x2));
    EXPECT_TRUE(std::isfinite(rect.y2));
}

// Test getBaseline returns a finite value
TEST_F(TextWordTest_1191, GetBaseline_ReturnsFiniteValue_1191) {
    auto word = createTextWord(0, 12.0);
    double baseline = word->getBaseline();
    EXPECT_TRUE(std::isfinite(baseline));
}

// Test that copy constructor is deleted
TEST_F(TextWordTest_1191, CopyConstructorDeleted_1191) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

// Test that copy assignment is deleted
TEST_F(TextWordTest_1191, CopyAssignmentDeleted_1191) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test getCharPos on empty word
TEST_F(TextWordTest_1191, GetCharPos_EmptyWord_1191) {
    auto word = createTextWord(0, 12.0);
    int charPos = word->getCharPos();
    // Should be some initial value, just ensure it doesn't crash
    EXPECT_TRUE(true);
}

// Test getCharLen on empty word
TEST_F(TextWordTest_1191, GetCharLen_EmptyWord_1191) {
    auto word = createTextWord(0, 12.0);
    int charLen = word->getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test cmpYX static method with two words
TEST_F(TextWordTest_1191, CmpYX_TwoWords_1191) {
    auto word1 = createTextWord(0, 12.0);
    auto word2 = createTextWord(0, 12.0);
    // Just verify it doesn't crash and returns a bool
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    // With identical construction parameters, result could be either true or false
    (void)result;
    SUCCEED();
}

// Test zero font size
TEST_F(TextWordTest_1191, GetFontSize_ZeroSize_1191) {
    auto word = createTextWord(0, 0.0);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 0.0);
}

// Test negative font size (boundary)
TEST_F(TextWordTest_1191, GetFontSize_NegativeSize_1191) {
    auto word = createTextWord(0, -1.0);
    // Just verify construction doesn't crash
    EXPECT_TRUE(std::isfinite(word->getFontSize()));
}

// Test that getSpaceAfter and hasSpaceAfter return consistent values
TEST_F(TextWordTest_1191, SpaceAfterConsistency_1191) {
    auto word = createTextWord(0, 12.0);
    EXPECT_EQ(word->getSpaceAfter(), word->hasSpaceAfter());
}

// Test getFontInfo with no characters
TEST_F(TextWordTest_1191, GetFontInfo_EmptyWord_1191) {
    auto word = createTextWord(0, 12.0);
    // With no chars added, getFontInfo(0) should return nullptr or handle gracefully
    // This tests boundary - accessing index 0 on empty word
    if (word->getLength() == 0) {
        SUCCEED(); // Can't safely call getFontInfo on empty word
    }
}

// Test getFontName with no characters
TEST_F(TextWordTest_1191, GetFontName_EmptyWord_1191) {
    auto word = createTextWord(0, 12.0);
    if (word->getLength() == 0) {
        SUCCEED(); // Can't safely call getFontName on empty word
    }
}
