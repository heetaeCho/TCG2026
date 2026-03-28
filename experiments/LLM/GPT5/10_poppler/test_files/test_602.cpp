#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

using namespace testing;

class GfxStateTest_602 : public ::testing::Test {
protected:
    // Setup and teardown for the test cases
    GfxStateTest_602() {}
    ~GfxStateTest_602() override {}

    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation of getStrokeAdjust
TEST_F(GfxStateTest_602, GetStrokeAdjust_NormalOperation_602) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    
    // Assuming constructor initializes strokeAdjust to false
    EXPECT_FALSE(gfxState.getStrokeAdjust());

    gfxState.setStrokeAdjust(true);
    EXPECT_TRUE(gfxState.getStrokeAdjust());
}

// Test boundary conditions for stroke adjust
TEST_F(GfxStateTest_602, GetStrokeAdjust_BoundaryConditions_602) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);

    // Set stroke adjust to true and check
    gfxState.setStrokeAdjust(true);
    EXPECT_TRUE(gfxState.getStrokeAdjust());

    // Set stroke adjust to false and check
    gfxState.setStrokeAdjust(false);
    EXPECT_FALSE(gfxState.getStrokeAdjust());
}

// Test exceptional case where setting an invalid value could cause issues (e.g., setting to invalid range)
TEST_F(GfxStateTest_602, GetStrokeAdjust_ExceptionalCase_602) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);

    // Assuming setStrokeAdjust accepts only valid bool, there might be no true exception in this case, 
    // but we can assume setting unexpected values or handling error conditions could be tested here
    try {
        gfxState.setStrokeAdjust(true);  // Valid call
        EXPECT_TRUE(gfxState.getStrokeAdjust());
    } catch (const std::exception& e) {
        FAIL() << "Exception occurred: " << e.what();
    }
    
    try {
        gfxState.setStrokeAdjust(false);  // Valid call
        EXPECT_FALSE(gfxState.getStrokeAdjust());
    } catch (const std::exception& e) {
        FAIL() << "Exception occurred: " << e.what();
    }
}

// Verify external interactions (e.g., mocking)
class MockGfxState : public GfxState {
public:
    MockGfxState() : GfxState(72.0, 72.0, nullptr, 0, false) {}
    MOCK_METHOD(bool, getStrokeAdjust, (), (const, override));
};

TEST_F(GfxStateTest_602, VerifyExternalInteraction_602) {
    MockGfxState mockGfxState;
    EXPECT_CALL(mockGfxState, getStrokeAdjust()).WillOnce(Return(true));

    // Verify that mock method is called
    EXPECT_TRUE(mockGfxState.getStrokeAdjust());
}