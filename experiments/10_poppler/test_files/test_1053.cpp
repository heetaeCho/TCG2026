#include <gtest/gtest.h>

#include "ProfileData.h"



class ProfileDataTest_1053 : public ::testing::Test {

protected:

    ProfileData profile_data;

};



TEST_F(ProfileDataTest_1053, InitialCountIsZero_1053) {

    EXPECT_EQ(profile_data.getCount(), 0);

}



TEST_F(ProfileDataTest_1053, AddElementIncreasesCount_1053) {

    profile_data.addElement(1.0);

    EXPECT_EQ(profile_data.getCount(), 1);

}



TEST_F(ProfileDataTest_1053, MultipleAddElementsIncreaseCount_1053) {

    profile_data.addElement(1.0);

    profile_data.addElement(2.0);

    profile_data.addElement(3.0);

    EXPECT_EQ(profile_data.getCount(), 3);

}



TEST_F(ProfileDataTest_1053, AddElementUpdatesTotal_1053) {

    profile_data.addElement(1.0);

    profile_data.addElement(2.0);

    EXPECT_DOUBLE_EQ(profile_data.getTotal(), 3.0);

}



TEST_F(ProfileDataTest_1053, AddElementUpdatesMin_1053) {

    profile_data.addElement(5.0);

    profile_data.addElement(3.0);

    profile_data.addElement(7.0);

    EXPECT_DOUBLE_EQ(profile_data.getMin(), 3.0);

}



TEST_F(ProfileDataTest_1053, AddElementUpdatesMax_1053) {

    profile_data.addElement(2.0);

    profile_data.addElement(4.0);

    profile_data.addElement(1.0);

    EXPECT_DOUBLE_EQ(profile_data.getMax(), 4.0);

}



TEST_F(ProfileDataTest_1053, AddSingleElementSetsMinAndMaxToThatValue_1053) {

    profile_data.addElement(42.0);

    EXPECT_DOUBLE_EQ(profile_data.getMin(), 42.0);

    EXPECT_DOUBLE_EQ(profile_data.getMax(), 42.0);

}



TEST_F(ProfileDataTest_1053, BoundaryConditionWithZeroElement_1053) {

    EXPECT_EQ(profile_data.getCount(), 0);

    EXPECT_DOUBLE_EQ(profile_data.getTotal(), 0.0);

    // Assuming getMin() and getMax() return reasonable defaults when no elements are added

    // Here we assume they might throw or return 0, but since not specified, we check for 0

    EXPECT_DOUBLE_EQ(profile_data.getMin(), 0.0);

    EXPECT_DOUBLE_EQ(profile_data.getMax(), 0.0);

}



TEST_F(ProfileDataTest_1053, BoundaryConditionWithNegativeElements_1053) {

    profile_data.addElement(-1.0);

    profile_data.addElement(-2.0);

    profile_data.addElement(-3.0);

    EXPECT_EQ(profile_data.getCount(), 3);

    EXPECT_DOUBLE_EQ(profile_data.getTotal(), -6.0);

    EXPECT_DOUBLE_EQ(profile_data.getMin(), -3.0);

    EXPECT_DOUBLE_EQ(profile_data.getMax(), -1.0);

}
