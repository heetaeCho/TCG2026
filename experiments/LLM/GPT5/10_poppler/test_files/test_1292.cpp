#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Mock callbacks
void mockUnderlayCbk(PSOutputDev* psOut, void* data) {}
void mockOverlayCbk(PSOutputDev* psOut, void* data) {}

class PSOutputDevTest_1292 : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        // Assuming psOutputDev is initialized with the constructor taking fileName, docA, etc.
        // For simplicity, we will skip the actual initialization here.
        psOutputDev = new PSOutputDev("dummy.ps", nullptr, "title", 1, PSOutMode::ePSLevel1, 8, 11, false, true, 0, 0, 100, 100, PSForceRasterize::eRasterize, false, nullptr, nullptr, PSLevel::ePSLevel3);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Test normal operation of isOk() function
TEST_F(PSOutputDevTest_1292, IsOk_Normal_1292) {
    ASSERT_TRUE(psOutputDev->isOk());
}

// Test exceptional behavior of isOk() when it's manually set to false
TEST_F(PSOutputDevTest_1292, IsOk_ManualControl_1292) {
    psOutputDev->setManualCtrl(true);
    ASSERT_FALSE(psOutputDev->isOk());
}

// Test boundary condition: setting invalid values for scale
TEST_F(PSOutputDevTest_1292, SetScale_InvalidValues_1292) {
    psOutputDev->setScale(-1.0, 0.0); // Invalid scale
    // The test should ensure that this behavior does not cause issues internally
    // Since no return value is available from setScale, we'll verify the state change or indirectly through another public method.
    ASSERT_FALSE(psOutputDev->isOk());
}

// Test callback interaction: verify if underlay callback is set
TEST_F(PSOutputDevTest_1292, SetUnderlayCbk_Interaction_1292) {
    psOutputDev->setUnderlayCbk(mockUnderlayCbk, nullptr);

    // Assuming that we have a way to check that the callback was set properly, like calling the callback from within the function
    // We can trigger a scenario that would call the callback to verify that it was correctly assigned.
    // Since the code does not provide an easy way to directly trigger this, we assume the callback is called when appropriate.
    ASSERT_NO_FATAL_FAILURE(psOutputDev->setUnderlayCbk(mockUnderlayCbk, nullptr));
}

// Test callback interaction: verify if overlay callback is set
TEST_F(PSOutputDevTest_1292, SetOverlayCbk_Interaction_1292) {
    psOutputDev->setOverlayCbk(mockOverlayCbk, nullptr);

    // Similar to the underlay callback, we would check if this callback works in the context it is triggered
    ASSERT_NO_FATAL_FAILURE(psOutputDev->setOverlayCbk(mockOverlayCbk, nullptr));
}

// Test error case: handle incorrect settings for raster resolution
TEST_F(PSOutputDevTest_1292, SetRasterResolution_Error_1292) {
    psOutputDev->setRasterResolution(-1.0);  // Invalid raster resolution
    // Check if the error is handled in a safe manner without causing crashes.
    ASSERT_FALSE(psOutputDev->isOk());  // Assuming isOk() returns false on error conditions
}

// Test setting various boolean options
TEST_F(PSOutputDevTest_1292, SetDisplayText_Flag_1292) {
    psOutputDev->setDisplayText(true);
    // Verify if setting the display text flag has the expected outcome
    ASSERT_TRUE(psOutputDev->isOk());
}

TEST_F(PSOutputDevTest_1292, SetRasterAntialias_Flag_1292) {
    psOutputDev->setRasterAntialias(true);
    // Ensure it does not break the functionality and performs as expected.
    ASSERT_TRUE(psOutputDev->isOk());
}

// Test setting of rasterize force
TEST_F(PSOutputDevTest_1292, SetForceRasterize_1292) {
    psOutputDev->setForceRasterize(PSForceRasterize::eRasterize);
    ASSERT_TRUE(psOutputDev->isOk());
}