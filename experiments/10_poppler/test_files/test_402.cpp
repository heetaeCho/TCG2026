#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxColorSpaceTest_402 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxColorSpaceTest_402, UseGetGrayLine_Default_402) {

    EXPECT_FALSE(colorSpace->useGetGrayLine());

}



TEST_F(GfxColorSpaceTest_402, UseGetRGBLine_Default_402) {

    EXPECT_FALSE(colorSpace->useGetRGBLine());

}



TEST_F(GfxColorSpaceTest_402, UseGetCMYKLine_Default_402) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxColorSpaceTest_402, UseGetDeviceNLine_Default_402) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}



TEST_F(GfxColorSpaceTest_402, GetOverprintMask_Default_402) {

    EXPECT_EQ(0u, colorSpace->getOverprintMask());

}



// Assuming getMapping returns an empty vector by default

TEST_F(GfxColorSpaceTest_402, GetMapping_Default_402) {

    EXPECT_TRUE(colorSpace->getMapping().empty());

}



// Test for boundary condition with maxSepComps = 0

TEST_F(GfxColorSpaceTest_402, CreateMapping_ZeroComponents_402) {

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    colorSpace->createMapping(&separationList, 0);

    // No observable behavior to assert here, but the call should not crash

}



// Test for boundary condition with maxSepComps = 1

TEST_F(GfxColorSpaceTest_402, CreateMapping_OneComponent_402) {

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    colorSpace->createMapping(&separationList, 1);

    // No observable behavior to assert here, but the call should not crash

}



// Test for boundary condition with maxSepComps = large number

TEST_F(GfxColorSpaceTest_402, CreateMapping_LargeComponents_402) {

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    colorSpace->createMapping(&separationList, 1000);

    // No observable behavior to assert here, but the call should not crash

}



// Test for exceptional case with null pointer

TEST_F(GfxColorSpaceTest_402, CreateMapping_NullPointer_402) {

    colorSpace->createMapping(nullptr, 10);

    // No observable behavior to assert here, but the call should not crash

}



// Assuming getNComps returns a default value of 0

TEST_F(GfxColorSpaceTest_402, GetNComps_Default_402) {

    EXPECT_EQ(0, colorSpace->getNComps());

}
