#include <gtest/gtest.h>

#include "poppler/Annot.h"



class AnnotBorderArrayTest_751 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotBorderArray> annotBorderArray;



    void SetUp() override {

        annotBorderArray = std::make_unique<AnnotBorderArray>();

    }

};



TEST_F(AnnotBorderArrayTest_751, SetVerticalCorner_NormalOperation_751) {

    double testValue = 2.0;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_751, SetVerticalCorner_BoundaryCondition_Zero_751) {

    double testValue = 0.0;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_751, SetVerticalCorner_BoundaryCondition_Negative_751) {

    double testValue = -1.0;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_751, GetVerticalCorner_DefaultValue_751) {

    // Assuming default value is 0.0 as no constructor initializer list is provided

    EXPECT_EQ(annotBorderArray->getVerticalCorner(), 0.0);

}
