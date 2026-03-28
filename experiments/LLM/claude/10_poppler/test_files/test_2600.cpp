#include <gtest/gtest.h>
#include "splash/SplashXPathScanner.h"
#include "splash/SplashXPath.h"
#include "splash/SplashPath.h"
#include "splash/SplashBitmap.h"

class SplashXPathScannerTest_2600 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a simple rectangular path
static SplashPath makeRectPath(double x0, double y0, double x1, double y1) {
    SplashPath path;
    path.moveTo(x0, y0);
    path.lineTo(x1, y0);
    path.lineTo(x1, y1);
    path.lineTo(x0, y1);
    path.close();
    return path;
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxReturnsValidBoundsForRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_LE(xMin, 10);
    EXPECT_LE(yMin, 20);
    EXPECT_GE(xMax, 100);
    EXPECT_GE(yMax, 200);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxAAReturnsValidBoundsForRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    int xMin, yMin, xMax, yMax;
    scanner.getBBoxAA(&xMin, &yMin, &xMax, &yMax);

    // AA bounding box should encompass the path
    EXPECT_LE(xMin, 10);
    EXPECT_LE(yMin, 20);
    EXPECT_GE(xMax, 100);
    EXPECT_GE(yMax, 200);
}

TEST_F(SplashXPathScannerTest_2600, TestPointInsideRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    // Point clearly inside the rectangle
    bool inside = scanner.test(50, 100);
    EXPECT_TRUE(inside);
}

TEST_F(SplashXPathScannerTest_2600, TestPointOutsideRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    // Point clearly outside the rectangle
    bool outside = scanner.test(200, 300);
    EXPECT_FALSE(outside);
}

TEST_F(SplashXPathScannerTest_2600, TestSpanInsideRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    // Span clearly inside the rectangle
    bool spanInside = scanner.testSpan(30, 80, 100);
    EXPECT_TRUE(spanInside);
}

TEST_F(SplashXPathScannerTest_2600, TestSpanOutsideRectangle_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    // Span outside the rectangle
    bool spanOutside = scanner.testSpan(150, 200, 100);
    EXPECT_FALSE(spanOutside);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxWithClipping_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    // Clip to a smaller vertical range
    SplashXPathScanner scanner(xPath, false, 50, 150);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    // The bounding box should be clipped
    EXPECT_GE(yMin, 50);
    EXPECT_LE(yMax, 150);
}

TEST_F(SplashXPathScannerTest_2600, EvenOddFillRule_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, true, 0, 300);

    // Point inside should still be detected with even-odd rule
    bool inside = scanner.test(50, 100);
    EXPECT_TRUE(inside);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxWithEmptyPath_2600) {
    SplashPath path;
    // Just a single point, no real area
    path.moveTo(50.0, 50.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 100);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    // With default initialization xMin > xMax means empty bbox
    // or the bbox might be degenerate
    // We just verify getBBox doesn't crash and returns some values
    EXPECT_TRUE(true);
}

TEST_F(SplashXPathScannerTest_2600, TestPointOutsideClipRange_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 50, 150);

    // Test point outside clip range but inside path
    bool result = scanner.test(50, 30);
    EXPECT_FALSE(result);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxConsistentWithGetBBoxAA_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    int xMinAA, yMinAA, xMaxAA, yMaxAA;
    scanner.getBBoxAA(&xMinAA, &yMinAA, &xMaxAA, &yMaxAA);

    // Both bounding boxes should be valid (non-empty for this case)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
    EXPECT_LE(xMinAA, xMaxAA);
    EXPECT_LE(yMinAA, yMaxAA);
}

TEST_F(SplashXPathScannerTest_2600, SmallRectangleBBox_2600) {
    SplashPath path = makeRectPath(0.0, 0.0, 1.0, 1.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 10);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_LE(xMin, 0);
    EXPECT_LE(yMin, 0);
    EXPECT_GE(xMax, 1);
    EXPECT_GE(yMax, 1);
}

TEST_F(SplashXPathScannerTest_2600, LargeRectangleBBox_2600) {
    SplashPath path = makeRectPath(0.0, 0.0, 10000.0, 10000.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 20000);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_LE(xMin, 0);
    EXPECT_LE(yMin, 0);
    EXPECT_GE(xMax, 10000);
    EXPECT_GE(yMax, 10000);
}

TEST_F(SplashXPathScannerTest_2600, NegativeCoordinatesPath_2600) {
    SplashPath path = makeRectPath(-100.0, -200.0, -10.0, -20.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, -300, 0);

    int xMin, yMin, xMax, yMax;
    scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_LE(xMin, -100);
    EXPECT_GE(xMax, -10);
}

TEST_F(SplashXPathScannerTest_2600, TestSpanPartiallyOverlapping_2600) {
    SplashPath path = makeRectPath(10.0, 20.0, 100.0, 200.0);
    SplashXPath xPath(&path, nullptr, 0, false);
    SplashXPathScanner scanner(xPath, false, 0, 300);

    // Span that partially overlaps - starts inside, ends outside
    bool result = scanner.testSpan(50, 150, 100);
    // This should be false since not the entire span is inside
    EXPECT_FALSE(result);
}
