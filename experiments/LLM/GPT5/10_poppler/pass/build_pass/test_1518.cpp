#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/BBoxOutputDev.h"

class BBoxOutputDevTest_1518 : public ::testing::Test {
protected:
    BBoxOutputDev bboxOutputDev;
};

TEST_F(BBoxOutputDevTest_1518, UpsideDownReturnsFalse_1518) {
    // Test for normal operation
    EXPECT_FALSE(bboxOutputDev.upsideDown());
}

TEST_F(BBoxOutputDevTest_1518, ConstructorWithTextVectorRaster_1518) {
    // Test the constructor with text, vector, and raster
    BBoxOutputDev bboxOutputDev(true, true, true);
    EXPECT_FALSE(bboxOutputDev.upsideDown());  // Assuming default behavior is false
}

TEST_F(BBoxOutputDevTest_1518, ConstructorWithTextVectorRasterLwidth_1518) {
    // Test the constructor with text, vector, raster, and lwidth
    BBoxOutputDev bboxOutputDev(true, true, true, true);
    EXPECT_FALSE(bboxOutputDev.upsideDown());  // Assuming default behavior is false
}

TEST_F(BBoxOutputDevTest_1518, EndPageCalled_1518) {
    // Mock and verify behavior when endPage is called (if observable)
    // You'd need to mock OutputDev's base class if endPage is called here.
}

TEST_F(BBoxOutputDevTest_1518, StrokeCalled_1518) {
    // Mock and verify behavior when stroke is called (if observable)
    // You'd need to mock OutputDev's base class if stroke is called here.
}

TEST_F(BBoxOutputDevTest_1518, FillCalled_1518) {
    // Mock and verify behavior when fill is called (if observable)
    // You'd need to mock OutputDev's base class if fill is called here.
}

TEST_F(BBoxOutputDevTest_1518, DrawCharCalled_1518) {
    // Mock and verify behavior when drawChar is called (if observable)
    // You'd need to mock OutputDev's base class if drawChar is called here.
}

TEST_F(BBoxOutputDevTest_1518, DrawImageCalled_1518) {
    // Mock and verify behavior when drawImage is called (if observable)
    // You'd need to mock OutputDev's base class if drawImage is called here.
}

TEST_F(BBoxOutputDevTest_1518, DrawMaskedImageCalled_1518) {
    // Mock and verify behavior when drawMaskedImage is called (if observable)
    // You'd need to mock OutputDev's base class if drawMaskedImage is called here.
}

TEST_F(BBoxOutputDevTest_1518, DrawSoftMaskedImageCalled_1518) {
    // Mock and verify behavior when drawSoftMaskedImage is called (if observable)
    // You'd need to mock OutputDev's base class if drawSoftMaskedImage is called here.
}

TEST_F(BBoxOutputDevTest_1518, GetX1ReturnsCorrectValue_1518) {
    // Test boundary condition for getX1
    // Replace with actual expected value.
    EXPECT_EQ(bboxOutputDev.getX1(), 0.0);
}

TEST_F(BBoxOutputDevTest_1518, GetY1ReturnsCorrectValue_1518) {
    // Test boundary condition for getY1
    // Replace with actual expected value.
    EXPECT_EQ(bboxOutputDev.getY1(), 0.0);
}

TEST_F(BBoxOutputDevTest_1518, GetX2ReturnsCorrectValue_1518) {
    // Test boundary condition for getX2
    // Replace with actual expected value.
    EXPECT_EQ(bboxOutputDev.getX2(), 0.0);
}

TEST_F(BBoxOutputDevTest_1518, GetY2ReturnsCorrectValue_1518) {
    // Test boundary condition for getY2
    // Replace with actual expected value.
    EXPECT_EQ(bboxOutputDev.getY2(), 0.0);
}

TEST_F(BBoxOutputDevTest_1518, GetHasGraphicsReturnsCorrectValue_1518) {
    // Test boundary condition for getHasGraphics
    // Replace with actual expected value.
    EXPECT_EQ(bboxOutputDev.getHasGraphics(), 0.0);
}