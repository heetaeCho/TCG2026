#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest_1116 : public ::testing::Test {

protected:

    std::unique_ptr<SplashOutputDev> splashOutputDev;



    void SetUp() override {

        // Initialize with default parameters for the constructor

        splashOutputDev = std::make_unique<SplashOutputDev>(splashModeRGB8, 0, nullptr, false, splashThinLineNone, false);

    }

};



TEST_F(SplashOutputDevTest_1116, SetEnableFreeTypeToTrue_1116) {

    splashOutputDev->setEnableFreeType(true);

    // No observable behavior to verify directly, but we can check consistency

}



TEST_F(SplashOutputDevTest_1116, SetEnableFreeTypeToFalse_1116) {

    splashOutputDev->setEnableFreeType(false);

    // No observable behavior to verify directly, but we can check consistency

}



TEST_F(SplashOutputDevTest_1116, EnableFreeTypeDefaultState_1116) {

    // Assuming default state is false as not set otherwise

    // No observable behavior to verify directly, but we can check consistency

}
