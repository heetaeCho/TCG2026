#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Test suite for PSOutputDev class
class PSOutputDevTest_1320 : public testing::Test {
protected:
    // A simple mock for the PSOutputDev class, for testing purposes.
    PSOutputDev *psOutputDev;

    // Set up method
    void SetUp() override {
        // Initialize PSOutputDev with a dummy fileName and docA for the constructor
        psOutputDev = new PSOutputDev("dummy.ps", nullptr, "Test Title", 1, PSOutMode::PSOutDefault, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::PSForceNone, false, nullptr, nullptr, PSLevel::PSLevel1);
    }

    // Tear down method
    void TearDown() override {
        delete psOutputDev;
    }
};

// Test to check normal operation of getFontPassthrough
TEST_F(PSOutputDevTest_1320, GetFontPassthrough_ReturnsCorrectValue_1320) {
    // Given
    bool expectedValue = true;
    psOutputDev->setFontPassthrough(expectedValue);

    // When
    bool result = psOutputDev->getFontPassthrough();

    // Then
    EXPECT_EQ(result, expectedValue);
}

// Test to check boundary case where fontPassthrough is set to false
TEST_F(PSOutputDevTest_1320, GetFontPassthrough_ReturnsFalse_1321) {
    // Given
    bool expectedValue = false;
    psOutputDev->setFontPassthrough(expectedValue);

    // When
    bool result = psOutputDev->getFontPassthrough();

    // Then
    EXPECT_EQ(result, expectedValue);
}

// Test to check if the getter works for a default constructed PSOutputDev object
TEST_F(PSOutputDevTest_1320, GetFontPassthrough_DefaultValue_1322) {
    // Given: Default constructor sets fontPassthrough to some default value (assumed to be false)
    bool expectedValue = false;

    // When
    bool result = psOutputDev->getFontPassthrough();

    // Then
    EXPECT_EQ(result, expectedValue);
}