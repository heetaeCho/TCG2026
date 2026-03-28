#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "./TestProjects/poppler/poppler/CryptoSignBackend.h"  // Adjust the path if necessary

namespace CryptoSignTest {

class CryptoSignBackendTest_1962 : public ::testing::Test {
protected:
    // You can set up any necessary mock objects or common setups here
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(CryptoSignBackendTest_1962, CreateAvailableBackends_NSS3Enabled_1962) {
    // Simulate the condition where NSS3 is enabled
    #if defined(ENABLE_NSS3)
        auto backends = CryptoSign::createAvailableBackends();
        ASSERT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::NSS3) != backends.end()) << "NSS3 should be included in backends";
    #else
        GTEST_SKIP() << "NSS3 is not enabled, skipping test.";
    #endif
}

TEST_F(CryptoSignBackendTest_1962, CreateAvailableBackends_GPGMEEnabled_1963) {
    // Simulate the condition where GPGME is enabled and the version is sufficient
    #if defined(ENABLE_GPGME)
        if (CryptoSign::GpgSignatureBackend::hasSufficientVersion()) {
            auto backends = CryptoSign::createAvailableBackends();
            ASSERT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::GPGME) != backends.end()) << "GPGME should be included in backends";
        }
        else {
            GTEST_SKIP() << "GPGME version is insufficient, skipping test.";
        }
    #else
        GTEST_SKIP() << "GPGME is not enabled, skipping test.";
    #endif
}

TEST_F(CryptoSignBackendTest_1962, CreateAvailableBackends_NoBackendsAvailable_1964) {
    // Test the scenario where no backends are available
    #if !defined(ENABLE_NSS3) && !defined(ENABLE_GPGME)
        auto backends = CryptoSign::createAvailableBackends();
        ASSERT_TRUE(backends.empty()) << "No backends should be available if both NSS3 and GPGME are disabled.";
    #else
        GTEST_SKIP() << "At least one backend is enabled, skipping test.";
    #endif
}

TEST_F(CryptoSignBackendTest_1962, CreateAvailableBackends_MultipleBackends_1965) {
    // Test the scenario where both backends are available (if both NSS3 and GPGME are enabled)
    #if defined(ENABLE_NSS3) && defined(ENABLE_GPGME)
        if (CryptoSign::GpgSignatureBackend::hasSufficientVersion()) {
            auto backends = CryptoSign::createAvailableBackends();
            ASSERT_GE(backends.size(), 2) << "Both NSS3 and GPGME should be available as backends";
            ASSERT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::NSS3) != backends.end()) << "NSS3 should be in the list of backends";
            ASSERT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::GPGME) != backends.end()) << "GPGME should be in the list of backends";
        }
        else {
            GTEST_SKIP() << "GPGME version is insufficient, skipping test.";
        }
    #else
        GTEST_SKIP() << "Both NSS3 and GPGME are not enabled, skipping test.";
    #endif
}

}  // namespace CryptoSignTest