#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PDFDoc* doc = nullptr;

    char psTitle[10] = "testTitle";

    std::vector<int> pages = {1, 2};

    PSOutMode mode = psModeNormal;

    int paperWidth = 595; // A4 width

    int paperHeight = 842; // A4 height

    bool noCrop = false;

    bool duplex = false;

    int imgLLX = 0;

    int imgLLY = 0;

    int imgURX = 595;

    int imgURY = 842;

    PSForceRasterize forceRasterize = psForceRasterizeNone;

    bool manualCtrl = false;

    PSOutCustomCodeCbk customCodeCbk = nullptr;

    void* customCodeCbkData = nullptr;

    PSLevel level = psLevel3;



    PSOutputDev* psOutputDev = nullptr;



    virtual void SetUp() {

        psOutputDev = new PSOutputDev("./testfile.ps", doc, psTitle, pages, mode, paperWidth, paperHeight,

                                       noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize,

                                       manualCtrl, customCodeCbk, customCodeCbkData, level);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1318, GetEmbedCIDPostScript_DefaultValue_1318) {

    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());

}



TEST_F(PSOutputDevTest_1318, SetAndGetEmbedCIDPostScript_1318) {

    psOutputDev->setEmbedCIDPostScript(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());



    psOutputDev->setEmbedCIDPostScript(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());

}



TEST_F(PSOutputDevTest_1318, SetAndGetEmbedCIDPostScript_BoundaryConditions_1318) {

    // Test boundary condition for setting to true

    psOutputDev->setEmbedCIDPostScript(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());



    // Test boundary condition for setting to false

    psOutputDev->setEmbedCIDPostScript(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());

}



TEST_F(PSOutputDevTest_1318, SetAndGetEmbedCIDPostScript_ExceptionalCases_1318) {

    // Since the setter and getter do not have exceptional cases observable through the interface,

    // we can only test normal operation here.

    psOutputDev->setEmbedCIDPostScript(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());



    psOutputDev->setEmbedCIDPostScript(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());

}
