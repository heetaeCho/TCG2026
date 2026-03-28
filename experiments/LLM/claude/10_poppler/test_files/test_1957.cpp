#include <gtest/gtest.h>
#include "CryptoSignBackend.h"

class CryptoSignToStdStringTest_1957 : public ::testing::Test {
protected:
};

TEST_F(CryptoSignToStdStringTest_1957, UnsignedSignatureField_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::unsigned_signature_field);
    EXPECT_EQ(result, "Unsigned");
}

TEST_F(CryptoSignToStdStringTest_1957, UnknownSignatureType_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::unknown_signature_type);
    EXPECT_EQ(result, "Unknown");
}

TEST_F(CryptoSignToStdStringTest_1957, ETSICAdESDetached_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::ETSI_CAdES_detached);
    EXPECT_EQ(result, "ETSI.CAdES.detached");
}

TEST_F(CryptoSignToStdStringTest_1957, AdbePkcs7Detached_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::adbe_pkcs7_detached);
    EXPECT_EQ(result, "adbe.pkcs7.detached");
}

TEST_F(CryptoSignToStdStringTest_1957, AdbePkcs7Sha1_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::adbe_pkcs7_sha1);
    EXPECT_EQ(result, "adbe.pkcs7.sha1");
}

TEST_F(CryptoSignToStdStringTest_1957, G10cPgpSignatureDetached_1957) {
    std::string result = CryptoSign::toStdString(CryptoSign::SignatureType::g10c_pgp_signature_detached);
    EXPECT_EQ(result, "g10c.pgp.signature.detached");
}

TEST_F(CryptoSignToStdStringTest_1957, UnhandledValue_1957) {
    // Cast an out-of-range integer to SignatureType to trigger the default "Unhandled" path
    std::string result = CryptoSign::toStdString(static_cast<CryptoSign::SignatureType>(99));
    EXPECT_EQ(result, "Unhandled");
}

TEST_F(CryptoSignToStdStringTest_1957, AllEnumValuesProduceNonEmptyStrings_1957) {
    std::vector<CryptoSign::SignatureType> allTypes = {
        CryptoSign::SignatureType::adbe_pkcs7_sha1,
        CryptoSign::SignatureType::adbe_pkcs7_detached,
        CryptoSign::SignatureType::ETSI_CAdES_detached,
        CryptoSign::SignatureType::g10c_pgp_signature_detached,
        CryptoSign::SignatureType::unknown_signature_type,
        CryptoSign::SignatureType::unsigned_signature_field
    };
    for (auto type : allTypes) {
        std::string result = CryptoSign::toStdString(type);
        EXPECT_FALSE(result.empty()) << "Expected non-empty string for enum value " << static_cast<int>(type);
    }
}

TEST_F(CryptoSignToStdStringTest_1957, AllEnumValuesAreDistinct_1957) {
    std::vector<CryptoSign::SignatureType> allTypes = {
        CryptoSign::SignatureType::adbe_pkcs7_sha1,
        CryptoSign::SignatureType::adbe_pkcs7_detached,
        CryptoSign::SignatureType::ETSI_CAdES_detached,
        CryptoSign::SignatureType::g10c_pgp_signature_detached,
        CryptoSign::SignatureType::unknown_signature_type,
        CryptoSign::SignatureType::unsigned_signature_field
    };
    std::set<std::string> results;
    for (auto type : allTypes) {
        results.insert(CryptoSign::toStdString(type));
    }
    EXPECT_EQ(results.size(), allTypes.size()) << "All enum values should map to distinct strings";
}

TEST_F(CryptoSignToStdStringTest_1957, NegativeEnumValueReturnsUnhandled_1957) {
    std::string result = CryptoSign::toStdString(static_cast<CryptoSign::SignatureType>(-1));
    EXPECT_EQ(result, "Unhandled");
}

TEST_F(CryptoSignToStdStringTest_1957, BoundaryValueJustAboveMax_1957) {
    // The highest defined enum value is 5 (unsigned_signature_field), test 6
    std::string result = CryptoSign::toStdString(static_cast<CryptoSign::SignatureType>(6));
    EXPECT_EQ(result, "Unhandled");
}
