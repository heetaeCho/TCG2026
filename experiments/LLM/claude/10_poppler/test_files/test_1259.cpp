#include <gtest/gtest.h>
#include <QPainterPath>
#include "GfxState.h"

// Since convertPath is a static function in the .cc file, we need to either
// include it or replicate its signature for testing. We'll include the source
// or declare it. Since it's static, we need to include the .cc file directly
// to access it in tests.
// 
// We include the implementation file to get access to the static function.
// This is a common technique for testing static (file-scope) functions.

// Forward declare or include necessary headers
#include "QPainterOutputDev.h"

// We need access to the static function. Since it's static in the .cc file,
// we include the .cc file to make it accessible.
// However, this may cause linking issues. An alternative approach is to
// define a wrapper or use a test-specific compilation unit.

// For testing purposes, we replicate the function signature and include the source:
namespace {
#include "QPainterOutputDev.cc"
}

class ConvertPathTest_1259 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty path with no subpaths returns an empty QPainterPath
TEST_F(ConvertPathTest_1259, EmptyPath_ReturnsEmptyQPainterPath_1259) {
    GfxPath path;
    // path has no subpaths by default
    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_TRUE(result.isEmpty());
    EXPECT_EQ(result.elementCount(), 0);
}

// Test: Single subpath with one point (moveTo only, no lines or curves)
TEST_F(ConvertPathTest_1259, SinglePointSubpath_MoveToOnly_1259) {
    GfxPath path;
    path.moveTo(10.0, 20.0);
    // After moveTo, there's a subpath with one point but no lines yet
    // We need to add at least a lineTo to create a subpath entry
    // Actually, moveTo alone sets justMoved but may not create a full subpath
    // Let's add a lineTo to ensure a subpath is created
    path.lineTo(10.0, 20.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.fillRule(), Qt::WindingFill);
}

// Test: Fill rule is set correctly - WindingFill
TEST_F(ConvertPathTest_1259, FillRuleWindingFill_1259) {
    GfxPath path;
    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_EQ(result.fillRule(), Qt::WindingFill);
}

// Test: Fill rule is set correctly - OddEvenFill
TEST_F(ConvertPathTest_1259, FillRuleOddEvenFill_1259) {
    GfxPath path;
    QPainterPath result = convertPath(&path, Qt::OddEvenFill);
    EXPECT_EQ(result.fillRule(), Qt::OddEvenFill);
}

