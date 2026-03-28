#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxPatternColorSpaceTest : public Test {

protected:

    std::unique_ptr<GfxColorSpace> underA;

    GfxPatternColorSpace* patternColorSpace;



    void SetUp() override {

        underA = std::make_unique<MockGfxColorSpace>();

        patternColorSpace = new GfxPatternColorSpace(std::move(underA));

    }



    void TearDown() override {

        delete patternColorSpace;

    }

};



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(int, getNComps, (), (const, override));

    MOCK_METHOD(GfxColorSpaceMode, getMode, (), (const, override));

    MOCK_METHOD(void, getGray, (const GfxColor*, GfxGray*), (const, override));

    MOCK_METHOD(void, getRGB, (const GfxColor*, GfxRGB*), (const, override));

    MOCK_METHOD(void, getCMYK, (const GfxColor*, GfxCMYK*), (const, override));

    MOCK_METHOD(void, getDeviceN, (const GfxColor*, GfxColor*), (const, override));

    MOCK_METHOD(void, getDefaultColor, (GfxColor*), (const, override));

    MOCK_METHOD(GfxColorSpace*, getUnder, (), (override));

};



TEST_F(GfxPatternColorSpaceTest, GetNComps_ReturnsZero_488) {

    EXPECT_EQ(patternColorSpace->getNComps(), 0);

}



TEST_F(GfxPatternColorSpaceTest, GetMode_ForwardsToUnderlying_488) {

    GfxColorSpaceMode expectedMode = DeviceGray;

    EXPECT_CALL(*underA, getMode()).WillOnce(Return(expectedMode));



    EXPECT_EQ(patternColorSpace->getMode(), expectedMode);

}



TEST_F(GfxPatternColorSpaceTest, GetGray_ForwardsToUnderlying_488) {

    const GfxColor* color = nullptr;

    GfxGray gray;



    EXPECT_CALL(*underA, getGray(color, &gray));



    patternColorSpace->getGray(color, &gray);

}



TEST_F(GfxPatternColorSpaceTest, GetRGB_ForwardsToUnderlying_488) {

    const GfxColor* color = nullptr;

    GfxRGB rgb;



    EXPECT_CALL(*underA, getRGB(color, &rgb));



    patternColorSpace->getRGB(color, &rgb);

}



TEST_F(GfxPatternColorSpaceTest, GetCMYK_ForwardsToUnderlying_488) {

    const GfxColor* color = nullptr;

    GfxCMYK cmyk;



    EXPECT_CALL(*underA, getCMYK(color, &cmyk));



    patternColorSpace->getCMYK(color, &cmyk);

}



TEST_F(GfxPatternColorSpaceTest, GetDeviceN_ForwardsToUnderlying_488) {

    const GfxColor* color = nullptr;

    GfxColor deviceN;



    EXPECT_CALL(*underA, getDeviceN(color, &deviceN));



    patternColorSpace->getDeviceN(color, &deviceN);

}



TEST_F(GfxPatternColorSpaceTest, GetDefaultColor_ForwardsToUnderlying_488) {

    GfxColor color;



    EXPECT_CALL(*underA, getDefaultColor(&color));



    patternColorSpace->getDefaultColor(&color);

}



TEST_F(GfxPatternColorSpaceTest, GetUnder_ReturnsUnderlyingPointer_488) {

    EXPECT_EQ(patternColorSpace->getUnder(), underA.get());

}
