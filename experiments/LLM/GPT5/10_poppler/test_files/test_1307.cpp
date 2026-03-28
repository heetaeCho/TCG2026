#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1307 : public ::testing::Test {
protected:
    PSOutputDev psOutputDev;

    PSOutputDevTest_1307()
        : psOutputDev("output.ps", nullptr, nullptr, 1, PSOutMode::ePSLevel2, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::eNone, false, nullptr, nullptr, PSLevel::ePSLevel2) {
    }
};

// Normal operation test case for setPSCenter
TEST_F(PSOutputDevTest_1307, setPSCenter_Normal_Operation_1307) {
    // Set PS center to true
    psOutputDev.setPSCenter(true);

    // Verify that the member variable 'psCenter' is set correctly
    ASSERT_TRUE(psOutputDev.psCenter);
}

// Boundary condition test case for setPSCenter
TEST_F(PSOutputDevTest_1307, setPSCenter_Boundary_Condition_1307) {
    // Set PS center to false
    psOutputDev.setPSCenter(false);

    // Verify that the member variable 'psCenter' is set correctly
    ASSERT_FALSE(psOutputDev.psCenter);
}

// Exceptional case test case for setPSCenter (assumes a scenario where invalid state handling should be tested)
TEST_F(PSOutputDevTest_1307, setPSCenter_Exceptional_Case_1307) {
    // Simulate an exceptional scenario where an invalid input could occur (if applicable)
    // Since setPSCenter is a simple setter, it's hard to simulate an exception without extra logic
    // Hence, we assume the setter should work without exceptions in this case.
    try {
        psOutputDev.setPSCenter(true);
    } catch (const std::exception& e) {
        FAIL() << "setPSCenter threw an exception: " << e.what();
    }
}

// Verification of external interaction: Mocking a callback function to verify interaction
TEST_F(PSOutputDevTest_1307, setUnderlayCbk_External_Interaction_1307) {
    // Define a mock callback
    MockCallback mockCbk;
    
    // Set up the mock callback
    psOutputDev.setUnderlayCbk(mockCbk.callback, nullptr);
    
    // Check that the callback was set (this would require an actual invocation, if possible)
    ASSERT_EQ(psOutputDev.underlayCbk, mockCbk.callback);
}

// Test for the 'psCenter' member value through getter (if applicable)
TEST_F(PSOutputDevTest_1307, getPSCenter_1307) {
    // First set psCenter to true
    psOutputDev.setPSCenter(true);
    // Verify that the getter would return true
    ASSERT_TRUE(psOutputDev.psCenter);
}