#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/CryptoSignBackend.h"  // Adjust the path as needed

namespace CryptoSign {

class SignatureTypeFromStringTest : public ::testing::Test {
};

// Test case for normal operation
TEST_F(SignatureTypeFromStringTest, ValidSignatureTypes_1956) {
    EXPECT_EQ(signatureTypeFromString("ETSI.CAdES.detached"), SignatureType::ETSI_CAdES_detached);
    EXPECT_EQ(signatureTypeFromString("adbe.pkcs7.detached"), SignatureType::adbe_pkcs7_detached);
    EXPECT_EQ(signatureTypeFromString("adbe.pkcs7.sha1"), SignatureType::adbe_pkcs7_sha1);
    EXPECT_EQ(signatureTypeFromString("g10c.pgp.signature.detached"), SignatureType::g10c_pgp_signature_detached);
}

// Test case for unknown signature type
TEST_F(SignatureTypeFromStringTest, UnknownSignatureType_1957) {
    EXPECT_EQ(signatureTypeFromString("unknown_signature"), SignatureType::unknown_signature_type);
}

// Test case for empty string input
TEST_F(SignatureTypeFromStringTest, EmptyString_1958) {
    EXPECT_EQ(signatureTypeFromString(""), SignatureType::unknown_signature_type);
}

// Test case for string with spaces
TEST_F(SignatureTypeFromStringTest, StringWithSpaces_1959) {
    EXPECT_EQ(signatureTypeFromString(" ETSI.CAdES.detached "), SignatureType::ETSI_CAdES_detached);
}

// Test case for case-sensitive input (ensure that the function is case-sensitive)
TEST_F(SignatureTypeFromStringTest, CaseSensitiveInput_1960) {
    EXPECT_EQ(signatureTypeFromString("etsi.cades.detached"), SignatureType::unknown_signature_type);
}

// Test case for valid signature type with leading/trailing spaces
TEST_F(SignatureTypeFromStringTest, ValidSignatureWithSpaces_1961) {
    EXPECT_EQ(signatureTypeFromString(" adbe.pkcs7.detached "), SignatureType::adbe_pkcs7_detached);
}

}  // namespace CryptoSign