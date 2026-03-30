#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxState.h"

class GfxStateTest_612 : public ::testing::Test {
protected:
    // Setup and Teardown if necessary
    GfxStateTest_612() {
        // You can add setup logic here if necessary
    }

    ~GfxStateTest_612() override {
        // You can add teardown logic here if necessary
    }

    // Mock objects and/or test data can be declared here.
};

TEST_F(GfxStateTest_612, GetRise_ReturnsCorrectValue_612) {
    // Arrange: Create a GfxState object with a known 'rise' value
    double testRiseValue = 10.5;
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);  // Assuming constructor is used like this
    gfxState.setRise(testRiseValue); // Assuming setRise is used for setting rise
    
    // Act: Call getRise() to get the rise value
    double result = gfxState.getRise();

    // Assert: Verify that getRise returns the expected value
    EXPECT_EQ(result, testRiseValue);
}

TEST_F(GfxStateTest_612, GetRise_DefaultValue_612) {
    // Arrange: Create a default GfxState object without modifying 'rise'
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);  // Assuming constructor is used like this
    
    // Act: Call getRise() to get the rise value
    double result = gfxState.getRise();

    // Assert: Verify that getRise returns the default value (assuming it starts at 0)
    EXPECT_EQ(result, 0.0);
}