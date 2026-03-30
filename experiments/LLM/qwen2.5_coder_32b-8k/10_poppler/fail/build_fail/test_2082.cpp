#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "poppler-page.h"



// Mock structure to simulate PopplerAnnotMarkup and Annot for testing purposes.

struct MockPopplerAnnotMarkup : public _PopplerAnnotMarkup {

    std::shared_ptr<AnnotMarkup> annot = std::make_shared<AnnotMarkup>();

};



struct MockAnnotPopup : public Annot {

    void setRect(double x1, double y1, double x2, double y2) override {

        last_x1 = x1;

        last_y1 = y1;

        last_x2 = x2;

        last_y2 = y2;

    }

    double last_x1, last_y1, last_x2, last_y2;

};



TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NonNullRect_Success_2082) {

    MockPopplerAnnotMarkup mock_markup;

    MockAnnotPopup mock_popup;



    mock_markup.annot->setPopup(std::make_unique<MockAnnotPopup>(mock_popup));



    PopplerRectangle rect = {1.0, 2.0, 3.0, 4.0};

    poppler_annot_markup_set_popup_rectangle(reinterpret_cast<PopplerAnnotMarkup*>(&mock_markup), &rect);



    EXPECT_EQ(mock_popup.last_x1, 1.0);

    EXPECT_EQ(mock_popup.last_y1, 2.0);

    EXPECT_EQ(mock_popup.last_x2, 3.0);

    EXPECT_EQ(mock_popup.last_y2, 4.0);

}



TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NullRect_DoNothing_2082) {

    MockPopplerAnnotMarkup mock_markup;

    MockAnnotPopup mock_popup;



    mock_markup.annot->setPopup(std::make_unique<MockAnnotPopup>(mock_popup));



    poppler_annot_markup_set_popup_rectangle(reinterpret_cast<PopplerAnnotMarkup*>(&mock_markup), nullptr);



    EXPECT_EQ(mock_popup.last_x1, 0.0);

    EXPECT_EQ(mock_popup.last_y1, 0.0);

    EXPECT_EQ(mock_popup.last_x2, 0.0);

    EXPECT_EQ(mock_popup.last_y2, 0.0);

}



TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NoPopup_DoNothing_2082) {

    MockPopplerAnnotMarkup mock_markup;



    PopplerRectangle rect = {1.0, 2.0, 3.0, 4.0};

    poppler_annot_markup_set_popup_rectangle(reinterpret_cast<PopplerAnnotMarkup*>(&mock_markup), &rect);

}



TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_BoundaryValues_Success_2082) {

    MockPopplerAnnotMarkup mock_markup;

    MockAnnotPopup mock_popup;



    mock_markup.annot->setPopup(std::make_unique<MockAnnotPopup>(mock_popup));



    PopplerRectangle rect = {-1.0, -2.0, 1000.0, 2000.0};

    poppler_annot_markup_set_popup_rectangle(reinterpret_cast<PopplerAnnotMarkup*>(&mock_markup), &rect);



    EXPECT_EQ(mock_popup.last_x1, -1.0);

    EXPECT_EQ(mock_popup.last_y1, -2.0);

    EXPECT_EQ(mock_popup.last_x2, 1000.0);

    EXPECT_EQ(mock_popup.last_y2, 2000.0);

}
