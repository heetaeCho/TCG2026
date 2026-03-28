#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



// Mock class for PDFDoc as it's an external collaborator

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



// Test fixture for PSOutputDev tests

class PSOutputDevTest_1295 : public ::testing::Test {

protected:

    MockPDFDoc mockDoc;

    std::vector<int> pages = {1};

    const char* fileName = "dummy.ps";

    PSOutMode modeA = psModeEPS;

    int paperWidthA = 800;

    int paperHeightA = 600;

    bool noCrop = false;

    bool duplexA = false;

    int imgLLXA = 0;

    int imgLLYA = 0;

    int imgURXA = 800;

    int imgURYA = 600;

    PSForceRasterize forceRasterizeA = psForceRasterizeNone;

    bool manualCtrlA = false;

    PSOutCustomCodeCbk customCodeCbkA = nullptr;

    void* customCodeCbkDataA = nullptr;

    PSLevel levelA = psLevel2;



    std::unique_ptr<PSOutputDev> psOutputDev;



    void SetUp() override {

        psOutputDev = std::make_unique<PSOutputDev>(fileName, &mockDoc, nullptr, pages, modeA, paperWidthA, paperHeightA,

                                                    noCrop, duplexA, imgLLXA, imgLLYA, imgURXA, imgURYA,

                                                    forceRasterizeA, manualCtrlA, customCodeCbkA, customCodeCbkDataA,

                                                    levelA);

    }

};



// Test useTilingPatternFill returns true

TEST_F(PSOutputDevTest_1295, UseTilingPatternFillReturnsTrue_1295) {

    EXPECT_TRUE(psOutputDev->useTilingPatternFill());

}



// Test other methods - Normal Operation

TEST_F(PSOutputDevTest_1295, WriteHeaderDoesNotThrow_1295) {

    PDFRectangle mediaBox;

    PDFRectangle cropBox;

    int pageRotate = 0;

    const char* title = "test";

    EXPECT_NO_THROW(psOutputDev->writeHeader(1, &mediaBox, &cropBox, pageRotate, title));

}



TEST_F(PSOutputDevTest_1295, WriteXpdfProcsetDoesNotThrow_1295) {

    EXPECT_NO_THROW(psOutputDev->writeXpdfProcset());

}



TEST_F(PSOutputDevTest_1295, WritePageTrailerDoesNotThrow_1295) {

    EXPECT_NO_THROW(psOutputDev->writePageTrailer());

}



TEST_F(PSOutputDevTest_1295, WriteTrailerDoesNotThrow_1295) {

    EXPECT_NO_THROW(psOutputDev->writeTrailer());

}



// Test other methods - Boundary Conditions

TEST_F(PSOutputDevTest_1295, CheckPageSliceWithMinValuesReturnsFalse_1295) {

    Page page;

    double hDPI = 0.0;

    double vDPI = 0.0;

    int rotate = 0;

    bool useMediaBox = false;

    bool crop = false;

    int sliceX = 0;

    int sliceY = 0;

    int sliceW = 0;

    int sliceH = 0;

    bool printing = false;

    auto abortCheckCbk = [](void*) { return false; };

    void* abortCheckCbkData = nullptr;

    auto annotDisplayDecideCbk = [](Annot*, void*) { return true; };

    void* annotDisplayDecideCbkData = nullptr;

    EXPECT_FALSE(psOutputDev->checkPageSlice(&page, hDPI, vDPI, rotate, useMediaBox, crop,

                                             sliceX, sliceY, sliceW, sliceH, printing,

                                             abortCheckCbk, abortCheckCbkData,

                                             annotDisplayDecideCbk, annotDisplayDecideCbkData));

}



// Test other methods - Exceptional or Error Cases

TEST_F(PSOutputDevTest_1295, UseShadedFillsWithInvalidTypeReturnsFalse_1295) {

    EXPECT_FALSE(psOutputDev->useShadedFills(-1));

}



TEST_F(PSOutputDevTest_1295, UseDrawFormReturnsTrue_1295) {

    EXPECT_TRUE(psOutputDev->useDrawForm());

}
