#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateCurveToTest_663 : public ::testing::Test {
protected:
    GfxState* state;

    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = new GfxState(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        delete state;
    }
};

// Test that curveTo updates curX and curY to the endpoint (x3, y3)
TEST_F(GfxStateCurveToTest_663, CurveToUpdatesCurrentPosition_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test curveTo with all zero control and end points
TEST_F(GfxStateCurveToTest_663, CurveToAllZeros_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test curveTo with negative coordinates
TEST_F(GfxStateCurveToTest_663, CurveToNegativeCoordinates_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(-10.0, -20.0, -30.0, -40.0, -50.0, -60.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), -50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -60.0);
}

// Test curveTo with very large coordinates
TEST_F(GfxStateCurveToTest_663, CurveToLargeCoordinates_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1e10, 1e10, 1e10, 1e10, 1e15, 1e15);

    EXPECT_DOUBLE_EQ(state->getCurX(), 1e15);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e15);
}

// Test curveTo with very small (near-zero) coordinates
TEST_F(GfxStateCurveToTest_663, CurveToVerySmallCoordinates_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1e-15, 1e-15, 1e-15, 1e-15, 1e-15, 1e-15);

    EXPECT_DOUBLE_EQ(state->getCurX(), 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e-15);
}

// Test that curveTo creates a path (isPath returns true after curveTo)
TEST_F(GfxStateCurveToTest_663, CurveToCreatesPath_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    EXPECT_TRUE(state->isPath());
}

// Test that isCurPt returns true after curveTo (there is a current point)
TEST_F(GfxStateCurveToTest_663, CurveToSetsCurPt_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    EXPECT_TRUE(state->isCurPt());
}

// Test multiple curveTo calls in sequence
TEST_F(GfxStateCurveToTest_663, MultipleCurveToCalls_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);

    state->curveTo(7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 11.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 12.0);

    state->curveTo(13.0, 14.0, 15.0, 16.0, 17.0, 18.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 17.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 18.0);
}

// Test curveTo after lineTo
TEST_F(GfxStateCurveToTest_663, CurveToAfterLineTo_663) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->curveTo(150.0, 150.0, 200.0, 200.0, 250.0, 250.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 250.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 250.0);
}

// Test that the path has the correct number of subpaths after curveTo
TEST_F(GfxStateCurveToTest_663, CurveToPathSubpathCount_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    const GfxPath* path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getNumSubpaths(), 1);
}

// Test curveTo where endpoint matches start point (degenerate case)
TEST_F(GfxStateCurveToTest_663, CurveToEndpointMatchesStart_663) {
    state->moveTo(100.0, 200.0);
    state->curveTo(150.0, 250.0, 50.0, 150.0, 100.0, 200.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test curveTo with fractional values
TEST_F(GfxStateCurveToTest_663, CurveToFractionalValues_663) {
    state->moveTo(0.5, 0.5);
    state->curveTo(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);

    EXPECT_DOUBLE_EQ(state->getCurX(), 5.5);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.6);
}

// Test that curveTo only affects curX/curY, not line position
TEST_F(GfxStateCurveToTest_663, CurveToDoesNotAffectLinePosition_663) {
    state->moveTo(10.0, 20.0);
    double lineXBefore = state->getLineX();
    double lineYBefore = state->getLineY();

    state->curveTo(30.0, 40.0, 50.0, 60.0, 70.0, 80.0);

    EXPECT_DOUBLE_EQ(state->getLineX(), lineXBefore);
    EXPECT_DOUBLE_EQ(state->getLineY(), lineYBefore);
}

// Test curveTo where control points are collinear (straight line curve)
TEST_F(GfxStateCurveToTest_663, CurveToCollinearControlPoints_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 30.0);
}

// Test curveTo followed by clearPath resets path state
TEST_F(GfxStateCurveToTest_663, CurveToFollowedByClearPath_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    EXPECT_TRUE(state->isPath());

    state->clearPath();

    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test curveTo with mixed positive and negative control points
TEST_F(GfxStateCurveToTest_663, CurveToMixedSignControlPoints_663) {
    state->moveTo(0.0, 0.0);
    state->curveTo(-10.0, 20.0, 30.0, -40.0, -50.0, 60.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), -50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}
