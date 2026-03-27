#include <gtest/gtest.h>

#include "ProfileData.h"



class ProfileDataTest : public ::testing::Test {

protected:

    ProfileData* profileData;



    void SetUp() override {

        profileData = new ProfileData();

    }



    void TearDown() override {

        delete profileData;

    }

};



TEST_F(ProfileDataTest_1055, InitialMinValueIsZero_1055) {

    EXPECT_EQ(profileData->getMin(), 0.0);

}



TEST_F(ProfileDataTest_1055, AddElementUpdatesMinCorrectly_1055) {

    profileData->addElement(5.0);

    profileData->addElement(3.0);

    profileData->addElement(7.0);

    EXPECT_EQ(profileData->getMin(), 3.0);

}



TEST_F(ProfileDataTest_1055, AddSingleElementUpdatesMinCorrectly_1055) {

    profileData->addElement(42.0);

    EXPECT_EQ(profileData->getMin(), 42.0);

}



TEST_F(ProfileDataTest_1055, MinValueDoesNotChangeWithLargerElements_1055) {

    profileData->addElement(1.0);

    profileData->addElement(2.0);

    profileData->addElement(3.0);

    EXPECT_EQ(profileData->getMin(), 1.0);

}



TEST_F(ProfileDataTest_1055, MinValueUpdatesWithNegativeElements_1055) {

    profileData->addElement(-10.0);

    profileData->addElement(-20.0);

    profileData->addElement(-5.0);

    EXPECT_EQ(profileData->getMin(), -20.0);

}



TEST_F(ProfileDataTest_1055, MinValueResetsAfterAddingSmallerElement_1055) {

    profileData->addElement(10.0);

    profileData->addElement(20.0);

    profileData->addElement(5.0);

    EXPECT_EQ(profileData->getMin(), 5.0);

}
