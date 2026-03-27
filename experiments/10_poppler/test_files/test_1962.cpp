#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CryptoSignBackend.h"



namespace CryptoSign {

    std::vector<Backend::Type> createAvailableBackends();

}



class CreateAvailableBackendsTest_1962 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(CreateAvailableBackendsTest_1962, ReturnsEmptyVectorIfNoBackendsEnabled_1962) {

    std::vector<CryptoSign::Backend::Type> backends = CryptoSign::createAvailableBackends();

    EXPECT_TRUE(backends.empty());

}



#ifdef ENABLE_NSS3

TEST_F(CreateAvailableBackendsTest_1962, ReturnsNSS3IfOnlyNss3Enabled_1962) {

    std::vector<CryptoSign::Backend::Type> backends = CryptoSign::createAvailableBackends();

    EXPECT_EQ(backends.size(), 1);

    EXPECT_EQ(backends[0], CryptoSign::Backend::Type::NSS3);

}

#endif



#ifdef ENABLE_GPGME

TEST_F(CreateAvailableBackendsTest_1962, ReturnsGpgmeIfOnlyGpgmeEnabledAndSufficientVersion_1962) {

    std::vector<CryptoSign::Backend::Type> backends = CryptoSign::createAvailableBackends();

    EXPECT_EQ(backends.size(), 1);

    EXPECT_EQ(backends[0], CryptoSign::Backend::Type::GPGME);

}

#endif



#ifdef ENABLE_NSS3

#ifdef ENABLE_GPGME

TEST_F(CreateAvailableBackendsTest_1962, ReturnsBothIfNss3AndGpgmeEnabledAndSufficientVersion_1962) {

    std::vector<CryptoSign::Backend::Type> backends = CryptoSign::createAvailableBackends();

    EXPECT_EQ(backends.size(), 2);

    EXPECT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::NSS3) != backends.end());

    EXPECT_TRUE(std::find(backends.begin(), backends.end(), CryptoSign::Backend::Type::GPGME) != backends.end());

}

#endif

#endif



#ifdef ENABLE_GPGME

TEST_F(CreateAvailableBackendsTest_1962, ReturnsEmptyVectorIfGpgmeEnabledButInsufficientVersion_1962) {

    // Assuming a way to mock GpgSignatureBackend::hasSufficientVersion() to return false

    EXPECT_CALL(*mockGpgSignatureBackend, hasSufficientVersion()).WillOnce(::testing::Return(false));

    std::vector<CryptoSign::Backend::Type> backends = CryptoSign::createAvailableBackends();

    EXPECT_TRUE(backends.empty());

}

#endif

```


