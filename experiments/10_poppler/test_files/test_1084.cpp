#include <gtest/gtest.h>

#include "OutputDev.h"

#include "GfxLCMSProfilePtr.h"



class OutputDevTest_1084 : public ::testing::Test {

protected:

    OutputDev* outputDev;



    void SetUp() override {

        outputDev = new OutputDev();

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(OutputDevTest_1084, SetDefaultCMYKProfile_NormalOperation_1084) {

    GfxLCMSProfilePtr profile(new MockGfxLCMSProfile());

    outputDev->setDefaultCMYKProfile(profile);

    EXPECT_EQ(outputDev->getDefaultCMYKProfile(), profile);

}



TEST_F(OutputDevTest_1084, SetDefaultCMYKProfile_NullProfile_1084) {

    GfxLCMSProfilePtr nullProfile;

    outputDev->setDefaultCMYKProfile(nullProfile);

    EXPECT_EQ(outputDev->getDefaultCMYKProfile(), nullProfile);

}
