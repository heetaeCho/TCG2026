#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BBoxOutputDev.h"
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <cmath>
#include <limits>

class BBoxOutputDevTest_1519 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test default constructor creates a valid object
TEST_F(BBoxOutputDevTest_1519, DefaultConstructor_1519) {
    BBoxOutputDev dev;
    // After construction, bounding box should be in a default/empty state
    // The coordinates should reflect no content has been drawn
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    // With no content, we expect an empty/degenerate bounding box
    // Typically x1 > x2 or y1 > y2 for an empty box, or all zeros
    SUCCEED(); // Just verify no crash
}

// Test three-argument constructor
TEST_F(BBoxOutputDevTest_1519, ThreeArgConstructor_1519) {
    BBoxOutputDev dev(true, true, true);
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    SUCCEED();
}

// Test four-argument constructor
TEST_F(BBoxOutputDevTest_1519, FourArgConstructor_1519) {
    BBoxOutputDev dev(true, true, true, true);
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    SUCCEED();
}

// Test that useDrawChar returns true
TEST_F(BBoxOutputDevTest_1519, UseDrawCharReturnsTrue_1519) {
    BBoxOutputDev dev;
    EXPECT_TRUE(dev.useDrawChar());
}

// Test that upsideDown returns expected value
TEST_F(BBoxOutputDevTest_1519, UpsideDown_1519) {
    BBoxOutputDev dev;
    // Just verify we get a consistent result (typically true for PDF)
    bool result = dev.upsideDown();
    // Call again to ensure consistency
    EXPECT_EQ(result, dev.upsideDown());
}

// Test that interpretType3Chars returns expected value
TEST_F(BBoxOutputDevTest_1519, InterpretType3Chars_1519) {
    BBoxOutputDev dev;
    bool result = dev.interpretType3Chars();
    // Call again to ensure consistency
    EXPECT_EQ(result, dev.interpretType3Chars());
}

// Test getHasGraphics with default constructor (no drawing done)
TEST_F(BBoxOutputDevTest_1519, GetHasGraphicsDefault_1519) {
    BBoxOutputDev dev;
    double hasGraphics = dev.getHasGraphics();
    // With no drawing operations, hasGraphics should be false (0)
    EXPECT_EQ(hasGraphics, 0.0);
}

// Test that bounding box getters return consistent values after construction
TEST_F(BBoxOutputDevTest_1519, BoundingBoxConsistencyAfterConstruction_1519) {
    BBoxOutputDev dev;
    double x1_first = dev.getX1();
    double y1_first = dev.getY1();
    double x2_first = dev.getX2();
    double y2_first = dev.getY2();

    // Multiple calls should return same values
    EXPECT_EQ(x1_first, dev.getX1());
    EXPECT_EQ(y1_first, dev.getY1());
    EXPECT_EQ(x2_first, dev.getX2());
    EXPECT_EQ(y2_first, dev.getY2());
}

// Test constructor with all flags disabled
TEST_F(BBoxOutputDevTest_1519, AllFlagsDisabled_1519) {
    BBoxOutputDev dev(false, false, false);
    EXPECT_TRUE(dev.useDrawChar());
    double hasGraphics = dev.getHasGraphics();
    EXPECT_EQ(hasGraphics, 0.0);
}

// Test constructor with only text enabled
TEST_F(BBoxOutputDevTest_1519, OnlyTextEnabled_1519) {
    BBoxOutputDev dev(true, false, false);
    SUCCEED();
}

// Test constructor with only vector enabled
TEST_F(BBoxOutputDevTest_1519, OnlyVectorEnabled_1519) {
    BBoxOutputDev dev(false, true, false);
    SUCCEED();
}

// Test constructor with only raster enabled
TEST_F(BBoxOutputDevTest_1519, OnlyRasterEnabled_1519) {
    BBoxOutputDev dev(false, false, true);
    SUCCEED();
}

// Test four-arg constructor with lwidth enabled
TEST_F(BBoxOutputDevTest_1519, LwidthEnabled_1519) {
    BBoxOutputDev dev(true, true, true, true);
    SUCCEED();
}

// Test four-arg constructor with lwidth disabled
TEST_F(BBoxOutputDevTest_1519, LwidthDisabled_1519) {
    BBoxOutputDev dev(true, true, true, false);
    SUCCEED();
}

// Test endPage doesn't crash on fresh device
TEST_F(BBoxOutputDevTest_1519, EndPageNoCrash_1519) {
    BBoxOutputDev dev;
    dev.endPage();
    SUCCEED();
}

// Test that after endPage, bounding box is still accessible
TEST_F(BBoxOutputDevTest_1519, BoundingBoxAfterEndPage_1519) {
    BBoxOutputDev dev;
    dev.endPage();
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    // Should not crash
    SUCCEED();
}

// Test multiple endPage calls
TEST_F(BBoxOutputDevTest_1519, MultipleEndPageCalls_1519) {
    BBoxOutputDev dev;
    dev.endPage();
    dev.endPage();
    dev.endPage();
    SUCCEED();
}

// Test that getHasGraphics returns 0 when no graphics operations performed
TEST_F(BBoxOutputDevTest_1519, NoGraphicsOperations_1519) {
    BBoxOutputDev dev(true, true, true, true);
    EXPECT_EQ(dev.getHasGraphics(), 0.0);
}

// Test initial bounding box values - empty box should have specific characteristics
TEST_F(BBoxOutputDevTest_1519, InitialBoundingBoxEmpty_1519) {
    BBoxOutputDev dev;
    double x1 = dev.getX1();
    double y1 = dev.getY1();
    double x2 = dev.getX2();
    double y2 = dev.getY2();
    
    // For an empty bounding box, x2 should be <= x1 and y2 should be <= y1
    // or all should be zero - depends on implementation
    // We just verify we get finite values
    EXPECT_FALSE(std::isnan(x1));
    EXPECT_FALSE(std::isnan(y1));
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

// Test stroke with nullptr state - boundary/error case
// Note: This tests observable crash behavior, so we skip if it would segfault
// Instead we test that the object is properly constructed and methods are callable
TEST_F(BBoxOutputDevTest_1519, ConstructorCombinations_1519) {
    // Test various constructor parameter combinations
    {
        BBoxOutputDev dev(false, false, false, false);
        EXPECT_TRUE(dev.useDrawChar());
    }
    {
        BBoxOutputDev dev(true, false, false, true);
        EXPECT_TRUE(dev.useDrawChar());
    }
    {
        BBoxOutputDev dev(false, true, false, true);
        EXPECT_TRUE(dev.useDrawChar());
    }
    {
        BBoxOutputDev dev(false, false, true, true);
        EXPECT_TRUE(dev.useDrawChar());
    }
}
