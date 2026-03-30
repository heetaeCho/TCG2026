#include <gtest/gtest.h>
#include "NSSCryptoSignBackend.h"  // Include the header file with ConvertHashTypeFromNss
#include "HashAlgorithm.h"  // Include the enum HashAlgorithm

// Test case for ConvertHashTypeFromNss function (TEST_ID: 1793)
class NSSCryptoSignBackendTest_1793 : public ::testing::Test {
protected:
    // Helper function for checking conversion results
    void CheckHashConversion(HASH_HashType input, HashAlgorithm expected) {
        EXPECT_EQ(ConvertHashTypeFromNss(input), expected);
    }
};

// Normal Operation Tests
TEST_F(NSSCryptoSignBackendTest_1793, ConvertMD2_1793) {
    CheckHashConversion(HASH_AlgMD2, HashAlgorithm::Md2);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertMD5_1793) {
    CheckHashConversion(HASH_AlgMD5, HashAlgorithm::Md5);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA1_1793) {
    CheckHashConversion(HASH_AlgSHA1, HashAlgorithm::Sha1);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA256_1793) {
    CheckHashConversion(HASH_AlgSHA256, HashAlgorithm::Sha256);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA384_1793) {
    CheckHashConversion(HASH_AlgSHA384, HashAlgorithm::Sha384);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA512_1793) {
    CheckHashConversion(HASH_AlgSHA512, HashAlgorithm::Sha512);
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA224_1793) {
    CheckHashConversion(HASH_AlgSHA224, HashAlgorithm::Sha224);
}

// Boundary Condition Tests
TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA3_224_1793) {
    CheckHashConversion(HASH_AlgSHA3_224, HashAlgorithm::Unknown);  // Since NSS_VMAJOR < 3 || NSS_VMINOR < 91 in non-SHA3 environments
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertSHA3_256_1793) {
    CheckHashConversion(HASH_AlgSHA3_256, HashAlgorithm::Unknown);  // Same as above
}

// Exceptional or Error Cases
TEST_F(NSSCryptoSignBackendTest_1793, ConvertNULL_1793) {
    CheckHashConversion(HASH_AlgNULL, HashAlgorithm::Unknown);  // Expected behavior for HASH_AlgNULL
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertTOTAL_1793) {
    CheckHashConversion(HASH_AlgTOTAL, HashAlgorithm::Unknown);  // Expected behavior for HASH_AlgTOTAL
}

TEST_F(NSSCryptoSignBackendTest_1793, ConvertInvalid_1793) {
    CheckHashConversion(static_cast<HASH_HashType>(9999), HashAlgorithm::Unknown);  // Invalid type, should return Unknown
}