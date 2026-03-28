#include <gtest/gtest.h>
#include "splash/SplashPath.h"

class SplashPathTest_1536 : public ::testing::Test {
protected:
    SplashPath path;
};

// Test that a newly created path has length 0
TEST_F(SplashPathTest_1536, DefaultConstructorCreatesEmptyPath_1536) {
    EXPECT_EQ(path.getLength(), 0);
}

// Test that getCurPt returns false when path is empty (no current point)
TEST_F(SplashPathTest_1536, GetCurPtReturnsFalseWhenEmpty_1536) {
    SplashCoord x, y;
    EXPECT_FALSE(path.getCurPt(&x, &y));
}

// Test moveTo adds a point and increases length
TEST_F(SplashPathTest_1536, MoveToAddsOnePoint_1536) {
    SplashError err = path.moveTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

// Test that after moveTo, getCurPt returns the correct point
TEST_F(SplashPathTest_1536, MoveToSetsCurPt_1536) {
    path.moveTo(10.0, 20.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test getPoint after moveTo
TEST_F(SplashPathTest_1536, GetPointAfterMoveTo_1536) {
    path.moveTo(5.0, 15.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 15.0);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test lineTo without moveTo should fail
TEST_F(SplashPathTest_1536, LineToWithoutMoveToFails_1536) {
    SplashError err = path.lineTo(10.0, 20.0);
    EXPECT_NE(err, splashOk);
}

// Test lineTo after moveTo succeeds
TEST_F(SplashPathTest_1536, LineToAfterMoveToSucceeds_1536) {
    path.moveTo(0.0, 0.0);
    SplashError err = path.lineTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 2);
}

// Test lineTo updates current point
TEST_F(SplashPathTest_1536, LineToUpdatesCurPt_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 20.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test getPoint after lineTo
TEST_F(SplashPathTest_1536, GetPointAfterLineTo_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 20.0);
    double x, y;
    unsigned char f;
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test curveTo without moveTo should fail
TEST_F(SplashPathTest_1536, CurveToWithoutMoveToFails_1536) {
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_NE(err, splashOk);
}

// Test curveTo after moveTo succeeds and adds 3 points
TEST_F(SplashPathTest_1536, CurveToAddsThreePoints_1536) {
    path.moveTo(0.0, 0.0);
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 4); // 1 moveTo + 3 curveTo points
}

// Test curveTo updates current point to last control point
TEST_F(SplashPathTest_1536, CurveToUpdatesCurPt_1536) {
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test curveTo control points have curve flag
TEST_F(SplashPathTest_1536, CurveToPointsHaveCurveFlag_1536) {
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    double x, y;
    unsigned char f;
    // First control point
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    EXPECT_TRUE(f & splashPathCurve);

    // Second control point
    path.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
    EXPECT_TRUE(f & splashPathCurve);

    // End point
    path.getPoint(3, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test close without moveTo should fail
TEST_F(SplashPathTest_1536, CloseWithoutMoveToFails_1536) {
    SplashError err = path.close(true);
    EXPECT_NE(err, splashOk);
}

// Test close after moveTo and lineTo
TEST_F(SplashPathTest_1536, CloseAfterLineToSucceeds_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

// Test close sets the closed flag on the last point
TEST_F(SplashPathTest_1536, CloseSetsFlagsCorrectly_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(true);

    int len = path.getLength();
    double x, y;
    unsigned char f;
    // The last point added by close should go back to subpath start
    path.getPoint(len - 1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathLast);
}

// Test offset shifts all points
TEST_F(SplashPathTest_1536, OffsetShiftsAllPoints_1536) {
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.offset(10.0, 20.0);

    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 11.0);
    EXPECT_DOUBLE_EQ(y, 22.0);

    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 13.0);
    EXPECT_DOUBLE_EQ(y, 24.0);
}

// Test append merges another path
TEST_F(SplashPathTest_1536, AppendMergesPaths_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);

    SplashPath path2;
    path2.moveTo(2.0, 2.0);
    path2.lineTo(3.0, 3.0);

    path.append(&path2);
    EXPECT_EQ(path.getLength(), 4);

    double x, y;
    unsigned char f;
    path.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 2.0);

    path.getPoint(3, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test move constructor transfers path data
TEST_F(SplashPathTest_1536, MoveConstructorTransfersData_1536) {
    path.moveTo(5.0, 10.0);
    path.lineTo(15.0, 20.0);

    SplashPath movedPath(std::move(path));
    EXPECT_EQ(movedPath.getLength(), 2);

    double x, y;
    unsigned char f;
    movedPath.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);

    movedPath.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test that after move constructor, original path is empty
TEST_F(SplashPathTest_1536, MoveConstructorLeavesSourceEmpty_1536) {
    path.moveTo(5.0, 10.0);
    SplashPath movedPath(std::move(path));
    EXPECT_EQ(path.getLength(), 0);
}

// Test multiple moveTo calls (starting new subpaths)
TEST_F(SplashPathTest_1536, MultipleMoveToStartsNewSubpaths_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(5.0, 5.0);
    path.lineTo(6.0, 6.0);
    EXPECT_EQ(path.getLength(), 4);
}

// Test reserve does not change length
TEST_F(SplashPathTest_1536, ReserveDoesNotChangeLength_1536) {
    path.reserve(100);
    EXPECT_EQ(path.getLength(), 0);
}

// Test reserve then add points works
TEST_F(SplashPathTest_1536, ReserveThenAddPoints_1536) {
    path.reserve(10);
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

// Test offset with zero displacement
TEST_F(SplashPathTest_1536, OffsetWithZeroDisplacement_1536) {
    path.moveTo(5.0, 10.0);
    path.offset(0.0, 0.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test offset with negative values
TEST_F(SplashPathTest_1536, OffsetWithNegativeValues_1536) {
    path.moveTo(10.0, 20.0);
    path.offset(-5.0, -10.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test close with force=false on already closed subpath
TEST_F(SplashPathTest_1536, DoubleCloseWithForce_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err1 = path.close(true);
    EXPECT_EQ(err1, splashOk);
    // Closing again may fail since subpath is already closed
    SplashError err2 = path.close(false);
    // We just check it doesn't crash; behavior may vary
}

// Test building a complex path
TEST_F(SplashPathTest_1536, ComplexPathBuilding_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(100.0, 0.0);
    path.curveTo(100.0, 50.0, 50.0, 100.0, 0.0, 100.0);
    path.close(true);

    // moveTo: 1 pt, lineTo: 1 pt, curveTo: 3 pts, close: 1 pt
    int len = path.getLength();
    EXPECT_GE(len, 5);

    // Verify first point
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test getPoint on all points of a simple path
TEST_F(SplashPathTest_1536, GetPointAllPointsSimplePath_1536) {
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.lineTo(5.0, 6.0);

    EXPECT_EQ(path.getLength(), 3);

    double x, y;
    unsigned char f;

    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);

    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);

    path.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test getCurPt reflects last added point after multiple operations
TEST_F(SplashPathTest_1536, GetCurPtReflectsLastPoint_1536) {
    path.moveTo(1.0, 1.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 1.0);

    path.lineTo(2.0, 3.0);
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 3.0);

    path.curveTo(4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 8.0);
    EXPECT_DOUBLE_EQ(y, 9.0);
}

// Test appending empty path doesn't change length
TEST_F(SplashPathTest_1536, AppendEmptyPathNoChange_1536) {
    path.moveTo(1.0, 1.0);
    SplashPath emptyPath;
    path.append(&emptyPath);
    EXPECT_EQ(path.getLength(), 1);
}

// Test appending to empty path
TEST_F(SplashPathTest_1536, AppendToEmptyPath_1536) {
    SplashPath path2;
    path2.moveTo(1.0, 2.0);
    path2.lineTo(3.0, 4.0);
    path.append(&path2);
    EXPECT_EQ(path.getLength(), 2);
}

// Test moveTo with zero coordinates
TEST_F(SplashPathTest_1536, MoveToZeroCoordinates_1536) {
    SplashError err = path.moveTo(0.0, 0.0);
    EXPECT_EQ(err, splashOk);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test moveTo with large coordinates
TEST_F(SplashPathTest_1536, MoveToLargeCoordinates_1536) {
    SplashError err = path.moveTo(1e10, -1e10);
    EXPECT_EQ(err, splashOk);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1e10);
    EXPECT_DOUBLE_EQ(y, -1e10);
}

// Test that first point of a subpath has splashPathFirst flag
TEST_F(SplashPathTest_1536, FirstPointHasFirstFlag_1536) {
    path.moveTo(1.0, 2.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test addStrokeAdjustHint doesn't crash
TEST_F(SplashPathTest_1536, AddStrokeAdjustHintNoCrash_1536) {
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.lineTo(20.0, 0.0);
    // Just verify it doesn't crash
    path.addStrokeAdjustHint(0, 1, 0, 2);
    EXPECT_EQ(path.getLength(), 3);
}
