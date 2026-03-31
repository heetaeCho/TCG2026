#include <gtest/gtest.h>
#include "TextOutputDev.h"

// Test fixture for TextWordSelection
class TextWordSelectionTest_1215 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getEnd returns the correct end value when constructed with positive values
TEST_F(TextWordSelectionTest_1215, GetEndReturnsCorrectValue_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, 5);
    EXPECT_EQ(selection.getEnd(), 5);
}

// Test that getEnd returns zero when end is initialized to zero
TEST_F(TextWordSelectionTest_1215, GetEndReturnsZero_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, 0);
    EXPECT_EQ(selection.getEnd(), 0);
}

// Test that getEnd returns correct value for large end value
TEST_F(TextWordSelectionTest_1215, GetEndReturnsLargeValue_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, 100000);
    EXPECT_EQ(selection.getEnd(), 100000);
}

// Test that getEnd returns negative value when constructed with negative end
TEST_F(TextWordSelectionTest_1215, GetEndReturnsNegativeValue_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, -1);
    EXPECT_EQ(selection.getEnd(), -1);
}

// Test that getBegin returns the correct begin value
TEST_F(TextWordSelectionTest_1215, GetBeginReturnsCorrectValue_1215) {
    TextWord word;
    TextWordSelection selection(&word, 3, 10);
    EXPECT_EQ(selection.getBegin(), 3);
}

// Test that getBegin returns zero
TEST_F(TextWordSelectionTest_1215, GetBeginReturnsZero_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, 10);
    EXPECT_EQ(selection.getBegin(), 0);
}

// Test that getWord returns the correct word pointer
TEST_F(TextWordSelectionTest_1215, GetWordReturnsCorrectPointer_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, 5);
    EXPECT_EQ(selection.getWord(), &word);
}

// Test that getWord returns nullptr when constructed with nullptr
TEST_F(TextWordSelectionTest_1215, GetWordReturnsNullptr_1215) {
    TextWordSelection selection(nullptr, 0, 5);
    EXPECT_EQ(selection.getWord(), nullptr);
}

// Test begin equals end (empty selection)
TEST_F(TextWordSelectionTest_1215, EmptySelectionBeginEqualsEnd_1215) {
    TextWord word;
    TextWordSelection selection(&word, 5, 5);
    EXPECT_EQ(selection.getBegin(), selection.getEnd());
    EXPECT_EQ(selection.getEnd(), 5);
}

// Test that begin is less than end in normal case
TEST_F(TextWordSelectionTest_1215, BeginLessThanEnd_1215) {
    TextWord word;
    TextWordSelection selection(&word, 2, 8);
    EXPECT_LT(selection.getBegin(), selection.getEnd());
    EXPECT_EQ(selection.getBegin(), 2);
    EXPECT_EQ(selection.getEnd(), 8);
}

// Test boundary with INT_MAX
TEST_F(TextWordSelectionTest_1215, GetEndWithIntMax_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, INT_MAX);
    EXPECT_EQ(selection.getEnd(), INT_MAX);
}

// Test boundary with INT_MIN
TEST_F(TextWordSelectionTest_1215, GetEndWithIntMin_1215) {
    TextWord word;
    TextWordSelection selection(&word, 0, INT_MIN);
    EXPECT_EQ(selection.getEnd(), INT_MIN);
}

// Test that multiple selections with different words are independent
TEST_F(TextWordSelectionTest_1215, MultipleSelectionsAreIndependent_1215) {
    TextWord word1;
    TextWord word2;
    TextWordSelection sel1(&word1, 0, 3);
    TextWordSelection sel2(&word2, 4, 7);
    
    EXPECT_EQ(sel1.getWord(), &word1);
    EXPECT_EQ(sel2.getWord(), &word2);
    EXPECT_NE(sel1.getWord(), sel2.getWord());
    EXPECT_EQ(sel1.getEnd(), 3);
    EXPECT_EQ(sel2.getEnd(), 7);
    EXPECT_EQ(sel1.getBegin(), 0);
    EXPECT_EQ(sel2.getBegin(), 4);
}
