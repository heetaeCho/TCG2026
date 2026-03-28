#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mocking dependencies if needed (e.g., TextSelectionVisitor, AnnotLink)
class MockTextSelectionVisitor : public TextSelectionVisitor {
public:
    MOCK_METHOD(void, visit, (const TextWord* word), (override));
};

// Test suite for TextWord
TEST_F(TextWordTest_1200, GetFontSize_1200) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 0, 12.0);

    // Act
    double fontSize = word.getFontSize();

    // Assert
    EXPECT_EQ(fontSize, 12.0);
}

TEST_F(TextWordTest_1201, GetRotation_1201) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 90, 12.0);

    // Act
    int rotation = word.getRotation();

    // Assert
    EXPECT_EQ(rotation, 90);
}

TEST_F(TextWordTest_1202, GetColor_1202) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 0, 12.0);
    double r, g, b;

    // Act
    word.getColor(&r, &g, &b);

    // Assert
    EXPECT_DOUBLE_EQ(r, 0.0);
    EXPECT_DOUBLE_EQ(g, 0.0);
    EXPECT_DOUBLE_EQ(b, 0.0);
}

TEST_F(TextWordTest_1203, HasSpaceAfter_1203) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 0, 12.0);

    // Act
    bool hasSpace = word.hasSpaceAfter();

    // Assert
    EXPECT_FALSE(hasSpace);
}

// Boundary test for TextPool
TEST_F(TextPoolTest_1204, AddWordBoundary_1204) {
    // Arrange
    TextPool pool;
    GfxState gfxState;
    TextWord* word = new TextWord(&gfxState, 0, 12.0);

    // Act
    pool.addWord(word);

    // Assert
    EXPECT_EQ(pool.getPool(0), word);
}

TEST_F(TextPoolTest_1205, SetPoolBoundary_1205) {
    // Arrange
    TextPool pool;
    GfxState gfxState;
    TextWord* word = new TextWord(&gfxState, 0, 12.0);
    
    // Act
    pool.setPool(0, word);
    TextWord* result = pool.getPool(0);

    // Assert
    EXPECT_EQ(result, word);
}

// Exceptional case: Verify behavior when trying to set a word for an invalid base index
TEST_F(TextPoolTest_1206, SetPoolInvalidBaseIdx_1206) {
    // Arrange
    TextPool pool;
    GfxState gfxState;
    TextWord* word = new TextWord(&gfxState, 0, 12.0);

    // Act & Assert
    EXPECT_THROW(pool.setPool(-1, word), std::out_of_range);
}

// Test for verifying interaction with external mock objects (e.g., TextSelectionVisitor)
TEST_F(TextWordTest_1207, VisitSelection_1207) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 0, 12.0);
    MockTextSelectionVisitor mockVisitor;

    // Expect that the visit function will be called with the word object
    EXPECT_CALL(mockVisitor, visit(&word)).Times(1);

    // Act
    word.visitSelection(&mockVisitor, nullptr);
}

// Boundary test for TextWord length
TEST_F(TextWordTest_1208, GetLengthBoundary_1208) {
    // Arrange
    GfxState gfxState;
    TextWord word(&gfxState, 0, 12.0);
    
    // Act
    int length = word.getLength();

    // Assert
    EXPECT_GE(length, 0);  // Length should not be negative
}