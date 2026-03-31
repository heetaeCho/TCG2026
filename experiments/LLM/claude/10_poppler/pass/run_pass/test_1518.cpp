#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BBoxOutputDev.h"

// Test fixture for BBoxOutputDev
class BBoxOutputDevTest_1518 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates a valid object
TEST_F(BBoxOutputDevTest_1518, DefaultConstructor_1518) {
    BBoxOutputDev dev;
    // After construction with no operations, bounding box should be in initial state
    // We just verify the object is constructible and getters don't crash
    (void)dev.getX1();
    (void)dev.getY1();
    (void)dev.getX2();
    (void)dev.getY2();
    (void)dev.getHasGraphics();
}

// Test three-argument constructor
TEST_F(BBoxOutputDevTest_1518, ThreeArgConstructor_1518) {
    BBoxOutputDev dev(true, true, true);
    (void)dev.getX1();
    (void)dev.getY1();
    (void)dev.getX2();
    (void)dev.getY2();
    (void)dev.getHasGraphics();
}

// Test four-argument constructor
TEST_F(BBoxOutputDevTest_1518, FourArgConstructor_1518) {
    BBoxOutputDev dev(true, true, true, true);
    (void)dev.getX1();
    (void)dev.getY1();
    (void)dev.getX2();
    (void)dev.getY2();
}

// Test constructor with all flags disabled
TEST_F(BBoxOutputDevTest_1518, ConstructorAllFlagsDisabled_1518) {
    BBoxOutputDev dev(false, false, false);
    (void)dev.getX1();
    (void)dev.getY1();
    (void)dev.getX2();
    (void)dev.getY2();
    (void)dev.getHasGraphics();
}

// Test four-argument constructor with all flags disabled
TEST_F(BBoxOutputDevTest_1518, FourArgConstructorAllFlagsDisabled_1518) {
    BBoxOutputDev dev(false, false, false, false);
    (void)dev.getX1();
    (void)dev.getY1();
    (void)dev.getX2();
    (void)dev.getY2();
}

// Test upsideDown returns false
TEST_F(BBoxOutputDevTest_1518, UpsideDownReturnsFalse_1518) {
    BBoxOutputDev dev;
    EXPECT_FALSE(dev.upsideDown());
}

// Test useDrawChar returns expected value
TEST_F(BBoxOutputDevTest_1518, UseDrawChar_1518) {
    BBoxOutputDev dev;
    // useDrawChar is overridden; we just verify it returns a boolean without crashing
    bool result = dev.useDrawChar();
    // Typically OutputDev implementations that override drawChar return true
    EXPECT_TRUE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(BBoxOutputDevTest_1518, InterpretType3Chars_1518) {
    BBoxOutputDev dev;
    // Just verify it returns a boolean without crashing
    (void)dev.interpretType3Chars();
}

// Test getHasGraphics on freshly constructed object (no graphics drawn)
TEST_F(BBoxOutputDevTest_1518, InitialHasGraphicsFalse_1518) {
    BBoxOutputDev dev;
    // No drawing operations performed, so hasGraphics should be false (0)
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

// Test that bounding box coordinates are accessible after default construction
TEST_F(BBoxOutputDevTest_1518, InitialBoundingBoxValues_1518) {
    BBoxOutputDev dev;
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    // Initially, the bounding box should be empty or zero-sized
    // x1 >= x2 and y1 >= y2 would indicate no valid bbox, or all could be 0
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
}

// Test endPage can be called without crashing
TEST_F(BBoxOutputDevTest_1518, EndPageNoCrash_1518) {
    BBoxOutputDev dev;
    dev.endPage();
    // Just verifying no crash occurs
}

// Test that with text disabled, the bounding box is not updated by drawChar
// (This tests the text flag behavior through the three-arg constructor)
TEST_F(BBoxOutputDevTest_1518, TextDisabledNoUpdate_1518) {
    BBoxOutputDev devNoText(false, true, true);
    // Without a valid GfxState we can't call drawChar, but we verify construction
    double hasGraphics = devNoText.getHasGraphics();
    EXPECT_EQ(hasGraphics, 0);
}

// Test mixed constructor flags
TEST_F(BBoxOutputDevTest_1518, MixedFlags_TextOnly_1518) {
    BBoxOutputDev dev(true, false, false);
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

TEST_F(BBoxOutputDevTest_1518, MixedFlags_VectorOnly_1518) {
    BBoxOutputDev dev(false, true, false);
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

TEST_F(BBoxOutputDevTest_1518, MixedFlags_RasterOnly_1518) {
    BBoxOutputDev dev(false, false, true);
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

// Test four-arg with lwidth enabled
TEST_F(BBoxOutputDevTest_1518, FourArgLwidthEnabled_1518) {
    BBoxOutputDev dev(true, true, true, true);
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

// Test four-arg with lwidth disabled but others enabled
TEST_F(BBoxOutputDevTest_1518, FourArgLwidthDisabled_1518) {
    BBoxOutputDev dev(true, true, true, false);
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.getHasGraphics(), 0);
}

// Test that multiple calls to endPage don't crash
TEST_F(BBoxOutputDevTest_1518, MultipleEndPageCalls_1518) {
    BBoxOutputDev dev;
    dev.endPage();
    dev.endPage();
    dev.endPage();
    // No crash expected
}

// Verify consistent return from upsideDown across calls
TEST_F(BBoxOutputDevTest_1518, UpsideDownConsistent_1518) {
    BBoxOutputDev dev;
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_EQ(dev.upsideDown(), dev.upsideDown());
}

// Verify bounding box is consistent on repeated access
TEST_F(BBoxOutputDevTest_1518, BoundingBoxConsistentAccess_1518) {
    BBoxOutputDev dev;
    double x1_first = dev.getX1();
    double y1_first = dev.getY1();
    double x2_first = dev.getX2();
    double y2_first = dev.getY2();

    EXPECT_EQ(dev.getX1(), x1_first);
    EXPECT_EQ(dev.getY1(), y1_first);
    EXPECT_EQ(dev.getX2(), x2_first);
    EXPECT_EQ(dev.getY2(), y2_first);
}
