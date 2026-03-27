#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/SplashOutputDev.cc"

#include "./TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getGray, (const GfxColor* color, GfxGray* gray), (const, override));

    MOCK_METHOD(void, getRGB, (const GfxColor* color, GfxRGB* rgb), (const, override));

    MOCK_METHOD(void, getCMYK, (const GfxColor* color, GfxCMYK* cmyk), (const, override));

    MOCK_METHOD(void, getDeviceN, (const GfxColor* color, GfxColor* deviceN), (const, override));

};



class ConvertGfxColorTest : public Test {

protected:

    MockGfxColorSpace mockColorSpace;

    SplashColor destColor;

    GfxColor srcColor;

};



TEST_F(ConvertGfxColorTest, Mono1_NormalOperation_1574) {

    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce([](const GfxColor*, GfxGray* gray){ *gray = 0.5; });



    convertGfxColor(&destColor, splashModeMono1, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

}



TEST_F(ConvertGfxColorTest, Mono8_NormalOperation_1574) {

    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce([](const GfxColor*, GfxGray* gray){ *gray = 0.5; });



    convertGfxColor(&destColor, splashModeMono8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

}



TEST_F(ConvertGfxColorTest, RGB8_NormalOperation_1574) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce([&rgb](const GfxColor*, GfxRGB* output){ *output = rgb; });



    convertGfxColor(&destColor, splashModeRGB8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

    EXPECT_EQ(destColor[1], 128);

    EXPECT_EQ(destColor[2], 128);

}



TEST_F(ConvertGfxColorTest, BGR8_NormalOperation_1574) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce([&rgb](const GfxColor*, GfxRGB* output){ *output = rgb; });



    convertGfxColor(&destColor, splashModeBGR8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

    EXPECT_EQ(destColor[1], 128);

    EXPECT_EQ(destColor[2], 128);

}



TEST_F(ConvertGfxColorTest, XBGR8_NormalOperation_1574) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce([&rgb](const GfxColor*, GfxRGB* output){ *output = rgb; });



    convertGfxColor(&destColor, splashModeXBGR8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

    EXPECT_EQ(destColor[1], 128);

    EXPECT_EQ(destColor[2], 128);

    EXPECT_EQ(destColor[3], 255);

}



TEST_F(ConvertGfxColorTest, CMYK8_NormalOperation_1574) {

    GfxCMYK cmyk = {0.5, 0.5, 0.5, 0.5};

    EXPECT_CALL(mockColorSpace, getCMYK(_, _)).WillOnce([&cmyk](const GfxColor*, GfxCMYK* output){ *output = cmyk; });



    convertGfxColor(&destColor, splashModeCMYK8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 128);

    EXPECT_EQ(destColor[1], 128);

    EXPECT_EQ(destColor[2], 128);

    EXPECT_EQ(destColor[3], 128);

}



TEST_F(ConvertGfxColorTest, DeviceN8_NormalOperation_1574) {

    GfxColor deviceN;

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        deviceN.c[i] = 0.5;

    }

    EXPECT_CALL(mockColorSpace, getDeviceN(_, _)).WillOnce([&deviceN](const GfxColor*, GfxColor* output){ *output = deviceN; });



    convertGfxColor(&destColor, splashModeDeviceN8, &mockColorSpace, &srcColor);

    

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        EXPECT_EQ(destColor[i], 128);

    }

}



TEST_F(ConvertGfxColorTest, Mono8_BoundaryCondition_1574) {

    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce([](const GfxColor*, GfxGray* gray){ *gray = 0.0; });



    convertGfxColor(&destColor, splashModeMono8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 0);



    EXPECT_CALL(mockColorSpace, getGray(_, _)).WillOnce([](const GfxColor*, GfxGray* gray){ *gray = 1.0; });



    convertGfxColor(&destColor, splashModeMono8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 255);

}



TEST_F(ConvertGfxColorTest, RGB8_BoundaryCondition_1574) {

    GfxRGB rgb = {0.0, 0.0, 0.0};

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce([&rgb](const GfxColor*, GfxRGB* output){ *output = rgb; });



    convertGfxColor(&destColor, splashModeRGB8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 0);

    EXPECT_EQ(destColor[1], 0);

    EXPECT_EQ(destColor[2], 0);



    rgb = {1.0, 1.0, 1.0};

    EXPECT_CALL(mockColorSpace, getRGB(_, _)).WillOnce([&rgb](const GfxColor*, GfxRGB* output){ *output = rgb; });



    convertGfxColor(&destColor, splashModeRGB8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 255);

    EXPECT_EQ(destColor[1], 255);

    EXPECT_EQ(destColor[2], 255);

}



TEST_F(ConvertGfxColorTest, CMYK8_BoundaryCondition_1574) {

    GfxCMYK cmyk = {0.0, 0.0, 0.0, 0.0};

    EXPECT_CALL(mockColorSpace, getCMYK(_, _)).WillOnce([&cmyk](const GfxColor*, GfxCMYK* output){ *output = cmyk; });



    convertGfxColor(&destColor, splashModeCMYK8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 0);

    EXPECT_EQ(destColor[1], 0);

    EXPECT_EQ(destColor[2], 0);

    EXPECT_EQ(destColor[3], 0);



    cmyk = {1.0, 1.0, 1.0, 1.0};

    EXPECT_CALL(mockColorSpace, getCMYK(_, _)).WillOnce([&cmyk](const GfxColor*, GfxCMYK* output){ *output = cmyk; });



    convertGfxColor(&destColor, splashModeCMYK8, &mockColorSpace, &srcColor);

    

    EXPECT_EQ(destColor[0], 255);

    EXPECT_EQ(destColor[1], 255);

    EXPECT_EQ(destColor[2], 255);

    EXPECT_EQ(destColor[3], 255);

}



TEST_F(ConvertGfxColorTest, DeviceN8_BoundaryCondition_1574) {

    GfxColor deviceN;

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        deviceN.c[i] = 0.0;

    }

    EXPECT_CALL(mockColorSpace, getDeviceN(_, _)).WillOnce([&deviceN](const GfxColor*, GfxColor* output){ *output = deviceN; });



    convertGfxColor(&destColor, splashModeDeviceN8, &mockColorSpace, &srcColor);

    

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        EXPECT_EQ(destColor[i], 0);

    }



    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        deviceN.c[i] = 1.0;

    }

    EXPECT_CALL(mockColorSpace, getDeviceN(_, _)).WillOnce([&deviceN](const GfxColor*, GfxColor* output){ *output = deviceN; });



    convertGfxColor(&destColor, splashModeDeviceN8, &mockColorSpace, &srcColor);

    

    for (int i = 0; i < SPOT_NCOMPS + 4; ++i) {

        EXPECT_EQ(destColor[i], 255);

    }

}
