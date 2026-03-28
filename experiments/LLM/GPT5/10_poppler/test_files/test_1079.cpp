#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/OutputDev.h"

// Mock for GfxLCMSProfilePtr to simulate dependency in OutputDev
class MockGfxLCMSProfile : public GfxLCMSProfile {
public:
    MOCK_METHOD(void, someMethod, (), (override));
};

// Test Fixture for OutputDev
class OutputDevTest_1079 : public ::testing::Test {
protected:
    OutputDev* outputDev;

    void SetUp() override {
        outputDev = new OutputDev();
    }

    void TearDown() override {
        delete outputDev;
    }
};

// Test case: Normal operation of getDisplayProfile
TEST_F(OutputDevTest_1079, GetDisplayProfile_Normal_Operation_1079) {
    // Simulate setting a display profile
    GfxLCMSProfilePtr mockProfile = std::make_shared<MockGfxLCMSProfile>();
    outputDev->setDisplayProfile(mockProfile);

    // Verify that getDisplayProfile returns the correct profile
    GfxLCMSProfilePtr result = outputDev->getDisplayProfile();
    ASSERT_EQ(result, mockProfile);
}

// Test case: Boundary condition for null profile
TEST_F(OutputDevTest_1079, GetDisplayProfile_Null_Profile_1079) {
    // Set a null display profile
    outputDev->setDisplayProfile(nullptr);

    // Verify that getDisplayProfile returns nullptr when no profile is set
    GfxLCMSProfilePtr result = outputDev->getDisplayProfile();
    ASSERT_EQ(result, nullptr);
}

// Test case: Set display profile and verify it through getDisplayProfile
TEST_F(OutputDevTest_1079, SetAndGetDisplayProfile_1079) {
    // Create a new mock profile
    GfxLCMSProfilePtr profile = std::make_shared<MockGfxLCMSProfile>();
    outputDev->setDisplayProfile(profile);

    // Assert that the profile set is the same one retrieved
    GfxLCMSProfilePtr retrievedProfile = outputDev->getDisplayProfile();
    ASSERT_EQ(retrievedProfile, profile);
}

// Exceptional case: Testing setDisplayProfile with a null pointer
TEST_F(OutputDevTest_1079, SetDisplayProfile_NullPointer_1079) {
    // Test if setting a null pointer to display profile does not crash
    ASSERT_NO_THROW(outputDev->setDisplayProfile(nullptr));
}

// Test case: Boundary condition for default profiles
TEST_F(OutputDevTest_1079, GetDefaultProfiles_1079) {
    // Test the retrieval of default profiles (gray, RGB, CMYK)
    ASSERT_EQ(outputDev->getDefaultGrayProfile(), nullptr);
    ASSERT_EQ(outputDev->getDefaultRGBProfile(), nullptr);
    ASSERT_EQ(outputDev->getDefaultCMYKProfile(), nullptr);
}