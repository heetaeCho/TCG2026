#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include <memory>



using namespace std;



class OutputDevTest : public ::testing::Test {

protected:

    unique_ptr<OutputDev> outputDev;

    

    void SetUp() override {

        outputDev = make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1081, DefaultGrayProfileInitiallyNull_1081) {

    EXPECT_EQ(outputDev->getDefaultGrayProfile(), nullptr);

}



TEST_F(OutputDevTest_1081, SetAndGetDefaultGrayProfile_1081) {

    GfxLCMSProfilePtr profile = make_shared<GfxLCMSProfile>();

    outputDev->setDefaultGrayProfile(profile);

    EXPECT_EQ(outputDev->getDefaultGrayProfile(), profile);

}
