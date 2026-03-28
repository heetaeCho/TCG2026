#include "gtest/gtest.h"
#include "ProfileData.h"

class ProfileDataTest_1054 : public ::testing::Test {
protected:
    ProfileData profileData;

    // This is the setup method for common test initialization
    void SetUp() override {
        // Any setup code can go here
    }
};

// Normal Operation Test - Testing the default total value
TEST_F(ProfileDataTest_1054, GetTotal_InitialValue_1054) {
    // Test the initial state of the 'total' variable
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 0.0);
}

// Boundary Test - Testing with a single element added
TEST_F(ProfileDataTest_1054, AddElement_SingleElement_1054) {
    profileData.addElement(10.0);  // Add a single element with value 10.0
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 10.0);  // Check if total is updated correctly
    EXPECT_EQ(profileData.getCount(), 1);  // Check if count is 1
}

// Boundary Test - Testing the minimum value of total
TEST_F(ProfileDataTest_1054, AddElement_MinValue_1054) {
    profileData.addElement(0.0);  // Add a zero value element
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 0.0);  // Check if total remains correct
    EXPECT_EQ(profileData.getCount(), 1);  // Verify count is 1 after one addition
}

// Boundary Test - Testing the total with large values
TEST_F(ProfileDataTest_1054, AddElement_LargeValue_1054) {
    profileData.addElement(1e6);  // Add a very large number
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 1e6);  // Check if total is updated correctly
    EXPECT_EQ(profileData.getCount(), 1);  // Ensure the count is correct
}

// Exceptional Case Test - Testing behavior when a negative value is added (if applicable in your logic)
TEST_F(ProfileDataTest_1054, AddElement_NegativeValue_1054) {
    profileData.addElement(-10.0);  // Adding a negative value should still work depending on class design
    EXPECT_DOUBLE_EQ(profileData.getTotal(), -10.0);  // Ensure total reflects the negative value
    EXPECT_EQ(profileData.getCount(), 1);  // Verify count is incremented
}

// Boundary Test - Testing behavior with large number of elements
TEST_F(ProfileDataTest_1054, AddElement_MultipleElements_1054) {
    for (int i = 1; i <= 1000; ++i) {
        profileData.addElement(i);  // Add elements from 1 to 1000
    }
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 500500);  // The sum of 1+2+3...+1000
    EXPECT_EQ(profileData.getCount(), 1000);  // Ensure the count is accurate
}

// Boundary Test - Testing the behavior when the maximum is set correctly
TEST_F(ProfileDataTest_1054, GetMax_ValueConsistency_1054) {
    profileData.addElement(50.0);  // Add an element of value 50
    EXPECT_DOUBLE_EQ(profileData.getMax(), 50.0);  // Check that max is updated
    profileData.addElement(75.0);  // Add another element
    EXPECT_DOUBLE_EQ(profileData.getMax(), 75.0);  // Ensure max is updated correctly
}

// Exceptional Case Test - Testing behavior when 'addElement' is never called
TEST_F(ProfileDataTest_1054, GetTotal_NoElements_1054) {
    EXPECT_DOUBLE_EQ(profileData.getTotal(), 0.0);  // Verify total is still 0 if no element is added
    EXPECT_EQ(profileData.getCount(), 0);  // Ensure count remains 0
}