#include <gtest/gtest.h>
#include "splash/SplashPath.h"

// Test fixture for SplashPath
class SplashPathTest_1535 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction results in empty path
TEST_F(SplashPathTest_1535, DefaultConstructorCreatesEmptyPath_1535) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

// Test that getCurPt returns false when path is empty
TEST_F(SplashPathTest_1535, GetCurPtReturnsFalseWhenEmpty_1535) {
    SplashPath path;
    SplashCoord x, y;
    EXPECT_FALSE(path.getCurPt(&x, &y));
}

// Test moveTo adds a point
TEST_F(SplashPathTest_1535, MoveToAddsOnePoint_1535) {
    SplashPath path;
    SplashError err = path.moveTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

// Test getCurPt returns the current point after moveTo
TEST_F(SplashPathTest_1535, GetCurPtAfterMoveTo_1535) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test lineTo without moveTo should fail
TEST_F(SplashPathTest_1535, LineToWithoutMoveToFails_1535) {
    SplashPath path;
    SplashError err = path.lineTo(5.0, 5.0);
    EXPECT_NE(err, splashOk);
}

// Test lineTo after moveTo adds a point
TEST_F(SplashPathTest_1535, LineToAfterMoveToAddsPoint_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.lineTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 2);
}

// Test getCurPt after lineTo returns the last point
TEST_F(SplashPathTest_1535, GetCurPtAfterLineTo_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(15.0, 25.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 25.0);
}

// Test curveTo without moveTo should fail
TEST_F(SplashPathTest_1535, CurveToWithoutMoveToFails_1535) {
    SplashPath path;
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_NE(err, splashOk);
}

// Test curveTo after moveTo adds 3 points
TEST_F(SplashPathTest_1535, CurveToAddsThreePoints_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 4); // moveTo point + 3 curve points
}

// Test getCurPt after curveTo returns the endpoint
TEST_F(SplashPathTest_1535, GetCurPtAfterCurveTo_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test close on a subpath with at least two points
TEST_F(SplashPathTest_1535, CloseSubpath_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

// Test close on empty path should fail
TEST_F(SplashPathTest_1535, CloseEmptyPathFails_1535) {
    SplashPath path;
    SplashError err = path.close(true);
    EXPECT_NE(err, splashOk);
}

// Test multiple moveTo/lineTo operations
TEST_F(SplashPathTest_1535, MultipleLineToIncreasesLength_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);
    EXPECT_EQ(path.getLength(), 4);
}

// Test getPoint on first point
TEST_F(SplashPathTest_1535, GetPointReturnsCorrectFirstPoint_1535) {
    SplashPath path;
    path.moveTo(42.0, 84.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 42.0);
    EXPECT_DOUBLE_EQ(y, 84.0);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test getPoint on subsequent point
TEST_F(SplashPathTest_1535, GetPointReturnsCorrectSubsequentPoint_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 10.0);
    double x, y;
    unsigned char f;
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test getPoint flags for curve points
TEST_F(SplashPathTest_1535, GetPointCurveFlags_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    double x, y;
    unsigned char f;
    // The first control point of the curve (index 1) should have the curve flag
    path.getPoint(1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
    path.getPoint(2, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
}

// Test offset moves all points
TEST_F(SplashPathTest_1535, OffsetMovesAllPoints_1535) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.lineTo(30.0, 40.0);
    path.offset(5.0, -5.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 15.0);
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 35.0);
    EXPECT_DOUBLE_EQ(y, 35.0);
}

// Test append merges two paths
TEST_F(SplashPathTest_1535, AppendMergesPaths_1535) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(1.0, 1.0);

    SplashPath path2;
    path2.moveTo(2.0, 2.0);
    path2.lineTo(3.0, 3.0);

    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 4);
}

// Test append with empty path doesn't change length
TEST_F(SplashPathTest_1535, AppendEmptyPathNoChange_1535) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);

    SplashPath emptyPath;
    path1.append(&emptyPath);
    EXPECT_EQ(path1.getLength(), 1);
}

// Test append to empty path
TEST_F(SplashPathTest_1535, AppendToEmptyPath_1535) {
    SplashPath emptyPath;
    SplashPath path2;
    path2.moveTo(1.0, 2.0);
    path2.lineTo(3.0, 4.0);

    emptyPath.append(&path2);
    EXPECT_EQ(emptyPath.getLength(), 2);
}

// Test move constructor
TEST_F(SplashPathTest_1535, MoveConstructor_1535) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.lineTo(30.0, 40.0);
    int origLength = path.getLength();

    SplashPath movedPath(std::move(path));
    EXPECT_EQ(movedPath.getLength(), origLength);
}

