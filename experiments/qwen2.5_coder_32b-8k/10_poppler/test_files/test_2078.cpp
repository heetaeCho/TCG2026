#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-page.h"



// Mock class for PDFDoc

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



// Test fixture for poppler_annot_markup_set_popup

class PopplerAnnotMarkupSetPopupTest_2078 : public ::testing::Test {

protected:

    void SetUp() override {

        pdf_doc = std::make_unique<MockPDFDoc>();

        popup_rect = new PopplerRectangle{0, 0, 100, 100};

        poppler_annot = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

    }



    void TearDown() override {

        g_free(poppler_annot);

        delete popup_rect;

    }



    std::unique_ptr<MockPDFDoc> pdf_doc;

    PopplerRectangle* popup_rect;

    PopplerAnnotMarkup* poppler_annot;

};



TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetValidPopupRect_2078) {

    EXPECT_NO_THROW(poppler_annot_markup_set_popup(poppler_annot, popup_rect));

}



TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetNullPopupRect_2078) {

    EXPECT_NO_THROW(poppler_annot_markup_set_popup(poppler_annot, nullptr));

}



TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetInvalidPopplerAnnot_2078) {

    PopplerRectangle* invalid_rect = new PopplerRectangle{0, 0, 100, 100};

    EXPECT_NO_THROW(poppler_annot_markup_set_popup(nullptr, invalid_rect));

    delete invalid_rect;

}



TEST_F(PopplerAnnotMarkupSetPopupTest_2078, SetBoundaryConditionRect_2078) {

    PopplerRectangle* boundary_rect = new PopplerRectangle{INT_MIN, INT_MIN, INT_MAX, INT_MAX};

    EXPECT_NO_THROW(poppler_annot_markup_set_popup(poppler_annot, boundary_rect));

    delete boundary_rect;

}
