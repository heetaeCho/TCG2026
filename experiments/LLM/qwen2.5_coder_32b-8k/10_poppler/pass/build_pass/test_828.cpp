#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



class AnnotLineTest_828 : public ::testing::Test {

protected:

    AnnotLine* annotLine;



    void SetUp() override {

        // Assuming PDFDoc and PDFRectangle are available for construction, which they are not in the given code.

        // For testing purposes, we will assume a mock or placeholder constructor is used here.

        annotLine = new AnnotLine(nullptr, nullptr);

    }



    void TearDown() override {

        delete annotLine;

    }

};



TEST_F(AnnotLineTest_828, GetLeaderLineExtension_DefaultValue_828) {

    EXPECT_DOUBLE_EQ(0.0, annotLine->getLeaderLineExtension());

}



TEST_F(AnnotLineTest_828, SetAndGetLeaderLineExtension_NormalOperation_828) {

    double extension = 5.75;

    annotLine->setLeaderLineExtension(extension);

    EXPECT_DOUBLE_EQ(extension, annotLine->getLeaderLineExtension());

}



TEST_F(AnnotLineTest_828, SetAndGetLeaderLineExtension_BoundaryCondition_Zero_828) {

    double extension = 0.0;

    annotLine->setLeaderLineExtension(extension);

    EXPECT_DOUBLE_EQ(extension, annotLine->getLeaderLineExtension());

}



TEST_F(AnnotLineTest_828, SetAndGetLeaderLineExtension_BoundaryCondition_NegativeValue_828) {

    double extension = -1.5;

    annotLine->setLeaderLineExtension(extension);

    EXPECT_DOUBLE_EQ(extension, annotLine->getLeaderLineExtension());

}
