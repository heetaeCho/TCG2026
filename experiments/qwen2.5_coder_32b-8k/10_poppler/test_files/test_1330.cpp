#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> psOutputDev;



    virtual void SetUp() {

        // Initialize the PSOutputDev with dummy values

        PDFDoc* doc = nullptr; // Assuming a valid PDFDoc pointer is required, but not used in tests

        psOutputDev = std::make_unique<PSOutputDev>(

            "dummy.ps", 

            doc, 

            const_cast<char*>("TestTitle"), 

            1, 

            PSOutMode::psOutModeNormal,

            595, 

            842, 

            false, 

            false, 

            0, 

            0, 

            595, 

            842, 

            PSForceRasterize::psRasterizeAuto,

            false, 

            nullptr, 

            nullptr, 

            PSLevel::psLevel1);

    }

};



TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpace_DefaultValue_1330) {

    EXPECT_FALSE(psOutputDev->getOptimizeColorSpace());

}



TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpace_True_1330) {

    psOutputDev->setOptimizeColorSpace(true);

    EXPECT_TRUE(psOutputDev->getOptimizeColorSpace());

}



TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpace_False_1330) {

    psOutputDev->setOptimizeColorSpace(false);

    EXPECT_FALSE(psOutputDev->getOptimizeColorSpace());

}
