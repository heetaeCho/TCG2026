#include <gtest/gtest.h>
#include "PSOutputDev.h"

// Mock classes for any external dependencies (if necessary)
class MockPDFDoc : public PDFDoc {
    // Implement necessary mocks here if needed
};

// Unit test suite for PSOutputDev class
class PSOutputDevTest_1303 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up the required objects before each test
        psOutputDev = new PSOutputDev("test.ps", nullptr, "test_title", 1, PSOutMode::PSLevel1, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::None, false, nullptr, nullptr, PSLevel::PSLevel2);
    }

    void TearDown() override {
        // Clean up after each test
        delete psOutputDev;
    }

    PSOutputDev* psOutputDev;
};

// Test normal behavior of setClip
TEST_F(PSOutputDevTest_1303, SetClip_Normal_Operation_1303) {
    // Call the method with valid values
    psOutputDev->setClip(0.0, 0.0, 100.0, 100.0);

    // Verify that the values have been correctly set
    EXPECT_EQ(psOutputDev->clipLLX0, 0.0);
    EXPECT_EQ(psOutputDev->clipLLY0, 0.0);
    EXPECT_EQ(psOutputDev->clipURX0, 100.0);
    EXPECT_EQ(psOutputDev->clipURY0, 100.0);
}

// Test boundary conditions with large values
TEST_F(PSOutputDevTest_1303, SetClip_Large_Values_1303) {
    // Call with extremely large values
    psOutputDev->setClip(1e6, 1e6, 1e7, 1e7);

    // Verify the values have been set correctly
    EXPECT_EQ(psOutputDev->clipLLX0, 1e6);
    EXPECT_EQ(psOutputDev->clipLLY0, 1e6);
    EXPECT_EQ(psOutputDev->clipURX0, 1e7);
    EXPECT_EQ(psOutputDev->clipURY0, 1e7);
}

// Test boundary conditions with negative values
TEST_F(PSOutputDevTest_1303, SetClip_Negative_Values_1303) {
    // Call with negative values
    psOutputDev->setClip(-100.0, -100.0, -50.0, -50.0);

    // Verify the values have been set correctly
    EXPECT_EQ(psOutputDev->clipLLX0, -100.0);
    EXPECT_EQ(psOutputDev->clipLLY0, -100.0);
    EXPECT_EQ(psOutputDev->clipURX0, -50.0);
    EXPECT_EQ(psOutputDev->clipURY0, -50.0);
}

// Test behavior with zero values for clipping
TEST_F(PSOutputDevTest_1303, SetClip_Zero_Values_1303) {
    // Call with zero values
    psOutputDev->setClip(0.0, 0.0, 0.0, 0.0);

    // Verify the values have been set correctly
    EXPECT_EQ(psOutputDev->clipLLX0, 0.0);
    EXPECT_EQ(psOutputDev->clipLLY0, 0.0);
    EXPECT_EQ(psOutputDev->clipURX0, 0.0);
    EXPECT_EQ(psOutputDev->clipURY0, 0.0);
}

// Test that the clip values remain consistent after multiple calls
TEST_F(PSOutputDevTest_1303, SetClip_Consistency_1303) {
    // Call with one set of values
    psOutputDev->setClip(10.0, 10.0, 200.0, 200.0);

    // Verify the values
    EXPECT_EQ(psOutputDev->clipLLX0, 10.0);
    EXPECT_EQ(psOutputDev->clipLLY0, 10.0);
    EXPECT_EQ(psOutputDev->clipURX0, 200.0);
    EXPECT_EQ(psOutputDev->clipURY0, 200.0);

    // Call with another set of values
    psOutputDev->setClip(20.0, 20.0, 250.0, 250.0);

    // Verify the values again
    EXPECT_EQ(psOutputDev->clipLLX0, 20.0);
    EXPECT_EQ(psOutputDev->clipLLY0, 20.0);
    EXPECT_EQ(psOutputDev->clipURX0, 250.0);
    EXPECT_EQ(psOutputDev->clipURY0, 250.0);
}