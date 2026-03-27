#include <gtest/gtest.h>

#include "GfxState.h"



class GfxDeviceNColorSpaceTest_485 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> alt;

    std::vector<std::string> names = {"Name1", "Name2"};

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;

    std::unique_ptr<Function> func;



    void SetUp() override {

        alt = nullptr; // Assuming no alternative color space for simplicity

        func = nullptr; // Assuming no function for simplicity

    }

};



TEST_F(GfxDeviceNColorSpaceTest_485, GetAlt_ReturnsNullPtr_485) {

    GfxDeviceNColorSpace deviceN(2, std::move(names), std::move(alt), std::move(func), std::move(sepsCS));

    EXPECT_EQ(deviceN.getAlt(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_485, GetAlt_ReturnsValidPointer_485) {

    auto altPtr = std::make_unique<GfxColorSpace>();

    GfxDeviceNColorSpace deviceN(2, std::move(names), std::move(altPtr), std::move(func), std::move(sepsCS));

    EXPECT_NE(deviceN.getAlt(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_485, GetColorantName_ReturnsCorrectName_485) {

    GfxDeviceNColorSpace deviceN(2, names, std::move(alt), std::move(func), std::move(sepsCS));

    EXPECT_EQ(deviceN.getColorantName(0), "Name1");

    EXPECT_EQ(deviceN.getColorantName(1), "Name2");

}



TEST_F(GfxDeviceNColorSpaceTest_485, GetColorantName_OutOfBounds_ReturnsEmptyString_485) {

    GfxDeviceNColorSpace deviceN(2, names, std::move(alt), std::move(func), std::move(sepsCS));

    EXPECT_THROW(deviceN.getColorantName(-1), std::out_of_range);

    EXPECT_THROW(deviceN.getColorantName(2), std::out_of_range); // Out of bounds

}
