#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using namespace testing;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getRGB, (const GfxColor *color, GfxRGB *rgb), (override));

};



class GfxStateTest_579 : public Test {

protected:

    MockGfxColorSpace mockFillColorSpace;

    std::unique_ptr<GfxColorSpace> fillColorSpacePtr = std::make_unique<MockGfxColorSpace>(mockFillColorSpace);

    GfxState gfxState(300, 300, nullptr, 0, false);



    void SetUp() override {

        gfxState.setFillColorSpace(std::move(fillColorSpacePtr));

    }

};



TEST_F(GfxStateTest_579, GetFillRGB_NormalOperation_579) {

    GfxRGB expectedRgb = {1.0f, 0.5f, 0.25f};

    GfxRGB actualRgb;



    EXPECT_CALL(mockFillColorSpace, getRGB(_, _))

        .WillOnce(DoAll(SetArgReferee<1>(expectedRgb), Return()));



    gfxState.getFillRGB(&actualRgb);



    EXPECT_EQ(actualRgb, expectedRgb);

}



TEST_F(GfxStateTest_579, GetFillRGB_ZeroValues_579) {

    GfxRGB expectedRgb = {0.0f, 0.0f, 0.0f};

    GfxRGB actualRgb;



    EXPECT_CALL(mockFillColorSpace, getRGB(_, _))

        .WillOnce(DoAll(SetArgReferee<1>(expectedRgb), Return()));



    gfxState.getFillRGB(&actualRgb);



    EXPECT_EQ(actualRgb, expectedRgb);

}



TEST_F(GfxStateTest_579, GetFillRGB_MaxValues_579) {

    GfxRGB expectedRgb = {1.0f, 1.0f, 1.0f};

    GfxRGB actualRgb;



    EXPECT_CALL(mockFillColorSpace, getRGB(_, _))

        .WillOnce(DoAll(SetArgReferee<1>(expectedRgb), Return()));



    gfxState.getFillRGB(&actualRgb);



    EXPECT_EQ(actualRgb, expectedRgb);

}



TEST_F(GfxStateTest_579, GetFillRGB_MockInteraction_579) {

    GfxRGB expectedRgb = {0.3f, 0.6f, 0.9f};

    GfxRGB actualRgb;



    EXPECT_CALL(mockFillColorSpace, getRGB(_, _))

        .WillOnce(DoAll(SetArgReferee<1>(expectedRgb), Return()));



    gfxState.getFillRGB(&actualRgb);



    EXPECT_EQ(actualRgb, expectedRgb);

}
