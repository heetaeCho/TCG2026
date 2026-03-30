#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxImageColorMapTest : public Test {

protected:

    MockGfxColorSpace* mockColorSpace;

    std::unique_ptr<GfxColorSpace> colorSpacePtr;



    void SetUp() override {

        mockColorSpace = new MockGfxColorSpace();

        colorSpacePtr.reset(mockColorSpace);

    }



    void TearDown() override {

        // No specific teardown required as unique_ptr will handle deletion

    }

};



// Mock class for GfxColorSpace if needed

class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(int, getNumComponents, (), (const));

    MOCK_METHOD(void, free, (), (override));

};



TEST_F(GfxImageColorMapTest_531, GetColorSpace_ReturnsCorrectPointer_531) {

    GfxImageColorMap colorMap(8, nullptr, std::move(colorSpacePtr));

    EXPECT_EQ(mockColorSpace, colorMap.getColorSpace());

}



TEST_F(GfxImageColorMapTest_531, IsOk_ReturnsTrueForValidInitialization_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_TRUE(colorMap.isOk());

}



TEST_F(GfxImageColorMapTest_531, Copy_ReturnsNewInstanceWithSameColorSpace_531) {

    GfxImageColorMap original(8, nullptr, std::move(colorSpacePtr));

    GfxImageColorMap* copy = original.copy();

    EXPECT_NE(&original, copy);

    EXPECT_EQ(mockColorSpace, copy->getColorSpace());

    delete copy;

}



TEST_F(GfxImageColorMapTest_531, GetNumPixelComps_ReturnsValidValue_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_GT(colorMap.getNumPixelComps(), 0);

}



TEST_F(GfxImageColorMapTest_531, GetBits_ReturnsInitializedBits_531) {

    int bits = 8;

    GfxImageColorMap colorMap(bits, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_EQ(colorMap.getBits(), bits);

}



TEST_F(GfxImageColorMapTest_531, GetDecodeLow_ReturnsValidValue_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 0.0);

}



TEST_F(GfxImageColorMapTest_531, GetDecodeHigh_ReturnsValidValue_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 255.0);

}



TEST_F(GfxImageColorMapTest_531, UseRGBLine_ReturnsFalseByDefault_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_FALSE(colorMap.useRGBLine());

}



TEST_F(GfxImageColorMapTest_531, UseCMYKLine_ReturnsFalseByDefault_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_FALSE(colorMap.useCMYKLine());

}



TEST_F(GfxImageColorMapTest_531, UseDeviceNLine_ReturnsFalseByDefault_531) {

    GfxImageColorMap colorMap(8, nullptr, std::make_unique<MockGfxColorSpace>());

    EXPECT_FALSE(colorMap.useDeviceNLine());

}
