#include <gtest/gtest.h>

#include "Annot.h"



class AnnotCalloutMultiLineTest_741 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotCalloutMultiLine> annot;



    void SetUp() override {

        // Initialize with sample coordinates

        annot = std::make_unique<AnnotCalloutMultiLine>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    }

};



TEST_F(AnnotCalloutMultiLineTest_741, GetX3_ReturnsCorrectValue_741) {

    EXPECT_DOUBLE_EQ(annot->getX3(), 5.0);

}



TEST_F(AnnotCalloutMultiLineTest_741, BoundaryCondition_GetX3_ZeroCoordinates_741) {

    AnnotCalloutMultiLine zeroCoordAnnot(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(zeroCoordAnnot.getX3(), 0.0);

}



TEST_F(AnnotCalloutMultiLineTest_741, BoundaryCondition_GetX3_NegativeCoordinates_741) {

    AnnotCalloutMultiLine negativeCoordAnnot(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);

    EXPECT_DOUBLE_EQ(negativeCoordAnnot.getX3(), -5.0);

}
