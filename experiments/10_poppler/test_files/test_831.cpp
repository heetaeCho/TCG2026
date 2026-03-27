#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_831 : public ::testing::Test {

protected:

    PDFDoc* docA;

    PDFRectangle rect;

    AnnotLine* annotLine;



    void SetUp() override {

        docA = new PDFDoc();

        annotLine = new AnnotLine(docA, &rect);

    }



    void TearDown() override {

        delete annotLine;

        delete docA;

    }

};



TEST_F(AnnotLineTest_831, GetLeaderLineOffset_DefaultValue_831) {

    EXPECT_EQ(annotLine->getLeaderLineOffset(), 0.0);

}



TEST_F(AnnotLineTest_831, SetAndGetLeaderLineOffset_831) {

    double offset = 5.0;

    annotLine->setLeaderLineLength(offset);

    EXPECT_NE(annotLine->getLeaderLineOffset(), offset); // Leader line length and offset are different properties



    offset = 10.0;

    annotLine->setLeaderLineOffset(offset);

    EXPECT_EQ(annotLine->getLeaderLineOffset(), offset);

}



TEST_F(AnnotLineTest_831, GetLeaderLineOffset_NegativeValue_831) {

    double negativeOffset = -3.5;

    annotLine->setLeaderLineOffset(negativeOffset);

    EXPECT_EQ(annotLine->getLeaderLineOffset(), negativeOffset);

}



TEST_F(AnnotLineTest_831, GetLeaderLineOffset_ZeroValue_831) {

    double zeroOffset = 0.0;

    annotLine->setLeaderLineOffset(zeroOffset);

    EXPECT_EQ(annotLine->getLeaderLineOffset(), zeroOffset);

}
