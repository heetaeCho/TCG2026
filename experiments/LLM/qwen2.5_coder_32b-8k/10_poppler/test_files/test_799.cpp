#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotMarkupTest_799 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotMarkup> annotMarkup;



    void SetUp() override {

        // Assuming a mock PDFDoc and PDFRectangle for construction

        PDFDoc* docA = nullptr; // Mock or real object as required by the constructor

        PDFRectangle* rect = nullptr; // Mock or real object as required by the constructor

        annotMarkup = std::make_unique<AnnotMarkup>(docA, rect);

    }

};



TEST_F(AnnotMarkupTest_799, GetOpacity_DefaultValue_799) {

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 0.0); // Assuming default opacity is 0

}



TEST_F(AnnotMarkupTest_799, SetAndGetOpacity_NormalOperation_799) {

    annotMarkup->setOpacity(0.5);

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 0.5);



    annotMarkup->setOpacity(1.0);

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 1.0);



    annotMarkup->setOpacity(0.0);

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 0.0);

}



TEST_F(AnnotMarkupTest_799, SetAndGetOpacity_BoundaryConditions_799) {

    annotMarkup->setOpacity(-0.1); // Assuming negative opacity is clamped to 0

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 0.0);



    annotMarkup->setOpacity(1.1); // Assuming opacity above 1 is clamped to 1

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 1.0);

}
