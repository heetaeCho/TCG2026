#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "Link.h"

// Helper to create a minimal GfxState for TextWord construction
// We need to create a TextWord instance for testing. Since TextWord requires
// a GfxState pointer, we need to set up minimal infrastructure.

class TextWordTest_1189 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll attempt to create TextWord objects for testing.
        // The constructor requires (const GfxState*, int rotA, double fontSize)
    }

    void TearDown() override {
    }

    // Helper to create a TextWord with a given rotation
    // Note: GfxState creation may require PDFDoc context; we try with nullptr
    // and see if it works for basic property tests.
    std::unique_ptr<TextWord> createTextWord(int rot, double fontSize) {
        // TextWord constructor takes (const GfxState*, int, double)
        // Passing nullptr for GfxState - the constructor may handle this
        return std::make_unique<TextWord>(nullptr, rot, fontSize);
    }
};

// Test that a newly created TextWord has zero length
TEST_F(TextWordTest_1189, NewWordHasZeroLength_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getLength(), 0);
}

// Test that len() returns the same as getLength() for empty word
TEST_F(TextWordTest_1189, LenMatchesGetLength_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->len(), word->getLength());
}

// Test getCharPos on empty word returns 0
TEST_F(TextWordTest_1189, GetCharPosEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getCharPos(), 0);
}

// Test getCharLen on empty word
TEST_F(TextWordTest_1189, GetCharLenEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    // For an empty word, charLen should be 0
    EXPECT_EQ(word->getCharLen(), 0);
}

// Test getRotation returns the rotation passed in constructor
TEST_F(TextWordTest_1189, GetRotationReturnsConstructorValue_1189) {
    for (int rot = 0; rot < 4; ++rot) {
        auto word = createTextWord(rot, 12.0);
        ASSERT_NE(word, nullptr);
        EXPECT_EQ(word->getRotation(), rot);
    }
}

// Test getFontSize returns the font size passed in constructor
TEST_F(TextWordTest_1189, GetFontSizeReturnsConstructorValue_1189) {
    auto word = createTextWord(0, 14.5);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 14.5);
}

// Test getNext returns nullptr for a standalone word
TEST_F(TextWordTest_1189, GetNextReturnsNullForStandaloneWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getNext(), nullptr);
}

// Test nextWord returns nullptr for a standalone word
TEST_F(TextWordTest_1189, NextWordReturnsNullForStandaloneWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->nextWord(), nullptr);
}

// Test getSpaceAfter on newly created word
TEST_F(TextWordTest_1189, GetSpaceAfterDefaultFalse_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->getSpaceAfter());
}

// Test hasSpaceAfter on newly created word
TEST_F(TextWordTest_1189, HasSpaceAfterDefaultFalse_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->hasSpaceAfter());
}

// Test isUnderlined on newly created word
TEST_F(TextWordTest_1189, IsUnderlinedDefaultFalse_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_FALSE(word->isUnderlined());
}

// Test getLink returns nullptr for a standalone word
TEST_F(TextWordTest_1189, GetLinkReturnsNullByDefault_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    EXPECT_EQ(word->getLink(), nullptr);
}

// Test getText on empty word
TEST_F(TextWordTest_1189, GetTextEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

// Test getColor on newly created word
TEST_F(TextWordTest_1189, GetColorDefaultValues_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double r, g, b;
    word->getColor(&r, &g, &b);
    // Colors should be initialized to some default (typically 0)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox on empty word (both overloads)
TEST_F(TextWordTest_1189, GetBBoxEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounds should still be valid numbers
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getBBox PDFRectangle overload
TEST_F(TextWordTest_1189, GetBBoxPDFRectangleEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    PDFRectangle rect = word->getBBox();
    EXPECT_LE(rect.x1, rect.x2);
    EXPECT_LE(rect.y1, rect.y2);
}

// Test getFontInfo on empty word with invalid index
TEST_F(TextWordTest_1189, GetFontInfoInvalidIndex_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    // Accessing font info at index 0 when word is empty
    // Should return nullptr or handle gracefully
    const TextFontInfo* fi = word->getFontInfo(0);
    EXPECT_EQ(fi, nullptr);
}

// Test getFontName on empty word
TEST_F(TextWordTest_1189, GetFontNameInvalidIndex_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    const GooString* name = word->getFontName(0);
    EXPECT_EQ(name, nullptr);
}

// Test different rotation values
TEST_F(TextWordTest_1189, RotationBoundaryValues_1189) {
    // rotation 0
    auto word0 = createTextWord(0, 10.0);
    EXPECT_EQ(word0->getRotation(), 0);

    // rotation 1
    auto word1 = createTextWord(1, 10.0);
    EXPECT_EQ(word1->getRotation(), 1);

    // rotation 2
    auto word2 = createTextWord(2, 10.0);
    EXPECT_EQ(word2->getRotation(), 2);

    // rotation 3
    auto word3 = createTextWord(3, 10.0);
    EXPECT_EQ(word3->getRotation(), 3);
}

// Test with zero font size
TEST_F(TextWordTest_1189, ZeroFontSize_1189) {
    auto word = createTextWord(0, 0.0);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 0.0);
}

// Test with very large font size
TEST_F(TextWordTest_1189, LargeFontSize_1189) {
    auto word = createTextWord(0, 1000.0);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 1000.0);
}

// Test with very small font size
TEST_F(TextWordTest_1189, SmallFontSize_1189) {
    auto word = createTextWord(0, 0.001);
    ASSERT_NE(word, nullptr);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 0.001);
}

// Test copy constructor is deleted (compile-time constraint, just verify it's not copyable)
TEST_F(TextWordTest_1189, NotCopyable_1189) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

// Test cmpYX static method with two words
TEST_F(TextWordTest_1189, CmpYXStaticMethod_1189) {
    auto word1 = createTextWord(0, 12.0);
    auto word2 = createTextWord(0, 12.0);
    ASSERT_NE(word1, nullptr);
    ASSERT_NE(word2, nullptr);
    // Both words are at default position, so comparison should be deterministic
    // We just verify it doesn't crash and returns a boolean
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    // Since both words are identical in position, result could be true or false
    // We just check it doesn't crash
    (void)result;
}

// Test getBaseline on empty word
TEST_F(TextWordTest_1189, GetBaselineEmptyWord_1189) {
    auto word = createTextWord(0, 12.0);
    ASSERT_NE(word, nullptr);
    double baseline = word->getBaseline();
    // Baseline should be a finite number
    EXPECT_FALSE(std::isnan(baseline));
    EXPECT_FALSE(std::isinf(baseline));
}