// Test move constructor leaves source empty
TEST_F(SplashPathTest_1535, MoveConstructorSourceEmpty_1535) {
    SplashPath path;
    path.moveTo(10.0, 20.0);

    SplashPath movedPath(std::move(path));
    // After move, the original should be in a valid but unspecified state
    // Typically length would be 0
    EXPECT_EQ(path.getLength(), 0);
}

// Test getPoint on curve endpoint
TEST_F(SplashPathTest_1535, GetPointCurveEndpoint_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    double x, y;
    unsigned char f;
    path.getPoint(3, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test reserve doesn't change length
TEST_F(SplashPathTest_1535, ReserveDoesNotChangeLength_1535) {
    SplashPath path;
    path.reserve(100);
    EXPECT_EQ(path.getLength(), 0);
}

// Test reserve followed by operations
TEST_F(SplashPathTest_1535, ReserveFollowedByOperations_1535) {
    SplashPath path;
    path.reserve(100);
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

// Test close with force on single point subpath
TEST_F(SplashPathTest_1535, CloseWithForceSinglePoint_1535) {
    SplashPath path;
    path.moveTo(5.0, 5.0);
    SplashError err = path.close(true);
    // A single point subpath close behavior - may succeed or fail depending on implementation
    // We just check it doesn't crash
    (void)err;
}

// Test multiple subpaths
TEST_F(SplashPathTest_1535, MultipleSubpaths_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(10.0, 10.0);
    path.lineTo(11.0, 11.0);
    EXPECT_EQ(path.getLength(), 4);
}

// Test close then moveTo starts new subpath
TEST_F(SplashPathTest_1535, CloseAndNewSubpath_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    path.moveTo(20.0, 20.0);
    path.lineTo(30.0, 30.0);
    EXPECT_EQ(path.getLength(), 5);
}

// Test offset on empty path doesn't crash
TEST_F(SplashPathTest_1535, OffsetEmptyPath_1535) {
    SplashPath path;
    path.offset(5.0, 5.0);
    EXPECT_EQ(path.getLength(), 0);
}

// Test offset with zero values
TEST_F(SplashPathTest_1535, OffsetWithZero_1535) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.offset(0.0, 0.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test negative coordinates
TEST_F(SplashPathTest_1535, NegativeCoordinates_1535) {
    SplashPath path;
    path.moveTo(-10.0, -20.0);
    path.lineTo(-30.0, -40.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, -30.0);
    EXPECT_DOUBLE_EQ(y, -40.0);
}

// Test very large coordinates
TEST_F(SplashPathTest_1535, LargeCoordinates_1535) {
    SplashPath path;
    path.moveTo(1e10, 1e10);
    path.lineTo(1e15, 1e15);
    double x, y;
    unsigned char f;
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1e15);
    EXPECT_DOUBLE_EQ(y, 1e15);
}

// Test first point has splashPathFirst flag
TEST_F(SplashPathTest_1535, FirstPointHasFirstFlag_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test close sets closed flag
TEST_F(SplashPathTest_1535, CloseSetsFlagOnLastPoint_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    // After closing, we check if the last point of the subpath has the closed flag
    double x, y;
    unsigned char f;
    path.getPoint(2, &x, &y, &f);
    EXPECT_TRUE(f & splashPathClosed);
}

// Test addStrokeAdjustHint doesn't change length
TEST_F(SplashPathTest_1535, AddStrokeAdjustHintDoesNotChangeLength_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    int lengthBefore = path.getLength();
    path.addStrokeAdjustHint(0, 1, 0, 1);
    EXPECT_EQ(path.getLength(), lengthBefore);
}

// Test building a complex path
TEST_F(SplashPathTest_1535, ComplexPath_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(100.0, 0.0);
    path.curveTo(100.0, 50.0, 50.0, 100.0, 0.0, 100.0);
    path.close(false);
    // moveTo(1) + lineTo(1) + curveTo(3) = 5 points
    EXPECT_EQ(path.getLength(), 5);
}

// Test last point of closed subpath and first point of next
TEST_F(SplashPathTest_1535, NewSubpathAfterClose_1535) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.close(false);
    path.moveTo(20.0, 20.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 20.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test getPoint on moved path
TEST_F(SplashPathTest_1535, GetPointOnMovedPath_1535) {
    SplashPath path;
    path.moveTo(7.0, 8.0);
    path.lineTo(9.0, 10.0);

    SplashPath movedPath(std::move(path));
    double x, y;
    unsigned char f;
    movedPath.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 7.0);
    EXPECT_DOUBLE_EQ(y, 8.0);
    movedPath.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 9.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}
