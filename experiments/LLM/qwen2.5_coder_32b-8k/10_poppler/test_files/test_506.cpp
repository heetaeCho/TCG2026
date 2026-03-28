#include <gtest/gtest.h>

#include "GfxState.h"



class GfxShadingTest : public ::testing::Test {

protected:

    GfxShadingTest() 

        : shading(new GfxShading(1)) // Assuming type 1 for testing purposes

    {

        // Set up some known bounding box values for testing

        shading->bbox_xMin = -10.5;

        shading->bbox_yMin = -20.3;

        shading->bbox_xMax = 100.0;

        shading->bbox_yMax = 200.0;

    }



    ~GfxShadingTest() override {

        delete shading;

    }



    GfxShading* shading;

};



TEST_F(GfxShadingTest_506, GetBBox_ReturnsCorrectValues_506) {

    double xMinA = 0, yMinA = 0, xMaxA = 0, yMaxA = 0;

    shading->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_DOUBLE_EQ(xMinA, -10.5);

    EXPECT_DOUBLE_EQ(yMinA, -20.3);

    EXPECT_DOUBLE_EQ(xMaxA, 100.0);

    EXPECT_DOUBLE_EQ(yMaxA, 200.0);

}



TEST_F(GfxShadingTest_506, GetBBox_OutputsZeroForNullPointers_506) {

    double xMinA = 1, yMinA = 1, xMaxA = 1, yMaxA = 1;

    shading->getBBox(nullptr, &yMinA, &xMaxA, &yMaxA);

    EXPECT_DOUBLE_EQ(yMinA, -20.3);

    EXPECT_DOUBLE_EQ(xMaxA, 100.0);

    EXPECT_DOUBLE_EQ(yMaxA, 200.0);



    shading->getBBox(&xMinA, nullptr, &xMaxA, &yMaxA);

    EXPECT_DOUBLE_EQ(xMinA, -10.5);

    EXPECT_DOUBLE_EQ(xMaxA, 100.0);

    EXPECT_DOUBLE_EQ(yMaxA, 200.0);



    shading->getBBox(&xMinA, &yMinA, nullptr, &yMaxA);

    EXPECT_DOUBLE_EQ(xMinA, -10.5);

    EXPECT_DOUBLE_EQ(yMinA, -20.3);

    EXPECT_DOUBLE_EQ(yMaxA, 200.0);



    shading->getBBox(&xMinA, &yMinA, &xMaxA, nullptr);

    EXPECT_DOUBLE_EQ(xMinA, -10.5);

    EXPECT_DOUBLE_EQ(yMinA, -20.3);

    EXPECT_DOUBLE_EQ(xMaxA, 100.0);



    shading->getBBox(nullptr, nullptr, nullptr, nullptr);

    // No changes expected if all pointers are null

}
