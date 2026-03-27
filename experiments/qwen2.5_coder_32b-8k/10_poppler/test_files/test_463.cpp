#include <gtest/gtest.h>

#include "GfxState.h"



class GfxICCBasedColorSpaceTest_463 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> alt;

    Ref iccProfileStream;

    std::unique_ptr<GfxICCBasedColorSpace> colorSpace;



    void SetUp() override {

        alt = nullptr;

        iccProfileStream.num = 0;

        iccProfileStream.gen = 0;

        colorSpace = std::make_unique<GfxICCBasedColorSpace>(1, std::move(alt), &iccProfileStream);

    }

};



TEST_F(GfxICCBasedColorSpaceTest_463, SetAndGetProfile_NormalOperation_463) {

    GfxLCMSProfilePtr profile;

    colorSpace->setProfile(profile);

    EXPECT_EQ(colorSpace->getProfile(), profile);

}



TEST_F(GfxICCBasedColorSpaceTest_463, GetProfile_DefaultValue_463) {

    GfxLCMSProfilePtr defaultProfile;

    EXPECT_EQ(colorSpace->getProfile(), defaultProfile);

}
