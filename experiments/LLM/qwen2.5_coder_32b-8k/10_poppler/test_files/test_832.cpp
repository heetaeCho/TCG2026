#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_832 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    std::unique_ptr<AnnotLine> annotLine;



    void SetUp() override {

        doc = new PDFDoc();

        annotLine = std::make_unique<AnnotLine>(doc, &rect);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotLineTest_832, GetCaptionPos_DefaultValue_832) {

    EXPECT_EQ(annotLine->getCaptionPos(), AnnotLineCaptionPos::defaultPosition);

}



// Assuming AnnotLineCaptionPos has specific values like Top, Bottom, etc.

TEST_F(AnnotLineTest_832, SetAndGetCaptionPos_Top_832) {

    // Assuming there's a method to set caption position

    annotLine->setCaptionPos(AnnotLineCaptionPos::Top);

    EXPECT_EQ(annotLine->getCaptionPos(), AnnotLineCaptionPos::Top);

}



TEST_F(AnnotLineTest_832, SetAndGetCaptionPos_Bottom_832) {

    // Assuming there's a method to set caption position

    annotLine->setCaptionPos(AnnotLineCaptionPos::Bottom);

    EXPECT_EQ(annotLine->getCaptionPos(), AnnotLineCaptionPos::Bottom);

}



TEST_F(AnnotLineTest_832, SetAndGetVertices_832) {

    double x1 = 10.0, y1 = 20.0, x2 = 30.0, y2 = 40.0;

    annotLine->setVertices(x1, y1, x2, y2);

    EXPECT_EQ(annotLine->getX1(), x1);

    EXPECT_EQ(annotLine->getY1(), y1);

    EXPECT_EQ(annotLine->getX2(), x2);

    EXPECT_EQ(annotLine->getY2(), y2);

}



TEST_F(AnnotLineTest_832, SetAndGetStartEndStyle_832) {

    AnnotLineEndingStyle start = AnnotLineEndingStyle::Square;

    AnnotLineEndingStyle end = AnnotLineEndingStyle::Circle;

    annotLine->setStartEndStyle(start, end);

    EXPECT_EQ(annotLine->getStartStyle(), start);

    EXPECT_EQ(annotLine->getEndStyle(), end);

}



TEST_F(AnnotLineTest_832, SetAndGetInteriorColor_832) {

    auto color = std::make_unique<AnnotColor>(1.0, 0.5, 0.0);

    annotLine->setInteriorColor(std::move(color));

    const AnnotColor* interiorColor = annotLine->getInteriorColor();

    EXPECT_EQ(interiorColor->getRed(), 1.0);

    EXPECT_EQ(interiorColor->getGreen(), 0.5);

    EXPECT_EQ(interiorColor->getBlue(), 0.0);

}



TEST_F(AnnotLineTest_832, SetAndGetLeaderLineLength_832) {

    double length = 5.5;

    annotLine->setLeaderLineLength(length);

    EXPECT_EQ(annotLine->getLeaderLineLength(), length);

}



TEST_F(AnnotLineTest_832, SetAndGetLeaderLineExtension_832) {

    double extension = 2.0;

    annotLine->setLeaderLineExtension(extension);

    EXPECT_EQ(annotLine->getLeaderLineExtension(), extension);

}



TEST_F(AnnotLineTest_832, SetAndGetCaption_832) {

    bool caption = true;

    annotLine->setCaption(caption);

    EXPECT_EQ(annotLine->getCaption(), caption);

}



TEST_F(AnnotLineTest_832, SetAndGetIntent_832) {

    AnnotLineIntent intent = AnnotLineIntent::MeasureDistance;

    annotLine->setIntent(intent);

    EXPECT_EQ(annotLine->getIntent(), intent);

}
