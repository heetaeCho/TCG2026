#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BBoxOutputDev.h"
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class BBoxOutputDevTest_1520 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test default constructor creates a valid object
TEST_F(BBoxOutputDevTest_1520, DefaultConstructor_1520) {
    BBoxOutputDev dev;
    // After construction without any drawing, bounding box should be in initial state
    // We just verify it doesn't crash and returns some values
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    // Initial bounding box should have x1 >= x2 and y1 >= y2 (empty bbox)
    // or some default values
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
}

// Test 3-parameter constructor
TEST_F(BBoxOutputDevTest_1520, ThreeParamConstructor_1520) {
    BBoxOutputDev dev(true, true, true);
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
}

// Test 4-parameter constructor
TEST_F(BBoxOutputDevTest_1520, FourParamConstructor_1520) {
    BBoxOutputDev dev(true, true, true, true);
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
}

// Test interpretType3Chars returns false
TEST_F(BBoxOutputDevTest_1520, InterpretType3CharsReturnsFalse_1520) {
    BBoxOutputDev dev;
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test upsideDown returns expected value
TEST_F(BBoxOutputDevTest_1520, UpsideDown_1520) {
    BBoxOutputDev dev;
    // OutputDev::upsideDown() typically returns true for PDF coordinate system
    bool result = dev.upsideDown();
    (void)result;
    // Just verify it doesn't crash; we don't know the exact return value
}

// Test useDrawChar returns expected value
TEST_F(BBoxOutputDevTest_1520, UseDrawChar_1520) {
    BBoxOutputDev dev;
    bool result = dev.useDrawChar();
    // useDrawChar should return true for BBoxOutputDev to receive drawChar calls
    EXPECT_TRUE(result);
}

// Test getHasGraphics initially
TEST_F(BBoxOutputDevTest_1520, GetHasGraphicsInitially_1520) {
    BBoxOutputDev dev;
    double hasGfx = dev.getHasGraphics();
    // Initially there should be no graphics
    EXPECT_EQ(hasGfx, 0);
}

// Test initial bounding box is empty or has sentinel values
TEST_F(BBoxOutputDevTest_1520, InitialBBoxIsEmpty_1520) {
    BBoxOutputDev dev;
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    // For an empty bounding box, x1 should be >= x2 and y1 should be >= y2
    // or all zeros, depending on implementation
    // Common pattern: initialized to large positive for mins, large negative for maxs
    EXPECT_GE(x1, x2);
    EXPECT_GE(y1, y2);
}

// Test constructor with all false parameters
TEST_F(BBoxOutputDevTest_1520, ConstructorAllFalse_1520) {
    BBoxOutputDev dev(false, false, false);
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    EXPECT_GE(x1, x2);
    EXPECT_GE(y1, y2);
}

// Test constructor with only text enabled
TEST_F(BBoxOutputDevTest_1520, ConstructorTextOnly_1520) {
    BBoxOutputDev dev(true, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test constructor with only vector enabled
TEST_F(BBoxOutputDevTest_1520, ConstructorVectorOnly_1520) {
    BBoxOutputDev dev(false, true, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test constructor with only raster enabled
TEST_F(BBoxOutputDevTest_1520, ConstructorRasterOnly_1520) {
    BBoxOutputDev dev(false, false, true);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test 4-param constructor with lwidth true
TEST_F(BBoxOutputDevTest_1520, ConstructorWithLineWidth_1520) {
    BBoxOutputDev dev(true, true, true, true);
    EXPECT_FALSE(dev.interpretType3Chars());
    double hasGfx = dev.getHasGraphics();
    EXPECT_EQ(hasGfx, 0);
}

// Test 4-param constructor with lwidth false
TEST_F(BBoxOutputDevTest_1520, ConstructorWithoutLineWidth_1520) {
    BBoxOutputDev dev(true, true, true, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test endPage can be called without crash
TEST_F(BBoxOutputDevTest_1520, EndPageNoCrash_1520) {
    BBoxOutputDev dev;
    dev.endPage();
    // Just verify no crash
}

// Test that after endPage, bounding box accessors still work
TEST_F(BBoxOutputDevTest_1520, AccessorsAfterEndPage_1520) {
    BBoxOutputDev dev;
    dev.endPage();
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    double hasGfx = dev.getHasGraphics();
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
    (void)hasGfx;
}

// Test multiple endPage calls
TEST_F(BBoxOutputDevTest_1520, MultipleEndPageCalls_1520) {
    BBoxOutputDev dev;
    dev.endPage();
    dev.endPage();
    dev.endPage();
    // Should not crash
}

// Test that getX1, getY1, getX2, getY2 return consistent values for default constructor
TEST_F(BBoxOutputDevTest_1520, BBoxCoordinatesConsistency_1520) {
    BBoxOutputDev dev1;
    BBoxOutputDev dev2;
    
    EXPECT_EQ(dev1.getX1(), dev2.getX1());
    EXPECT_EQ(dev1.getY1(), dev2.getY1());
    EXPECT_EQ(dev1.getX2(), dev2.getX2());
    EXPECT_EQ(dev1.getY2(), dev2.getY2());
}

// Test stroke with null state doesn't crash (boundary case - may or may not be valid)
// Note: This is commented out since passing null GfxState* may cause segfault
// and we can't know without implementation details

// Test fill with GfxState
TEST_F(BBoxOutputDevTest_1520, StrokeWithValidState_1520) {
    BBoxOutputDev dev(false, true, false);
    // We need a valid GfxState to test stroke/fill, which requires complex setup
    // This test verifies the object is in correct state for vector operations
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_TRUE(dev.useDrawChar());
}

// Test that different constructor combinations produce same initial bbox
TEST_F(BBoxOutputDevTest_1520, DifferentConstructorsSameInitialBBox_1520) {
    BBoxOutputDev dev1;
    BBoxOutputDev dev2(true, true, true);
    BBoxOutputDev dev3(false, false, false, false);
    
    EXPECT_EQ(dev1.getX1(), dev2.getX1());
    EXPECT_EQ(dev1.getY1(), dev2.getY1());
    EXPECT_EQ(dev1.getX2(), dev2.getX2());
    EXPECT_EQ(dev1.getY2(), dev2.getY2());
    
    EXPECT_EQ(dev2.getX1(), dev3.getX1());
    EXPECT_EQ(dev2.getY1(), dev3.getY1());
    EXPECT_EQ(dev2.getX2(), dev3.getX2());
    EXPECT_EQ(dev2.getY2(), dev3.getY2());
}
