#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *state;



    void SetUp() override {

        state = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_620, GetClipBBox_DefaultValues_620) {

    double xMin, yMin, xMax, yMax;

    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, 0.0);

    EXPECT_EQ(yMin, 0.0);

    EXPECT_EQ(xMax, 0.0);

    EXPECT_EQ(yMax, 0.0);

}



TEST_F(GfxStateTest_620, GetClipBBox_AfterClipToRect_620) {

    double xMin, yMin, xMax, yMax;

    state->clipToRect(10.0, 20.0, 30.0, 40.0);

    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, 10.0);

    EXPECT_EQ(yMin, 20.0);

    EXPECT_EQ(xMax, 30.0);

    EXPECT_EQ(yMax, 40.0);

}



TEST_F(GfxStateTest_620, GetClipBBox_AfterMultipleClips_620) {

    double xMin, yMin, xMax, yMax;

    state->clipToRect(10.0, 20.0, 50.0, 70.0);

    state->clipToRect(20.0, 30.0, 40.0, 60.0);

    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, 20.0);

    EXPECT_EQ(yMin, 30.0);

    EXPECT_EQ(xMax, 40.0);

    EXPECT_EQ(yMax, 60.0);

}



TEST_F(GfxStateTest_620, GetClipBBox_BoundaryConditions_620) {

    double xMin, yMin, xMax, yMax;

    state->clipToRect(0.0, 0.0, 1.0, 1.0);

    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, 0.0);

    EXPECT_EQ(yMin, 0.0);

    EXPECT_EQ(xMax, 1.0);

    EXPECT_EQ(yMax, 1.0);



    state->clipToRect(-1.0, -1.0, 2.0, 2.0);

    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, -1.0);

    EXPECT_EQ(yMin, -1.0);

    EXPECT_EQ(xMax, 2.0);

    EXPECT_EQ(yMax, 2.0);

}



TEST_F(GfxStateTest_620, GetClipBBox_RestoreAfterClip_620) {

    double xMin, yMin, xMax, yMax;

    state->clipToRect(10.0, 20.0, 30.0, 40.0);

    GfxState *savedState = state->save();

    state->clipToRect(15.0, 25.0, 25.0, 35.0);

    state->restore();



    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, 10.0);

    EXPECT_EQ(yMin, 20.0);

    EXPECT_EQ(xMax, 30.0);

    EXPECT_EQ(yMax, 40.0);



    delete savedState;

}
