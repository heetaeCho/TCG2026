#include <gtest/gtest.h>

#include "OutputDev.h"



class OutputDevTest_1080 : public ::testing::Test {

protected:

    OutputDev* outputDev;



    void SetUp() override {

        outputDev = new OutputDev();

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(OutputDevTest_1080, SetDefaultGrayProfile_NormalOperation_1080) {

    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();

    outputDev->setDefaultGrayProfile(profile);

    EXPECT_EQ(outputDev->getDefaultGrayProfile(), profile);

}



TEST_F(OutputDevTest_1080, SetDefaultGrayProfile_NullProfile_1080) {

    GfxLCMSProfilePtr nullProfile;

    outputDev->setDefaultGrayProfile(nullProfile);

    EXPECT_EQ(outputDev->getDefaultGrayProfile(), nullProfile);

}
