#include <gtest/gtest.h>

#include "Annot.h"



class AnnotBorderArrayTest : public ::testing::Test {

protected:

    std::unique_ptr<AnnotBorderArray> annotBorderArray;



    void SetUp() override {

        annotBorderArray = std::make_unique<AnnotBorderArray>();

    }

};



TEST_F(AnnotBorderArrayTest_753, DefaultConstructorInitializesVerticalCornerToZero_753) {

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), 0.0);

}



TEST_F(AnnotBorderArrayTest_753, SetVerticalCornerUpdatesValueCorrectly_753) {

    double testValue = 10.5;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_753, SetNegativeVerticalCornerUpdatesValueCorrectly_753) {

    double testValue = -10.5;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_753, SetZeroVerticalCornerUpdatesValueCorrectly_753) {

    double testValue = 0.0;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_753, SetLargeVerticalCornerUpdatesValueCorrectly_753) {

    double testValue = 1e6;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), testValue);

}



TEST_F(AnnotBorderArrayTest_753, SetVerySmallVerticalCornerUpdatesValueCorrectly_753) {

    double testValue = 1e-6;

    annotBorderArray->setVerticalCorner(testValue);

    EXPECT_DOUBLE_EQ(annotBorderArray->getVerticalCorner(), testValue);

}
