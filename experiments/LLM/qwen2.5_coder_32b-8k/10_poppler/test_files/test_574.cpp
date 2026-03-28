#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_574, GetRotate_DefaultValue_574) {

    EXPECT_EQ(gfxState->getRotate(), 0);

}



TEST_F(GfxStateTest_574, GetRotate_SetValue_574) {

    GfxState state(72.0, 72.0, nullptr, 90, false);

    EXPECT_EQ(state.getRotate(), 90);

}



TEST_F(GfxStateTest_574, GetHDPI_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getHDPI(), 72.0);

}



TEST_F(GfxStateTest_574, GetVDPI_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getVDPI(), 72.0);

}



TEST_F(GfxStateTest_574, GetCTM_DefaultValue_574) {

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expectedCtm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(ctm, expectedCtm);

}



TEST_F(GfxStateTest_574, GetX1_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getX1(), 0.0);

}



TEST_F(GfxStateTest_574,GetY1_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getY1(), 0.0);

}



TEST_F(GfxStateTest_574,GetX2_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getX2(), 0.0);

}



TEST_F(GfxStateTest_574,GetY2_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getY2(), 0.0);

}



TEST_F(GfxStateTest_574, GetPageWidth_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getPageWidth(), 0.0);

}



TEST_F(GfxStateTest_574, GetPageHeight_DefaultValue_574) {

    EXPECT_DOUBLE_EQ(gfxState->getPageHeight(), 0.0);

}



TEST_F(GfxStateTest_574, SetCTM_ChangesMatrix_574) {

    gfxState->setCTM(2.0, 0.0, 0.0, 3.0, 1.0, 1.0);

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expectedCtm = {2.0, 0.0, 0.0, 3.0, 1.0, 1.0};

    EXPECT_EQ(ctm, expectedCtm);

}



TEST_F(GfxStateTest_574, ConcatCTM_ChangesMatrix_574) {

    gfxState->setCTM(2.0, 0.0, 0.0, 3.0, 1.0, 1.0);

    gfxState->concatCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expectedCtm = {8.0, 6.0, 9.0, 12.0, 17.0, 19.0};

    EXPECT_EQ(ctm, expectedCtm);

}



TEST_F(GfxStateTest_574, GetClipBBox_DefaultValue_574) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, -1e20);

    EXPECT_DOUBLE_EQ(yMin, -1e20);

    EXPECT_DOUBLE_EQ(xMax, 1e20);

    EXPECT_DOUBLE_EQ(yMax, 1e20);

}



TEST_F(GfxStateTest_574, GetTransformedLineWidth_DefaultValue_574) {

    gfxState->setLineWidth(1.0);

    EXPECT_DOUBLE_EQ(gfxState->getTransformedLineWidth(), 1.0);

}
