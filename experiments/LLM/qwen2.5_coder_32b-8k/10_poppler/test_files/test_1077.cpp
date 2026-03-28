#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "OutputDev.h"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, dummy, (), (override));

};



TEST_F(OutputDevTest_1077, GetVectorAntialias_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_FALSE(outputDev.getVectorAntialias());

}



TEST_F(OutputDevTest_1077, SetAndGetVectorAntialias_Toggle_1077) {

    OutputDev outputDev;



    outputDev.setVectorAntialias(true);

    EXPECT_TRUE(outputDev.getVectorAntialias());



    outputDev.setVectorAntialias(false);

    EXPECT_FALSE(outputDev.getVectorAntialias());

}



TEST_F(OutputDevTest_1077, GetDisplayProfile_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_EQ(nullptr, outputDev.getDisplayProfile().get());

}



TEST_F(OutputDevTest_1077, SetAndGetDisplayProfile_1077) {

    OutputDev outputDev;

    auto mockProfile = std::make_shared<GfxLCMSProfile>();



    outputDev.setDisplayProfile(mockProfile);

    EXPECT_EQ(mockProfile, outputDev.getDisplayProfile());

}



TEST_F(OutputDevTest_1077, GetDefaultGrayProfile_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_EQ(nullptr, outputDev.getDefaultGrayProfile().get());

}



TEST_F(OutputDevTest_1077, SetAndGetDefaultGrayProfile_1077) {

    OutputDev outputDev;

    auto mockProfile = std::make_shared<GfxLCMSProfile>();



    outputDev.setDefaultGrayProfile(mockProfile);

    EXPECT_EQ(mockProfile, outputDev.getDefaultGrayProfile());

}



TEST_F(OutputDevTest_1077, GetDefaultRGBProfile_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_EQ(nullptr, outputDev.getDefaultRGBProfile().get());

}



TEST_F(OutputDevTest_1077, SetAndGetDefaultRGBProfile_1077) {

    OutputDev outputDev;

    auto mockProfile = std::make_shared<GfxLCMSProfile>();



    outputDev.setDefaultRGBProfile(mockProfile);

    EXPECT_EQ(mockProfile, outputDev.getDefaultRGBProfile());

}



TEST_F(OutputDevTest_1077, GetDefaultCMYKProfile_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_EQ(nullptr, outputDev.getDefaultCMYKProfile().get());

}



TEST_F(OutputDevTest_1077, SetAndGetDefaultCMYKProfile_1077) {

    OutputDev outputDev;

    auto mockProfile = std::make_shared<GfxLCMSProfile>();



    outputDev.setDefaultCMYKProfile(mockProfile);

    EXPECT_EQ(mockProfile, outputDev.getDefaultCMYKProfile());

}



TEST_F(OutputDevTest_1077, GetIccColorSpaceCache_DefaultValue_1077) {

    OutputDev outputDev;

    EXPECT_NE(nullptr, outputDev.getIccColorSpaceCache());

}
