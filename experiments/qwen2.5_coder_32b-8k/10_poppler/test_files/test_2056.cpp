#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "PDFRectangle.h"

#include "poppler-page.h"

#include "poppler-private.h"



class PopplerAnnotCircleTest_2056 : public ::testing::Test {

protected:

    PopplerDocument *doc;

    PopplerRectangle rect;



    void SetUp() override {

        doc = new _PopplerDocument();

        rect.x1 = 10;

        rect.y1 = 20;

        rect.x2 = 30;

        rect.y2 = 40;

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(PopplerAnnotCircleTest_2056, NormalOperation_2056) {

    PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotCircleTest_2056, BoundaryConditions_ZeroSize_2056) {

    rect.x1 = 0;

    rect.y1 = 0;

    rect.x2 = 0;

    rect.y2 = 0;



    PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnegCircleTest_2056, BoundaryConditions_MaxInt_2056) {

    rect.x1 = INT_MIN;

    rect.y1 = INT_MIN;

    rect.x2 = INT_MAX;

    rect.y2 = INT_MAX;



    PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotCircleTest_2056, ExceptionalCase_NullDoc_2056) {

    doc = nullptr;

    PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);

    EXPECT_EQ(annot, nullptr);

}



TEST_F(PopplerAnnotCircleTest_2056, ExceptionalCase_NullRect_2056) {

    rect = {};

    PopplerAnnot *annot = poppler_annot_circle_new(doc, nullptr);

    EXPECT_EQ(annot, nullptr);

}
