#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.h"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"

#include "./TestProjects/poppler/glib/poppler-page.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



class PopplerAnnotInkTest_2135 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new _PopplerDocument();

        rect = new _PopplerRectangle{0, 0, 100, 100};

    }



    void TearDown() override {

        delete doc;

        delete rect;

    }



    _PopplerDocument* doc;

    _PopplerRectangle* rect;

};



TEST_F(PopplerAnnotInkTest_2135, CreateValidAnnotation_2135) {

    PopplerAnnot* annot = poppler_annot_ink_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(rect));

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotInkTest_2135, CreateAnnotationWithZeroSizedRect_2135) {

    _PopplerRectangle zeroRect{0, 0, 0, 0};

    PopplerAnnot* annot = poppler_annot_ink_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(&zeroRect));

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotInkTest_2135, CreateAnnotationWithNegativeRect_2135) {

    _PopplerRectangle negativeRect{-50, -50, 50, 50};

    PopplerAnnot* annot = poppler_annot_ink_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(&negativeRect));

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotInkTest_2135, CreateAnnotationWithLargerX2ThanX1_2135) {

    _PopplerRectangle largerX2Rect{0, 0, -100, 100};

    PopplerAnnot* annot = poppler_annot_ink_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(&largerX2Rect));

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotInkTest_2135, CreateAnnotationWithLargerY2ThanY1_2135) {

    _PopplerRectangle largerY2Rect{0, 0, 100, -100};

    PopplerAnnot* annot = poppler_annot_ink_new(reinterpret_cast<PopplerDocument*>(doc), reinterpret_cast<PopplerRectangle*>(&largerY2Rect));

    EXPECT_NE(annot, nullptr);

}
