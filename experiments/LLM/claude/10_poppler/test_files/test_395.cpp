#include <gtest/gtest.h>
#include <cstring>
#include "GfxState.h"

class ClearGfxColorTest_395 : public ::testing::Test {
protected:
    GfxColor color;

    void SetUp() override {
        // Fill with non-zero values to verify clearing
        for (int i = 0; i < gfxColorMaxComps; i++) {
            color.c[i] = (GfxColorComp)(i + 1);
        }
    }
};

// Test that clearGfxColor sets all components to zero
TEST_F(ClearGfxColorTest_395, AllComponentsSetToZero_395) {
    clearGfxColor(&color);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(color.c[i], 0) << "Component " << i << " was not cleared to zero";
    }
}

// Test clearing an already zeroed color
TEST_F(ClearGfxColorTest_395, ClearAlreadyZeroedColor_395) {
    memset(color.c, 0, sizeof(GfxColorComp) * gfxColorMaxComps);
    clearGfxColor(&color);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(color.c[i], 0) << "Component " << i << " should remain zero";
    }
}

// Test clearing color with maximum values
TEST_F(ClearGfxColorTest_395, ClearColorWithMaxValues_395) {
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = (GfxColorComp)(-1); // Set to max value for the type
    }
    clearGfxColor(&color);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(color.c[i], 0) << "Component " << i << " was not cleared to zero after max value";
    }
}

// Test that clearGfxColor clears all gfxColorMaxComps components
TEST_F(ClearGfxColorTest_395, ClearsExactlyMaxCompsComponents_395) {
    // Verify we're clearing the expected number of components
    GfxColor testColor;
    memset(&testColor, 0xFF, sizeof(GfxColor));
    clearGfxColor(&testColor);
    
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(testColor.c[i], 0) << "Component " << i << " within gfxColorMaxComps should be zero";
    }
}

// Test calling clearGfxColor multiple times produces same result
TEST_F(ClearGfxColorTest_395, MultipleClearCallsIdempotent_395) {
    clearGfxColor(&color);
    GfxColor firstClear;
    memcpy(&firstClear, &color, sizeof(GfxColor));
    
    clearGfxColor(&color);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(color.c[i], firstClear.c[i]) << "Multiple clears should produce identical results at component " << i;
    }
}

// Test that first component is cleared
TEST_F(ClearGfxColorTest_395, FirstComponentCleared_395) {
    color.c[0] = 12345;
    clearGfxColor(&color);
    EXPECT_EQ(color.c[0], 0);
}

// Test that last component (within gfxColorMaxComps) is cleared
TEST_F(ClearGfxColorTest_395, LastComponentCleared_395) {
    color.c[gfxColorMaxComps - 1] = 99999;
    clearGfxColor(&color);
    EXPECT_EQ(color.c[gfxColorMaxComps - 1], 0);
}

// Test clearing with only one component set to non-zero
TEST_F(ClearGfxColorTest_395, SingleNonZeroComponentCleared_395) {
    memset(color.c, 0, sizeof(GfxColorComp) * gfxColorMaxComps);
    int midIndex = gfxColorMaxComps / 2;
    color.c[midIndex] = 42;
    clearGfxColor(&color);
    EXPECT_EQ(color.c[midIndex], 0);
}

// Test on stack-allocated GfxColor
TEST_F(ClearGfxColorTest_395, StackAllocatedColor_395) {
    GfxColor stackColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        stackColor.c[i] = (GfxColorComp)(i * 100);
    }
    clearGfxColor(&stackColor);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(stackColor.c[i], 0);
    }
}
