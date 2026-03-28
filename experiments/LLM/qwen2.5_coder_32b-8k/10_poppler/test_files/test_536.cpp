#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using namespace testing;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_CONST_METHOD0(useGetRGBLine, bool());

};



class GfxImageColorMapTest_536 : public Test {

protected:

    std::unique_ptr<MockGfxColorSpace> mockColorSpace;

    std::unique_ptr<MockGfxColorSpace> mockColorSpace2;

    GfxImageColorMap* imageColorMap;



    void SetUp() override {

        mockColorSpace = std::make_unique<MockGfxColorSpace>();

        mockColorSpace2 = std::make_unique<MockGfxColorSpace>();

        imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace));

    }



    void TearDown() override {

        delete imageColorMap;

    }

};



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsTrueWhenOnlyPrimaryUsesGetRGBLine_536) {

    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(true));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(false));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsTrueWhenOnlySecondaryUsesGetRGBLine_536) {

    imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));



    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(true));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsTrueWhenBothPrimaryAndSecondaryUseGetRGBLine_536) {

    imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));



    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(true));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(true));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsFalseWhenNeitherPrimaryNorSecondaryUseGetRGBLine_536) {

    imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));



    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(false));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsTrueWhenOnlyPrimaryUsesGetRGBLine_Boundary_536) {

    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(true));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(false));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsFalseWhenOnlySecondaryUsesGetRGBLine_Boundary_536) {

    imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));



    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(true));



    imageColorMap->useRGBLine();

}



TEST_F(GfxImageColorMapTest_536, UseRGBLine_ReturnsFalseWhenNeitherUsesGetRGBLine_ErrorCase_536) {

    imageColorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));



    EXPECT_CALL(*mockColorSpace, useGetRGBLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetRGBLine()).WillOnce(Return(false));



    imageColorMap->useRGBLine();

}
