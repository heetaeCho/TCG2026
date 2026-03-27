#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CryptoSignBackend.h"



using namespace CryptoSign;



TEST(CryptoSignTests_1956, SignatureTypeFromString_ReturnsETSI_CAdES_detached_1956) {

    EXPECT_EQ(signatureTypeFromString("ETSI.CAdES.detached"), SignatureType::ETSI_CAdES_detached);

}



TEST(CryptoSignTests_1956, SignatureTypeFromString_Returnsadbe_pkcs7_detached_1956) {

    EXPECT_EQ(signatureTypeFromString("adbe.pkcs7.detached"), SignatureType::adbe_pkcs7_detached);

}



TEST(CryptoSignTests_1956, SignatureTypeFromString_Returnsadbe_pkcs7_sha1_1956) {

    EXPECT_EQ(signatureTypeFromString("adbe.pkcs7.sha1"), SignatureType::adbe_pkcs7_sha1);

}



TEST(CryptoSignTests_1956, SignatureTypeFromString_Returnsg10c_pgp_signature_detached_1956) {

    EXPECT_EQ(signatureTypeFromString("g10c.pgp.signature.detached"), SignatureType::g10c_pgp_signature_detached);

}



TEST(CryptoSignTests_1956, SignatureTypeFromString_ReturnsUnknownForInvalidInput_1956) {

    EXPECT_EQ(signatureTypeFromString("invalid.input"), SignatureType::unknown_signature_type);

}



TEST(CryptoSignTests_1956, SignatureTypeFromString_BoundaryConditionEmptyString_1956) {

    EXPECT_EQ(signatureTypeFromString(""), SignatureType::unknown_signature_type);

}
