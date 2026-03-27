#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_836 : public ::testing::Test {

protected:

    void SetUp() override {

        coord1 = std::make_unique<AnnotCoord>(10.5, 20.5);

        annotLine = std::make_unique<AnnotLine>(nullptr, nullptr);

        annotLine->coord1 = std::move(coord1);

    }



    std::unique_ptr<AnnotCoord> coord1;

    std::unique_ptr<AnnotLine> annotLine;

};



TEST_F(AnnotLineTest_836, GetX1_ReturnsCorrectValue_836) {

    EXPECT_DOUBLE_EQ(annotLine->getX1(), 10.5);

}



TEST_F(AnnotLineTest_836, GetY1_ReturnsCorrectValue_836) {

    EXPECT_DOUBLE_EQ(annotLine->getY1(), 20.5);

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetX1_ZeroValue_836) {

    coord1 = std::make_unique<AnnotCoord>(0.0, 20.5);

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getX1(), 0.0);

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetY1_ZeroValue_836) {

    coord1 = std::make_unique<AnnotCoord>(10.5, 0.0);

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getY1(), 0.0);

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetX1_NegativeValue_836) {

    coord1 = std::make_unique<AnnotCoord>(-10.5, 20.5);

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getX1(), -10.5);

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetY1_NegativeValue_836) {

    coord1 = std::make_unique<AnnotCoord>(10.5, -20.5);

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getY1(), -20.5);

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetX1_MaxValue_836) {

    coord1 = std::make_unique<AnnotCoord>(std::numeric_limits<double>::max(), 20.5);

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getX1(), std::numeric_limits<double>::max());

}



TEST_F(AnnotLineTest_836, BoundaryCondition_GetY1_MaxValue_836) {

    coord1 = std::make_unique<AnnotCoord>(10.5, std::numeric_limits<double>::max());

    annotLine->coord1 = std::move(coord1);

    EXPECT_DOUBLE_EQ(annotLine->getY1(), std::numeric_limits<double>::max());

}
