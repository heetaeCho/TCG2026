#include <gtest/gtest.h>
#include "ProfileData.h"

class ProfileDataTest_1056 : public ::testing::Test {
protected:
    ProfileData pd;
};

// Test default state - count should be 0
TEST_F(ProfileDataTest_1056, DefaultCount_1056) {
    EXPECT_EQ(pd.getCount(), 0);
}

// Test default state - total should be 0
TEST_F(ProfileDataTest_1056, DefaultTotal_1056) {
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
}

// Test default state - min should be 0
TEST_F(ProfileDataTest_1056, DefaultMin_1056) {
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
}

// Test default state - max should be 0
TEST_F(ProfileDataTest_1056, DefaultMax_1056) {
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding a single element
TEST_F(ProfileDataTest_1056, AddSingleElement_1056) {
    pd.addElement(5.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 5.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 5.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}

// Test adding multiple elements - count increases
TEST_F(ProfileDataTest_1056, AddMultipleElementsCount_1056) {
    pd.addElement(1.0);
    pd.addElement(2.0);
    pd.addElement(3.0);
    EXPECT_EQ(pd.getCount(), 3);
}

// Test adding multiple elements - total is sum
TEST_F(ProfileDataTest_1056, AddMultipleElementsTotal_1056) {
    pd.addElement(1.0);
    pd.addElement(2.0);
    pd.addElement(3.0);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 6.0);
}

// Test adding multiple elements - min is tracked
TEST_F(ProfileDataTest_1056, AddMultipleElementsMin_1056) {
    pd.addElement(3.0);
    pd.addElement(1.0);
    pd.addElement(2.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
}

// Test adding multiple elements - max is tracked
TEST_F(ProfileDataTest_1056, AddMultipleElementsMax_1056) {
    pd.addElement(1.0);
    pd.addElement(3.0);
    pd.addElement(2.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 3.0);
}

// Test adding zero value
TEST_F(ProfileDataTest_1056, AddZeroElement_1056) {
    pd.addElement(0.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding negative values
TEST_F(ProfileDataTest_1056, AddNegativeElement_1056) {
    pd.addElement(-5.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), -5.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -5.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), -5.0);
}

// Test min with negative values
TEST_F(ProfileDataTest_1056, MinWithNegativeValues_1056) {
    pd.addElement(-1.0);
    pd.addElement(-5.0);
    pd.addElement(-2.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -5.0);
}

// Test max with negative values
TEST_F(ProfileDataTest_1056, MaxWithNegativeValues_1056) {
    pd.addElement(-1.0);
    pd.addElement(-5.0);
    pd.addElement(-2.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), -1.0);
}

// Test with very large values
TEST_F(ProfileDataTest_1056, LargeValues_1056) {
    pd.addElement(1e15);
    pd.addElement(2e15);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3e15);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e15);
    EXPECT_DOUBLE_EQ(pd.getMax(), 2e15);
}

// Test with very small values
TEST_F(ProfileDataTest_1056, VerySmallValues_1056) {
    pd.addElement(1e-15);
    pd.addElement(2e-15);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3e-15);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e-15);
    EXPECT_DOUBLE_EQ(pd.getMax(), 2e-15);
}

// Test adding same value multiple times
TEST_F(ProfileDataTest_1056, AddSameValueMultipleTimes_1056) {
    pd.addElement(4.0);
    pd.addElement(4.0);
    pd.addElement(4.0);
    EXPECT_EQ(pd.getCount(), 3);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 12.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 4.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 4.0);
}

// Test min is first element when it's the smallest
TEST_F(ProfileDataTest_1056, MinIsFirstElement_1056) {
    pd.addElement(1.0);
    pd.addElement(5.0);
    pd.addElement(10.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
}

// Test min is last element when it's the smallest
TEST_F(ProfileDataTest_1056, MinIsLastElement_1056) {
    pd.addElement(10.0);
    pd.addElement(5.0);
    pd.addElement(1.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
}

// Test max is first element when it's the largest
TEST_F(ProfileDataTest_1056, MaxIsFirstElement_1056) {
    pd.addElement(10.0);
    pd.addElement(5.0);
    pd.addElement(1.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 10.0);
}

// Test max is last element when it's the largest
TEST_F(ProfileDataTest_1056, MaxIsLastElement_1056) {
    pd.addElement(1.0);
    pd.addElement(5.0);
    pd.addElement(10.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 10.0);
}

// Test mixed positive and negative values
TEST_F(ProfileDataTest_1056, MixedPositiveNegativeValues_1056) {
    pd.addElement(-3.0);
    pd.addElement(5.0);
    pd.addElement(-1.0);
    pd.addElement(2.0);
    EXPECT_EQ(pd.getCount(), 4);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -3.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}
