#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_651 : public ::testing::Test {
protected:
    GfxState *gfxState;

    void SetUp() override {
        gfxState = new GfxState(72.0, 72.0, nullptr, 0, false); // Arbitrary constructor values for initialization
    }

    void TearDown() override {
        delete gfxState;
    }
};

// Normal operation: Test setting and getting the 'rise' value.
TEST_F(GfxStateTest_651, SetRise_SetsCorrectRiseValue_651) {
    double riseValue = 10.0;
    gfxState->setRise(riseValue);
    EXPECT_EQ(gfxState->getRise(), riseValue);
}

// Boundary conditions: Test setting 'rise' to 0.
TEST_F(GfxStateTest_651, SetRise_SetsZeroRiseValue_651) {
    double riseValue = 0.0;
    gfxState->setRise(riseValue);
    EXPECT_EQ(gfxState->getRise(), riseValue);
}

// Boundary conditions: Test setting 'rise' to a very large value.
TEST_F(GfxStateTest_651, SetRise_SetsLargeRiseValue_651) {
    double riseValue = 1e6; // large value
    gfxState->setRise(riseValue);
    EXPECT_EQ(gfxState->getRise(), riseValue);
}

// Exceptional cases: Test setting rise to a negative value (if applicable).
TEST_F(GfxStateTest_651, SetRise_SetsNegativeRiseValue_651) {
    double riseValue = -5.0;
    gfxState->setRise(riseValue);
    EXPECT_EQ(gfxState->getRise(), riseValue);
}