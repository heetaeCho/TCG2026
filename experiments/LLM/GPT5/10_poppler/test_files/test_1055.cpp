#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ProfileData.h"

// Test Fixture for ProfileData
class ProfileDataTest_1055 : public ::testing::Test {
protected:
    ProfileData profileData;
};

// Normal Operation Test Case - Testing getMin() behavior
TEST_F(ProfileDataTest_1055, GetMin_1055) {
    // Test if getMin returns the correct default value (which is 0)
    EXPECT_EQ(profileData.getMin(), 0.0);
}

// Boundary Condition Test Case - Testing behavior after adding an element
TEST_F(ProfileDataTest_1055, GetMin_AfterAddingElement_1055) {
    // Simulate adding an element (min value should now be that element)
    profileData.addElement(5.0);

    // Test if getMin reflects the updated value
    EXPECT_EQ(profileData.getMin(), 5.0);
}

// Boundary Condition Test Case - Testing behavior after adding multiple elements
TEST_F(ProfileDataTest_1055, GetMin_AfterMultipleElements_1055) {
    // Simulate adding multiple elements
    profileData.addElement(10.0);
    profileData.addElement(5.0);
    profileData.addElement(15.0);

    // Test if getMin reflects the minimum value (which is 5)
    EXPECT_EQ(profileData.getMin(), 5.0);
}

// Exceptional/Error Case - Assuming the min value should remain 0 if no elements are added
TEST_F(ProfileDataTest_1055, GetMin_NoElementsAdded_1055) {
    // Test if getMin correctly returns 0 when no elements are added
    EXPECT_EQ(profileData.getMin(), 0.0);
}