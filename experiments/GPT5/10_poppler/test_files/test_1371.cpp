#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-form.cc"

// Mock classes for external dependencies
class MockBackend : public CryptoSign::Backend {
public:
    MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>, getAvailableSigningCertificates, (), (override));
};

class MockCryptoSignFactory : public CryptoSign::Factory {
public:
    MOCK_METHOD(std::unique_ptr<CryptoSign::Backend>, createActive, (), (override));
};

// Test Fixture
class GetAvailableSigningCertificatesTest_1371 : public ::testing::Test {
protected:
    MockCryptoSignFactory mockFactory;
    MockBackend mockBackend;
    
    // This would normally be injected into the system but for testing, we simulate the mock interactions
    Poppler::getAvailableSigningCertificates() {
        ON_CALL(mockFactory, createActive()).WillByDefault(testing::Return(std::make_unique<MockBackend>(mockBackend)));
    }
};

// Test: Normal Operation when certificates are available
TEST_F(GetAvailableSigningCertificatesTest_1371, GetCertificates_ValidBackend_1371) {
    // Prepare mock data
    std::vector<std::unique_ptr<X509CertificateInfo>> mockCerts;
    mockCerts.push_back(std::make_unique<X509CertificateInfo>());
    
    // Setup the mock method call
    ON_CALL(mockBackend, getAvailableSigningCertificates()).WillByDefault(testing::Return(mockCerts));
    
    // Test the function
    QVector<CertificateInfo> result = Poppler::getAvailableSigningCertificates();

    // Validate results
    EXPECT_EQ(result.size(), 1);
    // Further validations could go here based on actual CertificateInfo properties
}

// Test: Boundary Condition with empty certificates
TEST_F(GetAvailableSigningCertificatesTest_1371, GetCertificates_EmptyBackend_1371) {
    // Setup the mock method call to return an empty vector
    ON_CALL(mockBackend, getAvailableSigningCertificates()).WillByDefault(testing::Return(std::vector<std::unique_ptr<X509CertificateInfo>>{}));

    // Test the function
    QVector<CertificateInfo> result = Poppler::getAvailableSigningCertificates();

    // Validate results
    EXPECT_EQ(result.size(), 0);
}

// Test: Exceptional/Error case when backend creation fails
TEST_F(GetAvailableSigningCertificatesTest_1371, GetCertificates_FailedBackend_1371) {
    // Simulate failed backend creation
    ON_CALL(mockFactory, createActive()).WillByDefault(testing::Return(nullptr));

    // Test the function
    QVector<CertificateInfo> result = Poppler::getAvailableSigningCertificates();

    // Validate results
    EXPECT_EQ(result.size(), 0);
}

// Test: Verification of external interaction (createActive is called)
TEST_F(GetAvailableSigningCertificatesTest_1371, VerifyCreateActiveCall_1371) {
    // Setup the mock method call to simulate backend creation
    EXPECT_CALL(mockFactory, createActive()).Times(1).WillOnce(testing::Return(std::make_unique<MockBackend>(mockBackend)));

    // Test the function
    Poppler::getAvailableSigningCertificates();
}