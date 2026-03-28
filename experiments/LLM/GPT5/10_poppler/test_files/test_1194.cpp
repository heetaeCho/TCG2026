#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include "TextOutputDev.h"

// Mocking the dependencies (if needed)
class MockTextSelectionVisitor : public TextSelectionVisitor {
public:
    MOCK_METHOD(void, visit, (TextWord *word), (override));
};

// Test Suite for TextWord
TEST_F(TextWordTest_1194, GetEdgeReturnsCorrectEdge_1194) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    double edge = word.getEdge(0);

    // Assert
    EXPECT_DOUBLE_EQ(edge, word.chars[0].edge);
}

TEST_F(TextWordTest_1194, GetFontInfoReturnsCorrectFontInfo_1195) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    const TextFontInfo* returnedFontInfo = word.getFontInfo(0);

    // Assert
    EXPECT_EQ(returnedFontInfo, &fontInfo);
}

TEST_F(TextWordTest_1194, GetLengthReturnsCorrectLength_1196) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    int length = word.getLength();

    // Assert
    EXPECT_EQ(length, 2);
}

TEST_F(TextWordTest_1194, GetBBoxReturnsCorrectBoundingBox_1197) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    double xMin, yMin, xMax, yMax;
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    word.getBBox(&xMin, &yMin, &xMax, &yMax);

    // Assert
    EXPECT_GE(xMax, xMin);
    EXPECT_GE(yMax, yMin);
}

TEST_F(TextWordTest_1194, GetTextReturnsCorrectText_1198) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    auto text = word.getText();

    // Assert
    EXPECT_EQ(text->length(), 2);
}

TEST_F(TextWordTest_1194, GetRotationReturnsCorrectRotation_1199) {
    // Arrange
    TextWord word(nullptr, 90, 12.0);

    // Act
    int rotation = word.getRotation();

    // Assert
    EXPECT_EQ(rotation, 90);
}

TEST_F(TextWordTest_1194, GetCharReturnsCorrectCharacter_1200) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    CharCode charCode = 65; // 'A'
    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, charCode, 0, Matrix());

    // Act
    const Unicode* character = word.getChar(0);

    // Assert
    EXPECT_EQ(*character, 'A');
}

TEST_F(TextWordTest_1194, VisitSelectionCallsVisit_1201) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    MockTextSelectionVisitor mockVisitor;
    TextSelectionVisitor* visitor = &mockVisitor;

    word.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Expect
    EXPECT_CALL(mockVisitor, visit(&word)).Times(1);

    // Act
    word.visitSelection(visitor, nullptr);
}

TEST_F(TextWordTest_1194, AddCombiningReturnsTrueWhenValid_1202) {
    // Arrange
    TextWord word(nullptr, 0, 12.0);
    TextFontInfo fontInfo;
    word.addChar(&fontInfo, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    bool result = word.addCombining(&fontInfo, 12.0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(TextWordTest_1194, MergeCombinesWordsCorrectly_1203) {
    // Arrange
    TextWord word1(nullptr, 0, 12.0);
    TextWord word2(nullptr, 0, 12.0);
    word1.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());
    word2.addChar(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, Matrix());

    // Act
    word1.merge(&word2);

    // Assert
    EXPECT_EQ(word1.getLength(), 2);
}