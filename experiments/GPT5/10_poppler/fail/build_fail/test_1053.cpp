#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ProfileData.h"

// Mock class to simulate external behavior (if needed)
class MockHandler {
public:
    MOCK_METHOD(void, onElementAdded, (double elapsed), ());
};

// Test class to verify ProfileData behavior
class ProfileDataTest_1053 : public ::testing::Test {
protected:
    ProfileData profileData;

    // Test the basic normal operation of getCount
    TEST_F(ProfileDataTest_1053, GetCount_1053) {
        EXPECT_EQ(profileData.getCount(), 0); // Initially, the count should be 0
    }

    // Test addElement to increase the count
    TEST_F(ProfileDataTest_1053, AddElement_IncreasesCount_1053) {
        profileData.addElement(10.0);  // Add an element
        EXPECT_EQ(profileData.getCount(), 1); // Count should be 1
    }

    // Test that getTotal works after adding an element
    TEST_F(ProfileDataTest_1053, GetTotal_AfterAddElement_1053) {
        profileData.addElement(10.0);
        EXPECT_EQ(profileData.getTotal(), 10.0); // Total should match added element
    }

    // Test that getMin returns the minimum value added
    TEST_F(ProfileDataTest_1053, GetMin_AfterAddElement_1053) {
        profileData.addElement(10.0);
        profileData.addElement(5.0);
        EXPECT_EQ(profileData.getMin(), 5.0); // Min should be the smallest value
    }

    // Test that getMax returns the maximum value added
    TEST_F(ProfileDataTest_1053, GetMax_AfterAddElement_1053) {
        profileData.addElement(10.0);
        profileData.addElement(20.0);
        EXPECT_EQ(profileData.getMax(), 20.0); // Max should be the largest value
    }

    // Test boundary condition: adding zero value
    TEST_F(ProfileDataTest_1053, AddElement_ZeroValue_1053) {
        profileData.addElement(0.0);
        EXPECT_EQ(profileData.getCount(), 1);  // Count should be 1
        EXPECT_EQ(profileData.getTotal(), 0.0); // Total should be 0
    }

    // Test exceptional case: ensure no errors when adding negative value
    TEST_F(ProfileDataTest_1053, AddElement_NegativeValue_1053) {
        profileData.addElement(-5.0);
        EXPECT_EQ(profileData.getCount(), 1);  // Count should still be 1
        EXPECT_EQ(profileData.getTotal(), -5.0); // Total should reflect the negative value
        EXPECT_EQ(profileData.getMin(), -5.0);   // Min should be -5
        EXPECT_EQ(profileData.getMax(), -5.0);   // Max should be -5
    }

    // Test exceptional case: adding multiple elements and verifying correct count and totals
    TEST_F(ProfileDataTest_1053, AddMultipleElements_1053) {
        profileData.addElement(10.0);
        profileData.addElement(15.0);
        profileData.addElement(20.0);
        
        EXPECT_EQ(profileData.getCount(), 3);  // Count should be 3
        EXPECT_EQ(profileData.getTotal(), 45.0); // Total should be sum of elements (10 + 15 + 20)
        EXPECT_EQ(profileData.getMin(), 10.0);  // Min should be the smallest value (10)
        EXPECT_EQ(profileData.getMax(), 20.0);  // Max should be the largest value (20)
    }

    // Test external interaction: mock handler on adding an element (if required)
    TEST_F(ProfileDataTest_1053, VerifyExternalInteraction_1053) {
        MockHandler mockHandler;
        EXPECT_CALL(mockHandler, onElementAdded(10.0)).Times(1);
        profileData.addElement(10.0);
    }
};

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}