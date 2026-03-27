#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "poppler-annot.cc"

}



class PopplerAnnotTest_2061 : public ::testing::Test {

protected:

    virtual void SetUp() {

        document = new _PopplerDocument();

        rect.x1 = 1;

        rect.y1 = 2;

        rect.x2 = 3;

        rect.y2 = 4;

    }



    virtual void TearDown() {

        delete document;

    }



    _PopplerDocument *document;

    _PopplerRectangle rect;

};



TEST_F(PopplerAnnotTest_2061, CreateValidStampAnnotation_2061) {

    PopplerAnnot *annot = poppler_annot_stamp_new(document, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2061, CreateStampWithZeroSizedRectangle_2061) {

    rect.x1 = 0;

    rect.y1 = 0;

    rect.x2 = 0;

    rect.y2 = 0;



    PopplerAnnot *annot = poppler_annot_stamp_new(document, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnegTest_2061, CreateStampWithNegativeCoordinates_2061) {

    rect.x1 = -1;

    rect.y1 = -2;

    rect.x2 = -3;

    rect.y2 = -4;



    PopplerAnnot *annot = poppler_annot_stamp_new(document, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2061, CreateStampWithInvertedCoordinates_2061) {

    rect.x1 = 3;

    rect.y1 = 4;

    rect.x2 = 1;

    rect.y2 = 2;



    PopplerAnnot *annot = poppler_annot_stamp_new(document, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2061, CreateStampWithLargeCoordinates_2061) {

    rect.x1 = 10000;

    rect.y1 = 20000;

    rect.x2 = 30000;

    rect.y2 = 40000;



    PopplerAnnot *annot = poppler_annot_stamp_new(document, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2061, CreateStampWithNullDocument_2061) {

    PopplerAnnot *annot = poppler_annot_stamp_new(nullptr, &rect);

    EXPECT_EQ(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2061, CreateStampWithNullRectangle_2061) {

    PopplerAnnot *annot = poppler_annot_stamp_new(document, nullptr);

    EXPECT_EQ(annot, nullptr);

}
