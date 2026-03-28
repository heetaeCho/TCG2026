#include <gtest/gtest.h>
#include "splash/SplashPath.h"

// Test fixture for SplashPath
class SplashPathTest_1537 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(SplashPathTest_1537, DefaultConstruction_1537) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

// Test noCurrentPoint on empty path (accessed via getCurPt behavior)
TEST_F(SplashPathTest_1537, GetCurPtOnEmptyPath_1537) {
    SplashPath path;
    SplashCoord x, y;
    bool result = path.getCurPt(&x, &y);
    EXPECT_FALSE(result);
}

// Test moveTo adds a point
TEST_F(SplashPathTest_1537, MoveToAddsPoint_1537) {
    SplashPath path;
    SplashError err = path.moveTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

// Test getCurPt after moveTo
TEST_F(SplashPathTest_1537, GetCurPtAfterMoveTo_1537) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    SplashCoord x, y;
    bool result = path.getCurPt(&x, &y);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test lineTo without moveTo should fail
TEST_F(SplashPathTest_1537, LineToWithoutMoveTo_1537) {
    SplashPath path;
    SplashError err = path.lineTo(5.0, 5.0);
    EXPECT_NE(err, splashOk);
}

// Test lineTo after moveTo
TEST_F(SplashPathTest_1537, LineToAfterMoveTo_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.lineTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 2);
}

// Test getCurPt after lineTo
TEST_F(SplashPathTest_1537, GetCurPtAfterLineTo_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 20.0);
    SplashCoord x, y;
    bool result = path.getCurPt(&x, &y);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test curveTo without moveTo should fail
TEST_F(SplashPathTest_1537, CurveToWithoutMoveTo_1537) {
    SplashPath path;
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_NE(err, splashOk);
}

// Test curveTo after moveTo
TEST_F(SplashPathTest_1537, CurveToAfterMoveTo_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(err, splashOk);
    // curveTo adds 3 control points
    EXPECT_EQ(path.getLength(), 4);
}

// Test getCurPt after curveTo
TEST_F(SplashPathTest_1537, GetCurPtAfterCurveTo_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    SplashCoord x, y;
    bool result = path.getCurPt(&x, &y);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test close without moveTo should fail
TEST_F(SplashPathTest_1537, CloseWithoutMoveTo_1537) {
    SplashPath path;
    SplashError err = path.close(true);
    EXPECT_NE(err, splashOk);
}

// Test close after moveTo and lineTo
TEST_F(SplashPathTest_1537, CloseAfterLineSegment_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

// Test closing an already closed subpath
TEST_F(SplashPathTest_1537, CloseAlreadyClosedSubpath_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(true);
    SplashError err = path.close(false);
    // closing already closed might return error or be no-op
    // We test that it doesn't crash at least
    (void)err;
}

// Test getPoint on first point
TEST_F(SplashPathTest_1537, GetPointFirstPoint_1537) {
    SplashPath path;
    path.moveTo(5.0, 15.0);
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 15.0);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test getPoint on line endpoint
TEST_F(SplashPathTest_1537, GetPointLineEndpoint_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 20.0);
    double x, y;
    unsigned char f;
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test multiple moveTo calls
TEST_F(SplashPathTest_1537, MultipleMoveToCalls_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.moveTo(5.0, 5.0);
    // Each moveTo should add a point
    EXPECT_EQ(path.getLength(), 2);
    SplashCoord x, y;
    path.getCurPt(&x, &y);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 5.0);
}

// Test offset
TEST_F(SplashPathTest_1537, OffsetPath_1537) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.lineTo(30.0, 40.0);
    path.offset(5.0, -3.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 17.0);
    
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 35.0);
    EXPECT_DOUBLE_EQ(y, 37.0);
}

// Test offset on empty path (should not crash)
TEST_F(SplashPathTest_1537, OffsetEmptyPath_1537) {
    SplashPath path;
    path.offset(5.0, 5.0);
    EXPECT_EQ(path.getLength(), 0);
}

// Test append
TEST_F(SplashPathTest_1537, AppendPath_1537) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(10.0, 10.0);
    
    SplashPath path2;
    path2.moveTo(20.0, 20.0);
    path2.lineTo(30.0, 30.0);
    
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 4);
}

// Test append empty path
TEST_F(SplashPathTest_1537, AppendEmptyPath_1537) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);
    
    SplashPath path2;
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 1);
}

// Test append to empty path
TEST_F(SplashPathTest_1537, AppendToEmptyPath_1537) {
    SplashPath path1;
    
    SplashPath path2;
    path2.moveTo(10.0, 10.0);
    path2.lineTo(20.0, 20.0);
    
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 2);
}

