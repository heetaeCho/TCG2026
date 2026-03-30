#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"

#include "./TestProjects/poppler/poppler/GfxState.h"



using namespace ::testing;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getGray, (const GfxColor *color, GfxGray *gray), (const, override));

    MOCK_METHOD(void, getRGB, (const GfxColor *color, GfxRGB *rgb), (const, override));

    MOCK_METHOD(void, getCMYK, (const GfxColor *color, GfxCMYK *cmyk), (const, override));

    MOCK_METHOD(void, getDeviceN, (const GfxColor *color, GfxColor *deviceN), (const, override));

};



void convertGfxShortColor(SplashColorPtr dest, const SplashColorMode colorMode, const GfxColorSpace *colorSpace, const GfxColor *src);



class ConvertGfxShortColorTest_1575 : public ::testing::Test {

protected:

    MockGfxColorSpace mockColorSpace;

    GfxColor srcColor;

    GfxRGB rgbColor;

    GfxCMYK cmykColor;

    GfxGray grayColor;

    GfxColor deviceNColor;

};



TEST_F(ConvertGfxShortColorTest_1575, Mono1_NormalOperation_1575) {

    unsigned char dest[1];

    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce(DoAll(SetArgReferee<1>(0.5), Return()));



    convertGfxShortColor(dest, splashModeMono1, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[0], 128);

}



TEST_F(ConvertGfxShortColorTest_1575, Mono8_NormalOperation_1575) {

    unsigned char dest[1];

    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce(DoAll(SetArgReferee<1>(0.5), Return()));



    convertGfxShortColor(dest, splashModeMono8, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[0], 128);

}



TEST_F(ConvertGfxShortColorTest_1575, RGB8_NormalOperation_1575) {

    unsigned char dest[3];

    rgbColor.r = 0.5;

    rgbColor.g = 0.6;

    rgbColor.b = 0.7;

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce(DoAll(SetArgReferee<1>(rgbColor), Return()));



    convertGfxShortColor(dest, splashModeRGB8, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[0], 128);

    ASSERT_EQ(dest[1], 153);

    ASSERT_EQ(dest[2], 179);

}



TEST_F(ConvertGfxShortColorTest_1575, BGR8_NormalOperation_1575) {

    unsigned char dest[3];

    rgbColor.r = 0.5;

    rgbColor.g = 0.6;

    rgbColor.b = 0.7;

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce(DoAll(SetArgReferee<1>(rgbColor), Return()));



    convertGfxShortColor(dest, splashModeBGR8, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[2], 128);

    ASSERT_EQ(dest[1], 153);

    ASSERT_EQ(dest[0], 179);

}



TEST_F(ConvertGfxShortColorTest_1575, XBGR8_NormalOperation_1575) {

    unsigned char dest[4];

    rgbColor.r = 0.5;

    rgbColor.g = 0.6;

    rgbColor.b = 0.7;

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce(DoAll(SetArgReferee<1>(rgbColor), Return()));



    convertGfxShortColor(dest, splashModeXBGR8, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[2], 128);

    ASSERT_EQ(dest[1], 153);

    ASSERT_EQ(dest[0], 179);

    ASSERT_EQ(dest[3], 255);

}



TEST_F(ConvertGfxShortColorTest_1575, CMYK8_NormalOperation_1575) {

    unsigned char dest[4];

    cmykColor.c = 0.5;

    cmykColor.m = 0.6;

    cmykColor.y = 0.7;

    cmykColor.k = 0.8;

    EXPECT_CALL(mockColorSpace, getCMYK(_, _)).WillOnce(DoAll(SetArgReferee<1>(cmykColor), Return()));



    convertGfxShortColor(dest, splashModeCMYK8, &mockColorSpace, &srcColor);

    ASSERT_EQ(dest[0], 128);

    ASSERT_EQ(dest[1], 153);

    ASSERT_EQ(dest[2], 179);

    ASSERT_EQ(dest[3], 204);

}



TEST_F(ConvertGfxShortColorTest_1575, DeviceN8_NormalOperation_1575) {

    unsigned char dest[SPOT_NCOMPS + 4];

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        deviceNColor.c[i] = static_cast<GfxColorComp>(i * 0.1);

    }

    EXPECT_CALL(mockColorSpace, getDeviceN(_, _)).WillOnce(DoAll(SetArrayArgument<1>(&deviceNColor.c[0], &deviceNColor.c[SPOT_NCOMPS + 4]), Return()));



    convertGfxShortColor(dest, splashModeDeviceN8, &mockColorSpace, &srcColor);

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        ASSERT_EQ(dest[i], static_cast<unsigned char>(i * 25.5));

    }

}
