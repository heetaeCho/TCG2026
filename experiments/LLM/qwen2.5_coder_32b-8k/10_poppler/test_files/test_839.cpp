#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"



using namespace testing;



class AnnotLineTest_839 : public ::testing::Test {

protected:

    void SetUp() override {

        coord2 = std::make_unique<AnnotCoord>(0.0, 5.0);

        annotLine = new AnnotLine(nullptr, nullptr);

        annotLine->coord2 = std::move(coord2);

    }



    void TearDown() override {

        delete annotLine;

    }



    std::unique_ptr<AnnotCoord> coord2;

    AnnotLine* annotLine;

};



TEST_F(AnnotLineTest_839, GetY2_ReturnsCorrectValue_839) {

    EXPECT_EQ(annotLine->getY2(), 5.0);

}



TEST_F(AnnotLineTest_839, GetY2_BoundaryCondition_Zero_839) {

    coord2 = std::make_unique<AnnotCoord>(0.0, 0.0);

    annotLine->coord2 = std::move(coord2);

    EXPECT_EQ(annotLine->getY2(), 0.0);

}



TEST_F(AnnotLineTest_839, GetY2_BoundaryCondition_Negative_839) {

    coord2 = std::make_unique<AnnotCoord>(0.0, -5.0);

    annotLine->coord2 = std::move(coord2);

    EXPECT_EQ(annotLine->getY2(), -5.0);

}
