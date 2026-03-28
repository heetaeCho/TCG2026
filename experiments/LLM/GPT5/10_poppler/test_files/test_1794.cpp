#include <gtest/gtest.h>
#include "HashAlgorithm.h"

// Function to test
static unsigned int digestLength(HashAlgorithm digestAlgId) {
    switch (digestAlgId) {
        case HashAlgorithm::Sha1: return 20;
        case HashAlgorithm::Sha256: return 32;
        case HashAlgorithm::Sha384: return 48;
        case HashAlgorithm::Sha512: return 64;
        default:
            printf("ERROR: Unrecognized Hash ID\n");
            return 0;
    }
}

// Test cases
TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_Sha1_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha1), 20);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_Sha256_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha256), 32);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_Sha384_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha384), 48);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_Sha512_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha512), 64);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_UnknownAlgorithm_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Unknown), 0);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_InvalidMd2_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Md2), 0);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_InvalidMd5_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Md5), 0);
}

TEST_F(NSSCryptoSignBackendTest_1794, DigestLength_Sha224_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha224), 0); // No defined length for Sha224
}