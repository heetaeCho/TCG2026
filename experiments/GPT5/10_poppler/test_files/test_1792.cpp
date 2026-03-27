#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HashAlgorithm.h"

// Function declaration
extern SECOidTag ConvertHashAlgorithmToNss(HashAlgorithm digestAlgId);

// Test suite for ConvertHashAlgorithmToNss
class ConvertHashAlgorithmToNssTest_1792 : public ::testing::Test {
protected:
    void SetUp() override {
        // Any necessary setup can go here
    }

    void TearDown() override {
        // Clean-up code, if needed, goes here
    }
};

// Test normal operation for all supported algorithms
TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Md2_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Md2), SEC_OID_MD2);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Md5_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Md5), SEC_OID_MD5);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Sha1_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha1), SEC_OID_SHA1);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Sha256_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha256), SEC_OID_SHA256);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Sha384_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha384), SEC_OID_SHA384);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Sha512_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha512), SEC_OID_SHA512);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Sha224_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha224), SEC_OID_SHA224);
}

// Test boundary condition for the Unknown value
TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_Unknown_1792) {
    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Unknown), SEC_OID_UNKNOWN);
}

// Test exceptional or error case for unsupported enum values (if any)
TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertHashAlgorithmToNss_InvalidValue_1792) {
    // If we pass a value outside the expected enum range, it should return SEC_OID_UNKNOWN
    EXPECT_EQ(ConvertHashAlgorithmToNss(static_cast<HashAlgorithm>(999)), SEC_OID_UNKNOWN);
}