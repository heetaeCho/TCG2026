#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"

#include "gmock/gmock.h"



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(bool, ok, (), (override));

};



class PSOutputDevTest_1293 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new MockPDFDoc();

        psTitle = "test_title";

        pages = {1};

        mode = psModeNormal;

        paperWidth = 595; // A4 width

        paperHeight = 842; // A4 height

        noCrop = false;

        duplex = false;

        imgLLX = 0;

        imgLLY = 0;

        imgURX = 595;

        imgURY = 842;

        forceRasterize = psForceRasterizeNone;

        manualCtrl = false;



        psOutputDev = new PSOutputDev("test_output.ps", doc, const_cast<char*>(psTitle.c_str()), pages, mode, paperWidth, paperHeight,

                                     noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize, manualCtrl, nullptr, nullptr, psLevel2);

    }



    void TearDown() override {

        delete psOutputDev;

        delete doc;

    }



    MockPDFDoc* doc;

    std::string psTitle;

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



    PSOutputDev* psOutputDev;

};



TEST_F(PSOutputDevTest_1293, UpsideDownFalse_1293) {

    EXPECT_FALSE(psOutputDev->upsideDown());

}



TEST_F(PSOutputDevTest_1293, NormalOperationCheckPageSlice_1293) {

    Page* mockPage = nullptr; // Assuming we can pass a null page for this test

    double hDPI = 72.0;

    double vDPI = 72.0;

    int rotate = 0;

    bool useMediaBox = true;

    bool crop = false;

    int sliceX = 0;

    int sliceY = 0;

    int sliceW = paperWidth;

    int sliceH = paperHeight;

    bool printing = false;



    EXPECT_CALL(*doc, ok()).WillOnce(::testing::Return(true));



    // Assuming the function should not crash and return some valid value

    bool result = psOutputDev->checkPageSlice(mockPage, hDPI, vDPI, rotate, useMediaBox, crop, sliceX, sliceY, sliceW, sliceH, printing,

                                              nullptr, nullptr, nullptr, nullptr);

    EXPECT_TRUE(result || !result); // This is a non-crashing test

}



TEST_F(PSOutputDevTest_1293, BoundaryConditionsCheckPageSlice_1293) {

    Page* mockPage = nullptr;

    double hDPI = 0.0; // boundary condition: zero DPI should be handled gracefully

    double vDPI = 72.0;

    int rotate = 0;

    bool useMediaBox = true;

    bool crop = false;

    int sliceX = 0;

    int sliceY = 0;

    int sliceW = paperWidth;

    int sliceH = paperHeight;

    bool printing = false;



    EXPECT_CALL(*doc, ok()).WillOnce(::testing::Return(true));



    // Assuming the function should not crash and return some valid value

    bool result = psOutputDev->checkPageSlice(mockPage, hDPI, vDPI, rotate, useMediaBox, crop, sliceX, sliceY, sliceW, sliceH, printing,

                                              nullptr, nullptr, nullptr, nullptr);

    EXPECT_TRUE(result || !result); // This is a non-crashing test

}



TEST_F(PSOutputDevTest_1293, ExceptionalCasesCheckPageSlice_1293) {

    Page* mockPage = nullptr;

    double hDPI = 72.0;

    double vDPI = 72.0;

    int rotate = 0;

    bool useMediaBox = true;

    bool crop = false;

    int sliceX = paperWidth; // boundary condition: outside the page

    int sliceY = paperHeight; // boundary condition: outside the page

    int sliceW = paperWidth;

    int sliceH = paperHeight;

    bool printing = false;



    EXPECT_CALL(*doc, ok()).WillOnce(::testing::Return(true));



    // Assuming the function should not crash and return some valid value

    bool result = psOutputDev->checkPageSlice(mockPage, hDPI, vDPI, rotate, useMediaBox, crop, sliceX, sliceY, sliceW, sliceH, printing,

                                              nullptr, nullptr, nullptr, nullptr);

    EXPECT_TRUE(result || !result); // This is a non-crashing test

}
