#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CertificateInfo.h" // Assuming this file contains the KeyLocation enum and other necessary definitions.

namespace Poppler {
    // Function to be tested
    static CertificateInfo::KeyLocation fromPopplerCore(KeyLocation location);
}

// Mock class for external collaborators, if any. No external collaborators in this case, so we don't need this.
class MockHandler {};

// Unit Test Fixture for Poppler::fromPopplerCore
class FromPopplerCoreTest_1365 : public ::testing::Test {
protected:
    // Set up any necessary objects or state for the tests if needed.
    void SetUp() override {}

    // Clean up any resources if needed.
    void TearDown() override {}
};

// Test for normal operation - verifying correct conversion from KeyLocation enum values to CertificateInfo::KeyLocation.
TEST_F(FromPopplerCoreTest_1365, ConvertKeyLocationComputer_1365) {
    KeyLocation input = KeyLocation::Computer;
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Computer);
}

TEST_F(FromPopplerCoreTest_1365, ConvertKeyLocationOther_1365) {
    KeyLocation input = KeyLocation::Other;
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Other);
}

TEST_F(FromPopplerCoreTest_1365, ConvertKeyLocationUnknown_1365) {
    KeyLocation input = KeyLocation::Unknown;
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}

TEST_F(FromPopplerCoreTest_1365, ConvertKeyLocationHardwareToken_1365) {
    KeyLocation input = KeyLocation::HardwareToken;
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::HardwareToken);
}

// Test for boundary condition: When input is an unrecognized or default value
TEST_F(FromPopplerCoreTest_1365, ConvertInvalidKeyLocation_1365) {
    // Simulate an invalid or default input (this should map to Unknown based on the code)
    KeyLocation input = static_cast<KeyLocation>(-1); // assuming invalid KeyLocation would be negative
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}

// Exceptional/error case - verifying how the function behaves with an invalid input (in this case, boundary test with invalid KeyLocation)
TEST_F(FromPopplerCoreTest_1365, ConvertNegativeKeyLocation_1365) {
    // Test a KeyLocation with an invalid value, this should be treated as 'Unknown'.
    KeyLocation input = static_cast<KeyLocation>(-10); // An unlikely value outside defined KeyLocation range.
    CertificateInfo::KeyLocation result = Poppler::fromPopplerCore(input);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}