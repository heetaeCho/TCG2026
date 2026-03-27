#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/PDFRectangle.h"



class PageTest_709 : public ::testing::Test {

protected:

    PDFRectangle mediaBox;

    PDFRectangle cropBox;

    std::unique_ptr<PageAttrs> attrs;

    Page page;



    void SetUp() override {

        mediaBox = PDFRectangle(0, 0, 100, 200);

        cropBox = PDFRectangle(10, 10, 90, 190);

        attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

        attrs->mediaBox = mediaBox;

        attrs->cropBox = cropBox;

        attrs->haveCropBox = true;



        page = Page(nullptr, 1, Object(), Ref(1, 0), std::move(attrs));

    }

};



TEST_F(PageTest_709, GetCropHeight_NormalOperation_709) {

    EXPECT_DOUBLE_EQ(page.getCropHeight(), 180);

}



TEST_F(PageTest_709, GetCropHeight_NoCropBox_709) {

    page.attrs->haveCropBox = false;

    EXPECT_DOUBLE_EQ(page.getCropHeight(), 200);

}



TEST_F(PageTest_709, GetCropHeight_ZeroHeightCropBox_709) {

    cropBox.y1 = 50;

    cropBox.y2 = 50;

    page.attrs->cropBox = cropBox;

    EXPECT_DOUBLE_EQ(page.getCropHeight(), 0);

}



TEST_F(PageTest_709, GetCropHeight_NegativeYValues_709) {

    cropBox.y1 = -10;

    cropBox.y2 = 10;

    page.attrs->cropBox = cropBox;

    EXPECT_DOUBLE_EQ(page.getCropHeight(), 20);

}



TEST_F(PageTest_709, GetCropHeight_MaximumDoubleValues_709) {

    cropBox.y1 = std::numeric_limits<double>::max();

    cropBox.y2 = std::numeric_limits<double>::max() + 1;

    page.attrs->cropBox = cropBox;

    EXPECT_DOUBLE_EQ(page.getCropHeight(), 1);

}



TEST_F(PageTest_709, GetCropHeight_MinimumDoubleValues_709) {

    cropBox.y1 = -std::numeric_limits<double>::max();

    cropBox.y2 = std::numeric_limits<double>::min();

    page.attrs->cropBox = cropBox;

    EXPECT_DOUBLE_EQ(page.getCropHeight(), std::numeric_limits<double>::min() + std::numeric_limits<double>::max());

}
