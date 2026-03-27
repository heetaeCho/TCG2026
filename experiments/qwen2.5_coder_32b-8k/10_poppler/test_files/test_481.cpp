#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>

#include <vector>

#include <string>



class GfxDeviceNColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxDeviceNColorSpace> deviceNCS;

    const int nComps = 4;

    const std::vector<std::string> names = {"Cyan", "Magenta", "Yellow", "Black"};

    std::unique_ptr<GfxColorSpace> altColorSpace = nullptr;

    std::unique_ptr<Function> tintTransformFunc = nullptr;

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;



    void SetUp() override {

        deviceNCS = std::make_unique<GfxDeviceNColorSpace>(nComps, names, std::move(altColorSpace), std::move(tintTransformFunc), std::move(sepsCS));

    }

};



TEST_F(GfxDeviceNColorSpaceTest_481, GetModeReturnsDeviceN_481) {

    EXPECT_EQ(deviceNCS->getMode(), csDeviceN);

}



TEST_F(GfxDeviceNColorSpaceTest_481, GetNCompsReturnsCorrectValue_481) {

    EXPECT_EQ(deviceNCS->getNComps(), nComps);

}



TEST_F(GfxDeviceNColorSpaceTest_481, GetColorantNameReturnsCorrectName_481) {

    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(deviceNCS->getColorantName(i), names[i]);

    }

}



TEST_F(GfxDeviceNColorSpaceTest_481, BoundaryConditionGetColorantName_481) {

    // Test boundary condition for getColorantName

    EXPECT_THROW(deviceNCS->getColorantName(-1), std::out_of_range);

    EXPECT_THROW(deviceNCS->getColorantName(nComps), std::out_of_range);

}



TEST_F(GfxDeviceNColorSpaceTest_481, GetAltReturnsNullptr_481) {

    EXPECT_EQ(deviceNCS->getAlt(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_481, GetTintTransformFuncReturnsNullptr_481) {

    EXPECT_EQ(deviceNCS->getTintTransformFunc(), nullptr);

}
