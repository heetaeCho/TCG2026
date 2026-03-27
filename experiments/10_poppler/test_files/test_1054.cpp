#include <gtest/gtest.h>

#include "ProfileData.h"



class ProfileDataTest : public ::testing::Test {

protected:

    ProfileData profileData;

};



TEST_F(ProfileDataTest_1054, InitialTotalIsZero_1054) {

    EXPECT_EQ(profileData.getTotal(), 0.0);

}



TEST_F(ProfileDataTest_1054, AddElementIncreasesTotal_1054) {

    profileData.addElement(10.0);

    EXPECT_EQ(profileData.getTotal(), 10.0);



    profileData.addElement(20.0);

    EXPECT_EQ(profileData.getTotal(), 30.0);

}



TEST_F(ProfileDataTest_1054, AddElementUpdatesCount_1054) {

    profileData.addElement(5.0);

    EXPECT_EQ(profileData.getCount(), 1);



    profileData.addElement(15.0);

    EXPECT_EQ(profileData.getCount(), 2);

}



TEST_F(ProfileDataTest_1054, AddMultipleElementsCalculatesMin_1054) {

    profileData.addElement(30.0);

    profileData.addElement(10.0);

    profileData.addElement(20.0);



    EXPECT_EQ(profileData.getMin(), 10.0);

}



TEST_F(ProfileDataTest_1054, AddMultipleElementsCalculatesMax_1054) {

    profileData.addElement(30.0);

    profileData.addElement(10.0);

    profileData.addElement(20.0);



    EXPECT_EQ(profileData.getMax(), 30.0);

}



TEST_F(ProfileDataTest_1054, AddSingleElementMinEqualsMax_1054) {

    profileData.addElement(25.0);



    EXPECT_EQ(profileData.getMin(), 25.0);

    EXPECT_EQ(profileData.getMax(), 25.0);

}
