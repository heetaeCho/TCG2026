#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev *psOutputDev;



    void SetUp() override {

        // Mock parameters for PSOutputDev constructor

        const char* fileName = "test.ps";

        PDFDoc* docA = nullptr;  // Assuming PDFDoc is not needed for this test

        char* psTitleA = strdup("Test Title");

        int paperWidthA = 595;

        int paperHeightA = 842;

        bool noCrop = false;

        bool duplexA = false;

        int imgLLXA = 0;

        int imgLLYA = 0;

        int imgURXA = 595;

        int imgURYA = 842;

        PSForceRasterize forceRasterizeA = psForceRasterizeNone;

        bool manualCtrlA = false;

        PSOutCustomCodeCbk customCodeCbkA = nullptr;

        void* customCodeCbkDataA = nullptr;

        PSLevel levelA = psLevel1;



        psOutputDev = new PSOutputDev(fileName, docA, psTitleA, pages, modeA, paperWidthA, paperHeightA,

                                      noCrop, duplexA, imgLLXA, imgLLYA, imgURXA, imgURYA, forceRasterizeA,

                                      manualCtrlA, customCodeCbkA, customCodeCbkDataA, levelA);



        free(psTitleA);

    }



    void TearDown() override {

        delete psOutputDev;

    }



private:

    std::vector<int> pages = {1};

    PSOutMode modeA = psModeOK;

};



TEST_F(PSOutputDevTest_1327, SetEmbedCIDPostScript_DefaultValue_1327) {

    EXPECT_EQ(psOutputDev->getEmbedCIDPostScript(), false);

}



TEST_F(PSOutputDevTest_1327, SetEmbedCIDPostScript_SetTrue_1327) {

    psOutputDev->setEmbedCIDPostScript(true);

    EXPECT_EQ(psOutputDev->getEmbedCIDPostScript(), true);

}



TEST_F(PSOutputDevTest_1327, SetEmbedCIDPostScript_SetFalse_1327) {

    psOutputDev->setEmbedCIDPostScript(false);

    EXPECT_EQ(psOutputDev->getEmbedCIDPostScript(), false);

}
