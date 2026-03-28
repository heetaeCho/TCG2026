#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Mock class for external dependencies (if needed)
class MockCallback {
public:
    MOCK_METHOD(void, callback, (PSOutputDev* psOut, void* data), ());
};

class PSOutputDevTest_1335 : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;

    // Setup and teardown methods for test fixture
    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test PS Title", 1, PSOutMode::Text, 595, 842, false, true, 0, 0, 595, 842, PSForceRasterize::None, false, nullptr, nullptr, PSLevel::Level1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Test normal operation of setUseBinary function
TEST_F(PSOutputDevTest_1335, SetUseBinary_True_1335) {
    psOutputDev->setUseBinary(true);
    // Assuming the internal state of `useBinary` is observable via a public function
    ASSERT_TRUE(psOutputDev->getUseBinary());
}

TEST_F(PSOutputDevTest_1335, SetUseBinary_False_1335) {
    psOutputDev->setUseBinary(false);
    ASSERT_FALSE(psOutputDev->getUseBinary());
}

// Test normal operation of setting and verifying callback functions
TEST_F(PSOutputDevTest_1335, SetUnderlayCbk_ValidCallback_1335) {
    MockCallback mockCbk;
    void* data = nullptr;
    EXPECT_CALL(mockCbk, callback(testing::_, testing::_)).Times(1);
    psOutputDev->setUnderlayCbk(&MockCallback::callback, data);
    // Assuming there's a method to trigger the callback for testing
    psOutputDev->triggerUnderlayCallback();
}

TEST_F(PSOutputDevTest_1335, SetOverlayCbk_ValidCallback_1335) {
    MockCallback mockCbk;
    void* data = nullptr;
    EXPECT_CALL(mockCbk, callback(testing::_, testing::_)).Times(1);
    psOutputDev->setOverlayCbk(&MockCallback::callback, data);
    // Assuming there's a method to trigger the callback for testing
    psOutputDev->triggerOverlayCallback();
}

// Test boundary condition: setting values at extremes
TEST_F(PSOutputDevTest_1335, SetRasterResolution_LowValue_1335) {
    psOutputDev->setRasterResolution(0.0);
    // Assuming there's a method to get the raster resolution for comparison
    ASSERT_EQ(psOutputDev->getRasterResolution(), 0.0);
}

TEST_F(PSOutputDevTest_1335, SetRasterResolution_HighValue_1335) {
    psOutputDev->setRasterResolution(10000.0);
    ASSERT_EQ(psOutputDev->getRasterResolution(), 10000.0);
}

// Test exceptional/error cases, if observable via public methods
TEST_F(PSOutputDevTest_1335, SetUseBinary_InvalidValue_1335) {
    // Assuming setUseBinary doesn't accept non-bool values, we expect no changes.
    // Here you can check if an invalid value is ignored, for example
    ASSERT_NO_THROW(psOutputDev->setUseBinary(-1));
    ASSERT_FALSE(psOutputDev->getUseBinary()); // Default is false
}

TEST_F(PSOutputDevTest_1335, SetRasterResolution_Invalid_1335) {
    ASSERT_NO_THROW(psOutputDev->setRasterResolution(-1.0));
    ASSERT_EQ(psOutputDev->getRasterResolution(), -1.0);
}

// Test for verifying external interactions (mock handlers)
TEST_F(PSOutputDevTest_1335, SetUnderlayCbk_ExternalInteraction_1335) {
    MockCallback mockCbk;
    void* data = nullptr;
    EXPECT_CALL(mockCbk, callback(testing::_, testing::_)).Times(1);
    psOutputDev->setUnderlayCbk(&MockCallback::callback, data);
    psOutputDev->triggerUnderlayCallback();  // Trigger callback
}

TEST_F(PSOutputDevTest_1335, SetOverlayCbk_ExternalInteraction_1335) {
    MockCallback mockCbk;
    void* data = nullptr;
    EXPECT_CALL(mockCbk, callback(testing::_, testing::_)).Times(1);
    psOutputDev->setOverlayCbk(&MockCallback::callback, data);
    psOutputDev->triggerOverlayCallback();  // Trigger callback
}