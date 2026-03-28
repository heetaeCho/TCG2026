#include <gtest/gtest.h>
#include "ProfileData.h"

class ProfileDataTest_1055 : public ::testing::Test {
protected:
    ProfileData pd;
};

// Test default state - count should be 0
TEST_F(ProfileDataTest_1055, DefaultCount_1055) {
    EXPECT_EQ(pd.getCount(), 0);
}

// Test default state - total should be 0
TEST_F(ProfileDataTest_1055, DefaultTotal_1055) {
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
}

// Test default state - min should be 0
TEST_F(ProfileDataTest_1055, DefaultMin_1055) {
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
}

// Test default state - max should be 0
TEST_F(ProfileDataTest_1055, DefaultMax_1055) {
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding a single element
TEST_F(ProfileDataTest_1055, AddSingleElement_1055) {
    pd.addElement(5.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 5.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 5.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}

// Test adding two elements where second is larger
TEST_F(ProfileDataTest_1055, AddTwoElementsIncreasing_1055) {
    pd.addElement(3.0);
    pd.addElement(7.0);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 10.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 3.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 7.0);
}

// Test adding two elements where second is smaller
TEST_F(ProfileDataTest_1055, AddTwoElementsDecreasing_1055) {
    pd.addElement(7.0);
    pd.addElement(3.0);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 10.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 3.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 7.0);
}

// Test adding multiple elements
TEST_F(ProfileDataTest_1055, AddMultipleElements_1055) {
    pd.addElement(5.0);
    pd.addElement(1.0);
    pd.addElement(10.0);
    pd.addElement(3.0);
    EXPECT_EQ(pd.getCount(), 4);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 19.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 10.0);
}

// Test adding zero value
TEST_F(ProfileDataTest_1055, AddZeroValue_1055) {
    pd.addElement(0.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 0.0);
}

// Test adding negative values
TEST_F(ProfileDataTest_1055, AddNegativeValue_1055) {
    pd.addElement(-5.0);
    EXPECT_EQ(pd.getCount(), 1);
    EXPECT_DOUBLE_EQ(pd.getTotal(), -5.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -5.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), -5.0);
}

// Test adding mix of negative and positive values
TEST_F(ProfileDataTest_1055, AddMixedValues_1055) {
    pd.addElement(-3.0);
    pd.addElement(5.0);
    pd.addElement(-1.0);
    pd.addElement(2.0);
    EXPECT_EQ(pd.getCount(), 4);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 3.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), -3.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 5.0);
}

// Test adding identical elements
TEST_F(ProfileDataTest_1055, AddIdenticalElements_1055) {
    pd.addElement(4.0);
    pd.addElement(4.0);
    pd.addElement(4.0);
    EXPECT_EQ(pd.getCount(), 3);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 12.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 4.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 4.0);
}

// Test adding very small values
TEST_F(ProfileDataTest_1055, AddVerySmallValues_1055) {
    pd.addElement(1e-15);
    pd.addElement(1e-10);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e-15);
    EXPECT_DOUBLE_EQ(pd.getMax(), 1e-10);
}

// Test adding very large values
TEST_F(ProfileDataTest_1055, AddVeryLargeValues_1055) {
    pd.addElement(1e15);
    pd.addElement(1e10);
    EXPECT_EQ(pd.getCount(), 2);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1e10);
    EXPECT_DOUBLE_EQ(pd.getMax(), 1e15);
    EXPECT_DOUBLE_EQ(pd.getTotal(), 1e15 + 1e10);
}

// Test that min is updated correctly when new minimum appears later
TEST_F(ProfileDataTest_1055, MinUpdatedCorrectly_1055) {
    pd.addElement(10.0);
    pd.addElement(5.0);
    pd.addElement(1.0);
    EXPECT_DOUBLE_EQ(pd.getMin(), 1.0);
}

// Test that max is updated correctly when new maximum appears later
TEST_F(ProfileDataTest_1055, MaxUpdatedCorrectly_1055) {
    pd.addElement(1.0);
    pd.addElement(5.0);
    pd.addElement(10.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 10.0);
}

// Test count increments correctly with many additions
TEST_F(ProfileDataTest_1055, CountIncrementsCorrectly_1055) {
    for (int i = 0; i < 100; ++i) {
        pd.addElement(static_cast<double>(i));
    }
    EXPECT_EQ(pd.getCount(), 100);
    EXPECT_DOUBLE_EQ(pd.getMin(), 0.0);
    EXPECT_DOUBLE_EQ(pd.getMax(), 99.0);
    // Sum of 0..99 = 99*100/2 = 4950
    EXPECT_DOUBLE_EQ(pd.getTotal(), 4950.0);
}
