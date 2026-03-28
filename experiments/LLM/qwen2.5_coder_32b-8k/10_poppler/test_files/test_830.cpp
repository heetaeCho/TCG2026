#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_830 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object dictObject;

    const Object* obj;



    void SetUp() override {

        // Initialize necessary objects for constructing AnnotLine

        // For simplicity, assuming these are already initialized in the test environment.

        docA = nullptr;  // Replace with actual initialization if needed

        obj = nullptr;   // Replace with actual initialization if needed

    }



    AnnotLine createAnnotLine() {

        return AnnotLine(docA, &dictObject, obj);

    }

};



TEST_F(AnnotLineTest_830, DefaultIntent_830) {

    AnnotLine annotLine = createAnnotLine();

    EXPECT_EQ(annotLine.getIntent(), AnnotLineIntent::intentUnknown); // Assuming default intent is unknown

}



TEST_F(AnnotLineTest_830, SetAndGetIntent_830) {

    AnnotLine annotLine = createAnnotLine();

    annotLine.setIntent(AnnotLineIntent::intentMeasurement);

    EXPECT_EQ(annotLine.getIntent(), AnnotLineIntent::intentMeasurement);

}



TEST_F(AnnotLineTest_830, SetAndGetVertices_830) {

    AnnotLine annotLine = createAnnotLine();

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annotLine.setVertices(x1, y1, x2, y2);

    EXPECT_EQ(annotLine.getX1(), x1);

    EXPECT_EQ(annotLine.getY1(), y1);

    EXPECT_EQ(annotLine.getX2(), x2);

    EXPECT_EQ(annotLine.getY2(), y2);

}



TEST_F(AnnotLineTest_830, BoundaryVertices_830) {

    AnnotLine annotLine = createAnnotLine();

    double x1 = -1.0, y1 = 0.0, x2 = 0.0, y2 = 1.0;

    annotLine.setVertices(x1, y1, x2, y2);

    EXPECT_EQ(annotLine.getX1(), x1);

    EXPECT_EQ(annotLine.getY1(), y1);

    EXPECT_EQ(annotLine.getX2(), x2);

    EXPECT_EQ(annotLine.getY2(), y2);

}



TEST_F(AnnotLineTest_830, SetAndGetStartEndStyle_830) {

    AnnotLine annotLine = createAnnotLine();

    AnnotLineEndingStyle startStyle = AnnotLineEndingStyle::endingCircle;

    AnnotLineEndingStyle endStyle = AnnotLineEndingStyle::endingSquare;

    annotLine.setStartEndStyle(startStyle, endStyle);

    EXPECT_EQ(annotLine.getStartStyle(), startStyle);

    EXPECT_EQ(annotLine.getEndStyle(), endStyle);

}



TEST_F(AnnotLineTest_830, SetAndGetInteriorColor_830) {

    AnnotLine annotLine = createAnnotLine();

    std::unique_ptr<AnnotColor> color(new AnnotColor());

    annotLine.setInteriorColor(std::move(color));

    EXPECT_NE(annotLine.getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_830, SetAndGetLeaderLineLength_830) {

    AnnotLine annotLine = createAnnotLine();

    double length = 5.0;

    annotLine.setLeaderLineLength(length);

    EXPECT_EQ(annotLine.getLeaderLineLength(), length);

}



TEST_F(AnnotLineTest_830, SetAndGetLeaderLineExtension_830) {

    AnnotLine annotLine = createAnnotLine();

    double extension = 10.0;

    annotLine.setLeaderLineExtension(extension);

    EXPECT_EQ(annotLine.getLeaderLineExtension(), extension);

}



TEST_F(AnnotLineTest_830, SetAndGetCaption_830) {

    AnnotLine annotLine = createAnnotLine();

    bool caption = true;

    annotLine.setCaption(caption);

    EXPECT_EQ(annotLine.getCaption(), caption);

}
