#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getRGB, (const GfxColor* color, GfxRGB* rgb), (override));

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    MockGfxImageColorMap(int bitsA, Object* decode, std::unique_ptr<GfxColorSpace>&& colorSpaceA)

        : GfxImageColorMap(bitsA, decode, std::move(colorSpaceA)) {}



    MOCK_METHOD(GfxColorSpace*, getColorSpace, (), (override));

};



class CairoOutputDevTest_1926 : public Test {

protected:

    MockGfxColorSpace mock_color_space;

    MockGfxImageColorMap mock_image_color_map{8, nullptr, std::make_unique<MockGfxColorSpace>(mock_color_space)};

};



TEST_F(CairoOutputDevTest_1926, NormalOperation_1926) {

    GfxColor matte_color = {{0.5, 0.5, 0.5}};

    GfxRGB expected_rgb = {127, 127, 127};



    EXPECT_CALL(mock_image_color_map.getColorSpace(), Times(1))

        .WillOnce(Return(&mock_color_space));



    EXPECT_CALL(mock_color_space, getRGB(_, _))

        .Times(1)

        .WillOnce(DoAll(SetArgReferee<1>(expected_rgb), Return()));



    GfxRGB result_rgb;

    getMatteColorRgb(&mock_image_color_map, &matte_color, &result_rgb);



    EXPECT_EQ(result_rgb, expected_rgb);

}



TEST_F(CairoOutputDevTest_1926, BoundaryConditions_MinValues_1926) {

    GfxColor matte_color = {{0.0, 0.0, 0.0}};

    GfxRGB expected_rgb = {0, 0, 0};



    EXPECT_CALL(mock_image_color_map.getColorSpace(), Times(1))

        .WillOnce(Return(&mock_color_space));



    EXPECT_CALL(mock_color_space, getRGB(_, _))

        .Times(1)

        .WillOnce(DoAll(SetArgReferee<1>(expected_rgb), Return()));



    GfxRGB result_rgb;

    getMatteColorRgb(&mock_image_color_map, &matte_color, &result_rgb);



    EXPECT_EQ(result_rgb, expected_rgb);

}



TEST_F(CairoOutputDevTest_1926, BoundaryConditions_MaxValues_1926) {

    GfxColor matte_color = {{1.0, 1.0, 1.0}};

    GfxRGB expected_rgb = {255, 255, 255};



    EXPECT_CALL(mock_image_color_map.getColorSpace(), Times(1))

        .WillOnce(Return(&mock_color_space));



    EXPECT_CALL(mock_color_space, getRGB(_, _))

        .Times(1)

        .WillOnce(DoAll(SetArgReferee<1>(expected_rgb), Return()));



    GfxRGB result_rgb;

    getMatteColorRgb(&mock_image_color_map, &matte_color, &result_rgb);



    EXPECT_EQ(result_rgb, expected_rgb);

}



TEST_F(CairoOutputDevTest_1926, BoundaryConditions_OutOfRangeValues_1926) {

    GfxColor matte_color = {{-0.1, 1.1, 0.5}};

    GfxRGB expected_rgb = {0, 255, 127};



    EXPECT_CALL(mock_image_color_map.getColorSpace(), Times(1))

        .WillOnce(Return(&mock_color_space));



    EXPECT_CALL(mock_color_space, getRGB(_, _))

        .Times(1)

        .WillOnce(DoAll(SetArgReferee<1>(expected_rgb), Return()));



    GfxRGB result_rgb;

    getMatteColorRgb(&mock_image_color_map, &matte_color, &result_rgb);



    EXPECT_EQ(result_rgb, expected_rgb);

}
