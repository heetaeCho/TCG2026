#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "Page.h"



class PopplerAnnotTest : public ::testing::Test {

protected:

    Page* mock_page;

    PopplerAnnot poppler_annot;



    void SetUp() override {

        mock_page = new Page(nullptr, 1, Object(), Ref(), std::make_unique<PageAttrs>());

        auto mock_annot = std::make_shared<Annot>();

        EXPECT_CALL(*mock_annot.get(), getPageNum()).WillOnce(::testing::Return(1));

        poppler_annot.annot = mock_annot;

    }



    void TearDown() override {

        delete mock_page;

    }

};



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_NormalOperation_2071) {

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_NE(cropbox, nullptr);

    EXPECT_EQ(page_out, mock_page);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageNotAdded_2071) {

    EXPECT_CALL(*poppler_annot.annot.get(), getPageNum()).WillOnce(::testing::Return(0));

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_EQ(cropbox, nullptr);

    EXPECT_EQ(page_out, nullptr);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageNull_2071) {

    EXPECT_CALL(*poppler_annot.annot.get(), getPageNum()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*mock_page, getDoc()).WillOnce(::testing::Return(nullptr));

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_EQ(cropbox, nullptr);

    EXPECT_EQ(page_out, nullptr);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageIndexBoundary_2071) {

    EXPECT_CALL(*poppler_annot.annot.get(), getPageNum()).WillOnce(::testing::Return(std::numeric_limits<int>::max()));

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_EQ(cropbox, nullptr);

    EXPECT_EQ(page_out, nullptr);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageIndexNegative_2071) {

    EXPECT_CALL(*poppler_annot.annot.get(), getPageNum()).WillOnce(::testing::Return(-1));

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_EQ(cropbox, nullptr);

    EXPECT_EQ(page_out, nullptr);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageIndexZero_2071) {

    EXPECT_CALL(*poppler_annot.annot.get(), getPageNum()).WillOnce(::testing::Return(0));

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, &page_out);

    EXPECT_EQ(cropbox, nullptr);

    EXPECT_EQ(page_out, nullptr);

}



TEST_F(PopplerAnnotTest, GetCropBoxAndPage_PageOutNull_2071) {

    Page* page_out = nullptr;

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox_and_page(&poppler_annot, page_out);

    EXPECT_NE(cropbox, nullptr);

}
