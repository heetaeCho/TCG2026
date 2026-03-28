#include <gtest/gtest.h>

#include "CairoOutputDev.h"

#include "GfxState.h"

#include "GfxAxialShading.h"



class CairoImageOutputDevTest_1746 : public ::testing::Test {

protected:

    CairoImageOutputDev output_dev;

};



TEST_F(CairoImageOutputDevTest_1746, AxialShadedFill_ReturnsTrue_1746) {

    // Arrange

    GfxState state;  // Assuming default constructor is available

    GfxAxialShading shading;  // Assuming default constructor is available

    double tMin = 0.0;

    double tMax = 1.0;



    // Act

    bool result = output_dev.axialShadedFill(&state, &shading, tMin, tMax);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(CairoImageOutputDevTest_1746, AxialShadedFill_BoundaryConditions_1746) {

    // Arrange

    GfxState state;

    GfxAxialShading shading;

    double tMin = 0.0;

    double tMax = 0.0;



    // Act

    bool result = output_dev.axialShadedFill(&state, &shading, tMin, tMax);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(CairoImageOutputDevTest_1746, AxialShadedFill_BoundaryConditions_MaxLessThanMin_1746) {

    // Arrange

    GfxState state;

    GfxAxialShading shading;

    double tMin = 1.0;

    double tMax = 0.0;



    // Act

    bool result = output_dev.axialShadedFill(&state, &shading, tMin, tMax);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(CairoImageOutputDevTest_1746, AxialShadedFill_BoundaryConditions_NegativeValues_1746) {

    // Arrange

    GfxState state;

    GfxAxialShading shading;

    double tMin = -1.0;

    double tMax = -2.0;



    // Act

    bool result = output_dev.axialShadedFill(&state, &shading, tMin, tMax);



    // Assert

    EXPECT_TRUE(result);

}
