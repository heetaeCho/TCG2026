#include <gtest/gtest.h>
#include "splash/SplashPath.h"

// Test fixture for SplashPath tests
class SplashPathTest_1538 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates empty path
TEST_F(SplashPathTest_1538, DefaultConstructor_EmptyPath_1538) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

// Test that getCurPt returns false on empty path
TEST_F(SplashPathTest_1538, GetCurPtOnEmptyPath_ReturnsFalse_1538) {
    SplashPath path;
    SplashCoord x, y;
    EXPECT_FALSE(path.getCurPt(&x, &y));
}

// Test moveTo adds a point
TEST_F(SplashPathTest_1538, MoveTo_AddsOnePoint_1538) {
    SplashPath path;
    SplashError err = path.moveTo(1.0, 2.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

// Test getCurPt after moveTo returns correct point
TEST_F(SplashPathTest_1538, GetCurPtAfterMoveTo_ReturnsCorrectPoint_1538) {
    SplashPath path;
    path.moveTo(3.5, 7.2);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 3.5);
    EXPECT_DOUBLE_EQ(y, 7.2);
}

// Test lineTo without moveTo should fail
TEST_F(SplashPathTest_1538, LineToWithoutMoveTo_ReturnsError_1538) {
    SplashPath path;
    SplashError err = path.lineTo(1.0, 2.0);
    EXPECT_NE(err, splashOk);
}

// Test lineTo after moveTo succeeds
TEST_F(SplashPathTest_1538, LineToAfterMoveTo_Succeeds_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.lineTo(1.0, 2.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 2);
}

// Test curveTo without moveTo should fail
TEST_F(SplashPathTest_1538, CurveToWithoutMoveTo_ReturnsError_1538) {
    SplashPath path;
    SplashError err = path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_NE(err, splashOk);
}

// Test curveTo after moveTo succeeds and adds 3 points
TEST_F(SplashPathTest_1538, CurveToAfterMoveTo_AddsThreePoints_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 4); // 1 moveTo + 3 curve control points
}

// Test getCurPt after lineTo returns correct last point
TEST_F(SplashPathTest_1538, GetCurPtAfterLineTo_ReturnsLastPoint_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 10.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test getCurPt after curveTo returns the last control point
TEST_F(SplashPathTest_1538, GetCurPtAfterCurveTo_ReturnsLastControlPoint_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test close without open subpath fails
TEST_F(SplashPathTest_1538, CloseWithoutSubpath_ReturnsError_1538) {
    SplashPath path;
    SplashError err = path.close(false);
    EXPECT_NE(err, splashOk);
}

// Test close on a subpath with at least two points
TEST_F(SplashPathTest_1538, CloseAfterLineSegment_Succeeds_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    SplashError err = path.close(false);
    EXPECT_EQ(err, splashOk);
}

// Test close with force on a single point subpath
TEST_F(SplashPathTest_1538, CloseForceOnSinglePoint_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    // With force=true, it should close even a single point subpath
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

// Test getPoint retrieves correct coordinates and flags
TEST_F(SplashPathTest_1538, GetPoint_RetrievesCorrectData_1538) {
    SplashPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);

    double x, y;
    unsigned char f;

    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    // First point should have splashPathFirst flag
    EXPECT_TRUE(f & splashPathFirst);

    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
    // Last point should have splashPathLast flag
    EXPECT_TRUE(f & splashPathLast);
}

// Test offset shifts all points
TEST_F(SplashPathTest_1538, Offset_ShiftsAllPoints_1538) {
    SplashPath path;
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

// Test append combines two paths
TEST_F(SplashPathTest_1538, Append_CombinesPaths_1538) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(1.0, 1.0);

    SplashPath path2;
    path2.moveTo(2.0, 2.0);
    path2.lineTo(3.0, 3.0);

    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 4);

    double x, y;
    unsigned char f;
    path1.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 2.0);

    path1.getPoint(3, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test move constructor transfers ownership
TEST_F(SplashPathTest_1538, MoveConstructor_TransfersData_1538) {
    SplashPath path;
    path.moveTo(5.0, 6.0);
    path.lineTo(7.0, 8.0);

    SplashPath movedPath(std::move(path));
    EXPECT_EQ(movedPath.getLength(), 2);

    double x, y;
    unsigned char f;
    movedPath.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);

    movedPath.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 7.0);
    EXPECT_DOUBLE_EQ(y, 8.0);
}

// Test move constructor leaves source in valid state
TEST_F(SplashPathTest_1538, MoveConstructor_SourceIsEmpty_1538) {
    SplashPath path;
    path.moveTo(1.0, 2.0);

    SplashPath movedPath(std::move(path));
    // After move, original path should be in some valid state (likely empty)
    EXPECT_EQ(path.getLength(), 0);
}

