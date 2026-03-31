#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "Link.h"

// Since we need GfxState to construct TextWord, and we're treating the implementation
// as a black box, we'll test what we can through the public interface.

class TextWordTest_1187 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to create a TextWord through its constructor
        // TextWord(const GfxState *state, int rotA, double fontSize)
    }

    void TearDown() override {
    }
};

// Test construction with rotation 0 and a specific font size
TEST_F(TextWordTest_1187, ConstructWithRotation0_1187) {
    // We need a GfxState to create a TextWord
    // Since GfxState construction may be complex, we'll try with nullptr
    // if the constructor handles it, or create a minimal state
    
    double fontSize = 12.0;
    int rotation = 0;
    
    // Attempt to create TextWord - this may crash if state is strictly required
    // In production code, state is always valid, but we test the interface
    TextWord word(nullptr, rotation, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
    EXPECT_EQ(word.getRotation(), rotation);
}

// Test construction with rotation 1
TEST_F(TextWordTest_1187, ConstructWithRotation1_1187) {
    double fontSize = 10.5;
    int rotation = 1;
    
    TextWord word(nullptr, rotation, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
    EXPECT_EQ(word.getRotation(), rotation);
}

// Test construction with rotation 2
TEST_F(TextWordTest_1187, ConstructWithRotation2_1187) {
    double fontSize = 8.0;
    int rotation = 2;
    
    TextWord word(nullptr, rotation, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
    EXPECT_EQ(word.getRotation(), rotation);
}

// Test construction with rotation 3
TEST_F(TextWordTest_1187, ConstructWithRotation3_1187) {
    double fontSize = 24.0;
    int rotation = 3;
    
    TextWord word(nullptr, rotation, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), fontSize);
    EXPECT_EQ(word.getRotation(), rotation);
}

// Test getFontSize returns correct value
TEST_F(TextWordTest_1187, GetFontSizeReturnsCorrectValue_1187) {
    double fontSize = 16.5;
    TextWord word(nullptr, 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 16.5);
}

// Test getFontSize with zero font size
TEST_F(TextWordTest_1187, GetFontSizeZero_1187) {
    double fontSize = 0.0;
    TextWord word(nullptr, 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.0);
}

// Test getFontSize with very large font size
TEST_F(TextWordTest_1187, GetFontSizeLarge_1187) {
    double fontSize = 1000.0;
    TextWord word(nullptr, 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 1000.0);
}

// Test getFontSize with very small font size
TEST_F(TextWordTest_1187, GetFontSizeSmall_1187) {
    double fontSize = 0.001;
    TextWord word(nullptr, 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), 0.001);
}

// Test that a newly created TextWord has length 0 (no characters added)
TEST_F(TextWordTest_1187, InitialLengthIsZero_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_EQ(word.getLength(), 0);
}

// Test that len() returns same as getLength() for empty word
TEST_F(TextWordTest_1187, LenMatchesGetLength_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_EQ(word.len(), word.getLength());
}

// Test getText on empty word
TEST_F(TextWordTest_1187, GetTextEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    auto text = word.getText();
    EXPECT_NE(text, nullptr);
    // Empty word should have empty text
    EXPECT_TRUE(text->empty());
}

// Test getNext returns nullptr for standalone word
TEST_F(TextWordTest_1187, GetNextReturnsNullForStandalone_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_EQ(word.getNext(), nullptr);
}

// Test nextWord returns nullptr for standalone word
TEST_F(TextWordTest_1187, NextWordReturnsNullForStandalone_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test getLink returns nullptr when no link is set
TEST_F(TextWordTest_1187, GetLinkReturnsNullByDefault_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_EQ(word.getLink(), nullptr);
}

// Test getSpaceAfter on newly created word
TEST_F(TextWordTest_1187, GetSpaceAfterDefault_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    // Default should be false
    EXPECT_FALSE(word.getSpaceAfter());
}

// Test hasSpaceAfter on newly created word
TEST_F(TextWordTest_1187, HasSpaceAfterDefault_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_FALSE(word.hasSpaceAfter());
}

// Test isUnderlined on newly created word
TEST_F(TextWordTest_1187, IsUnderlinedDefault_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    EXPECT_FALSE(word.isUnderlined());
}

// Test getColor returns default color values
TEST_F(TextWordTest_1187, GetColorDefault_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    double r, g, b;
    word.getColor(&r, &g, &b);
    
    // Default color should be initialized (likely 0,0,0)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getBBox (4-param version) on empty word
TEST_F(TextWordTest_1187, GetBBoxEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // For an empty word, bounding box values should be defined
    // (they may be initialized to some default)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getBBox (PDFRectangle version) on empty word
TEST_F(TextWordTest_1187, GetBBoxPDFRectangleEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    PDFRectangle rect = word.getBBox();
    
    EXPECT_LE(rect.x1, rect.x2);
    EXPECT_LE(rect.y1, rect.y2);
}

// Test getCharPos on empty word
TEST_F(TextWordTest_1187, GetCharPosEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    // charPos should be a valid value even for empty word
    int charPos = word.getCharPos();
    EXPECT_GE(charPos, 0);
}

// Test getCharLen on empty word
TEST_F(TextWordTest_1187, GetCharLenEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    int charLen = word.getCharLen();
    EXPECT_GE(charLen, 0);
}

// Test getBaseline returns a value
TEST_F(TextWordTest_1187, GetBaselineReturnsValue_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    double baseline = word.getBaseline();
    // Just verify it doesn't crash and returns a finite value
    EXPECT_FALSE(std::isnan(baseline));
}

// Test that copy constructor is deleted (compile-time check)
// This is verified by the = delete declaration; we just note it here
// The following should NOT compile if uncommented:
// TEST_F(TextWordTest_1187, CopyConstructorDeleted_1187) {
//     TextWord word(nullptr, 0, 12.0);
//     TextWord copy(word); // Should not compile
// }

// Test that copy assignment is deleted (compile-time check)
// TEST_F(TextWordTest_1187, CopyAssignmentDeleted_1187) {
//     TextWord word1(nullptr, 0, 12.0);
//     TextWord word2(nullptr, 0, 12.0);
//     word2 = word1; // Should not compile
// }

// Test cmpYX static comparison function
TEST_F(TextWordTest_1187, CmpYXStaticFunction_1187) {
    TextWord word1(nullptr, 0, 12.0);
    TextWord word2(nullptr, 0, 12.0);
    
    // Both words at default position, comparison should be well-defined
    bool result1 = TextWord::cmpYX(&word1, &word2);
    bool result2 = TextWord::cmpYX(&word2, &word1);
    
    // If they're equal, neither should be less than the other
    // (or both could be false in strict weak ordering)
    if (result1) {
        EXPECT_FALSE(result2);
    }
}

// Test negative font size
TEST_F(TextWordTest_1187, NegativeFontSize_1187) {
    double fontSize = -5.0;
    TextWord word(nullptr, 0, fontSize);
    
    EXPECT_DOUBLE_EQ(word.getFontSize(), -5.0);
}

// Test getFontInfo on empty word with index 0
TEST_F(TextWordTest_1187, GetFontInfoEmptyWordIndex0_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    // For empty word, this may return nullptr
    // We just verify it doesn't crash for boundary
    if (word.getLength() > 0) {
        const TextFontInfo *info = word.getFontInfo(0);
        // May or may not be null
        (void)info;
    }
}

// Test getFontName on empty word
TEST_F(TextWordTest_1187, GetFontNameEmptyWord_1187) {
    TextWord word(nullptr, 0, 12.0);
    
    if (word.getLength() > 0) {
        const GooString *name = word.getFontName(0);
        (void)name;
    }
}

// Test getRotation boundary values
TEST_F(TextWordTest_1187, GetRotationBoundary_1187) {
    for (int rot = 0; rot < 4; ++rot) {
        TextWord word(nullptr, rot, 12.0);
        EXPECT_EQ(word.getRotation(), rot);
    }
}
