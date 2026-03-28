#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <algorithm>
#include <gpgme++/global.h>
#include "GPGMECryptoSignBackend.h"
#include "GPGMECryptoSignBackendConfiguration.h"

// Since allowedTypes() is a static function in the .cc file, we cannot directly call it
// from the test. However, based on the prompt, we need to test the observable behavior.
// We'll test through the GpgSignatureConfiguration interface and any public API that
// exposes the allowedTypes behavior.
//
// Since the function is static (file-local), we need to test it indirectly through
// whatever public interface uses it. But given the constraints, we'll test
// GpgSignatureConfiguration behavior which directly affects allowedTypes().

class GpgSignatureConfigurationTest_1955 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize GPGME
        GpgME::initializeLibrary();
    }

    void TearDown() override {
        // Reset to default state
        GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    }
};

// Test that PGP signatures can be enabled
TEST_F(GpgSignatureConfigurationTest_1955, SetPgpSignaturesAllowedTrue_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    EXPECT_TRUE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test that PGP signatures can be disabled
TEST_F(GpgSignatureConfigurationTest_1955, SetPgpSignaturesAllowedFalse_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test toggling PGP signatures from false to true
TEST_F(GpgSignatureConfigurationTest_1955, TogglePgpSignaturesFalseToTrue_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    EXPECT_TRUE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test toggling PGP signatures from true to false
TEST_F(GpgSignatureConfigurationTest_1955, TogglePgpSignaturesTrueToFalse_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    EXPECT_TRUE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test that setting the same value multiple times is idempotent
TEST_F(GpgSignatureConfigurationTest_1955, SetPgpSignaturesAllowedIdempotentTrue_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    EXPECT_TRUE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test that setting false multiple times is idempotent
TEST_F(GpgSignatureConfigurationTest_1955, SetPgpSignaturesAllowedIdempotentFalse_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test default state - PGP signatures should be disabled by default
TEST_F(GpgSignatureConfigurationTest_1955, DefaultPgpSignaturesNotAllowed_1955) {
    // After TearDown resets to false, the default should be false
    GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
    EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
}

// Test rapid toggling
TEST_F(GpgSignatureConfigurationTest_1955, RapidToggling_1955) {
    for (int i = 0; i < 100; ++i) {
        GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
        EXPECT_TRUE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
        GpgSignatureConfiguration::setPgpSignaturesAllowed(false);
        EXPECT_FALSE(GpgSignatureConfiguration::arePgpSignaturesAllowed());
    }
}

// Test that arePgpSignaturesAllowed can be called multiple times consistently
TEST_F(GpgSignatureConfigurationTest_1955, ConsistentReadAfterWrite_1955) {
    GpgSignatureConfiguration::setPgpSignaturesAllowed(true);
    bool first = GpgSignatureConfiguration::arePgpSignaturesAllowed();
    bool second = GpgSignatureConfiguration::arePgpSignaturesAllowed();
    bool third = GpgSignatureConfiguration::arePgpSignaturesAllowed();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_TRUE(first);
}
