#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GPGMECryptoSignBackend.h" // Include the relevant header file for the function
#include "CertificateInfo.h" // Assuming this is the header file where X509CertificateInfo and related structures are defined

// Mock class for GpgME::Key to mock the interactions with external collaborators
class MockKey : public GpgME::Key {
public:
    MOCK_METHOD(const char*, issuerName, (), (const, override));
    MOCK_METHOD(size_t, userIDCount, (), (const, override));
    MOCK_METHOD(const GpgME::UserID&, userID, (size_t index), (const, override));
    MOCK_METHOD(const GpgME::Subkey&, subkey, (size_t index), (const, override));
    MOCK_METHOD(bool, canSign, (), (const, override));
    MOCK_METHOD(bool, canEncrypt, (), (const, override));
    MOCK_METHOD(bool, canCertify, (), (const, override));
    MOCK_METHOD(const char*, primaryFingerprint, (), (const, override));
    MOCK_METHOD(const char*, issuerSerial, (), (const, override));
};

// Helper function to create a mock key
std::unique_ptr<MockKey> createMockKey() {
    return std::make_unique<MockKey>();
}

// Test suite for getCertificateInfoFromKey
TEST_F(GPGMECryptoSignBackendTest_1954, GetCertificateInfoFromKey_CMSProtocol_Success_1954) {
    // Arrange
    auto mockKey = createMockKey();
    GpgME::Protocol protocol = GpgME::CMS;
    
    // Set up mock behavior
    EXPECT_CALL(*mockKey, issuerName())
        .WillOnce(testing::Return("Issuer"));
    EXPECT_CALL(*mockKey, userIDCount())
        .WillOnce(testing::Return(2));
    EXPECT_CALL(*mockKey, userID(0))
        .WillOnce(testing::Return(GpgME::UserID("user@example.com", "User")));
    EXPECT_CALL(*mockKey, userID(1))
        .WillOnce(testing::Return(GpgME::UserID("user2@example.com", "User2")));
    EXPECT_CALL(*mockKey, subkey(0))
        .WillOnce(testing::Return(GpgME::Subkey()));

    // Act
    auto result = getCertificateInfoFromKey(*mockKey, protocol);

    // Assert
    ASSERT_TRUE(result != nullptr);
    EXPECT_EQ(result->getSubjectInfo().email, "user@example.com");
}

TEST_F(GPGMECryptoSignBackendTest_1954, GetCertificateInfoFromKey_OpenPGPProtocol_Success_1954) {
    // Arrange
    auto mockKey = createMockKey();
    GpgME::Protocol protocol = GpgME::OpenPGP;
    
    // Set up mock behavior
    EXPECT_CALL(*mockKey, userIDCount())
        .WillOnce(testing::Return(1));
    EXPECT_CALL(*mockKey, userID(0))
        .WillOnce(testing::Return(GpgME::UserID("user@example.com", "User")));

    // Act
    auto result = getCertificateInfoFromKey(*mockKey, protocol);

    // Assert
    ASSERT_TRUE(result != nullptr);
    EXPECT_EQ(result->getSubjectInfo().email, "user@example.com");
    EXPECT_EQ(result->getCertificateType(), CertificateType::PGP);
}

TEST_F(GPGMECryptoSignBackendTest_1954, GetCertificateInfoFromKey_InvalidProtocol_Failure_1954) {
    // Arrange
    auto mockKey = createMockKey();
    GpgME::Protocol protocol = static_cast<GpgME::Protocol>(999); // Invalid protocol
    
    // Act
    auto result = getCertificateInfoFromKey(*mockKey, protocol);

    // Assert
    ASSERT_TRUE(result == nullptr);
}

TEST_F(GPGMECryptoSignBackendTest_1954, GetCertificateInfoFromKey_NullKey_Failure_1954) {
    // Act
    auto result = getCertificateInfoFromKey(*(std::unique_ptr<MockKey>())nullptr, GpgME::CMS);

    // Assert
    ASSERT_TRUE(result == nullptr);
}

TEST_F(GPGMECryptoSignBackendTest_1954, GetCertificateInfoFromKey_CertificateWithNoEmail_Success_1954) {
    // Arrange
    auto mockKey = createMockKey();
    GpgME::Protocol protocol = GpgME::CMS;
    
    // Set up mock behavior for missing email
    EXPECT_CALL(*mockKey, userIDCount())
        .WillOnce(testing::Return(1));
    EXPECT_CALL(*mockKey, userID(0))
        .WillOnce(testing::Return(GpgME::UserID("user@example.com", "")));
    EXPECT_CALL(*mockKey, userID(1))
        .WillOnce(testing::Return(GpgME::UserID("", "user2@example.com")));

    // Act
    auto result = getCertificateInfoFromKey(*mockKey, protocol);

    // Assert
    ASSERT_TRUE(result != nullptr);
    EXPECT_EQ(result->getSubjectInfo().email, "user2@example.com");
}