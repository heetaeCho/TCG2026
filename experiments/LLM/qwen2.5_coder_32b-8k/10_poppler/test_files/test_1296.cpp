#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include "PDFDoc.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Mock PDFDoc and other necessary parameters

        doc = new PDFDoc();

        psTitle = new char[6]{"TestDoc"};

        pages = {1, 2, 3};

        mode = psModeBinary;

        paperWidth = 595;  // A4 width in points

        paperHeight = 842; // A4 height in points

        noCrop = false;

        duplex = true;

        imgLLX = 0;

        imgLLY = 0;

        imgURX = paperWidth;

        imgURY = paperHeight;

        forceRasterize = psForceRasterizeOff;

        manualCtrl = false;

        customCodeCbk = nullptr;

        customCodeCbkData = nullptr;



        // Create an instance of PSOutputDev

        psOutputDev = new PSOutputDev("output.ps", doc, psTitle, pages, mode, paperWidth, paperHeight,

                                      noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize,

                                      manualCtrl, customCodeCbk, customCodeCbkData, psLevel2);

    }



    void TearDown() override {

        delete psOutputDev;

        delete[] psTitle;

        delete doc;

    }



    PDFDoc* doc;

    char* psTitle;

    std::vector<int> pages;

    PSOutMode mode;

    int paperWidth;

    int paperHeight;

    bool noCrop;

    bool duplex;

    int imgLLX;

    int imgLLY;

    int imgURX;

    int imgURY;

    PSForceRasterize forceRasterize;

    bool manualCtrl;

    PSOutCustomCodeCbk customCodeCbk;

    void* customCodeCbkData;



    PSOutputDev* psOutputDev;

};



TEST_F(PSOutputDevTest_1296, UseShadedFills_Level2_Type0_1296) {

    EXPECT_TRUE(psOutputDev->useShadedFills(0));

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_Level2_Type3_1296) {

    EXPECT_FALSE(psOutputDev->useShadedFills(3));

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_Level2_Type4_1296) {

    EXPECT_FALSE(psOutputDev->useShadedFills(4));

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_Level3_Type7_1296) {

    psOutputDev = new PSOutputDev("output.ps", doc, psTitle, pages, mode, paperWidth, paperHeight,

                                  noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize,

                                  manualCtrl, customCodeCbk, customCodeCbkData, psLevel3);

    EXPECT_TRUE(psOutputDev->useShadedFills(7));

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_Level2_Type7_1296) {

    EXPECT_FALSE(psOutputDev->useShadedFills(7));

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_BoundaryCondition_TypeNegative_1296) {

    EXPECT_TRUE(psOutputDev->useShadedFills(-1)); // Assuming negative type should be handled gracefully

}



TEST_F(PSOutputDevTest_1296, UseShadedFills_BoundaryCondition_TypeMaxInt_1296) {

    EXPECT_FALSE(psOutputDev->useShadedFills(INT_MAX));

}
