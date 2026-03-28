#include <gtest/gtest.h>
#include "TextOutputDev.h"  // Assuming the header file is located at ./TestProjects/poppler/poppler/TextOutputDev.h

// Mock class for TextWord to use in our tests
class MockTextWord : public TextWord {
public:
    MOCK_METHOD0(getText, const std::string&());
};

// Test suite for TextWordSelection
class TextWordSelectionTest_1213 : public ::testing::Test {
protected:
    // Helper function to create a TextWordSelection with mock values
    TextWordSelection createSelection(const TextWord* word, int begin, int end) {
        return TextWordSelection(word, begin, end);
    }
};

// Test case: Normal operation (valid word, begin, and end)
TEST_F(TextWordSelectionTest_1213, GetWordReturnsCorrectTextWord_1213) {
    MockTextWord word;
    const std::string word_text = "example";
    EXPECT_CALL(word, getText()).WillOnce(::testing::ReturnRef(word_text));
    
    TextWordSelection selection(&word, 0, 7);
    EXPECT_EQ(selection.getWord(), &word);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 7);
}

// Test case: Boundary condition (begin == end, edge case)
TEST_F(TextWordSelectionTest_1213, GetWordWithZeroLengthSelection_1213) {
    MockTextWord word;
    TextWordSelection selection(&word, 0, 0);

    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 0);
    EXPECT_EQ(selection.getWord(), &word);
}

// Test case: Boundary condition (max integer values for begin and end)
TEST_F(TextWordSelectionTest_1213, GetWordWithMaxBoundaryValues_1213) {
    MockTextWord word;
    TextWordSelection selection(&word, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    EXPECT_EQ(selection.getBegin(), std::numeric_limits<int>::min());
    EXPECT_EQ(selection.getEnd(), std::numeric_limits<int>::max());
    EXPECT_EQ(selection.getWord(), &word);
}

// Test case: Exceptional case (nullptr for the word)
TEST_F(TextWordSelectionTest_1213, GetWordWithNullWord_1213) {
    TextWordSelection selection(nullptr, 0, 7);
    
    // Since the word is null, we can test if this condition is handled properly
    EXPECT_EQ(selection.getWord(), nullptr);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 7);
}