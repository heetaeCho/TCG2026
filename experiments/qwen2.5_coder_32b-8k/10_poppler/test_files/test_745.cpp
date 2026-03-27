#include <gtest/gtest.h>

#include "Annot.h"



class AnnotQuadrilateralsTest : public ::testing::Test {

protected:

    std::unique_ptr<AnnotQuadrilateral[]> quads;

    int quadrilateralCount = 3; // Example count



    void SetUp() override {

        quads = std::make_unique<AnnotQuadrilateral[]>(quadrilateralCount);

        // Initialize quads if necessary

    }

};



TEST_F(AnnotQuadrilateralsTest_745, GetQuadrilateralsLength_ReturnsCorrectValue_745) {

    AnnotQuadrilaterals annotQuads(std::move(quads), quadrilateralCount);

    EXPECT_EQ(annotQuads.getQuadrilateralsLength(), quadrilateralCount);

}



TEST_F(AnnotQuadrilateralsTest_745, GetQuadrilateralsLength_ReturnsZeroForEmptyArray_745) {

    AnnotQuadrilaterals annotQuads(std::make_unique<AnnotQuadrilateral[]>(0), 0);

    EXPECT_EQ(annotQuads.getQuadrilateralsLength(), 0);

}



TEST_F(AnnotQuadrilateralsTest_745, GetQuadrilateralsLength_BoundaryCondition_MaxInt_745) {

    // Assuming quadrilateralsLength is an int and can't exceed INT_MAX

    AnnotQuadrilaterals annotQuads(std::make_unique<AnnotQuadrilateral[]>(INT_MAX), INT_MAX);

    EXPECT_EQ(annotQuads.getQuadrilateralsLength(), INT_MAX);

}



TEST_F(AnnotQuadrilateralsTest_745, GetQuadrilateralsLength_BoundaryCondition_OneElement_745) {

    AnnotQuadrilaterals annotQuads(std::make_unique<AnnotQuadrilateral[]>(1), 1);

    EXPECT_EQ(annotQuads.getQuadrilateralsLength(), 1);

}
