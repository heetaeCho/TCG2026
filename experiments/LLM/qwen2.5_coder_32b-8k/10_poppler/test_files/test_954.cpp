#include <gtest/gtest.h>

#include "poppler/PDFDoc.h"

#include "poppler/Page.h"



class PDFDocTest_954 : public ::testing::Test {

protected:

    std::unique_ptr<Page> mockPage1;

    std::unique_ptr<Page> mockPage2;



    void SetUp() override {

        // Create mock pages with known media widths

        mockPage1 = std::make_unique<Page>(nullptr, 1, Object(), Ref(), std::make_unique<PageAttrs>());

        mockPage2 = std::make_unique<Page>(nullptr, 2, Object(), Ref(), std::make_unique<PageAttrs>());



        // Set up known media widths for the mock pages

        EXPECT_CALL(*mockPage1, getMediaWidth()).WillRepeatedly(::testing::Return(595.0)); // A4 width in points

        EXPECT_CALL(*mockPage2, getMediaWidth()).WillRepeatedly(::testing::Return(842.0)); // A3 width in points



        // Create a PDFDoc instance and inject the mock pages

        pdfDoc = std::make_unique<PDFDoc>(std::unique_ptr<GooString>(), std::optional<GooString>(), std::optional<GooString>(), [](){});

        pdfDoc->pageCache.push_back(std::move(mockPage1));

        pdfDoc->pageCache.push_back(std::move(mockPage2));

    }



    std::unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_954, GetPageMediaWidth_ValidPage_954) {

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(1), 595.0);

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(2), 842.0);

}



TEST_F(PDFDocTest_954, GetPageMediaWidth_OutOfBoundsNegative_954) {

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(-1), 0.0);

}



TEST_F(PDFDocTest_954, GetPageMediaWidth_OutOfBoundsAboveMax_954) {

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(3), 0.0); // Assuming only two pages are available

}



TEST_F(PDFDocTest_954, GetPageMediaWidth_ZeroPages_954) {

    pdfDoc->pageCache.clear();

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(1), 0.0);

}
