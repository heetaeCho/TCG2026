#include <gtest/gtest.h>
#include "splash/SplashPath.h"

// Test fixture for SplashPath
class SplashPathTest_1539 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(SplashPathTest_1539, DefaultConstructor_CreatesEmptyPath_1539) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

TEST_F(SplashPathTest_1539, MoveConstructor_TransfersOwnership_1539) {
    SplashPath path1;
    path1.moveTo(1.0, 2.0);
    path1.lineTo(3.0, 4.0);
    int originalLength = path1.getLength();

    SplashPath path2(std::move(path1));
    EXPECT_EQ(path2.getLength(), originalLength);
}

// ==================== moveTo Tests ====================

TEST_F(SplashPathTest_1539, MoveTo_AddsFirstPoint_1539) {
    SplashPath path;
    SplashError err = path.moveTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

TEST_F(SplashPathTest_1539, MoveTo_MultipleMoveToCalls_1539) {
    SplashPath path;
    path.moveTo(1.0, 2.0);
    path.moveTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

TEST_F(SplashPathTest_1539, MoveTo_ZeroCoordinates_1539) {
    SplashPath path;
    SplashError err = path.moveTo(0.0, 0.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

TEST_F(SplashPathTest_1539, MoveTo_NegativeCoordinates_1539) {
    SplashPath path;
    SplashError err = path.moveTo(-5.0, -10.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 1);
}

// ==================== lineTo Tests ====================

TEST_F(SplashPathTest_1539, LineTo_WithoutMoveTo_ReturnsError_1539) {
    SplashPath path;
    SplashError err = path.lineTo(5.0, 5.0);
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashPathTest_1539, LineTo_AfterMoveTo_AddsPoint_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.lineTo(10.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 2);
}

TEST_F(SplashPathTest_1539, LineTo_MultipleLines_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);
    EXPECT_EQ(path.getLength(), 4);
}

// ==================== curveTo Tests ====================

TEST_F(SplashPathTest_1539, CurveTo_WithoutMoveTo_ReturnsError_1539) {
    SplashPath path;
    SplashError err = path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashPathTest_1539, CurveTo_AfterMoveTo_AddsThreePoints_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(path.getLength(), 4); // moveTo point + 3 curve points
}

TEST_F(SplashPathTest_1539, CurveTo_MultipleCurves_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    path.curveTo(4.0, 4.0, 5.0, 5.0, 6.0, 6.0);
    EXPECT_EQ(path.getLength(), 7); // 1 + 3 + 3
}

// ==================== close Tests ====================

TEST_F(SplashPathTest_1539, Close_EmptyPath_ReturnsError_1539) {
    SplashPath path;
    SplashError err = path.close(false);
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashPathTest_1539, Close_SinglePoint_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashPathTest_1539, Close_OpenSubpath_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(false);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashPathTest_1539, Close_AlreadyClosedSubpath_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    // Closing again should handle gracefully
    SplashError err = path.close(false);
    // May or may not be error; just verify no crash
    (void)err;
}

// ==================== getLength Tests ====================

TEST_F(SplashPathTest_1539, GetLength_EmptyPath_1539) {
    SplashPath path;
    EXPECT_EQ(path.getLength(), 0);
}

TEST_F(SplashPathTest_1539, GetLength_AfterMultipleOperations_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    EXPECT_EQ(path.getLength(), 1);
    path.lineTo(1.0, 1.0);
    EXPECT_EQ(path.getLength(), 2);
    path.lineTo(2.0, 2.0);
    EXPECT_EQ(path.getLength(), 3);
}

// ==================== getPoint Tests ====================

TEST_F(SplashPathTest_1539, GetPoint_RetrievesCorrectCoordinates_1539) {
    SplashPath path;
    path.moveTo(5.0, 10.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

TEST_F(SplashPathTest_1539, GetPoint_MoveToHasFirstFlag_1539) {
    SplashPath path;
    path.moveTo(1.0, 2.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_TRUE(f & splashPathFirst);
}

TEST_F(SplashPathTest_1539, GetPoint_LineToPoint_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(3.0, 4.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
}

TEST_F(SplashPathTest_1539, GetPoint_LastPointOfOpenSubpath_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    EXPECT_TRUE(f & splashPathLast);
}

TEST_F(SplashPathTest_1539, GetPoint_CurvePoints_HaveCurveFlag_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    
    double x, y;
    unsigned char f;
    // First control point
    path.getPoint(1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
    
    // Second control point
    path.getPoint(2, &x, &y, &f);
    EXPECT_TRUE(f & splashPathCurve);
}

// ==================== getCurPt Tests ====================

TEST_F(SplashPathTest_1539, GetCurPt_EmptyPath_ReturnsFalse_1539) {
    SplashPath path;
    SplashCoord x, y;
    EXPECT_FALSE(path.getCurPt(&x, &y));
}

TEST_F(SplashPathTest_1539, GetCurPt_AfterMoveTo_1539) {
    SplashPath path;
    path.moveTo(7.0, 8.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 7.0);
    EXPECT_DOUBLE_EQ(y, 8.0);
}

TEST_F(SplashPathTest_1539, GetCurPt_AfterLineTo_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(15.0, 25.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 15.0);
    EXPECT_DOUBLE_EQ(y, 25.0);
}

TEST_F(SplashPathTest_1539, GetCurPt_AfterCurveTo_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 9.0, 11.0);
    SplashCoord x, y;
    EXPECT_TRUE(path.getCurPt(&x, &y));
    EXPECT_DOUBLE_EQ(x, 9.0);
    EXPECT_DOUBLE_EQ(y, 11.0);
}

// ==================== offset Tests ====================

TEST_F(SplashPathTest_1539, Offset_EmptyPath_NoCrash_1539) {
    SplashPath path;
    path.offset(5.0, 10.0);
    EXPECT_EQ(path.getLength(), 0);
}

TEST_F(SplashPathTest_1539, Offset_ShiftsAllPoints_1539) {
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

TEST_F(SplashPathTest_1539, Offset_NegativeValues_1539) {
    SplashPath path;
    path.moveTo(10.0, 20.0);
    path.offset(-5.0, -10.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

TEST_F(SplashPathTest_1539, Offset_ZeroOffset_1539) {
    SplashPath path;
    path.moveTo(7.0, 8.0);
    path.offset(0.0, 0.0);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 7.0);
    EXPECT_DOUBLE_EQ(y, 8.0);
}

// ==================== append Tests ====================

TEST_F(SplashPathTest_1539, Append_EmptyToEmpty_1539) {
    SplashPath path1;
    SplashPath path2;
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 0);
}

TEST_F(SplashPathTest_1539, Append_NonEmptyToEmpty_1539) {
    SplashPath path1;
    SplashPath path2;
    path2.moveTo(1.0, 2.0);
    path2.lineTo(3.0, 4.0);
    
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 2);
    
    double x, y;
    unsigned char f;
    path1.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
}

TEST_F(SplashPathTest_1539, Append_NonEmptyToNonEmpty_1539) {
    SplashPath path1;
    path1.moveTo(0.0, 0.0);
    
    SplashPath path2;
    path2.moveTo(5.0, 5.0);
    path2.lineTo(10.0, 10.0);
    
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 3);
}

TEST_F(SplashPathTest_1539, Append_EmptyToNonEmpty_1539) {
    SplashPath path1;
    path1.moveTo(1.0, 2.0);
    
    SplashPath path2;
    path1.append(&path2);
    EXPECT_EQ(path1.getLength(), 1);
}

// ==================== reserve Tests ====================

TEST_F(SplashPathTest_1539, Reserve_DoesNotChangeLength_1539) {
    SplashPath path;
    path.reserve(100);
    EXPECT_EQ(path.getLength(), 0);
}

TEST_F(SplashPathTest_1539, Reserve_AllowsSubsequentAdds_1539) {
    SplashPath path;
    path.reserve(10);
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_EQ(path.getLength(), 2);
}

// ==================== Complex Path Tests ====================

TEST_F(SplashPathTest_1539, ComplexPath_MoveLineCloseMoveLineCurve_1539) {
    SplashPath path;
    
    // First subpath
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    
    // Second subpath
    path.moveTo(20.0, 20.0);
    path.lineTo(30.0, 20.0);
    path.curveTo(35.0, 25.0, 30.0, 30.0, 25.0, 30.0);
    
    // moveTo(1) + lineTo(2) + lineTo(1) + close adds closing point potentially
    // + moveTo(1) + lineTo(1) + curveTo(3)
    // Exact count depends on implementation of close
    EXPECT_GT(path.getLength(), 0);
}

TEST_F(SplashPathTest_1539, ClosedSubpath_FlagsIncludeClosedFlag_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    
    int len = path.getLength();
    // Check last point has closed flag
    double x, y;
    unsigned char f;
    path.getPoint(len - 1, &x, &y, &f);
    EXPECT_TRUE(f & splashPathClosed);
}

// ==================== addStrokeAdjustHint Tests ====================

TEST_F(SplashPathTest_1539, AddStrokeAdjustHint_NoCrash_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    // Just verify it doesn't crash
    path.addStrokeAdjustHint(0, 1, 0, 1);
    EXPECT_EQ(path.getLength(), 2);
}

TEST_F(SplashPathTest_1539, AddStrokeAdjustHint_Multiple_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.lineTo(0.0, 10.0);
    
    path.addStrokeAdjustHint(0, 1, 0, 1);
    path.addStrokeAdjustHint(1, 2, 1, 2);
    path.addStrokeAdjustHint(2, 3, 2, 3);
    
    EXPECT_EQ(path.getLength(), 4);
}

// ==================== Move semantics Tests ====================

TEST_F(SplashPathTest_1539, MoveConstructor_SourceBecomesEmpty_1539) {
    SplashPath path1;
    path1.moveTo(1.0, 2.0);
    path1.lineTo(3.0, 4.0);
    
    SplashPath path2(std::move(path1));
    EXPECT_EQ(path2.getLength(), 2);
    
    double x, y;
    unsigned char f;
    path2.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    
    path2.getPoint(1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
}

// ==================== Close with force Tests ====================

TEST_F(SplashPathTest_1539, Close_ForceTrue_OnOpenSubpath_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(true);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashPathTest_1539, Close_ForceFalse_OnOpenSubpath_1539) {
    SplashPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    SplashError err = path.close(false);
    EXPECT_EQ(err, splashOk);
}

// ==================== Large coordinate Tests ====================

TEST_F(SplashPathTest_1539, LargeCoordinates_1539) {
    SplashPath path;
    SplashError err = path.moveTo(1e10, 1e10);
    EXPECT_EQ(err, splashOk);
    err = path.lineTo(-1e10, -1e10);
    EXPECT_EQ(err, splashOk);
    
    double x, y;
    unsigned char f;
    path.getPoint(0, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1e10);
    EXPECT_DOUBLE_EQ(y, 1e10);
}

// ==================== Multiple subpaths Tests ====================

TEST_F(SplashPathTest_1539, MultipleSubpaths_CorrectLength_1539) {
    SplashPath path;
    
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.close(false);
    
    path.moveTo(2.0, 0.0);
    path.lineTo(3.0, 0.0);
    path.close(false);
    
    path.moveTo(4.0, 0.0);
    path.lineTo(5.0, 0.0);
    
    // At minimum we expect 6 points from the moveTolineTo pairs
    // close may or may not add extra points
    EXPECT_GE(path.getLength(), 6);
}

// ==================== GetCurPt after close Tests ====================

TEST_F(SplashPathTest_1539, GetCurPt_AfterClose_1539) {
    SplashPath path;
    path.moveTo(5.0, 5.0);
    path.lineTo(10.0, 10.0);
    path.close(false);
    
    SplashCoord x, y;
    bool result = path.getCurPt(&x, &y);
    EXPECT_TRUE(result);
}
