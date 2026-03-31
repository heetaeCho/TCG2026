#include <gtest/gtest.h>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateClosePathTest_664 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a page box and a GfxState with reasonable parameters
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test that closePath after moveTo and lineTo updates curX and curY to the start of the subpath
TEST_F(GfxStateClosePathTest_664, ClosePathUpdatesCurXYToSubpathStart_664) {
    // Move to a starting point
    state->moveTo(10.0, 20.0);
    // Draw lines to form an open path
    state->lineTo(30.0, 40.0);
    state->lineTo(50.0, 60.0);

    // Before closing, curX and curY should be at the last lineTo point
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);

    // Close the path - should return to the start of the subpath
    state->closePath();

    // After closing, curX and curY should be at the moveTo point (start of subpath)
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test closePath with a simple triangle (moveTo + two lineTo + closePath)
TEST_F(GfxStateClosePathTest_664, ClosePathTriangle_664) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(50.0, 100.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test closePath with negative coordinates
TEST_F(GfxStateClosePathTest_664, ClosePathNegativeCoordinates_664) {
    state->moveTo(-50.0, -100.0);
    state->lineTo(50.0, 100.0);
    state->lineTo(200.0, -50.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), -50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -100.0);
}

// Test closePath with curveTo
TEST_F(GfxStateClosePathTest_664, ClosePathAfterCurveTo_664) {
    state->moveTo(10.0, 10.0);
    state->curveTo(20.0, 20.0, 30.0, 30.0, 40.0, 40.0);

    // Before close, curX/curY should be at the end of the curve
    EXPECT_DOUBLE_EQ(state->getCurX(), 40.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);

    state->closePath();

    // After close, should return to the moveTo point
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 10.0);
}

// Test closePath when path is already at starting point (degenerate close)
TEST_F(GfxStateClosePathTest_664, ClosePathAlreadyAtStart_664) {
    state->moveTo(25.0, 75.0);
    state->lineTo(100.0, 200.0);
    state->lineTo(25.0, 75.0); // Return to start manually

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 25.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 75.0);
}

// Test closePath with floating-point coordinates
TEST_F(GfxStateClosePathTest_664, ClosePathFloatingPoint_664) {
    state->moveTo(1.23456789, 9.87654321);
    state->lineTo(100.111, 200.222);
    state->lineTo(300.333, 400.444);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 1.23456789);
    EXPECT_DOUBLE_EQ(state->getCurY(), 9.87654321);
}

// Test closePath with zero coordinates
TEST_F(GfxStateClosePathTest_664, ClosePathZeroCoordinates_664) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test closePath with very large coordinates
TEST_F(GfxStateClosePathTest_664, ClosePathLargeCoordinates_664) {
    state->moveTo(1e10, 1e10);
    state->lineTo(2e10, 3e10);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e10);
}

// Test closePath with very small (near-zero) coordinates
TEST_F(GfxStateClosePathTest_664, ClosePathSmallCoordinates_664) {
    state->moveTo(1e-15, 2e-15);
    state->lineTo(3e-15, 4e-15);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurY(), 2e-15);
}

// Test that closePath only affects the current subpath, then a new moveTo works
TEST_F(GfxStateClosePathTest_664, ClosePathThenNewSubpath_664) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);

    // Start a new subpath
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 300.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 400.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test closePath with a single lineTo segment
TEST_F(GfxStateClosePathTest_664, ClosePathSingleSegment_664) {
    state->moveTo(5.0, 15.0);
    state->lineTo(25.0, 35.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 15.0);
}

// Test closePath with multiple curveTo segments
TEST_F(GfxStateClosePathTest_664, ClosePathMultipleCurves_664) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    state->curveTo(70.0, 80.0, 90.0, 100.0, 110.0, 120.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 110.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 120.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test that the path object reflects closePath was called
TEST_F(GfxStateClosePathTest_664, ClosePathPathState_664) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);

    EXPECT_TRUE(state->isPath());

    state->closePath();

    // Path should still be valid after closing
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
    EXPECT_GE(path->getNumSubpaths(), 1);
}

// Test closePath with mixed lineTo and curveTo
TEST_F(GfxStateClosePathTest_664, ClosePathMixedLineAndCurve_664) {
    state->moveTo(5.0, 10.0);
    state->lineTo(50.0, 100.0);
    state->curveTo(60.0, 110.0, 70.0, 120.0, 80.0, 130.0);
    state->lineTo(200.0, 300.0);

    EXPECT_DOUBLE_EQ(state->getCurX(), 200.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 300.0);

    state->closePath();

    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 10.0);
}
