#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> ps_output_dev;



    void SetUp() override {

        // Initialize with some default values, assuming these are valid parameters for the constructor

        PDFDoc* docA = nullptr; // Assuming this is a mock or can be null for testing purposes

        char psTitleA[] = "Test Title";

        int paperWidthA = 800;

        int paperHeightA = 600;

        bool noCrop = false;

        bool duplexA = false;

        int imgLLXA = 0;

        int imgLLYA = 0;

        int imgURXA = 100;

        int imgURYA = 100;

        PSForceRasterize forceRasterizeA = psfrNone;

        bool manualCtrlA = false;



        ps_output_dev.reset(new PSOutputDev("test.ps", docA, psTitleA, std::vector<int>(), psomNormal,

                                           paperWidthA, paperHeightA, noCrop, duplexA, imgLLXA, imgLLYA, imgURXA, imgURYA,

                                           forceRasterizeA, manualCtrlA, nullptr, nullptr, psLevel2));

    }

};



TEST_F(PSOutputDevTest_1320, GetFontPassthroughDefault_1320) {

    // By default, fontPassthrough should be false

    EXPECT_FALSE(ps_output_dev->getFontPassthrough());

}



TEST_F(PSOutputDevTest_1320, SetGetFontPassthroughTrue_1320) {

    ps_output_dev->setFontPassthrough(true);

    EXPECT_TRUE(ps_output_dev->getFontPassthrough());

}



TEST_F(PSOutputDevTest_1320, SetGetFontPassthroughFalse_1320) {

    ps_output_dev->setFontPassthrough(false);

    EXPECT_FALSE(ps_output_dev->getFontPassthrough());

}
