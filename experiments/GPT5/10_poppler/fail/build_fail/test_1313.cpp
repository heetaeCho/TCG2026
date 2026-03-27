#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1313 : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "testTitle", 1, PSOutMode::kPSOutModeNone, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::kPSForceRasterizeNo, false, nullptr, nullptr, PSLevel::kPSLevel3);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

TEST_F(PSOutputDevTest_1313, SetRasterResolution_1313) {
    // Test for normal operation: Set the raster resolution and check the value.
    psOutputDev->setRasterResolution(300.0);
    EXPECT_EQ(psOutputDev->getRasterResolution(), 300.0);
}

TEST_F(PSOutputDevTest_1313, SetRasterResolution_Zero_1313) {
    // Boundary case: Set the raster resolution to zero and check the value.
    psOutputDev->setRasterResolution(0.0);
    EXPECT_EQ(psOutputDev->getRasterResolution(), 0.0);
}

TEST_F(PSOutputDevTest_1313, SetRasterResolution_Negative_1313) {
    // Exceptional case: Set the raster resolution to a negative value and check the value.
    psOutputDev->setRasterResolution(-100.0);
    EXPECT_EQ(psOutputDev->getRasterResolution(), -100.0);
}

TEST_F(PSOutputDevTest_1313, SetRasterResolution_LargeValue_1313) {
    // Boundary case: Set the raster resolution to a very large value.
    psOutputDev->setRasterResolution(10000.0);
    EXPECT_EQ(psOutputDev->getRasterResolution(), 10000.0);
}

TEST_F(PSOutputDevTest_1313, SetRasterResolution_CheckChanges_1313) {
    // Test for ensuring that changes to raster resolution are correctly applied.
    double newResolution = 150.0;
    psOutputDev->setRasterResolution(newResolution);
    EXPECT_EQ(psOutputDev->getRasterResolution(), newResolution);
}

TEST_F(PSOutputDevTest_1313, SetRasterResolution_DefaultValue_1313) {
    // Test default state if no resolution is set.
    PSOutputDev* newDev = new PSOutputDev("test.ps", nullptr, "testTitle", 1, PSOutMode::kPSOutModeNone, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::kPSForceRasterizeNo, false, nullptr, nullptr, PSLevel::kPSLevel3);
    EXPECT_EQ(newDev->getRasterResolution(), 0.0);  // Assuming default value is 0.0.
    delete newDev;
}