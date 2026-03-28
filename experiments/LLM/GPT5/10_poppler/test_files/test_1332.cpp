#include <gtest/gtest.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1332 : public testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test Title", 1, PSOutMode::ePSOutModeText, 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::ePSForceRasterizeNone, false, nullptr, nullptr, PSLevel::ePSLevel2);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Normal operation test for setPreloadImagesForms function
TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_True_1332) {
    psOutputDev->setPreloadImagesForms(true);
    // Assert that preloadImagesForms has been set to true
    ASSERT_TRUE(psOutputDev->preloadImagesForms);
}

TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_False_1332) {
    psOutputDev->setPreloadImagesForms(false);
    // Assert that preloadImagesForms has been set to false
    ASSERT_FALSE(psOutputDev->preloadImagesForms);
}

// Boundary test case - test the edge case with maximum boolean value
TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_MaxBoundary_1332) {
    psOutputDev->setPreloadImagesForms(true);
    // Assert the expected behavior at the boundary condition
    ASSERT_TRUE(psOutputDev->preloadImagesForms);
}

// Exceptional case - Mock external callback interaction
TEST_F(PSOutputDevTest_1332, SetUnderlayCallback_1332) {
    // Mock the callback function and set the underlay callback
    void (*mockUnderlayCallback)(PSOutputDev*, void*) = [](PSOutputDev* psOut, void* data) {
        ASSERT_NE(psOut, nullptr);
        ASSERT_EQ(data, nullptr); // Example: check callback data is correct
    };
    psOutputDev->setUnderlayCbk(mockUnderlayCallback, nullptr);
    // Test if the callback is set correctly (interaction observable in behavior)
    ASSERT_NO_THROW(psOutputDev->setUnderlayCbk(mockUnderlayCallback, nullptr));
}

// Mock behavior with external interaction for overlay callback
TEST_F(PSOutputDevTest_1332, SetOverlayCallback_1332) {
    void (*mockOverlayCallback)(PSOutputDev*, void*) = [](PSOutputDev* psOut, void* data) {
        ASSERT_NE(psOut, nullptr);
        ASSERT_EQ(data, nullptr);
    };
    psOutputDev->setOverlayCbk(mockOverlayCallback, nullptr);
    ASSERT_NO_THROW(psOutputDev->setOverlayCbk(mockOverlayCallback, nullptr));
}