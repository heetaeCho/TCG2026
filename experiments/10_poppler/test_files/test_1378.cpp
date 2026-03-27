#include <gtest/gtest.h>

#include "poppler-form.h"



namespace Poppler {

    bool hasNSSBackendFeature(CryptoSignBackendFeature feature);

    bool hasGPGBackendFeature(CryptoSignBackendFeature feature);

}



using namespace Poppler;



// Mock functions for hasNSSBackendFeature and hasGPGBackendFeature

bool mockHasNSSBackendFeature(CryptoSignBackendFeature feature) {

    // Mock implementation for testing

    return feature == CryptoSignBackendFeature::SupportsSigning;

}



bool mockHasGPGBackendFeature(CryptoSignBackendFeature feature) {

    // Mock implementation for testing

    return feature == CryptoSignBackendFeature::SupportsEncryption;

}



class HasCryptoSignBackendFeatureTest_1378 : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect calls to mock functions

        Poppler::hasNSSBackendFeature = mockHasNSSBackendFeature;

        Poppler::hasGPGBackendFeature = mockHasGPGBackendFeature;

    }

};



TEST_F(HasCryptoSignBackendFeatureTest_1378, NSS_Backend_SupportsSigning_1378) {

    EXPECT_TRUE(hasCryptoSignBackendFeature(CryptoSignBackend::NSS, CryptoSignBackendFeature::SupportsSigning));

}



TEST_F(HasCryptoSignBackendFeatureTest_1378, NSS_Backend_DoesNotSupportEncryption_1378) {

    EXPECT_FALSE(hasCryptoSignBackendFeature(CryptoSignBackend::NSS, CryptoSignBackendFeature::SupportsEncryption));

}



TEST_F(HasCryptoSignBackendFeatureTest_1378, GPG_Backend_SupportsEncryption_1378) {

    EXPECT_TRUE(hasCryptoSignBackendFeature(CryptoSignBackend::GPG, CryptoSignBackendFeature::SupportsEncryption));

}



TEST_F(HasCryptoSignBackendFeatureTest_1378, GPG_Backend_DoesNotSupportSigning_1378) {

    EXPECT_FALSE(hasCryptoSignBackendFeature(CryptoSignBackend::GPG, CryptoSignBackendFeature::SupportsSigning));

}



TEST_F(HasCryptoSignBackendFeatureTest_1378, Unknown_Backend_ReturnsFalse_1378) {

    EXPECT_FALSE(hasCryptoSignBackendFeature(static_cast<CryptoSignBackend>(2), CryptoSignBackendFeature::SupportsSigning));

}
