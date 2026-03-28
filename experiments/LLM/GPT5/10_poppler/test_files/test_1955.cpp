#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

namespace GpgME {
    enum Protocol { CMS, OpenPGP };
}

class GpgSignatureConfiguration {
public:
    static bool arePgpSignaturesAllowed() {
        // This is just a placeholder; the actual implementation should be mocked.
        return true;  // Assume true for the test
    }
    static void setPgpSignaturesAllowed(bool allowed) {
        // This is just a placeholder; the actual implementation should be mocked.
    }
};

static std::vector<GpgME::Protocol> allowedTypes() {
    std::vector<GpgME::Protocol> allowedTypes;
    allowedTypes.push_back(GpgME::CMS);
    if (GpgSignatureConfiguration::arePgpSignaturesAllowed()) {
        allowedTypes.push_back(GpgME::OpenPGP);
    }
    return allowedTypes;
}

// Mock class for testing GpgSignatureConfiguration's behavior
class MockGpgSignatureConfiguration : public GpgSignatureConfiguration {
public:
    MOCK_METHOD(bool, arePgpSignaturesAllowed, (), (static));
    MOCK_METHOD(void, setPgpSignaturesAllowed, (bool allowed), (static));
};

// Test suite
class GpgMECryptoSignBackendTest_1955 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary state before each test runs
    }

    void TearDown() override {
        // Clean up any necessary state after each test runs
    }
};

// Test: Normal operation when PGP signatures are allowed
TEST_F(GpgMECryptoSignBackendTest_1955, AllowedTypes_WithPgpSignatures_Allowed_1955) {
    // Arrange: Mock the behavior of arePgpSignaturesAllowed to return true
    MockGpgSignatureConfiguration mockConfig;
    EXPECT_CALL(mockConfig, arePgpSignaturesAllowed())
        .WillOnce(testing::Return(true));

    // Act: Call allowedTypes function to get the allowed protocols
    std::vector<GpgME::Protocol> result = allowedTypes();

    // Assert: Expect that OpenPGP is included in the allowed types
    ASSERT_THAT(result, testing::Contains(GpgME::OpenPGP));
    ASSERT_THAT(result, testing::Contains(GpgME::CMS));
}

// Test: Boundary condition when PGP signatures are not allowed
TEST_F(GpgMECryptoSignBackendTest_1955, AllowedTypes_WithPgpSignatures_NotAllowed_1955) {
    // Arrange: Mock the behavior of arePgpSignaturesAllowed to return false
    MockGpgSignatureConfiguration mockConfig;
    EXPECT_CALL(mockConfig, arePgpSignaturesAllowed())
        .WillOnce(testing::Return(false));

    // Act: Call allowedTypes function to get the allowed protocols
    std::vector<GpgME::Protocol> result = allowedTypes();

    // Assert: Expect that OpenPGP is not included in the allowed types
    ASSERT_THAT(result, testing::Not(testing::Contains(GpgME::OpenPGP)));
    ASSERT_THAT(result, testing::Contains(GpgME::CMS));
}

// Test: Exceptional case when arePgpSignaturesAllowed throws an exception
TEST_F(GpgMECryptoSignBackendTest_1955, AllowedTypes_ThrowsException_1955) {
    // Arrange: Mock the behavior of arePgpSignaturesAllowed to throw an exception
    MockGpgSignatureConfiguration mockConfig;
    EXPECT_CALL(mockConfig, arePgpSignaturesAllowed())
        .WillOnce(testing::Throw(std::runtime_error("Exception thrown")));

    // Act & Assert: Check that calling allowedTypes throws an exception
    EXPECT_THROW(allowedTypes(), std::runtime_error);
}