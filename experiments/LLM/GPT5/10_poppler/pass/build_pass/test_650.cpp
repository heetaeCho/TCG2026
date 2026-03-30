#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_650 : public ::testing::Test {
protected:
    GfxStateTest_650() : state(72.0, 72.0, nullptr, 0, false) {}

    GfxState state;
};

TEST_F(GfxStateTest_650, SetLeading_NormalOperation_650) {
    // Test normal setting of leading
    state.setLeading(10.5);
    EXPECT_EQ(state.getLeading(), 10.5);
}

TEST_F(GfxStateTest_650, SetLeading_BoundaryCondition_MinValue_650) {
    // Test boundary condition with the minimum possible leading value
    state.setLeading(0.0);
    EXPECT_EQ(state.getLeading(), 0.0);
}

TEST_F(GfxStateTest_650, SetLeading_BoundaryCondition_LargeValue_650) {
    // Test boundary condition with a very large value for leading
    state.setLeading(1e6);
    EXPECT_EQ(state.getLeading(), 1e6);
}

TEST_F(GfxStateTest_650, SetLeading_Zero_650) {
    // Test setting leading to zero
    state.setLeading(0.0);
    EXPECT_EQ(state.getLeading(), 0.0);
}

TEST_F(GfxStateTest_650, SetLeading_NegativeValue_650) {
    // Test setting leading to a negative value
    state.setLeading(-5.0);
    EXPECT_EQ(state.getLeading(), -5.0);
}

TEST_F(GfxStateTest_650, SetLeading_SuccessiveUpdates_650) {
    // Test setting leading successively
    state.setLeading(10.0);
    EXPECT_EQ(state.getLeading(), 10.0);
    state.setLeading(20.0);
    EXPECT_EQ(state.getLeading(), 20.0);
    state.setLeading(15.0);
    EXPECT_EQ(state.getLeading(), 15.0);
}

TEST_F(GfxStateTest_650, SetLeading_ExceptionalCase_InvalidValue_650) {
    // Test handling of invalid value (e.g., leading value too large for context)
    // Since the class doesn't handle this internally, we can't catch this explicitly here.
    // So we're testing just the expected behavior of setting an arbitrary value.
    state.setLeading(1000000.0);
    EXPECT_EQ(state.getLeading(), 1000000.0);
}