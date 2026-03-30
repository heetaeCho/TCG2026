#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest : public ::testing::Test {
protected:
    GfxState state;  // Assuming GfxState constructor initializes values

    GfxStateTest() : state(300.0, 300.0, nullptr, 0, false) {}  // Sample constructor arguments
};

// Test case 1: Verify normal operation when setting text knockout to true
TEST_F(GfxStateTest, SetTextKnockoutTrue_645) {
    state.setTextKnockout(true);
    EXPECT_TRUE(state.getTextKnockout()) << "Text knockout should be true after setting it to true";
}

// Test case 2: Verify normal operation when setting text knockout to false
TEST_F(GfxStateTest, SetTextKnockoutFalse_645) {
    state.setTextKnockout(false);
    EXPECT_FALSE(state.getTextKnockout()) << "Text knockout should be false after setting it to false";
}

// Test case 3: Verify the behavior when setting text knockout multiple times
TEST_F(GfxStateTest, SetTextKnockoutMultipleTimes_645) {
    state.setTextKnockout(true);
    EXPECT_TRUE(state.getTextKnockout()) << "Text knockout should be true initially";
    
    state.setTextKnockout(false);
    EXPECT_FALSE(state.getTextKnockout()) << "Text knockout should be false after being set to false";
    
    state.setTextKnockout(true);
    EXPECT_TRUE(state.getTextKnockout()) << "Text knockout should be true again after setting to true";
}

// Test case 4: Boundary test case - Setting text knockout to true with no previous state
TEST_F(GfxStateTest, BoundaryTextKnockoutTrue_645) {
    state.setTextKnockout(true);
    EXPECT_TRUE(state.getTextKnockout()) << "Text knockout should be true after setting it once";
}

// Test case 5: Boundary test case - Setting text knockout to false with no previous state
TEST_F(GfxStateTest, BoundaryTextKnockoutFalse_645) {
    state.setTextKnockout(false);
    EXPECT_FALSE(state.getTextKnockout()) << "Text knockout should be false after setting it once";
}