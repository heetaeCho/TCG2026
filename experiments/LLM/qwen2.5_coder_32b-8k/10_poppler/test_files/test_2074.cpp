#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "poppler-private.h"

#include "PDFRectangle.h"

#include "Page.h"



class PopplerAnnotTest_2074 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = new PopplerAnnot();

        poppler_rect = new PopplerRectangle();

        page = new Page(nullptr, 1, Object(), Ref(), std::make_unique<PageAttrs>());

        poppler_annot->annot = std::make_shared<Annot>();

    }



    void TearDown() override {

        delete poppler_annot;

        delete poppler_rect;

        delete page;

    }



    PopplerAnnot* poppler_annot;

    PopplerRectangle* poppler_rect;

    Page* page;

};



TEST_F(PopplerAnnotTest_2074, SetRectangleNormalOperation_2074) {

    poppler_rect->x1 = 1.0;

    poppler_rect->y1 = 2.0;

    poppler_rect->x2 = 3.0;

    poppler_rect->y2 = 4.0;



    PDFRectangle crop_box(0, 0, 5, 6);

    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(&crop_box));



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters

    PDFRectangle expected_rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(expected_rect.x1 + crop_box.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1 + crop_box.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2 + crop_box.x1, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2 + crop_box.y1, poppler_annot->annot->getRect().y2);

}



TEST_F(PopplerAnnotTest_2074, SetRectangleBoundaryConditions_2074) {

    poppler_rect->x1 = 0.0;

    poppler_rect->y1 = 0.0;

    poppler_rect->x2 = 0.0;

    poppler_rect->y2 = 0.0;



    PDFRectangle crop_box(0, 0, 5, 6);

    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(&crop_box));



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters

    PDFRectangle expected_rect(0.0, 0.0, 0.0, 0.0);

    EXPECT_EQ(expected_rect.x1 + crop_box.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1 + crop_box.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2 + crop_box.x1, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2 + crop_box.y1, poppler_annot->annot->getRect().y2);

}



TEST_F(PopplerAnnotTest_2074, SetRectangleWithNullCropBox_2074) {

    poppler_rect->x1 = 1.0;

    poppler_rect->y1 = 2.0;

    poppler_rect->x2 = 3.0;

    poppler_rect->y2 = 4.0;



    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(nullptr));



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters

    PDFRectangle expected_rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(expected_rect.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2, poppler_annot->annot->getRect().y2);

}



TEST_F(PopplerAnnotTest_2074, SetRectangleWithNegativeCoordinates_2074) {

    poppler_rect->x1 = -1.0;

    poppler_rect->y1 = -2.0;

    poppler_rect->x2 = -3.0;

    poppler_rect->y2 = -4.0;



    PDFRectangle crop_box(0, 0, 5, 6);

    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(&crop_box));



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters

    PDFRectangle expected_rect(-1.0, -2.0, -3.0, -4.0);

    EXPECT_EQ(expected_rect.x1 + crop_box.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1 + crop_box.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2 + crop_box.x1, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2 + crop_box.y1, poppler_annot->annot->getRect().y2);

}



TEST_F(PopplerAnnotTest_2074, SetRectangleWithRotatedPage_2074) {

    poppler_rect->x1 = 1.0;

    poppler_rect->y1 = 2.0;

    poppler_rect->x2 = 3.0;

    poppler_rect->y2 = 4.0;



    PDFRectangle crop_box(0, 0, 5, 6);

    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(&crop_box));

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(90)); // Example rotation



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters after un-rotation

    PDFRectangle expected_rect(1.0, 2.0, 3.0, 4.0); // These values are placeholders; actual logic unknown

    EXPECT_EQ(expected_rect.x1 + crop_box.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1 + crop_box.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2 + crop_box.x1, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2 + crop_box.y1, poppler_annot->annot->getRect().y2);

}



TEST_F(PopplerAnnotTest_2074, SetRectangleWithInvalidPageRotation_2074) {

    poppler_rect->x1 = 1.0;

    poppler_rect->y1 = 2.0;

    poppler_rect->x2 = 3.0;

    poppler_rect->y2 = 4.0;



    PDFRectangle crop_box(0, 0, 5, 6);

    EXPECT_CALL(*page, getCropBox()).WillOnce(::testing::Return(&crop_box));

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(123)); // Unsupported rotation



    poppler_annot_set_rectangle(poppler_annot, poppler_rect);



    // Assuming setRect is called with the correct parameters without un-rotation

    PDFRectangle expected_rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(expected_rect.x1 + crop_box.x1, poppler_annot->annot->getRect().x1);

    EXPECT_EQ(expected_rect.y1 + crop_box.y1, poppler_annot->annot->getRect().y1);

    EXPECT_EQ(expected_rect.x2 + crop_box.x1, poppler_annot->annot->getRect().x2);

    EXPECT_EQ(expected_rect.y2 + crop_box.y1, poppler_annot->annot->getRect().y2);

}
