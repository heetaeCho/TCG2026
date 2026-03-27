#include <gtest/gtest.h>

#include "CryptoSignBackend.h"

#include <string>



TEST(toStdStringTest_1957, ConvertAdbePkcs7Sha1_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::adbe_pkcs7_sha1), "adbe.pkcs7.sha1");

}



TEST(toStdStringTest_1957, ConvertAdbePkcs7Detached_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::adbe_pkcs7_detached), "adbe.pkcs7.detached");

}



TEST(toStdStringTest_1957, ConvertETSCaDES Detached_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::ETSI_CAdES_detached), "ETSI.CAdES.detached");

}



TEST(toStdStringTest_1957, ConvertG10cPgpSignatureDetached_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::g10c_pgp_signature_detached), "g10c.pgp.signature.detached");

}



TEST(toStdStringTest_1957, ConvertUnknownSignatureType_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::unknown_signature_type), "Unknown");

}



TEST(toStdStringTest_1957, ConvertUnsignedSignatureField_1957) {

    EXPECT_EQ(CryptoSign::toStdString(CryptoSign::SignatureType::unsigned_signature_field), "Unsigned");

}



TEST(toStdStringTest_1957, ConvertDefaultCase_1957) {

    // Assuming there's no enum value that maps to the default case

    // If there were, we would test it here.

    EXPECT_EQ(CryptoSign::toStdString(static_cast<CryptoSign::SignatureType>(6)), "Unhandled");

}
