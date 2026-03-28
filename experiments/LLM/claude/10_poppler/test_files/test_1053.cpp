#include <gtest/gtest.h>
#include "ProfileData.h"

class ProfileDataTest_1053 : public ::testing::Test {
protected:
    ProfileData profileData;
};

// Test initial state - count should be 0
TEST_F(ProfileDataTest_1053, InitialCountIsZero_1053) {
    EXPECT_EQ(profileData.getCount(), 0);
}

// Test initial state - total should be 0
TEST_F(ProfileDataTest_1053, InitialTotalIsZero_1053) {
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 0.0);
}

// Test initial state - min should be 0
TEST_F(ProfileDataTest_1053, InitialMinIsZero_1053) {
    EXPECT_DOUBLE_EQ(profileData.getMin(), 0.0);
}

// Test initial state - max should be 0
TEST_F(ProfileDataTest_1053, InitialMaxIsZero_1053) {
    EXPECT_DOUBLE_EQ(profileData.getMax(), 0.0);
}

// Test adding a single element updates count
TEST_F(ProfileDataTest_1053, AddOneElementCountIsOne_1053) {
    profileData.addElement(5.0);
    EXPECT_EQ(profileData.getCount(), 1);
}

// Test adding a single element updates total
TEST_F(ProfileDataTest_1053, AddOneElementTotalIsCorrect_1053) {
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 5.0);
}

// Test adding a single element sets min correctly
TEST_F(ProfileDataTest_1053, AddOneElementMinIsCorrect_1053) {
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 5.0);
}

// Test adding a single element sets max correctly
TEST_F(ProfileDataTest_1053, AddOneElementMaxIsCorrect_1053) {
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 5.0);
}

// Test adding multiple elements updates count correctly
TEST_F(ProfileDataTest_1053, AddMultipleElementsCountIsCorrect_1053) {
    profileData.addElement(1.0);
    profileData.addElement(2.0);
    profileData.addElement(3.0);
    EXPECT_EQ(profileData.getCount(), 3);
}

// Test adding multiple elements updates total correctly
TEST_F(ProfileDataTest_1053, AddMultipleElementsTotalIsCorrect_1053) {
    profileData.addElement(1.0);
    profileData.addElement(2.0);
    profileData.addElement(3.0);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 6.0);
}

// Test min is tracked correctly with multiple elements
TEST_F(ProfileDataTest_1053, AddMultipleElementsMinIsCorrect_1053) {
    profileData.addElement(3.0);
    profileData.addElement(1.0);
    profileData.addElement(2.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 1.0);
}

// Test max is tracked correctly with multiple elements
TEST_F(ProfileDataTest_1053, AddMultipleElementsMaxIsCorrect_1053) {
    profileData.addElement(1.0);
    profileData.addElement(3.0);
    profileData.addElement(2.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 3.0);
}

// Test adding zero value
TEST_F(ProfileDataTest_1053, AddZeroElement_1053) {
    profileData.addElement(0.0);
    EXPECT_EQ(profileData.getCount(), 1);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 0.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 0.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 0.0);
}

// Test adding negative values
TEST_F(ProfileDataTest_1053, AddNegativeElement_1053) {
    profileData.addElement(-5.0);
    EXPECT_EQ(profileData.getCount(), 1);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), -5.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), -5.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), -5.0);
}

// Test min/max with negative and positive values
TEST_F(ProfileDataTest_1053, MinMaxWithMixedValues_1053) {
    profileData.addElement(-10.0);
    profileData.addElement(20.0);
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), -10.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 20.0);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 15.0);
}

// Test adding very small values
TEST_F(ProfileDataTest_1053, AddVerySmallElement_1053) {
    profileData.addElement(1e-15);
    EXPECT_EQ(profileData.getCount(), 1);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 1e-15);
}

// Test adding very large values
TEST_F(ProfileDataTest_1053, AddVeryLargeElement_1053) {
    profileData.addElement(1e15);
    EXPECT_EQ(profileData.getCount(), 1);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 1e15);
}

// Test that min stays the same when larger elements are added
TEST_F(ProfileDataTest_1053, MinDoesNotChangeWithLargerValues_1053) {
    profileData.addElement(1.0);
    profileData.addElement(5.0);
    profileData.addElement(10.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 1.0);
}

// Test that max stays the same when smaller elements are added
TEST_F(ProfileDataTest_1053, MaxDoesNotChangeWithSmallerValues_1053) {
    profileData.addElement(10.0);
    profileData.addElement(5.0);
    profileData.addElement(1.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 10.0);
}

// Test adding identical elements
TEST_F(ProfileDataTest_1053, AddIdenticalElements_1053) {
    profileData.addElement(4.0);
    profileData.addElement(4.0);
    profileData.addElement(4.0);
    EXPECT_EQ(profileData.getCount(), 3);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 12.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 4.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 4.0);
}

// Test adding many elements
TEST_F(ProfileDataTest_1053, AddManyElements_1053) {
    double expectedTotal = 0.0;
    for (int i = 1; i <= 100; ++i) {
        profileData.addElement(static_cast<double>(i));
        expectedTotal += static_cast<double>(i);
    }
    EXPECT_EQ(profileData.getCount(), 100);
    EXPECT_DOUBLE_EQ(profileData.getTotal(), expectedTotal);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 1.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 100.0);
}

// Test min updates when a new minimum is added later
TEST_F(ProfileDataTest_1053, MinUpdatesWhenNewMinAdded_1053) {
    profileData.addElement(10.0);
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 5.0);
    profileData.addElement(2.0);
    EXPECT_DOUBLE_EQ(profileData.getMin(), 2.0);
}

// Test max updates when a new maximum is added later
TEST_F(ProfileDataTest_1053, MaxUpdatesWhenNewMaxAdded_1053) {
    profileData.addElement(1.0);
    profileData.addElement(5.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 5.0);
    profileData.addElement(10.0);
    EXPECT_DOUBLE_EQ(profileData.getMax(), 10.0);
}