// Test multiple moveTo calls create multiple subpaths
TEST_F(SplashPathTest_1538, MultipleMoveTo_CreatesMultipleSubpaths_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);

    EXPECT_EQ(path.getLength(), 4);

    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test reserve does not change length
TEST_F(SplashPathTest_1538, Reserve_DoesNotChangeLength_1538) {
    SplashPath path;
    path.reserve(100);
    EXPECT_EQ(path.getLength(), 0);
}

// Test reserve followed by normal operations
TEST_F(SplashPathTest_1538, ReserveThenAdd_WorksCorrectly_1538) {
    SplashPath path;
    path.reserve(50);
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

// Test closing already closed subpath
TEST_F(SplashPathTest_1538, CloseAlreadyClosed_ReturnsError_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    SplashError err1 = path.close(false);
    EXPECT_EQ(err1, splashOk);
    // Closing again should fail since the subpath is already closed
    SplashError err2 = path.close(false);
    EXPECT_NE(err2, splashOk);
}

// Test getPoint flags for curve points
TEST_F(SplashPathTest_1538, GetPointFlags_CurvePoints_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    double x, y;
    unsigned char f;

    // Control points of curve should have splashPathCurve flag
    path.getPoint(1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);

    path.getPoint(2, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);

    path.getPoint(3, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
}

// Test close sets the closed flag on the last point
TEST_F(SplashPathTest_1538, Close_SetsClosedFlag_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.close(false);

    double x, y;
    unsigned char f;
    // Last point of closed subpath should have splashPathClosed flag
    path.getPoint(path.getLength() - 1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathClosed);
}

// Test offset with zero displacement
TEST_F(SplashPathTest_1538, OffsetZero_NoChange_1538) {
    SplashPath path;
    path.moveTo(5.0, 10.0);
    path.offset(0.0, 0.0);

    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test offset with negative displacement
TEST_F(SplashPathTest_1538, OffsetNegative_ShiftsCorrectly_1538) {
    SplashPath path;
    path.moveTo(5.0, 10.0);
    path.offset(-3.0, -7.0);

    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test append empty path to non-empty path
TEST_F(SplashPathTest_1538, AppendEmptyPath_NoChange_1538) {
    SplashPath path;
    path.moveTo(1.0, 2.0);

    SplashPath emptyPath;
    path.append(&emptyPath);

    EXPECT_EQ(path.getLength(), 1);
}

// Test append non-empty path to empty path
TEST_F(SplashPathTest_1538, AppendToEmptyPath_1538) {
    SplashPath path;

    SplashPath otherPath;
    otherPath.moveTo(1.0, 2.0);
    otherPath.lineTo(3.0, 4.0);

    path.append(&otherPath);
    EXPECT_EQ(path.getLength(), 2);
}

// Test building a complex path with multiple operations
TEST_F(SplashPathTest_1538, ComplexPath_MultipleOperations_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.curveTo(7.0, 12.0, 3.0, 12.0, 0.0, 10.0);
    path.close(false);

    // moveTo(1) + lineTo(2) + curveTo(3) + close should give length: 1+2+3 = 6
    EXPECT_EQ(path.getLength(), 6);

    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
}

// Test addStrokeAdjustHint does not crash or change length
TEST_F(SplashPathTest_1538, AddStrokeAdjustHint_DoesNotAffectLength_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    int lenBefore = path.getLength();
    path.addStrokeAdjustHint(0, 1, 0, 1);
    EXPECT_EQ(path.getLength(), lenBefore);
}

// Test getLength on freshly constructed path
TEST_F(SplashPathTest_1538, GetLength_FreshPath_IsZero_1538) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

// Test multiple line segments
TEST_F(SplashPathTest_1538, MultipleLineSegments_CorrectLength_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    for (int i = 1; i <= 10; i++) {
        path.lineTo(static_cast<SplashCoord>(i), static_cast<SplashCoord>(i));
    }
    EXPECT_EQ(path.getLength(), 11); // 1 moveTo + 10 lineTo
}

// Test lineTo after close (new operations after closing)
TEST_F(SplashPathTest_1538, LineToAfterClose_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.close(false);

    // After close, lineTo should fail since there's no current open subpath
    SplashError err = path.lineTo(2.0, 2.0);
    EXPECT_NE(err, splashOk);
}

// Test moveTo after close starts new subpath
TEST_F(SplashPathTest_1538, MoveToAfterClose_StartsNewSubpath_1538) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.close(false);

    SplashError err = path.moveTo(5.0, 5.0);
    EXPECT_EQ(err, splashOk);

    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 5.0);
}
