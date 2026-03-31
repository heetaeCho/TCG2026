#include <gtest/gtest.h>
#include "TextOutputDev.h"

// Since TextWord is a complex class, we need to work with what's available.
// We'll test TextWordSelection's public interface.

class TextWordSelectionTest_1213 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getWord returns the word passed during construction
TEST_F(TextWordSelectionTest_1213, GetWordReturnsConstructedWord_1213) {
    // We need a TextWord pointer - we can use nullptr as a boundary case
    // or create a real one if possible. Since TextWord construction may be complex,
    // we test with a known pointer value.
    const TextWord *wordPtr = nullptr;
    TextWordSelection selection(wordPtr, 0, 5);
    EXPECT_EQ(selection.getWord(), wordPtr);
}

// Test that getBegin returns the begin value passed during construction
TEST_F(TextWordSelectionTest_1213, GetBeginReturnsConstructedBegin_1213) {
    TextWordSelection selection(nullptr, 3, 10);
    EXPECT_EQ(selection.getBegin(), 3);
}

// Test that getEnd returns the end value passed during construction
TEST_F(TextWordSelectionTest_1213, GetEndReturnsConstructedEnd_1213) {
    TextWordSelection selection(nullptr, 3, 10);
    EXPECT_EQ(selection.getEnd(), 10);
}

// Test with zero begin and end
TEST_F(TextWordSelectionTest_1213, ZeroBeginAndEnd_1213) {
    TextWordSelection selection(nullptr, 0, 0);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 0);
    EXPECT_EQ(selection.getWord(), nullptr);
}

// Test with begin equal to end
TEST_F(TextWordSelectionTest_1213, BeginEqualsEnd_1213) {
    TextWordSelection selection(nullptr, 5, 5);
    EXPECT_EQ(selection.getBegin(), 5);
    EXPECT_EQ(selection.getEnd(), 5);
}

// Test with large values for begin and end
TEST_F(TextWordSelectionTest_1213, LargeBeginAndEnd_1213) {
    TextWordSelection selection(nullptr, 100000, 200000);
    EXPECT_EQ(selection.getBegin(), 100000);
    EXPECT_EQ(selection.getEnd(), 200000);
}

// Test with negative values (boundary case)
TEST_F(TextWordSelectionTest_1213, NegativeBeginAndEnd_1213) {
    TextWordSelection selection(nullptr, -1, -1);
    EXPECT_EQ(selection.getBegin(), -1);
    EXPECT_EQ(selection.getEnd(), -1);
}

// Test that getWord returns a non-null pointer when constructed with one
TEST_F(TextWordSelectionTest_1213, GetWordReturnsNonNullPointer_1213) {
    // Use reinterpret_cast to create a dummy non-null pointer for testing
    // without actually constructing a TextWord
    const TextWord *dummyWord = reinterpret_cast<const TextWord *>(0x12345678);
    TextWordSelection selection(dummyWord, 1, 4);
    EXPECT_EQ(selection.getWord(), dummyWord);
    EXPECT_EQ(selection.getBegin(), 1);
    EXPECT_EQ(selection.getEnd(), 4);
}

// Test begin is 0 and end is 1 (single character selection)
TEST_F(TextWordSelectionTest_1213, SingleCharacterSelection_1213) {
    TextWordSelection selection(nullptr, 0, 1);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 1);
}

// Test that begin > end is allowed (no validation expected at this level)
TEST_F(TextWordSelectionTest_1213, BeginGreaterThanEnd_1213) {
    TextWordSelection selection(nullptr, 10, 5);
    EXPECT_EQ(selection.getBegin(), 10);
    EXPECT_EQ(selection.getEnd(), 5);
}