// Test move constructor
TEST_F(SplashPathTest_1537, MoveConstructor_1537) {
    SplashPath path1;
    path1.moveTo(5.0, 10.0);
    path1.lineTo(15.0, 20.0);
    
    SplashPath path2(std::move(path1));
    EXPECT_EQ(path2.getLength(), 2);
    
    double x, y;
    unsigned char f;
    path2.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
    
    path2.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test reserve does not change length
TEST_F(SplashPathTest_1537, ReserveDoesNotChangeLength_1537) {
    SplashPath path;
    path.reserve(100);
    EXPECT_EQ(path.getLength(), 0);
}

// Test reserve then add points
TEST_F(SplashPathTest_1537, ReserveThenAddPoints_1537) {
    SplashPath path;
    path.reserve(10);
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

// Test building a complex path
TEST_F(SplashPathTest_1537, ComplexPath_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(100.0, 0.0);
    path.lineTo(100.0, 100.0);
    path.lineTo(0.0, 100.0);
    path.close(true);
    
    // After close, should have the original 4 points
    EXPECT_EQ(path.getLength(), 4);
    
    // Start a new subpath
    path.moveTo(200.0, 200.0);
    path.lineTo(300.0, 300.0);
    EXPECT_EQ(path.getLength(), 6);
    
    SplashCoord x, y;
    path.getCurPt(&x, &y);
    EXPECT_DOUBLE_EQ(x, 300.0);
    EXPECT_DOUBLE_EQ(y, 300.0);
}

// Test curveTo flags contain splashPathCurve
TEST_F(SplashPathTest_1537, CurveToFlags_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    
    double x, y;
    unsigned char f;
    
    // Control points (indices 1 and 2) should have curve flag
    path.getPoint(1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
    
    path.getPoint(2, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
}

// Test close with force=false on single point subpath
TEST_F(SplashPathTest_1537, CloseForceOnSinglePoint_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.close(false);
    // Single point subpath - close with force=false behavior
    (void)err; // Just ensure it doesn't crash
}

// Test close with force=true on single point subpath
TEST_F(SplashPathTest_1537, CloseForceTrue_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.close(true);
    (void)err;
}

// Test getLength on various stages
TEST_F(SplashPathTest_1537, GetLengthProgression_1537) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
    
    path.moveTo(0.0, 0.0);
    EXPECT_EQ(path.getLength(), 1);
    
    path.lineTo(1.0, 1.0);
    EXPECT_EQ(path.getLength(), 2);
    
    path.lineTo(2.0, 2.0);
    EXPECT_EQ(path.getLength(), 3);
    
    path.curveTo(3.0, 3.0, 4.0, 4.0, 5.0, 5.0);
    EXPECT_EQ(path.getLength(), 6);
}

// Test addStrokeAdjustHint doesn't crash
TEST_F(SplashPathTest_1537, AddStrokeAdjustHint_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.lineTo(0.0, 10.0);
    path.addStrokeAdjustHint(0, 1, 2, 3);
    // Just verify it doesn't crash
    EXPECT_EQ(path.getLength(), 4);
}

// Test offset with zero values
TEST_F(SplashPathTest_1537, OffsetZero_1537) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.offset(0.0, 0.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 10.0);
    EXPECT_DOUBLE_EQ(y, 20.0);
}

// Test offset with negative values
TEST_F(SplashPathTest_1537, OffsetNegative_1537) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.offset(-15.0, -25.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, -5.0);
    EXPECT_DOUBLE_EQ(y, -5.0);
}

// Test first point flag
TEST_F(SplashPathTest_1537, FirstPointFlag_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_TRUE(f & splashPathFirst);
}

// Test closed path last point flag
TEST_F(SplashPathTest_1537, ClosedPathLastFlag_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(true);
    
    double x, y;
    unsigned char f;
    // The last point should have last and/or closed flags
    path.getPoint(path.getLength() - 1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathLast);
}

// Test append preserves point data
TEST_F(SplashPathTest_1537, AppendPreservesData_1537) {
    SplashPath path1;
    path1.moveTo(1.0, 2.0);
    
    SplashPath path2;
    path2.moveTo(3.0, 4.0);
    path2.lineTo(5.0, 6.0);
    
    path1.append(&path2);
    
    double x, y;
    unsigned char f;
    path1.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    
    path1.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
    
    path1.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 6.0);
}

// Test move constructor leaves source in valid state
TEST_F(SplashPathTest_1537, MoveConstructorSourceState_1537) {
    SplashPath path1;
    path1.moveTo(5.0, 10.0);
    
    SplashPath path2(std::move(path1));
    // path1 should be in a valid but unspecified state
    // At minimum, it should be destructible (tested implicitly)
    EXPECT_EQ(path2.getLength(), 1);
}

// Test many points (stress test for grow)
TEST_F(SplashPathTest_1537, ManyPoints_1537) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    for (int i = 1; i < 100; i++) {
        path.lineTo(static_cast<SplashCoord>(i), static_cast<SplashCoord>(i * 2));
    }
    EXPECT_EQ(path.getLength(), 100);
    
    double x, y;
    unsigned char f;
    path.getPoint(99, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 99.0);
    EXPECT_DOUBLE_EQ(y, 198.0);
}
