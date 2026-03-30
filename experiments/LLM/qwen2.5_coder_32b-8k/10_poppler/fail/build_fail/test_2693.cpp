#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pdftocairo.cc"

#include "PDFDoc.h"

#include "CairoOutputDev.h"



using namespace testing;



class RenderPageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary global variables

        ps = false;

        crop_x = 0;

        crop_y = 0;

        transp = false;

        printing = false;

        x_resolution = 150.0;

        y_resolution = 150.0;

        useCropBox = false;



        // Create mock objects

        doc = std::make_unique<StrictMock<MockPDFDoc>>();

        cairoOut = std::make_unique<CairoOutputDev>();

    }



    void TearDown() override {

        // Clean up if necessary

    }



    std::unique_ptr<StrictMock<MockPDFDoc>> doc;

    std::unique_ptr<CairoOutputDev> cairoOut;



    // Mock class for PDFDoc to isolate external dependencies

    class MockPDFDoc : public PDFDoc {

    public:

        MOCK_METHOD(void, displayPageSlice, (OutputDev * out, int page, double hDPI, double vDPI, int rotate, bool useMediaBox, bool crop, bool printing, int sliceX, int sliceY, int sliceW, int sliceH, _Bool (*)(void *) abortCheckCbk, void * abortCheckCbkData, _Bool (*)(Annot *, void *) annotDisplayDecideCbk, void * annotDisplayDecideCbkData, bool copyXRef), (override));

        MOCK_METHOD(double, getPageMediaWidth, (int page), (const, override));

        MOCK_METHOD(double, getPageMediaHeight, (int page), (const, override));

    };

};



TEST_F(RenderPageTest_2693, NormalOperation_2693) {

    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, BoundaryCondition_ZeroWidthHeight_2693) {

    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 0.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, BoundaryCondition_ZeroPageNumber_2693) {

    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 0, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, ExceptionHandling_PageNumberTooLarge_2693) {

    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 999999, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, PsTrue_2693) {

    ps = true;



    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, PrintingTrue_2693) {

    printing = true;



    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, true, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, TranspTrue_2693) {

    transp = true;



    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, CropSet_2693) {

    crop_x = 10;

    crop_y = 20;



    EXPECT_CALL(*doc, displayPageSlice(_, _, 150.0, 150.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}



TEST_F(RenderPageTest_2693, ResolutionSet_2693) {

    x_resolution = 300.0;

    y_resolution = 300.0;



    EXPECT_CALL(*doc, displayPageSlice(_, _, 300.0, 300.0, 0, false, false, false, -1, -1, -1, -1, nullptr, nullptr, nullptr, nullptr, false)).Times(1);



    renderPage(doc.get(), cairoOut.get(), 1, 612.0, 792.0, 504.0, 680.0);

}
