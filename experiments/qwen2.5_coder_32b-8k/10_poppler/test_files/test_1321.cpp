#include <gtest/gtest.h>

#include "poppler/PSOutputDev.h"

#include "poppler/PDFDoc.h"  // Assuming PDFDoc is needed for PSOutputDev construction



class PSOutputDevTest_1321 : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> psOutputDev;



    void SetUp() override {

        // Create a mock PDFDoc pointer (assuming it's required)

        PDFDoc* doc = nullptr;  // In actual usage, this would be a valid PDFDoc object

        char title[] = "TestTitle";

        int pages = 1;

        PSOutMode mode = psModePS3;  // Example mode

        int paperWidth = 595;

        int paperHeight = 842;

        bool noCrop = false;

        bool duplex = false;

        int imgLLX = 0;

        int imgLLY = 0;

        int imgURX = 595;

        int imgURY = 842;

        PSForceRasterize forceRasterize = psForceRasterizeNone;

        bool manualCtrl = false;

        void* customCodeCbkData = nullptr; // Assuming no actual callback data

        PSLevel level = psLevel2;



        psOutputDev.reset(new PSOutputDev("output.ps", doc, title, pages, mode,

                                            paperWidth, paperHeight, noCrop, duplex,

                                            imgLLX, imgLLY, imgURX, imgURY, forceRasterize,

                                            manualCtrl, nullptr, customCodeCbkData, level));

    }

};



TEST_F(PSOutputDevTest_1321, GetOptimizeColorSpace_DefaultValue_1321) {

    EXPECT_FALSE(psOutputDev->getOptimizeColorSpace());

}



TEST_F(PSOutputDevTest_1321, SetAndGetOptimizeColorSpace_True_1321) {

    psOutputDev->setOptimizeColorSpace(true);

    EXPECT_TRUE(psOutputDev->getOptimizeColorSpace());

}



TEST_F(PSOutputDevTest_1321, SetAndGetOptimizeColorSpace_False_1321) {

    psOutputDev->setOptimizeColorSpace(false);

    EXPECT_FALSE(psOutputDev->getOptimizeColorSpace());

}
