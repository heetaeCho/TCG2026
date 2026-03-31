#include <gtest/gtest.h>
#include <tuple>

// Include the PDFRectangle definition
#include "poppler/PDFRectangle.h"

// We need access to the static function. Include the .cc file to get it.
// This is necessary because calculateDxDy has internal linkage (static).
#include "poppler/Form.cc"

class CalculateDxDyTest_1514 : public ::testing::Test {
protected:
    PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
        return PDFRectangle(x1, y1, x2, y2);
    }
};

// Test default rotation (0 degrees)
TEST_F(CalculateDxDyTest_1514, Rot0_ReturnsDxDy_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, 40.0); // x2 - x1 = 50 - 10
    EXPECT_DOUBLE_EQ(dy, 60.0); // y2 - y1 = 80 - 20
}

// Test rotation 90 degrees
TEST_F(CalculateDxDyTest_1514, Rot90_ReturnsSwappedDimensions_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(90, &rect);
    EXPECT_DOUBLE_EQ(dx, 60.0); // y2 - y1 = 80 - 20
    EXPECT_DOUBLE_EQ(dy, 40.0); // x2 - x1 = 50 - 10
}

// Test rotation 180 degrees
TEST_F(CalculateDxDyTest_1514, Rot180_ReturnsExpectedValues_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(180, &rect);
    EXPECT_DOUBLE_EQ(dx, -30.0); // x2 - y2 = 50 - 80
    EXPECT_DOUBLE_EQ(dy, 60.0);  // y2 - y1 = 80 - 20
}

// Test rotation 270 degrees
TEST_F(CalculateDxDyTest_1514, Rot270_ReturnsSwappedDimensions_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(270, &rect);
    EXPECT_DOUBLE_EQ(dx, 60.0); // y2 - y1 = 80 - 20
    EXPECT_DOUBLE_EQ(dy, 40.0); // x2 - x1 = 50 - 10
}

// Test that an unrecognized rotation falls through to the default (same as 0)
TEST_F(CalculateDxDyTest_1514, UnrecognizedRotFallsToDefault_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(45, &rect);
    EXPECT_DOUBLE_EQ(dx, 40.0); // x2 - x1
    EXPECT_DOUBLE_EQ(dy, 60.0); // y2 - y1
}

// Test negative rotation value falls to default
TEST_F(CalculateDxDyTest_1514, NegativeRotFallsToDefault_1514) {
    PDFRectangle rect = makeRect(5.0, 10.0, 25.0, 40.0);
    auto [dx, dy] = calculateDxDy(-90, &rect);
    EXPECT_DOUBLE_EQ(dx, 20.0); // x2 - x1 = 25 - 5
    EXPECT_DOUBLE_EQ(dy, 30.0); // y2 - y1 = 40 - 10
}

// Test with a zero-size rectangle
TEST_F(CalculateDxDyTest_1514, ZeroSizeRect_Rot0_1514) {
    PDFRectangle rect = makeRect(0.0, 0.0, 0.0, 0.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, 0.0);
    EXPECT_DOUBLE_EQ(dy, 0.0);
}

// Test with a zero-size rectangle at rotation 90
TEST_F(CalculateDxDyTest_1514, ZeroSizeRect_Rot90_1514) {
    PDFRectangle rect = makeRect(0.0, 0.0, 0.0, 0.0);
    auto [dx, dy] = calculateDxDy(90, &rect);
    EXPECT_DOUBLE_EQ(dx, 0.0);
    EXPECT_DOUBLE_EQ(dy, 0.0);
}

// Test with negative coordinates
TEST_F(CalculateDxDyTest_1514, NegativeCoordinates_Rot0_1514) {
    PDFRectangle rect = makeRect(-30.0, -20.0, -10.0, -5.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, 20.0);  // -10 - (-30) = 20
    EXPECT_DOUBLE_EQ(dy, 15.0);  // -5 - (-20) = 15
}

// Test with negative coordinates at rotation 90
TEST_F(CalculateDxDyTest_1514, NegativeCoordinates_Rot90_1514) {
    PDFRectangle rect = makeRect(-30.0, -20.0, -10.0, -5.0);
    auto [dx, dy] = calculateDxDy(90, &rect);
    EXPECT_DOUBLE_EQ(dx, 15.0);  // y2 - y1 = -5 - (-20) = 15
    EXPECT_DOUBLE_EQ(dy, 20.0);  // x2 - x1 = -10 - (-30) = 20
}

// Test rotation 180 with specific values where x2 > y2
TEST_F(CalculateDxDyTest_1514, Rot180_X2GreaterThanY2_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 100.0, 50.0);
    auto [dx, dy] = calculateDxDy(180, &rect);
    EXPECT_DOUBLE_EQ(dx, 50.0);  // x2 - y2 = 100 - 50
    EXPECT_DOUBLE_EQ(dy, 30.0);  // y2 - y1 = 50 - 20
}

// Test with very large values
TEST_F(CalculateDxDyTest_1514, LargeValues_Rot0_1514) {
    PDFRectangle rect = makeRect(0.0, 0.0, 1e6, 1e6);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, 1e6);
    EXPECT_DOUBLE_EQ(dy, 1e6);
}

// Test with very small (fractional) values
TEST_F(CalculateDxDyTest_1514, SmallFractionalValues_Rot0_1514) {
    PDFRectangle rect = makeRect(0.001, 0.002, 0.003, 0.004);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_NEAR(dx, 0.002, 1e-10);
    EXPECT_NEAR(dy, 0.002, 1e-10);
}

// Test rotation 360 falls to default (same as 0)
TEST_F(CalculateDxDyTest_1514, Rot360FallsToDefault_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx, dy] = calculateDxDy(360, &rect);
    EXPECT_DOUBLE_EQ(dx, 40.0);
    EXPECT_DOUBLE_EQ(dy, 60.0);
}

// Test that rot 90 and rot 270 produce the same result
TEST_F(CalculateDxDyTest_1514, Rot90And270ProduceSameResult_1514) {
    PDFRectangle rect = makeRect(10.0, 20.0, 50.0, 80.0);
    auto [dx90, dy90] = calculateDxDy(90, &rect);
    auto [dx270, dy270] = calculateDxDy(270, &rect);
    EXPECT_DOUBLE_EQ(dx90, dx270);
    EXPECT_DOUBLE_EQ(dy90, dy270);
}

// Test unit rectangle at origin
TEST_F(CalculateDxDyTest_1514, UnitRectAtOrigin_Rot0_1514) {
    PDFRectangle rect = makeRect(0.0, 0.0, 1.0, 1.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, 1.0);
    EXPECT_DOUBLE_EQ(dy, 1.0);
}

// Test unit rectangle at origin rot 180
TEST_F(CalculateDxDyTest_1514, UnitRectAtOrigin_Rot180_1514) {
    PDFRectangle rect = makeRect(0.0, 0.0, 1.0, 1.0);
    auto [dx, dy] = calculateDxDy(180, &rect);
    EXPECT_DOUBLE_EQ(dx, 0.0);  // x2 - y2 = 1 - 1 = 0
    EXPECT_DOUBLE_EQ(dy, 1.0);  // y2 - y1 = 1 - 0 = 1
}

// Test where x1 > x2 (inverted rectangle)
TEST_F(CalculateDxDyTest_1514, InvertedRectangle_Rot0_1514) {
    PDFRectangle rect = makeRect(50.0, 80.0, 10.0, 20.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    EXPECT_DOUBLE_EQ(dx, -40.0); // x2 - x1 = 10 - 50
    EXPECT_DOUBLE_EQ(dy, -60.0); // y2 - y1 = 20 - 80
}
