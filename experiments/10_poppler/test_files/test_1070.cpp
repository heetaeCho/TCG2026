#include <gtest/gtest.h>

#include "OutputDev.h"



class OutputDevTest_1070 : public ::testing::Test {

protected:

    OutputDev* outputDev;



    void SetUp() override {

        outputDev = new OutputDev();

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_DefaultReturn_1070) {

    // Arrange

    GfxState* state = nullptr; // Assuming null is acceptable as per the signature comment

    GfxAxialShading* shading = nullptr; // Assuming null is acceptable as per the signature comment



    // Act

    bool result = outputDev->axialShadedSupportExtend(state, shading);



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_BoundaryNullState_1070) {

    // Arrange

    GfxState* state = nullptr;

    GfxAxialShading* shading = new GfxAxialShading(); // Assuming we can create a valid object



    // Act

    bool result = outputDev->axialShadedSupportExtend(state, shading);



    // Assert

    EXPECT_FALSE(result);



    delete shading; // Clean up

}



TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_BoundaryNullShading_1070) {

    // Arrange

    GfxState* state = new GfxState(); // Assuming we can create a valid object

    GfxAxialShading* shading = nullptr;



    // Act

    bool result = outputDev->axialShadedSupportExtend(state, shading);



    // Assert

    EXPECT_FALSE(result);



    delete state; // Clean up

}



TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_BoundaryNullBoth_1070) {

    // Arrange

    GfxState* state = nullptr;

    GfxAxialShading* shading = nullptr;



    // Act

    bool result = outputDev->axialShadedSupportExtend(state, shading);



    // Assert

    EXPECT_FALSE(result);

}
