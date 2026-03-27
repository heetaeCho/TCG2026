#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mock class for external dependencies
class MockTextSelectionVisitor : public TextSelectionVisitor {
public:
    MOCK_METHOD(void, visitSelection, (TextWord *word, const PDFRectangle *selection), (override));
};

// Test class for TextWord
class TextWordTest_1188 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test the getRotation function
TEST_F(TextWordTest_1188, GetRotationNormal_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);

    // When
    int rotation = textWord.getRotation();

    // Then
    EXPECT_EQ(rotation, 90);
}

// Test for boundary case in getRotation (rotation at 0 degrees)
TEST_F(TextWordTest_1188, GetRotationBoundaryZero_1188) {
    // Given
    TextWord textWord(nullptr, 0, 12.0);

    // When
    int rotation = textWord.getRotation();

    // Then
    EXPECT_EQ(rotation, 0);
}

// Test for boundary case in getRotation (rotation at 360 degrees)
TEST_F(TextWordTest_1188, GetRotationBoundaryMax_1188) {
    // Given
    TextWord textWord(nullptr, 360, 12.0);

    // When
    int rotation = textWord.getRotation();

    // Then
    EXPECT_EQ(rotation, 360);
}

// Test for exceptional case where rotation is negative
TEST_F(TextWordTest_1188, GetRotationExceptionalNegative_1188) {
    // Given
    TextWord textWord(nullptr, -90, 12.0);

    // When
    int rotation = textWord.getRotation();

    // Then
    EXPECT_EQ(rotation, -90);
}

// Test the nextWord function
TEST_F(TextWordTest_1188, NextWordNull_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);

    // When
    const TextWord* next = textWord.nextWord();

    // Then
    EXPECT_EQ(next, nullptr);  // No next word, should return nullptr
}

// Test the nextWord function with mock interaction
TEST_F(TextWordTest_1188, NextWordWithMock_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);
    TextWord nextWord(nullptr, 90, 12.0);
    textWord.merge(&nextWord);  // Assuming merge correctly sets nextWord

    // Mock object to check interaction
    MockTextSelectionVisitor mockVisitor;
    PDFRectangle rect;
    
    // When
    EXPECT_CALL(mockVisitor, visitSelection(&textWord, &rect)).Times(1);
    textWord.visitSelection(&mockVisitor, &rect);

    // Then
    // The mock function is called, no assertion needed unless expected call is missed
}

// Test for getText() returning non-empty text
TEST_F(TextWordTest_1188, GetTextNonEmpty_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);

    // When
    auto text = textWord.getText();

    // Then
    EXPECT_TRUE(text->length() > 0);  // Assuming getText() returns some non-empty text
}

// Test exceptional case for getColor (invalid input or unexpected behavior)
TEST_F(TextWordTest_1188, GetColorExceptional_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);
    double r, g, b;

    // When
    textWord.getColor(&r, &g, &b);

    // Then
    EXPECT_GE(r, 0.0);  // Ensure color values are within expected range
    EXPECT_GE(g, 0.0);
    EXPECT_GE(b, 0.0);
}

// Test getBBox to ensure proper behavior
TEST_F(TextWordTest_1188, GetBBoxNormal_1188) {
    // Given
    TextWord textWord(nullptr, 90, 12.0);
    double xMin, yMin, xMax, yMax;

    // When
    textWord.getBBox(&xMin, &yMin, &xMax, &yMax);

    // Then
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test boundary condition for empty TextWord
TEST_F(TextWordTest_1188, GetBBoxEmpty_1188) {
    // Given
    TextWord textWord(nullptr, 90, 0);  // With zero font size or no content
    double xMin, yMin, xMax, yMax;

    // When
    textWord.getBBox(&xMin, &yMin, &xMax, &yMax);

    // Then
    EXPECT_EQ(xMin, 0.0);
    EXPECT_EQ(yMin, 0.0);
    EXPECT_EQ(xMax, 0.0);
    EXPECT_EQ(yMax, 0.0);
}