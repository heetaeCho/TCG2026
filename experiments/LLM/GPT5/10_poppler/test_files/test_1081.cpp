#include <gtest/gtest.h>
#include <memory>
#include "OutputDev.h"

class OutputDevTest_1081 : public ::testing::Test {
protected:
    OutputDev outputDev;

    // Set up for each test
    void SetUp() override {
        // You can set up mock profiles or necessary data here if needed
    }
};

TEST_F(OutputDevTest_1081, GetDefaultGrayProfile_ReturnsCorrectProfile_1081) {
    // Setup: Initialize a mock or real GfxLCMSProfilePtr if possible
    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    // You can set the profile using the setter before testing, if required.
    outputDev.setDefaultGrayProfile(mockProfile);

    // Act: Get the profile using the getter
    GfxLCMSProfilePtr result = outputDev.getDefaultGrayProfile();

    // Assert: Check if the returned profile matches the expected mockProfile
    ASSERT_EQ(result, mockProfile) << "getDefaultGrayProfile should return the correct profile.";
}

TEST_F(OutputDevTest_1081, GetDefaultGrayProfile_ReturnsNullWhenNotSet_1081) {
    // Act: Get the profile when it hasn't been set
    GfxLCMSProfilePtr result = outputDev.getDefaultGrayProfile();

    // Assert: Expect that it returns null if no profile has been set
    ASSERT_EQ(result, nullptr) << "getDefaultGrayProfile should return nullptr when not set.";
}

TEST_F(OutputDevTest_1081, SetAndGetDefaultGrayProfile_ValidProfile_1081) {
    // Setup: Create a new mock profile
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();

    // Act: Set the profile using the setter
    outputDev.setDefaultGrayProfile(profile);

    // Assert: Ensure that the getter returns the same profile
    ASSERT_EQ(outputDev.getDefaultGrayProfile(), profile) << "The profile returned should match the one set.";
}

TEST_F(OutputDevTest_1081, GetDefaultGrayProfile_SingleCall_1081) {
    // Setup: Create a profile and set it
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();
    outputDev.setDefaultGrayProfile(profile);

    // Act: Get the profile once
    GfxLCMSProfilePtr result = outputDev.getDefaultGrayProfile();

    // Assert: Ensure it returns the correct profile after a single call
    ASSERT_EQ(result, profile) << "The profile returned after a single call should be correct.";
}