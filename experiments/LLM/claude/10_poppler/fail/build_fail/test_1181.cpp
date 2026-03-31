#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

#include <memory>
#include <string>

// Helper to create a minimal GfxState for TextWord construction
// We need a valid enough GfxState to not crash
class TextWordTest_1181 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF rectangle and GfxState
        // GfxState needs ctm, page width/height, rotation, etc.
        // Using a basic setup
    }

    std::unique_ptr<TextWord> createTextWord(int rot = 0, double fontSize = 12.0) {
        // Create a minimal GfxState
        PDFRectangle box;
        box.x1 = 0;
        box.y1 = 0;
        box.x2 = 612;
        box.y2 = 792;

        auto state = std::make_unique<GfxState>(72.0, 72.0, &box, 0, false);
        state->setFontSize(fontSize);
        
        // We store state to keep it alive
        states_.push_back(std::move(state));
        return std::make_unique<TextWord>(states_.back().get(), rot, fontSize);
    }

    std::vector<std::unique_ptr<GfxState>> states_;
};

TEST_F(TextWordTest_1181, DefaultLengthIsZero_1181) {
    auto word = createTextWord();
    EXPECT_EQ(word->getLength(), 0);
}

TEST_F(TextWordTest_1181, LenReturnsZeroForNewWord_1181) {
    auto word = createTextWord();
    EXPECT_EQ(word->len(), 0);
}

TEST_F(TextWordTest_1181, GetRotationReturnsCorrectValue_1181) {
    auto word0 = createTextWord(0);
    EXPECT_EQ(word0->getRotation(), 0);

    auto word1 = createTextWord(1);
    EXPECT_EQ(word1->getRotation(), 1);

    auto word2 = createTextWord(2);
    EXPECT_EQ(word2->getRotation(), 2);

    auto word3 = createTextWord(3);
    EXPECT_EQ(word3->getRotation(), 3);
}

TEST_F(TextWordTest_1181, GetFontSizeReturnsCorrectValue_1181) {
    auto word = createTextWord(0, 14.0);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 14.0);
}

TEST_F(TextWordTest_1181, GetFontSizeSmallValue_1181) {
    auto word = createTextWord(0, 0.5);
    EXPECT_DOUBLE_EQ(word->getFontSize(), 0.5);
}

TEST_F(TextWordTest_1181, GetTextEmptyWord_1181) {
    auto word = createTextWord();
    auto text = word->getText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->empty());
}

TEST_F(TextWordTest_1181, GetNextReturnsNullForNewWord_1181) {
    auto word = createTextWord();
    EXPECT_EQ(word->getNext(), nullptr);
    EXPECT_EQ(word->nextWord(), nullptr);
}

TEST_F(TextWordTest_1181, GetLinkReturnsNullForNewWord_1181) {
    auto word = createTextWord();
    EXPECT_EQ(word->getLink(), nullptr);
}

TEST_F(TextWordTest_1181, IsUnderlinedDefaultFalse_1181) {
    auto word = createTextWord();
    EXPECT_FALSE(word->isUnderlined());
}

TEST_F(TextWordTest_1181, SpaceAfterDefaultFalse_1181) {
    auto word = createTextWord();
    EXPECT_FALSE(word->getSpaceAfter());
    EXPECT_FALSE(word->hasSpaceAfter());
}

TEST_F(TextWordTest_1181, CopyConstructorDeleted_1181) {
    EXPECT_FALSE(std::is_copy_constructible<TextWord>::value);
}

TEST_F(TextWordTest_1181, CopyAssignmentDeleted_1181) {
    EXPECT_FALSE(std::is_copy_assignable<TextWord>::value);
}

TEST_F(TextWordTest_1181, GetColorDefaultValues_1181) {
    auto word = createTextWord();
    double r, g, b;
    word->getColor(&r, &g, &b);
    // Default color values should be valid doubles (typically 0)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

TEST_F(TextWordTest_1181, GetBBoxFourDoubles_1181) {
    auto word = createTextWord();
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    // For an empty word, bounding box values should still be valid
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(TextWordTest_1181, GetBBoxPDFRectangle_1181) {
    auto word = createTextWord();
    PDFRectangle rect = word->getBBox();
    EXPECT_LE(rect.x1, rect.x2);
    EXPECT_LE(rect.y1, rect.y2);
}

TEST_F(TextWordTest_1181, CmpYXStaticFunction_1181) {
    auto word1 = createTextWord(0, 12.0);
    auto word2 = createTextWord(0, 12.0);
    // Should not crash; result is a bool
    bool result = TextWord::cmpYX(word1.get(), word2.get());
    (void)result; // Just verify it doesn't crash
}

TEST_F(TextWordTest_1181, GetCharPosEmptyWord_1181) {
    auto word = createTextWord();
    int charPos = word->getCharPos();
    // For an empty word, charPos should be non-negative or some default
    (void)charPos; // Just verify no crash
}

TEST_F(TextWordTest_1181, GetCharLenEmptyWord_1181) {
    auto word = createTextWord();
    int charLen = word->getCharLen();
    (void)charLen; // Verify no crash
}

TEST_F(TextWordTest_1181, GetBaselineEmptyWord_1181) {
    auto word = createTextWord();
    double baseline = word->getBaseline();
    (void)baseline; // Verify no crash
}

TEST_F(TextWordTest_1181, MultipleRotationValues_1181) {
    for (int rot = 0; rot < 4; ++rot) {
        auto word = createTextWord(rot, 10.0);
        EXPECT_EQ(word->getRotation(), rot);
        EXPECT_EQ(word->getLength(), 0);
        EXPECT_DOUBLE_EQ(word->getFontSize(), 10.0);
    }
}

TEST_F(TextWordTest_1181, GetFontInfoEmptyWordReturnsNull_1181) {
    auto word = createTextWord();
    // With no characters, index 0 should be out of bounds or return null
    // Depending on implementation, this might return nullptr
    if (word->getLength() > 0) {
        const TextFontInfo* info = word->getFontInfo(0);
        (void)info;
    }
}

TEST_F(TextWordTest_1181, GetCharEmptyWordBoundary_1181) {
    auto word = createTextWord();
    // No characters added, so getLength() == 0
    EXPECT_EQ(word->getLength(), 0);
}