// Test: Single subpath with a line segment
TEST_F(ConvertPathTest_1259, SingleLineSubpath_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(100.0, 200.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    // Should have at least 2 elements: moveTo and lineTo
    EXPECT_GE(result.elementCount(), 2);

    // Check the first element is a moveTo at (0,0)
    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_EQ(elem0.type, QPainterPath::MoveToElement);
    EXPECT_DOUBLE_EQ(elem0.x, 0.0);
    EXPECT_DOUBLE_EQ(elem0.y, 0.0);

    // Check the second element is a lineTo at (100, 200)
    QPainterPath::Element elem1 = result.elementAt(1);
    EXPECT_EQ(elem1.type, QPainterPath::LineToElement);
    EXPECT_DOUBLE_EQ(elem1.x, 100.0);
    EXPECT_DOUBLE_EQ(elem1.y, 200.0);
}

// Test: Single subpath with multiple line segments
TEST_F(ConvertPathTest_1259, MultipleLineSegments_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.lineTo(0.0, 10.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_EQ(result.elementCount(), 4); // moveTo + 3 lineTo
}

// Test: Closed subpath
TEST_F(ConvertPathTest_1259, ClosedSubpath_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(10.0, 10.0);
    path.close();

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    // The path should be closed - check by verifying the current position
    // returns to the start
    QPointF currentPos = result.currentPosition();
    EXPECT_DOUBLE_EQ(currentPos.x(), 0.0);
    EXPECT_DOUBLE_EQ(currentPos.y(), 0.0);
}

// Test: Subpath with cubic Bezier curve
TEST_F(ConvertPathTest_1259, CubicBezierCurve_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    // Should have: moveTo + 3 elements for cubic (CurveToElement + 2 CurveToDataElement)
    EXPECT_EQ(result.elementCount(), 4);

    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_EQ(elem0.type, QPainterPath::MoveToElement);
    EXPECT_DOUBLE_EQ(elem0.x, 0.0);
    EXPECT_DOUBLE_EQ(elem0.y, 0.0);

    QPainterPath::Element elem1 = result.elementAt(1);
    EXPECT_EQ(elem1.type, QPainterPath::CurveToElement);
    EXPECT_DOUBLE_EQ(elem1.x, 10.0);
    EXPECT_DOUBLE_EQ(elem1.y, 20.0);

    QPainterPath::Element elem2 = result.elementAt(2);
    EXPECT_EQ(elem2.type, QPainterPath::CurveToDataElement);
    EXPECT_DOUBLE_EQ(elem2.x, 30.0);
    EXPECT_DOUBLE_EQ(elem2.y, 40.0);

    QPainterPath::Element elem3 = result.elementAt(3);
    EXPECT_EQ(elem3.type, QPainterPath::CurveToDataElement);
    EXPECT_DOUBLE_EQ(elem3.x, 50.0);
    EXPECT_DOUBLE_EQ(elem3.y, 60.0);
}

// Test: Mixed lines and curves in a single subpath
TEST_F(ConvertPathTest_1259, MixedLinesAndCurves_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.curveTo(20.0, 10.0, 30.0, 20.0, 40.0, 0.0);
    path.lineTo(50.0, 0.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    // moveTo(1) + lineTo(1) + cubicTo(3) + lineTo(1) = 6 elements
    EXPECT_EQ(result.elementCount(), 6);
}

// Test: Multiple subpaths
TEST_F(ConvertPathTest_1259, MultipleSubpaths_1259) {
    GfxPath path;
    // First subpath
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 10.0);
    // Second subpath
    path.moveTo(20.0, 20.0);
    path.lineTo(30.0, 30.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    // First subpath: moveTo + lineTo = 2
    // Second subpath: moveTo + lineTo = 2
    // Total: 4 elements
    EXPECT_EQ(result.elementCount(), 4);
}

// Test: Subpath with negative coordinates
TEST_F(ConvertPathTest_1259, NegativeCoordinates_1259) {
    GfxPath path;
    path.moveTo(-10.0, -20.0);
    path.lineTo(-30.0, -40.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_DOUBLE_EQ(elem0.x, -10.0);
    EXPECT_DOUBLE_EQ(elem0.y, -20.0);

    QPainterPath::Element elem1 = result.elementAt(1);
    EXPECT_DOUBLE_EQ(elem1.x, -30.0);
    EXPECT_DOUBLE_EQ(elem1.y, -40.0);
}

// Test: Subpath with zero coordinates
TEST_F(ConvertPathTest_1259, ZeroCoordinates_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(0.0, 0.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);

    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_DOUBLE_EQ(elem0.x, 0.0);
    EXPECT_DOUBLE_EQ(elem0.y, 0.0);
}

// Test: Large coordinates
TEST_F(ConvertPathTest_1259, LargeCoordinates_1259) {
    GfxPath path;
    path.moveTo(1e10, 1e10);
    path.lineTo(-1e10, -1e10);

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_FALSE(result.isEmpty());

    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_DOUBLE_EQ(elem0.x, 1e10);
    EXPECT_DOUBLE_EQ(elem0.y, 1e10);

    QPainterPath::Element elem1 = result.elementAt(1);
    EXPECT_DOUBLE_EQ(elem1.x, -1e10);
    EXPECT_DOUBLE_EQ(elem1.y, -1e10);
}

// Test: Multiple curves in sequence
TEST_F(ConvertPathTest_1259, MultipleCurvesInSequence_1259) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    path.curveTo(7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    QPainterPath result = convertPath(&path, Qt::WindingFill);

    // moveTo(1) + cubicTo(3) + cubicTo(3) = 7
    EXPECT_EQ(result.elementCount(), 7);
}

// Test: Closed subpath followed by open subpath
TEST_F(ConvertPathTest_1259, ClosedFollowedByOpenSubpath_1259) {
    GfxPath path;
    // First subpath - closed triangle
    path.moveTo(0.0, 0.0);
    path.lineTo(10.0, 0.0);
    path.lineTo(5.0, 10.0);
    path.close();

    // Second subpath - open line
    path.moveTo(20.0, 20.0);
    path.lineTo(30.0, 30.0);

    QPainterPath result = convertPath(&path, Qt::OddEvenFill);
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.fillRule(), Qt::OddEvenFill);
}

// Test: Subpath with only moveTo (single point, no additional points)
TEST_F(ConvertPathTest_1259, SubpathSinglePoint_1259) {
    GfxPath path;
    path.moveTo(5.0, 5.0);
    // Force creating a subpath by adding another move
    // Just moveTo creates a pending point but may not create a subpath with lines
    path.lineTo(5.0, 5.0); // degenerate line

    QPainterPath result = convertPath(&path, Qt::WindingFill);
    EXPECT_GE(result.elementCount(), 1);
}

// Test: Very small floating point coordinates
TEST_F(ConvertPathTest_1259, VerySmallCoordinates_1259) {
    GfxPath path;
    path.moveTo(1e-15, 1e-15);
    path.lineTo(2e-15, 2e-15);

    QPainterPath result = convertPath(&path, Qt::WindingFill);

    QPainterPath::Element elem0 = result.elementAt(0);
    EXPECT_DOUBLE_EQ(elem0.x, 1e-15);
    EXPECT_DOUBLE_EQ(elem0.y, 1e-15);
}
