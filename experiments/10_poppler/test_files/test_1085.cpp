#include <gtest/gtest.h>

#include "OutputDev.h"



class OutputDevTest_1085 : public ::testing::Test {

protected:

    std::unique_ptr<OutputDev> output_dev;



    void SetUp() override {

        output_dev = std::make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1085, GetDefaultCMYKProfile_DefaultState_1085) {

    GfxLCMSProfilePtr profile = output_dev->getDefaultCMYKProfile();

    EXPECT_EQ(profile, nullptr); // Assuming default state returns nullptr

}



TEST_F(OutputDevTest_1085, SetAndGetDefaultCMYKProfile_1085) {

    auto mock_profile = std::make_shared<GfxLCMSProfile>();

    output_dev->setDefaultCMYKProfile(mock_profile);

    GfxLCMSProfilePtr profile = output_dev->getDefaultCMYKProfile();

    EXPECT_EQ(profile, mock_profile);

}



TEST_F(OutputDevTest_1085, GetDefaultCMYKProfile_AfterNullSet_1085) {

    auto null_profile = nullptr;

    output_dev->setDefaultCMYKProfile(null_profile);

    GfxLCMSProfilePtr profile = output_dev->getDefaultCMYKProfile();

    EXPECT_EQ(profile, nullptr);

}



// Additional tests for other functions if needed



```


