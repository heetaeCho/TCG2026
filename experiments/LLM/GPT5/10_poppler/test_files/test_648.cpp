#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

class GfxStateTest_648 : public ::testing::Test {
protected:
    GfxStateTest_648() : gfxState(300, 300, nullptr, 0, false) {}

    GfxState gfxState;
};

TEST_F(GfxStateTest_648, SetWordSpaceNormal_648) {
    // Test setting a valid word space value
    double newSpace = 5.0;
    gfxState.setWordSpace(newSpace);
    EXPECT_EQ(gfxState.getWordSpace(), newSpace);
}

TEST_F(GfxStateTest_648, SetWordSpaceZero_649) {
    // Test setting word space to 0 (boundary condition)
    double newSpace = 0.0;
    gfxState.setWordSpace(newSpace);
    EXPECT_EQ(gfxState.getWordSpace(), newSpace);
}

TEST_F(GfxStateTest_648, SetWordSpaceNegative_650) {
    // Test setting a negative word space (edge case)
    double newSpace = -5.0;
    gfxState.setWordSpace(newSpace);
    EXPECT_EQ(gfxState.getWordSpace(), newSpace);
}

TEST_F(GfxStateTest_648, SetWordSpaceLargeValue_651) {
    // Test setting an extremely large word space value
    double newSpace = 1e6;
    gfxState.setWordSpace(newSpace);
    EXPECT_EQ(gfxState.getWordSpace(), newSpace);
}

TEST_F(GfxStateTest_648, SetWordSpaceBoundaryNegative_652) {
    // Test setting a large negative word space value
    double newSpace = -1e6;
    gfxState.setWordSpace(newSpace);
    EXPECT_EQ(gfxState.getWordSpace(), newSpace);
}

TEST_F(GfxStateTest_648, SetWordSpaceConsistency_653) {
    // Test setting and getting word space for consistency
    double firstSpace = 3.5;
    double secondSpace = 7.0;
    gfxState.setWordSpace(firstSpace);
    EXPECT_EQ(gfxState.getWordSpace(), firstSpace);
    gfxState.setWordSpace(secondSpace);
    EXPECT_EQ(gfxState.getWordSpace(), secondSpace);
}