#include <gtest/gtest.h>

#include "Annot.h"



class AnnotBorderArrayTest_752 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotBorderArray> annotBorderArray;



    void SetUp() override {

        annotBorderArray = std::make_unique<AnnotBorderArray>();

    }

};



TEST_F(AnnotBorderArrayTest_752, InitialHorizontalCornerValueIsZero_752) {

    EXPECT_EQ(annotBorderArray->getHorizontalCorner(), 0.0);

}



TEST_F(AnnotBorderArrayTest_752, SetHorizontalCornerUpdatesValue_752) {

    annotBorderArray->setHorizontalCorner(10.5);

    EXPECT_EQ(annotBorderArray->getHorizontalCorner(), 10.5);

}



TEST_F(AnnotBorderArrayTest_752, BoundaryCondition_SetHorizontalCornerToZero_752) {

    annotBorderArray->setHorizontalCorner(0.0);

    EXPECT_EQ(annotBorderArray->getHorizontalCorner(), 0.0);

}



TEST_F(AnnotBorderArrayTest_752, BoundaryCondition_SetHorizontalCornerToNegativeValue_752) {

    annotBorderArray->setHorizontalCorner(-5.0);

    EXPECT_EQ(annotBorderArray->getHorizontalCorner(), -5.0);

}
