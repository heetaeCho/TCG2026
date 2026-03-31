#include <gtest/gtest.h>
#include <gmock/gmock.h>

// NSS headers
#include <nss.h>
#include <cms.h>
#include <secoid.h>
#include <seccomon.h>
#include <secitem.h>

// Since my_NSS_CMSAttribute_GetType is a static function in the .cc file,
// we include the source to access it for testing purposes.
// In a real project, this might be exposed differently for testability.
#include "NSSCryptoSignBackend.cc"

class MyNSSCMSAttributeGetTypeTest_1790 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize NSS for the test suite
        if (NSS_NoDB_Init(nullptr) != SECSuccess) {
            // NSS may already be initialized
        }
    }

    static void TearDownTestSuite() {
        NSS_Shutdown();
    }
};

// Test that when SECOID_FindOID returns nullptr (unknown OID), we get SEC_OID_UNKNOWN
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsUnknownForUnrecognizedOID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    // Set up an OID that NSS won't recognize
    unsigned char bogusOidData[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    attr.type.data = bogusOidData;
    attr.type.len = sizeof(bogusOidData);

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_UNKNOWN);
}

// Test that when SECOID_FindOID finds a valid OID, the correct tag is returned
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsCorrectTagForKnownOID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    // Use a well-known OID - SEC_OID_PKCS7_DATA
    SECOidData *oidData = SECOID_FindOIDByTag(SEC_OID_PKCS7_DATA);
    ASSERT_NE(oidData, nullptr);

    attr.type = oidData->oid;

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_PKCS7_DATA);
}

// Test with another known OID to verify generality
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsCorrectTagForSHA256OID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    SECOidData *oidData = SECOID_FindOIDByTag(SEC_OID_SHA256);
    ASSERT_NE(oidData, nullptr);

    attr.type = oidData->oid;

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_SHA256);
}

// Test with zero-length OID data (boundary condition)
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsUnknownForEmptyOID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    attr.type.data = nullptr;
    attr.type.len = 0;

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_UNKNOWN);
}

// Test with PKCS9 content type OID (commonly used in CMS attributes)
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsCorrectTagForContentTypeOID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    SECOidData *oidData = SECOID_FindOIDByTag(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(oidData, nullptr);

    attr.type = oidData->oid;

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_PKCS9_CONTENT_TYPE);
}

// Test with signing time OID (another common CMS attribute)
TEST_F(MyNSSCMSAttributeGetTypeTest_1790, ReturnsCorrectTagForSigningTimeOID_1790) {
    NSSCMSAttribute attr;
    memset(&attr, 0, sizeof(attr));

    SECOidData *oidData = SECOID_FindOIDByTag(SEC_OID_PKCS9_SIGNING_TIME);
    ASSERT_NE(oidData, nullptr);

    attr.type = oidData->oid;

    SECOidTag result = my_NSS_CMSAttribute_GetType(&attr);
    EXPECT_EQ(result, SEC_OID_PKCS9_SIGNING_TIME);
}
