#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mocking TextWord for testing purposes
class MockTextWord : public TextWord {
public:
    MOCK_CONST_METHOD0(getText, std::string());
};

// Unit test for the TextWordSelection class
TEST_F(TextWordSelectionTest_1215, GetEnd_1215) {
    // Arrange
    MockTextWord mockWord;
    const int begin = 0;
    const int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Act
    int result = selection.getEnd();

    // Assert
    EXPECT_EQ(result, end);
}

TEST_F(TextWordSelectionTest_1215, GetWord_1215) {
    // Arrange
    MockTextWord mockWord;
    const int begin = 0;
    const int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Act
    const TextWord* result = selection.getWord();

    // Assert
    EXPECT_EQ(result, &mockWord);
}

TEST_F(TextWordSelectionTest_1215, GetBegin_1215) {
    // Arrange
    MockTextWord mockWord;
    const int begin = 5;
    const int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Act
    int result = selection.getBegin();

    // Assert
    EXPECT_EQ(result, begin);
}

// Exceptional case for invalid selection (boundary case)
TEST_F(TextWordSelectionTest_1215, GetEnd_InvalidSelection_1215) {
    // Arrange
    MockTextWord mockWord;
    const int begin = 10;
    const int end = 5;  // Invalid case, begin > end
    TextWordSelection selection(&mockWord, begin, end);

    // Act
    int result = selection.getEnd();

    // Assert
    EXPECT_EQ(result, end);  // For this interface, we may not be able to verify an exception directly unless it's visible via return values or callbacks.
}