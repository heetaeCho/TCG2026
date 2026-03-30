#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "PDFRectangle.h"



using namespace testing;



// Mock for external dependencies if needed



TEST_F(PopplerAnnotTest_2073, GetRectangle_NormalOperation_2073) {

    // Arrange

    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<Annot>();

    poppler_annot.annot->getRect() = PDFRectangle(10.0, 20.0, 30.0, 40.0);

    

    PopplerRectangle poppler_rect;



    // Act

    poppler_annot_get_rectangle(&poppler_annot, &poppler_rect);



    // Assert

    EXPECT_EQ(poppler_rect.x1, 10.0);

    EXPECT_EQ(poppler_rect.y1, 20.0);

    EXPECT_EQ(poppler_rect.x2, 30.0);

    EXPECT_EQ(poppler_rect.y2, 40.0);

}



TEST_F(PopplerAnnotTest_2073, GetRectangle_ZeroCropBox_2073) {

    // Arrange

    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<Annot>();

    poppler_annot.annot->getRect() = PDFRectangle(10.0, 20.0, 30.0, 40.0);

    

    PopplerRectangle poppler_rect;



    // Mock _poppler_annot_get_cropbox_and_page to return nullptr

    // Assuming _poppler_annot_get_cropbox_and_page is a function that can be mocked or stubbed

    // For this example, we assume it returns nullptr by default



    // Act

    poppler_annot_get_rectangle(&poppler_annot, &poppler_rect);



    // Assert

    EXPECT_EQ(poppler_rect.x1, 10.0);

    EXPECT_EQ(poppler_rect.y1, 20.0);

    EXPECT_EQ(poppler_rect.x2, 30.0);

    EXPECT_EQ(poppler_rect.y2, 40.0);

}



TEST_F(PopplerAnnotTest_2073, GetRectangle_NegativeCoordinates_2073) {

    // Arrange

    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<Annot>();

    poppler_annot.annot->getRect() = PDFRectangle(-10.0, -20.0, 10.0, 20.0);

    

    PopplerRectangle poppler_rect;



    // Act

    poppler_annot_get_rectangle(&poppler_annot, &poppler_rect);



    // Assert

    EXPECT_EQ(poppler_rect.x1, -10.0);

    EXPECT_EQ(poppler_rect.y1, -20.0);

    EXPECT_EQ(poppler_rect.x2, 10.0);

    EXPECT_EQ(poppler_rect.y2, 20.0);

}



TEST_F(PopplerAnnotTest_2073, GetRectangle_NullPopplerAnnot_2073) {

    // Arrange

    PopplerAnnot* poppler_annot = nullptr;

    PopplerRectangle poppler_rect;



    // Act & Assert

    EXPECT_DEATH(poppler_annot_get_rectangle(poppler_annot, &poppler_rect), "");

}



TEST_F(PopplerAnnotTest_2073, GetRectangle_NullPopplerRect_2073) {

    // Arrange

    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<Annot>();

    poppler_annot.annot->getRect() = PDFRectangle(10.0, 20.0, 30.0, 40.0);

    

    PopplerRectangle* poppler_rect = nullptr;



    // Act & Assert

    EXPECT_DEATH(poppler_annot_get_rectangle(&poppler_annot, poppler_rect), "");

}
