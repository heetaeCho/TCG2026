#include <gtest/gtest.h>
#include "TextOutputDev.h"  // Include the header for TextWordSelection

// Mock class for TextWord if needed (you may not need it if TextWord doesn't have dependencies)
class MockTextWord : public TextWord {
public:
    MOCK_METHOD(int, getLength, (), (const, override));  // Example of a mock method if needed
};

// Test fixture for TextWordSelection
class TextWordSelectionTest_1214 : public ::testing::Test {
protected:
    // Helper method for creating a TextWordSelection instance
    TextWordSelection* createTextWordSelection(const TextWord* word, int begin, int end) {
        return new TextWordSelection(word, begin, end);
    }
};

// Test for normal operation of getBegin()
TEST_F(TextWordSelectionTest_1214, GetBegin_Normal_Operation_1214) {
    MockTextWord mockWord;
    int begin = 5;
    int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Verify that the getBegin() method works as expected
    EXPECT_EQ(selection.getBegin(), begin);
}

// Test for normal operation of getEnd()
TEST_F(TextWordSelectionTest_1214, GetEnd_Normal_Operation_1214) {
    MockTextWord mockWord;
    int begin = 5;
    int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Verify that the getEnd() method works as expected
    EXPECT_EQ(selection.getEnd(), end);
}

// Test for exceptional case when the selection has a negative range
TEST_F(TextWordSelectionTest_1214, GetBegin_Invalid_Range_1214) {
    MockTextWord mockWord;
    int begin = 10;
    int end = 5;  // Invalid range where begin > end
    TextWordSelection selection(&mockWord, begin, end);

    // Verify that an invalid range is handled, but in this case, it's just an observable behavior based on implementation
    EXPECT_EQ(selection.getBegin(), begin);
    EXPECT_EQ(selection.getEnd(), end);
}

// Test for normal operation of getWord()
TEST_F(TextWordSelectionTest_1214, GetWord_Normal_Operation_1214) {
    MockTextWord mockWord;
    int begin = 5;
    int end = 10;
    TextWordSelection selection(&mockWord, begin, end);

    // Verify that getWord() returns the correct word (i.e., the mock word)
    EXPECT_EQ(selection.getWord(), &mockWord);
}