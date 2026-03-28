#include <gtest/gtest.h>
#include <sechash.h>
#include <secoid.h>
#include "HashAlgorithm.h"

// Declaration of the function under test (it's static in the .cc file,
// so we need to include the source or declare it here for testing purposes).
// Since it's a static function in the .cc file, we include the source directly.
// This is necessary because the function has internal linkage.
#include "NSSCryptoSignBackend.cc"

class ConvertHashAlgorithmToNssTest_1792 : public ::testing::Test {
protected:
};

TEST_F(ConvertHashAlgorithmToNssTest_1792, Md2ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Md2);
    EXPECT_EQ(result, SEC_OID_MD2);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Md5ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Md5);
    EXPECT_EQ(result, SEC_OID_MD5);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Sha1ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Sha1);
    EXPECT_EQ(result, SEC_OID_SHA1);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Sha256ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Sha256);
    EXPECT_EQ(result, SEC_OID_SHA256);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Sha384ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Sha384);
    EXPECT_EQ(result, SEC_OID_SHA384);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Sha512ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Sha512);
    EXPECT_EQ(result, SEC_OID_SHA512);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, Sha224ReturnsCorrectOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Sha224);
    EXPECT_EQ(result, SEC_OID_SHA224);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, UnknownReturnsUnknownOid_1792)
{
    SECOidTag result = ConvertHashAlgorithmToNss(HashAlgorithm::Unknown);
    EXPECT_EQ(result, SEC_OID_UNKNOWN);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, InvalidEnumValueReturnsUnknownOid_1792)
{
    // Test with an out-of-range enum value cast to HashAlgorithm
    SECOidTag result = ConvertHashAlgorithmToNss(static_cast<HashAlgorithm>(99));
    EXPECT_EQ(result, SEC_OID_UNKNOWN);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, NegativeEnumValueReturnsUnknownOid_1792)
{
    // Test with a negative out-of-range value
    SECOidTag result = ConvertHashAlgorithmToNss(static_cast<HashAlgorithm>(-1));
    EXPECT_EQ(result, SEC_OID_UNKNOWN);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, AllValidEnumsMapToDistinctOids_1792)
{
    // Verify that each valid hash algorithm maps to a distinct NSS OID
    std::set<SECOidTag> oids;
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Md2));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Md5));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Sha1));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Sha256));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Sha384));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Sha512));
    oids.insert(ConvertHashAlgorithmToNss(HashAlgorithm::Sha224));

    // 7 distinct valid algorithms should produce 7 distinct OIDs
    EXPECT_EQ(oids.size(), 7u);
}

TEST_F(ConvertHashAlgorithmToNssTest_1792, UnknownOidNotInValidSet_1792)
{
    // SEC_OID_UNKNOWN should not be returned by any valid (non-Unknown) algorithm
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Md2), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Md5), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Sha1), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Sha256), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Sha384), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Sha512), SEC_OID_UNKNOWN);
    EXPECT_NE(ConvertHashAlgorithmToNss(HashAlgorithm::Sha224), SEC_OID_UNKNOWN);
}
