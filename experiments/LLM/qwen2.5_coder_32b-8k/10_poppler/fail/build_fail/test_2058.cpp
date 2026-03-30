#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "PDFRectangle.h"

#include "poppler-private.h"



class PopplerAnnotTest_2058 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary test setup here if needed.

        doc = new _PopplerDocument();

        rect = new _PopplerRectangle();

    }



    void TearDown() override {

        // Clean up resources after each test.

        delete doc;

        delete rect;

    }



    _PopplerDocument* doc;

    _PopplerRectangle* rect;

};



TEST_F(PopplerAnnotTest_2058, CreateSquareAnnotation_NormalOperation_2058) {

    rect->x1 = 0; rect->y1 = 0; rect->x2 = 100; rect->y2 = 100;

    PopplerAnnot* annot = poppler_annot_square_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(rect));

    ASSERT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2058, CreateSquareAnnotation_BoundaryConditions_ZeroSize_2058) {

    rect->x1 = 0; rect->y1 = 0; rect->x2 = 0; rect->y2 = 0;

    PopplerAnnot* annot = poppler_annot_square_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(rect));

    ASSERT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2058, CreateSquareAnnotation_BoundaryConditions_NegativeCoordinates_2058) {

    rect->x1 = -50; rect->y1 = -50; rect->x2 = 50; rect->y2 = 50;

    PopplerAnnot* annot = poppler_annot_square_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(rect));

    ASSERT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2058, CreateSquareAnnotation_ExceptionalCase_NullDocument_2058) {

    rect->x1 = 0; rect->y1 = 0; rect->x2 = 100; rect->y2 = 100;

    PopplerAnnot* annot = poppler_annot_square_new(nullptr, reinterpret_cast<PopplerRectangle*>(rect));

    ASSERT_EQ(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2058, CreateSquareAnnotation_ExceptionalCase_NullRectangle_2058) {

    PopplerAnnot* annot = poppler_annot_square_new(reinterpret_cast<PopplerDocument*>(doc), nullptr);

    ASSERT_EQ(annot, nullptr);

}
