#include <gtest/gtest.h>

#include "GfxState.h"



class GfxImageColorMapTest_537 : public ::testing::Test {

protected:

    class MockGfxColorSpace : public GfxColorSpace {

    public:

        MOCK_CONST_METHOD0(useGetCMYKLine, bool());

    };



    std::unique_ptr<MockGfxColorSpace> mockColorSpace;

    std::unique_ptr<MockGfxColorSpace> mockColorSpace2;

    GfxImageColorMap* colorMap;



    void SetUp() override {

        mockColorSpace = std::make_unique<MockGfxColorSpace>();

        mockColorSpace2 = std::make_unique<MockGfxColorSpace>();

        colorMap = new GfxImageColorMap(8, nullptr, std::move(mockColorSpace));

        colorMap->colorSpace2 = mockColorSpace2.get();

    }



    void TearDown() override {

        delete colorMap;

    }

};



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsTrueWhenBothColorSpacesUseGetCMYKLine_537) {

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(true));



    EXPECT_TRUE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsTrueWhenOnlyFirstColorSpaceUsesGetCMYKLine_537) {

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(false));



    EXPECT_TRUE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsTrueWhenOnlySecondColorSpaceUsesGetCMYKLine_537) {

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(true));



    EXPECT_TRUE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsFalseWhenNeitherColorSpacesUseGetCMYKLine_537) {

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsTrueWhenOnlyFirstColorSpaceIsNotNullAndUsesGetCMYKLine_537) {

    colorMap->colorSpace2 = nullptr;

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(true));



    EXPECT_TRUE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsFalseWhenOnlyFirstColorSpaceIsNotNullAndDoesNotUseGetCMYKLine_537) {

    colorMap->colorSpace2 = nullptr;

    EXPECT_CALL(*mockColorSpace, useGetCMYKLine()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsTrueWhenOnlySecondColorSpaceIsNotNullAndUsesGetCMYKLine_537) {

    colorMap->colorSpace = nullptr;

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(true));



    EXPECT_TRUE(colorMap->useCMYKLine());

}



TEST_F(GfxImageColorMapTest_537, UseCMYKLine_ReturnsFalseWhenOnlySecondColorSpaceIsNotNullAndDoesNotUseGetCMYKLine_537) {

    colorMap->colorSpace = nullptr;

    EXPECT_CALL(*mockColorSpace2, useGetCMYKLine()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(colorMap->useCMYKLine());

}
