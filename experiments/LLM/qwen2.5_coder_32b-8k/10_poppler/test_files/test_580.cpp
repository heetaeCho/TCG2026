#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxState.h"

#include "TestProjects/poppler/poppler/GfxColorSpace.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Eq;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_CONST_METHOD2(getRGB, void(const GfxColor *, GfxRGB *));

};



class GfxStateTest_580 : public ::testing::Test {

protected:

    std::unique_ptr<MockGfxColorSpace> mockStrokeColorSpace;

    std::unique_ptr<GfxState> gfxState;



    GfxStateTest_580() {

        mockStrokeColorSpace = std::make_unique<MockGfxColorSpace>();

        gfxState = std::make_unique<GfxState>(100, 100, nullptr, 0, false);

        gfxState->setStrokeColorSpace(std::move(mockStrokeColorSpace));

    }

};



TEST_F(GfxStateTest_580, GetStrokeRGB_NormalOperation_580) {

    GfxRGB expectedRgb = {0.5, 0.5, 0.5};

    EXPECT_CALL(*mockStrokeColorSpace, getRGB(_, _))

        .WillOnce([](const GfxColor *, GfxRGB *rgb){

            *rgb = {0.5, 0.5, 0.5};

        });



    GfxRGB rgb;

    gfxState->getStrokeRGB(&rgb);

    EXPECT_EQ(rgb, expectedRgb);

}



TEST_F(GfxStateTest_580, GetStrokeRGB_BoundaryConditions_580) {

    GfxRGB expectedRgb = {0.0, 0.0, 0.0};

    EXPECT_CALL(*mockStrokeColorSpace, getRGB(_, _))

        .WillOnce([](const GfxColor *, GfxRGB *rgb){

            *rgb = {0.0, 0.0, 0.0};

        });



    GfxRGB rgb;

    gfxState->getStrokeRGB(&rgb);

    EXPECT_EQ(rgb, expectedRgb);



    expectedRgb = {1.0, 1.0, 1.0};

    EXPECT_CALL(*mockStrokeColorSpace, getRGB(_, _))

        .WillOnce([](const GfxColor *, GfxRGB *rgb){

            *rgb = {1.0, 1.0, 1.0};

        });



    gfxState->getStrokeRGB(&rgb);

    EXPECT_EQ(rgb, expectedRgb);

}
