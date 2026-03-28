#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



class AnnotPolygonTest_846 : public ::testing::Test {

protected:

    PDFDoc* docA;

    PDFRectangle rect;

    Object dictObject, obj;

    std::unique_ptr<AnnotPolygon> annotPolygon;



    void SetUp() override {

        docA = new PDFDoc();

        annotPolygon = std::make_unique<AnnotPolygon>(docA, &rect, AnnotSubtype::Square);

    }



    void TearDown() override {

        delete docA;

    }

};



TEST_F(AnnotPolygonTest_846, GetStartStyle_DefaultValue_846) {

    // Assuming default value is NoEnding

    EXPECT_EQ(annotPolygon->getStartStyle(), AnnotLineEndingStyle::NoEnding);

}



TEST_F(AnnotPolygonTest_846, SetStartEndStyle_StartStyleUpdated_846) {

    annotPolygon->setStartEndStyle(AnnotLineEndingStyle::Square, AnnotLineEndingStyle::Diamond);

    EXPECT_EQ(annotPolygon->getStartStyle(), AnnotLineEndingStyle::Square);

}



TEST_F(AnnotPolygonTest_846, SetStartEndStyle_EndStyleUpdated_846) {

    annotPolygon->setStartEndStyle(AnnotLineEndingStyle::Circle, AnnotLineEndingStyle::Diamond);

    EXPECT_EQ(annotPolygon->getEndStyle(), AnnotLineEndingStyle::Diamond);

}



TEST_F(AnnotPolygonTest_846, SetType_TypeUpdated_846) {

    annotPolygon->setType(AnnotSubtype::Circle);

    EXPECT_EQ(annotPolygon->getType(), AnnotSubtype::Circle);

}
