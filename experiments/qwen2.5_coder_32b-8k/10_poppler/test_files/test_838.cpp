#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_838 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotCoord> coord1;

    std::unique_ptr<AnnotCoord> coord2;

    PDFDoc* docA;

    PDFRectangle* rect;



    void SetUp() override {

        coord1 = std::make_unique<AnnotCoord>(0.0, 0.0);

        coord2 = std::make_unique<AnnotCoord>(10.0, 10.0);

        docA = nullptr; // Assuming PDFDoc and PDFRectangle constructors are not relevant for this test

        rect = nullptr;

    }

};



TEST_F(AnnotLineTest_838, GetX2_ReturnsCorrectValue_838) {

    AnnotLine annotLine(docA, rect);

    annotLine.setVertices(coord1->getX(), coord1->getY(), coord2->getX(), coord2->getY());

    EXPECT_DOUBLE_EQ(annotLine.getX2(), 10.0);

}



TEST_F(AnnotLineTest_838, SetAndGetStartEndStyle_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    AnnotLineEndingStyle start = AnnotLineEndingStyle::circle;

    AnnotLineEndingStyle end = AnnotLineEndingStyle::square;

    annotLine.setStartEndStyle(start, end);

    EXPECT_EQ(annotLine.getStartStyle(), start);

    EXPECT_EQ(annotLine.getEndStyle(), end);

}



TEST_F(AnnotLineTest_838, SetAndGetInteriorColor_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    std::unique_ptr<AnnotColor> color = std::make_unique<AnnotColor>();

    annotLine.setInteriorColor(std::move(color));

    EXPECT_NE(annotLine.getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_838, SetAndGetLeaderLineLength_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    double length = 5.0;

    annotLine.setLeaderLineLength(length);

    EXPECT_DOUBLE_EQ(annotLine.getLeaderLineLength(), length);

}



TEST_F(AnnotLineTest_838, SetAndGetLeaderLineExtension_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    double extension = 2.0;

    annotLine.setLeaderLineExtension(extension);

    EXPECT_DOUBLE_EQ(annotLine.getLeaderLineExtension(), extension);

}



TEST_F(AnnotLineTest_838, SetAndGetCaption_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    bool caption = true;

    annotLine.setCaption(caption);

    EXPECT_EQ(annotLine.getCaption(), caption);

}



TEST_F(AnnotLineTest_838, SetAndGetIntent_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    AnnotLineIntent intent = AnnotLineIntent::Arrow;

    annotLine.setIntent(intent);

    EXPECT_EQ(annotLine.getIntent(), intent);

}



TEST_F(AnnotLineTest_838, SetAndGetVertices_CorrectValues_838) {

    AnnotLine annotLine(docA, rect);

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annotLine.setVertices(x1, y1, x2, y2);

    EXPECT_DOUBLE_EQ(annotLine.getX1(), x1);

    EXPECT_DOUBLE_EQ(annotLine.getY1(), y1);

    EXPECT_DOUBLE_EQ(annotLine.getX2(), x2);

    EXPECT_DOUBLE_EQ(annotLine.getY2(), y2);

}



TEST_F(AnnotLineTest_838, BoundaryCondition_SetVertices_ZeroValues_838) {

    AnnotLine annotLine(docA, rect);

    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;

    annotLine.setVertices(x1, y1, x2, y2);

    EXPECT_DOUBLE_EQ(annotLine.getX1(), x1);

    EXPECT_DOUBLE_EQ(annotLine.getY1(), y1);

    EXPECT_DOUBLE_EQ(annotLine.getX2(), x2);

    EXPECT_DOUBLE_EQ(annotLine.getY2(), y2);

}



TEST_F(AnnotLineTest_838, BoundaryCondition_SetLeaderLineLength_ZeroValue_838) {

    AnnotLine annotLine(docA, rect);

    double length = 0.0;

    annotLine.setLeaderLineLength(length);

    EXPECT_DOUBLE_EQ(annotLine.getLeaderLineLength(), length);

}



TEST_F(AnnotLineTest_838, BoundaryCondition_SetLeaderLineExtension_ZeroValue_838) {

    AnnotLine annotLine(docA, rect);

    double extension = 0.0;

    annotLine.setLeaderLineExtension(extension);

    EXPECT_DOUBLE_EQ(annotLine.getLeaderLineExtension(), extension);

}
