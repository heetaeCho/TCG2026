#include <gtest/gtest.h>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateLineToTest_662 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test that lineTo updates curX and curY
TEST_F(GfxStateLineToTest_662, LineToUpdatesCurXAndCurY_662) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);
}

// Test that lineTo with zero coordinates works
TEST_F(GfxStateLineToTest_662, LineToZeroCoordinates_662) {
    state->moveTo(5.0, 5.0);
    state->lineTo(0.0, 0.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test that lineTo with negative coordinates works
TEST_F(GfxStateLineToTest_662, LineToNegativeCoordinates_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(-100.0, -200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), -100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -200.0);
}

// Test that lineTo with very large coordinates works
TEST_F(GfxStateLineToTest_662, LineToLargeCoordinates_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(1e10, 1e10);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e10);
}

// Test that lineTo with very small (near zero) coordinates works
TEST_F(GfxStateLineToTest_662, LineToVerySmallCoordinates_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e-15);
}

// Test multiple lineTo calls in sequence
TEST_F(GfxStateLineToTest_662, MultipleLineToCallsUpdateCurPos_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);

    state->lineTo(30.0, 40.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);

    state->lineTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test that lineTo creates a path (isPath returns true)
TEST_F(GfxStateLineToTest_662, LineToCreatesPath_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

// Test that lineTo adds to the path subpaths
TEST_F(GfxStateLineToTest_662, LineToAddsToPathSubpaths_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_GE(path->getNumSubpaths(), 1);
}

// Test lineTo after moveTo preserves the subpath correctly
TEST_F(GfxStateLineToTest_662, LineToAfterMoveToPreservesSubpath_662) {
    state->moveTo(5.0, 10.0);
    state->lineTo(15.0, 25.0);
    
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getNumSubpaths(), 1);
    
    // The last point should be the lineTo destination
    EXPECT_DOUBLE_EQ(path->getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 25.0);
}

// Test lineTo with same coordinates as current position (zero-length line)
TEST_F(GfxStateLineToTest_662, LineToSameAsCurrent_662) {
    state->moveTo(42.0, 84.0);
    state->lineTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
    EXPECT_TRUE(state->isPath());
}

// Test lineTo with only X changing
TEST_F(GfxStateLineToTest_662, LineToOnlyXChanges_662) {
    state->moveTo(10.0, 20.0);
    state->lineTo(50.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test lineTo with only Y changing
TEST_F(GfxStateLineToTest_662, LineToOnlyYChanges_662) {
    state->moveTo(10.0, 20.0);
    state->lineTo(10.0, 80.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 80.0);
}

// Test lineTo after clearPath and new moveTo
TEST_F(GfxStateLineToTest_662, LineToAfterClearPathAndMoveTo_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 300.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 400.0);
    
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getNumSubpaths(), 1);
}

// Test that isCurPt is true after moveTo followed by lineTo
TEST_F(GfxStateLineToTest_662, IsCurPtAfterLineTo_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(5.0, 5.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo with mixed positive and negative
TEST_F(GfxStateLineToTest_662, LineToMixedSignCoordinates_662) {
    state->moveTo(-50.0, 50.0);
    state->lineTo(50.0, -50.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -50.0);
}

// Test multiple moveTo+lineTo pairs create multiple subpaths
TEST_F(GfxStateLineToTest_662, MultipleSubpathsFromMoveToLineTo_662) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->moveTo(50.0, 50.0);
    state->lineTo(60.0, 60.0);
    
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getNumSubpaths(), 2);
}

// Test that lineTo updates the path's last coordinates
TEST_F(GfxStateLineToTest_662, LineToUpdatesPathLastCoordinates_662) {
    state->moveTo(1.0, 2.0);
    state->lineTo(3.0, 4.0);
    state->lineTo(5.0, 6.0);
    
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_DOUBLE_EQ(path->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 6.0);
}
