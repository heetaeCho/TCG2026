#include <gtest/gtest.h>

// Include the header that declares the enum and function
namespace Poppler {

enum class CryptoSignBackend { NSS = 0, GPG = 1 };

enum class CryptoSignBackendFeature {
    /// can the backend sign new signatures
    Signing = 0,
    /// can the backend verify existing signatures
    Verification = 1
};

bool hasCryptoSignBackendFeature(CryptoSignBackend backend, CryptoSignBackendFeature feature);

} // namespace Poppler

class HasCryptoSignBackendFeatureTest_1378 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test NSS backend with Signing feature
TEST_F(HasCryptoSignBackendFeatureTest_1378, NSSBackendSigningFeature_1378)
{
    // Just verify it returns a bool without crashing
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::NSS, Poppler::CryptoSignBackendFeature::Signing);
    EXPECT_TRUE(result == true || result == false);
}

// Test NSS backend with Verification feature
TEST_F(HasCryptoSignBackendFeatureTest_1378, NSSBackendVerificationFeature_1378)
{
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::NSS, Poppler::CryptoSignBackendFeature::Verification);
    EXPECT_TRUE(result == true || result == false);
}

// Test GPG backend with Signing feature
TEST_F(HasCryptoSignBackendFeatureTest_1378, GPGBackendSigningFeature_1378)
{
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::GPG, Poppler::CryptoSignBackendFeature::Signing);
    EXPECT_TRUE(result == true || result == false);
}

// Test GPG backend with Verification feature
TEST_F(HasCryptoSignBackendFeatureTest_1378, GPGBackendVerificationFeature_1378)
{
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::GPG, Poppler::CryptoSignBackendFeature::Verification);
    EXPECT_TRUE(result == true || result == false);
}

// Test with an invalid backend value (not NSS or GPG) - should return false per the default case
TEST_F(HasCryptoSignBackendFeatureTest_1378, InvalidBackendReturnsFalse_1378)
{
    // Cast an invalid integer to CryptoSignBackend to test the default switch case
    Poppler::CryptoSignBackend invalidBackend = static_cast<Poppler::CryptoSignBackend>(99);
    bool result = Poppler::hasCryptoSignBackendFeature(invalidBackend, Poppler::CryptoSignBackendFeature::Signing);
    EXPECT_FALSE(result);
}

// Test with another invalid backend value and Verification feature
TEST_F(HasCryptoSignBackendFeatureTest_1378, InvalidBackendVerificationReturnsFalse_1378)
{
    Poppler::CryptoSignBackend invalidBackend = static_cast<Poppler::CryptoSignBackend>(42);
    bool result = Poppler::hasCryptoSignBackendFeature(invalidBackend, Poppler::CryptoSignBackendFeature::Verification);
    EXPECT_FALSE(result);
}

// Test with negative invalid backend value
TEST_F(HasCryptoSignBackendFeatureTest_1378, NegativeInvalidBackendReturnsFalse_1378)
{
    Poppler::CryptoSignBackend invalidBackend = static_cast<Poppler::CryptoSignBackend>(-1);
    bool result = Poppler::hasCryptoSignBackendFeature(invalidBackend, Poppler::CryptoSignBackendFeature::Signing);
    EXPECT_FALSE(result);
}

// Test NSS backend consistency - calling the same function twice should yield the same result
TEST_F(HasCryptoSignBackendFeatureTest_1378, NSSBackendConsistentResult_1378)
{
    bool result1 = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::NSS, Poppler::CryptoSignBackendFeature::Signing);
    bool result2 = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::NSS, Poppler::CryptoSignBackendFeature::Signing);
    EXPECT_EQ(result1, result2);
}

// Test GPG backend consistency
TEST_F(HasCryptoSignBackendFeatureTest_1378, GPGBackendConsistentResult_1378)
{
    bool result1 = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::GPG, Poppler::CryptoSignBackendFeature::Verification);
    bool result2 = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::GPG, Poppler::CryptoSignBackendFeature::Verification);
    EXPECT_EQ(result1, result2);
}

// Test with invalid feature value for NSS backend - should not crash
TEST_F(HasCryptoSignBackendFeatureTest_1378, NSSBackendInvalidFeature_1378)
{
    Poppler::CryptoSignBackendFeature invalidFeature = static_cast<Poppler::CryptoSignBackendFeature>(999);
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::NSS, invalidFeature);
    EXPECT_TRUE(result == true || result == false);
}

// Test with invalid feature value for GPG backend - should not crash
TEST_F(HasCryptoSignBackendFeatureTest_1378, GPGBackendInvalidFeature_1378)
{
    Poppler::CryptoSignBackendFeature invalidFeature = static_cast<Poppler::CryptoSignBackendFeature>(999);
    bool result = Poppler::hasCryptoSignBackendFeature(Poppler::CryptoSignBackend::GPG, invalidFeature);
    EXPECT_TRUE(result == true || result == false);
}
