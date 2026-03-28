#include <gtest/gtest.h>

#include "ProfileData.h"



class ProfileDataTest_1056 : public ::testing::Test {

protected:

    ProfileData profileData;

};



TEST_F(ProfileDataTest_1056, InitialMaxIsZero_1056) {

    EXPECT_EQ(profileData.getMax(), 0.0);

}



TEST_F(ProfileDataTest_1056, AddElementUpdatesMax_1056) {

    profileData.addElement(5.0);

    EXPECT_EQ(profileData.getMax(), 5.0);



    profileData.addElement(10.0);

    EXPECT_EQ(profileData.getMax(), 10.0);



    profileData.addElement(7.5);

    EXPECT_EQ(profileData.getMax(), 10.0);

}



TEST_F(ProfileDataTest_1056, AddNegativeElementUpdatesMax_1056) {

    profileData.addElement(-3.0);

    profileData.addElement(-10.0);

    profileData.addElement(-5.0);

    EXPECT_EQ(profileData.getMax(), -3.0);

}



TEST_F(ProfileDataTest_1056, AddMultipleElementsUpdatesMax_1056) {

    profileData.addElement(2.0);

    profileData.addElement(4.0);

    profileData.addElement(1.0);

    profileData.addElement(3.0);

    EXPECT_EQ(profileData.getMax(), 4.0);

}



TEST_F(ProfileDataTest_1056, AddElementDoesNotUpdateMaxIfSmaller_1056) {

    profileData.addElement(20.0);

    profileData.addElement(10.0);

    profileData.addElement(15.0);

    EXPECT_EQ(profileData.getMax(), 20.0);

}
