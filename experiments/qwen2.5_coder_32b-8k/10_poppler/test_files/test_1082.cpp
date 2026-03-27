#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include <memory>



class OutputDevTest_1082 : public ::testing::Test {

protected:

    std::unique_ptr<OutputDev> output_dev;



    void SetUp() override {

        output_dev = std::make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1082, SetDefaultRGBProfile_NormalOperation_1082) {

    GfxLCMSProfilePtr test_profile = std::make_shared<GfxLCMSProfile>(); // Assuming GfxLCMSProfile is a valid type

    output_dev->setDefaultRGBProfile(test_profile);

    EXPECT_EQ(output_dev->getDefaultRGBProfile(), test_profile);

}



TEST_F(OutputDevTest_1082, SetDefaultRGBProfile_NullProfile_1082) {

    GfxLCMSProfilePtr null_profile = nullptr;

    output_dev->setDefaultRGBProfile(null_profile);

    EXPECT_EQ(output_dev->getDefaultRGBProfile(), null_profile);

}
