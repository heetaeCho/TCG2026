#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxState.h"

class GfxStateTest : public ::testing::Test {
protected:
    // Set up any necessary mock or test state here
    GfxState state1{300, 300, nullptr, 0, false};
    GfxState state2{300, 300, nullptr, 0, false};
};

TEST_F(GfxStateTest, GetX1_ReturnsCorrectValue_568) {
    // Setup: We assume the constructor initializes px1 to a value
    double expectedX1 = 10.0;  // Assuming px1 is 10.0 for this test
    state1 = GfxState(300, 300, nullptr, 0, false);  // Reset if needed

    // Action
    double actualX1 = state1.getX1();

    // Assertion
    ASSERT_EQ(actualX1, expectedX1) << "Expected getX1 to return " << expectedX1;
}

TEST_F(GfxStateTest, GetX1_HandlesBoundaryConditions_569) {
    // Test boundary conditions for getX1 function
    double minValue = -1e6;  // extreme value as an example
    double maxValue = 1e6;

    state1 = GfxState(300, 300, nullptr, 0, false);

    // Simulate boundary values
    state1.setX1(minValue);
    ASSERT_EQ(state1.getX1(), minValue) << "Expected getX1 to return " << minValue;

    state1.setX1(maxValue);
    ASSERT_EQ(state1.getX1(), maxValue) << "Expected getX1 to return " << maxValue;
}

TEST_F(GfxStateTest, GetX1_ExceptionalCases_570) {
    // Check exceptional cases, though none seem directly relevant in getX1, we can mock the behavior
    EXPECT_THROW(state1.getX1(), std::runtime_error) << "Expected getX1 to throw an exception in this case.";
}

TEST_F(GfxStateTest, SaveRestore_StateRestoration_571) {
    // Test saving and restoring state
    GfxState *savedState = state1.save();
    ASSERT_NE(savedState, nullptr) << "Expected saved state to be non-null";

    // Modify some state
    state1.setX1(100.0);

    // Restore and check
    GfxState *restoredState = state1.restore();
    ASSERT_EQ(restoredState->getX1(), savedState->getX1()) << "Expected state1 X1 to match restored state X1.";
}

TEST_F(GfxStateTest, SetAndGetX1_ModifiesStateCorrectly_572) {
    // Test modifying state through setters and validating getters
    double newX1 = 200.0;
    state1.setX1(newX1);

    double actualX1 = state1.getX1();
    ASSERT_EQ(actualX1, newX1) << "Expected getX1 to return " << newX1;
}