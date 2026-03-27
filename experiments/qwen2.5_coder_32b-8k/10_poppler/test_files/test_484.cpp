#include <gtest/gtest.h>

#include "GfxState.h"



class GfxDeviceNColorSpaceTest : public ::testing::Test {

protected:

    std::vector<std::string> colorNames = {"Red", "Green", "Blue"};

    GfxDeviceNColorSpace deviceNColorSpace(3, std::move(colorNames), nullptr, nullptr, {});



    virtual void SetUp() {}

    virtual void TearDown() {}

};



TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_ValidIndex_ReturnsCorrectName_484) {

    EXPECT_EQ(deviceNColorSpace.getColorantName(0), "Red");

    EXPECT_EQ(deviceNColorSpace.getColorantName(1), "Green");

    EXPECT_EQ(deviceNColorSpace.getColorantName(2), "Blue");

}



TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_OutOfBoundsIndex_ThrowsException_484) {

    EXPECT_THROW(deviceNColorSpace.getColorantName(-1), std::out_of_range);

    EXPECT_THROW(deviceNColorSpace.getColorantName(3), std::out_of_range);

}



TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_BoundaryIndex_ReturnsCorrectName_484) {

    EXPECT_EQ(deviceNColorSpace.getColorantName(0), "Red");

    EXPECT_EQ(deviceNColorSpace.getColorantName(2), "Blue");

}
