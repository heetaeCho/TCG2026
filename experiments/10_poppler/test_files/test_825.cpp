#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_825 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    AnnotLine* annotLine;



    void SetUp() override {

        doc = new PDFDoc();  // Assuming a default constructor exists

        annotLine = new AnnotLine(doc, &rect);

    }



    void TearDown() override {

        delete annotLine;

        delete doc;

    }

};



TEST_F(AnnotLineTest_825, GetEndStyle_DefaultValue_825) {

    // Assuming default value is AnnotLineEndingStyle::None

    EXPECT_EQ(annotLine->getEndStyle(), AnnotLineEndingStyle::None);

}



TEST_F(AnnotLineTest_825, SetStartEndStyleAndGetStyles_825) {

    AnnotLineEndingStyle startStyle = AnnotLineEndingStyle::Circle;

    AnnotLineEndingStyle endStyle = AnnotLineEndingStyle::Square;



    annotLine->setStartEndStyle(startStyle, endStyle);



    EXPECT_EQ(annotLine->getStartStyle(), startStyle);

    EXPECT_EQ(annotLine->getEndStyle(), endStyle);

}



TEST_F(AnnotLineTest_825, GetInteriorColor_DefaultValue_825) {

    // Assuming default value is nullptr

    EXPECT_EQ(annotLine->getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_825, SetAndGetInteriorColor_825) {

    auto color = std::make_unique<AnnotColor>();

    annotLine->setInteriorColor(std::move(color));



    // The original unique_ptr is now moved to the object, so we need a new one for comparison

    auto expectedColor = std::make_unique<AnnotColor>();



    EXPECT_EQ(*annotLine->getInteriorColor(), *expectedColor);

}



TEST_F(AnnotLineTest_825, GetLeaderLineLength_DefaultValue_825) {

    // Assuming default value is 0.0

    EXPECT_DOUBLE_EQ(annotLine->getLeaderLineLength(), 0.0);

}



TEST_F(AnnotLineTest_825, SetAndGetLeaderLineLength_825) {

    double leaderLineLength = 10.5;

    annotLine->setLeaderLineLength(leaderLineLength);



    EXPECT_DOUBLE_EQ(annotLine->getLeaderLineLength(), leaderLineLength);

}



TEST_F(AnnotLineTest_825, GetLeaderLineExtension_DefaultValue_825) {

    // Assuming default value is 0.0

    EXPECT_DOUBLE_EQ(annotLine->getLeaderLineExtension(), 0.0);

}



TEST_F(AnnotLineTest_825, SetAndGetLeaderLineExtension_825) {

    double leaderLineExtension = 5.2;

    annotLine->setLeaderLineExtension(leaderLineExtension);



    EXPECT_DOUBLE_EQ(annotLine->getLeaderLineExtension(), leaderLineExtension);

}



TEST_F(AnnotLineTest_825, GetCaption_DefaultValue_825) {

    // Assuming default value is false

    EXPECT_FALSE(annotLine->getCaption());

}



TEST_F(AnnotLineTest_825, SetAndGetCaption_825) {

    bool caption = true;

    annotLine->setCaption(caption);



    EXPECT_EQ(annotLine->getCaption(), caption);

}



TEST_F(AnnotLineTest_825, GetIntent_DefaultValue_825) {

    // Assuming default value is AnnotLineIntent::Unknown

    EXPECT_EQ(annotLine->getIntent(), AnnotLineIntent::Unknown);

}



TEST_F(AnnotLineTest_825, SetAndGetIntent_825) {

    AnnotLineIntent intent = AnnotLineIntent::Arrow;

    annotLine->setIntent(intent);



    EXPECT_EQ(annotLine->getIntent(), intent);

}



TEST_F(AnnotLineTest_825, GetLeaderLineOffset_DefaultValue_825) {

    // Assuming default value is 0.0

    EXPECT_DOUBLE_EQ(annotLine->getLeaderLineOffset(), 0.0);

}



TEST_F(AnnotLineTest_825, SetAndGetVertices_825) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annotLine->setVertices(x1, y1, x2, y2);



    EXPECT_DOUBLE_EQ(annotLine->getX1(), x1);

    EXPECT_DOUBLE_EQ(annotLine->getY1(), y1);

    EXPECT_DOUBLE_EQ(annotLine->getX2(), x2);

    EXPECT_DOUBLE_EQ(annotLine->getY2(), y2);

}
