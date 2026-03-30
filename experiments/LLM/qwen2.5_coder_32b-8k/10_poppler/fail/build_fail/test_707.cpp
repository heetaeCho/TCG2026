#include <gtest/gtest.h>

#include "Page.h"

#include "PDFRectangle.h"



using namespace std;



class PageTest_707 : public ::testing::Test {

protected:

    PDFRectangle mediaBox;

    unique_ptr<PageAttrs> attrs;

    Page page;



    void SetUp() override {

        mediaBox = PDFRectangle(0., 0., 612., 792.); // Example A4 size

        attrs = make_unique<PageAttrs>(nullptr, nullptr);

        attrs->mediaBox = mediaBox;

        page = Page(nullptr, 1, Object(), Ref(), move(attrs));

    }

};



TEST_F(PageTest_707, GetMediaHeight_ReturnsCorrectValue_707) {

    EXPECT_DOUBLE_EQ(page.getMediaHeight(), 792.);

}



TEST_F(PageTest_707, GetMediaHeight_ZeroHeightRectangle_707) {

    mediaBox = PDFRectangle(0., 0., 612., 0.);

    attrs->mediaBox = mediaBox;

    EXPECT_DOUBLE_EQ(page.getMediaHeight(), 0.);

}



TEST_F(PageTest_707, GetMediaHeight_NegativeHeightRectangle_707) {

    mediaBox = PDFRectangle(0., 500., 612., 400.);

    attrs->mediaBox = mediaBox;

    EXPECT_DOUBLE_EQ(page.getMediaHeight(), -100.);

}
