#include <gtest/gtest.h>
#include "TextOutputDev.h"

// Since TextWordSelection requires a TextWord pointer, and we need to construct
// TextWordSelection objects for testing, we need to work with the public interface.
// We'll use nullptr or valid TextWord pointers where possible.

class TextWordSelectionTest_1214 : public ::testing::Test {
protected:
    // Helper to create TextWordSelection objects for testing
};

// Test that getBegin returns the value passed as beginA in constructor
TEST_F(TextWordSelectionTest_1214, GetBeginReturnsConstructorValue_1214) {
    TextWordSelection selection(nullptr, 5, 10);
    EXPECT_EQ(selection.getBegin(), 5);
}

// Test that getEnd returns the value passed as endA in constructor
TEST_F(TextWordSelectionTest_1214, GetEndReturnsConstructorValue_1214) {
    TextWordSelection selection(nullptr, 5, 10);
    EXPECT_EQ(selection.getEnd(), 10);
}

// Test that getWord returns the pointer passed in constructor
TEST_F(TextWordSelectionTest_1214, GetWordReturnsConstructorPointer_1214) {
    TextWordSelection selection(nullptr, 0, 0);
    EXPECT_EQ(selection.getWord(), nullptr);
}

// Test with zero begin and end values
TEST_F(TextWordSelectionTest_1214, ZeroBeginAndEnd_1214) {
    TextWordSelection selection(nullptr, 0, 0);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), 0);
}

// Test with negative begin value (boundary condition)
TEST_F(TextWordSelectionTest_1214, NegativeBeginValue_1214) {
    TextWordSelection selection(nullptr, -1, 5);
    EXPECT_EQ(selection.getBegin(), -1);
    EXPECT_EQ(selection.getEnd(), 5);
}

// Test with negative end value (boundary condition)
TEST_F(TextWordSelectionTest_1214, NegativeEndValue_1214) {
    TextWordSelection selection(nullptr, 0, -1);
    EXPECT_EQ(selection.getBegin(), 0);
    EXPECT_EQ(selection.getEnd(), -1);
}

// Test with large values
TEST_F(TextWordSelectionTest_1214, LargeValues_1214) {
    TextWordSelection selection(nullptr, 1000000, 2000000);
    EXPECT_EQ(selection.getBegin(), 1000000);
    EXPECT_EQ(selection.getEnd(), 2000000);
}

// Test where begin equals end (single point selection)
TEST_F(TextWordSelectionTest_1214, BeginEqualsEnd_1214) {
    TextWordSelection selection(nullptr, 7, 7);
    EXPECT_EQ(selection.getBegin(), 7);
    EXPECT_EQ(selection.getEnd(), 7);
}

// Test where begin is greater than end (edge case)
TEST_F(TextWordSelectionTest_1214, BeginGreaterThanEnd_1214) {
    TextWordSelection selection(nullptr, 10, 5);
    EXPECT_EQ(selection.getBegin(), 10);
    EXPECT_EQ(selection.getEnd(), 5);
}

// Test with INT_MAX boundary
TEST_F(TextWordSelectionTest_1214, IntMaxBoundary_1214) {
    TextWordSelection selection(nullptr, INT_MAX, INT_MAX);
    EXPECT_EQ(selection.getBegin(), INT_MAX);
    EXPECT_EQ(selection.getEnd(), INT_MAX);
}

// Test with INT_MIN boundary
TEST_F(TextWordSelectionTest_1214, IntMinBoundary_1214) {
    TextWordSelection selection(nullptr, INT_MIN, INT_MIN);
    EXPECT_EQ(selection.getBegin(), INT_MIN);
    EXPECT_EQ(selection.getEnd(), INT_MIN);
}

// Test that multiple instances maintain independent state
TEST_F(TextWordSelectionTest_1214, MultipleInstancesIndependent_1214) {
    TextWordSelection sel1(nullptr, 1, 2);
    TextWordSelection sel2(nullptr, 3, 4);
    
    EXPECT_EQ(sel1.getBegin(), 1);
    EXPECT_EQ(sel1.getEnd(), 2);
    EXPECT_EQ(sel2.getBegin(), 3);
    EXPECT_EQ(sel2.getEnd(), 4);
}

// Test with typical word selection range
TEST_F(TextWordSelectionTest_1214, TypicalWordSelection_1214) {
    TextWordSelection selection(nullptr, 3, 8);
    EXPECT_EQ(selection.getBegin(), 3);
    EXPECT_EQ(selection.getEnd(), 8);
    EXPECT_EQ(selection.getWord(), nullptr);
}
