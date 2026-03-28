#include <gtest/gtest.h>
#include "ProfileData.h"

class ProfileDataTest_1054 : public ::testing::Test {
protected:
    ProfileData pd;
};

// Test initial state - count should be 0
TEST_F(ProfileDataTest_1054, InitialCountIsZero_1054) {
    EXPECT_EQ(pd.getCount(), 0);
}

// Test initial state - total should be 0
TEST_F(ProfileDataTest_1054, InitialTotalIsZero_1054) {
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
}

// Test initial state - min should be 0
TEST_F(ProfileDataTest_1054, InitialMinIsZero_1054) {
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
}

// Test initial state - max should be 0
TEST_F(ProfileDataTest_1054, InitialMaxIsZero_1054) {
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding a single element updates count
TEST_F(ProfileDataTest_1054, AddOneElementCountIsOne_1054) {
    pd.addElement(5.0);
    EXPECT_EQ(pd.getCount(), 1);
}

// Test adding a single element updates total
TEST_F(ProfileDataTest_1054, AddOneElementTotalCorrect_1054) {
    pd.addElement(5.0);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 5.0);
}

// Test adding a single element sets min
TEST_F(ProfileDataTest_1054, AddOneElementMinCorrect_1054) {
    pd.addElement(5.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 5.0);
}

// Test adding a single element sets max
TEST_F(ProfileDataTest_1054, AddOneElementMaxCorrect_1054) {
    pd.addElement(5.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}

// Test adding multiple elements updates count correctly
TEST_F(ProfileDataTest_1054, AddMultipleElementsCountCorrect_1054) {
    pd.addElement(1.0);
    pd.addElement(2.0);
    pd.addElement(3.0);
    EXPECT_EQ(pd.getCount(), 3);
}

// Test adding multiple elements updates total correctly
TEST_F(ProfileDataTest_1054, AddMultipleElementsTotalCorrect_1054) {
    pd.addElement(1.0);
    pd.addElement(2.0);
    pd.addElement(3.0);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 6.0);
}

// Test min is tracked correctly with multiple elements
TEST_F(ProfileDataTest_1054, AddMultipleElementsMinCorrect_1054) {
    pd.addElement(3.0);
    pd.addElement(1.0);
    pd.addElement(2.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
}

// Test max is tracked correctly with multiple elements
TEST_F(ProfileDataTest_1054, AddMultipleElementsMaxCorrect_1054) {
    pd.addElement(1.0);
    pd.addElement(3.0);
    pd.addElement(2.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 3.0);
}

// Test adding zero as an element
TEST_F(ProfileDataTest_1054, AddZeroElement_1054) {
    pd.addElement(0.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding negative values
TEST_F(ProfileDataTest_1054, AddNegativeElements_1054) {
    pd.addElement(-5.0);
    pd.addElement(-1.0);
    pd.addElement(-10.0);
    EXPECT_EQ(pd.getCount(), 3);
    EXPECT_DOUBLE_EQ(pd.getTotal(), -16.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -10.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), -1.0);
}

// Test min is the first element when only one element is added
TEST_F(ProfileDataTest_1054, SingleElementMinEqualsMax_1054) {
    pd.addElement(42.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), pd.getMax());
}

// Test adding elements in ascending order
TEST_F(ProfileDataTest_1054, AscendingOrderMinMax_1054) {
    pd.addElement(1.0);
    pd.addElement(2.0);
    pd.addElement(3.0);
    pd.addElement(4.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 4.0);
}

// Test adding elements in descending order
TEST_F(ProfileDataTest_1054, DescendingOrderMinMax_1054) {
    pd.addElement(4.0);
    pd.addElement(3.0);
    pd.addElement(2.0);
    pd.addElement(1.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 4.0);
}

// Test adding identical elements
TEST_F(ProfileDataTest_1054, IdenticalElements_1054) {
    pd.addElement(7.0);
    pd.addElement(7.0);
    pd.addElement(7.0);
    EXPECT_EQ(pd.getCount(), 3);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 21.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 7.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 7.0);
}

// Test very small positive values
TEST_F(ProfileDataTest_1054, VerySmallPositiveValues_1054) {
    pd.addElement(1e-15);
    pd.addElement(2e-15);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3e-15);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e-15);
    EXPECT_DOUBLE_EQ(pd.getMax(), 2e-15);
}

// Test very large values
TEST_F(ProfileDataTest_1054, VeryLargeValues_1054) {
    pd.addElement(1e15);
    pd.addElement(2e15);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3e15);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e15);
    EXPECT_DOUBLE_EQ(pd.getMax(), 2e15);
}

// Test mixed positive and negative values
TEST_F(ProfileDataTest_1054, MixedPositiveNegativeValues_1054) {
    pd.addElement(-3.0);
    pd.addElement(5.0);
    pd.addElement(0.0);
    pd.addElement(-1.0);
    pd.addElement(2.0);
    EXPECT_EQ(pd.getCount(), 5);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -3.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}

// Test that adding many elements accumulates total correctly
TEST_F(ProfileDataTest_1054, ManyElementsTotalAccumulation_1054) {
    for (int i = 1; i <= 100; i++) {
        pd.addElement(1.0);
    }
    EXPECT_EQ(pd.getCount(), 100);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 100.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 1.0);
}
