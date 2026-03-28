#include <gtest/gtest.h>
#include "CryptoSignBackend.h"
#include <string_view>

class CryptoSignBackendTest_1956 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(CryptoSignBackendTest_1956, ETSICAdESDetachedReturnsCorrectType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ETSI.CAdES.detached");
    EXPECT_EQ(result, CryptoSign::SignatureType::ETSI_CAdES_detached);
}

TEST_F(CryptoSignBackendTest_1956, AdbePkcs7DetachedReturnsCorrectType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("adbe.pkcs7.detached");
    EXPECT_EQ(result, CryptoSign::SignatureType::adbe_pkcs7_detached);
}

TEST_F(CryptoSignBackendTest_1956, AdbePkcs7Sha1ReturnsCorrectType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("adbe.pkcs7.sha1");
    EXPECT_EQ(result, CryptoSign::SignatureType::adbe_pkcs7_sha1);
}

TEST_F(CryptoSignBackendTest_1956, G10cPgpSignatureDetachedReturnsCorrectType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("g10c.pgp.signature.detached");
    EXPECT_EQ(result, CryptoSign::SignatureType::g10c_pgp_signature_detached);
}

// Unknown / error cases

TEST_F(CryptoSignBackendTest_1956, EmptyStringReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, RandomStringReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("some.random.string");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, CaseSensitiveETSIReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("etsi.cades.detached");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, CaseSensitiveAdbePkcs7DetachedUpperReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ADBE.PKCS7.DETACHED");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, CaseSensitiveAdbePkcs7Sha1UpperReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ADBE.PKCS7.SHA1");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, CaseSensitiveG10cUpperReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("G10C.PGP.SIGNATURE.DETACHED");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

// Boundary conditions - strings with extra characters

TEST_F(CryptoSignBackendTest_1956, ExtraLeadingSpaceReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString(" ETSI.CAdES.detached");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, ExtraTrailingSpaceReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ETSI.CAdES.detached ");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, SubstringOfValidTypeReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ETSI.CAdES");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, SuperstringOfValidTypeReturnsUnknownType_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ETSI.CAdES.detached.extra");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, NullCharInStringReturnsUnknownType_1956)
{
    // A string_view with embedded null - "ETSI.CAdES.detached\0x" has length > actual string
    std::string_view sv("ETSI.CAdES.detached\0x", 21);
    auto result = CryptoSign::signatureTypeFromString(sv);
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

// Verify enum values match expected integer representations

TEST_F(CryptoSignBackendTest_1956, EnumValuesAreCorrect_1956)
{
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::adbe_pkcs7_sha1), 0);
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::adbe_pkcs7_detached), 1);
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::ETSI_CAdES_detached), 2);
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::g10c_pgp_signature_detached), 3);
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::unknown_signature_type), 4);
    EXPECT_EQ(static_cast<int>(CryptoSign::SignatureType::unsigned_signature_field), 5);
}

// Test with partial matches

TEST_F(CryptoSignBackendTest_1956, PartialMatchAdbeReturnsUnknown_1956)
{
    auto result = CryptoSign::signatureTypeFromString("adbe.pkcs7");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, PartialMatchG10cReturnsUnknown_1956)
{
    auto result = CryptoSign::signatureTypeFromString("g10c.pgp");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

// Test with similar but different strings

TEST_F(CryptoSignBackendTest_1956, SimilarStringAdbeDetachedWithTypoReturnsUnknown_1956)
{
    auto result = CryptoSign::signatureTypeFromString("adbe.pkcs7.detachd");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}

TEST_F(CryptoSignBackendTest_1956, SimilarStringETSIWithTypoReturnsUnknown_1956)
{
    auto result = CryptoSign::signatureTypeFromString("ETSI.CAdES.detachd");
    EXPECT_EQ(result, CryptoSign::SignatureType::unknown_signature_type);
}
