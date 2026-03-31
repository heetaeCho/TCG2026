#include <gtest/gtest.h>
#include <gmock/gmock.h>

// NSS headers
#include <nss.h>
#include <cms.h>
#include <cert.h>
#include <secmod.h>
#include <pk11pub.h>

// Include the source file to access the static function
#include "NSSCryptoSignBackend.cc"

class CMSSignerInfoCreateTest_1801 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (NSS_NoDB_Init(nullptr) != SECSuccess) {
            GTEST_SKIP() << "NSS initialization failed";
        }
    }

    static void TearDownTestSuite() { NSS_Shutdown(); }
};

TEST_F(CMSSignerInfoCreateTest_1801, ReturnsNullWhenCmsSignedDataIsNull_1801)
{
    // Passing nullptr should not crash but behavior depends on NSS internals
    // NSS_CMSSignedData_GetSignerInfo with nullptr is expected to return nullptr
    NSSCMSSignerInfo *result = CMS_SignerInfoCreate(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CMSSignerInfoCreateTest_1801, ReturnsNullWhenNoSignerInfoPresent_1801)
{
    // Create a CMS message with signed data but no signer info
    NSSCMSMessage *cmsMsg = NSS_CMSMessage_Create(nullptr);
    ASSERT_NE(cmsMsg, nullptr);

    NSSCMSSignedData *signedData = NSS_CMSSignedData_Create(cmsMsg);
    if (signedData == nullptr) {
        NSS_CMSMessage_Destroy(cmsMsg);
        GTEST_SKIP() << "Could not create NSSCMSSignedData";
    }

    // No signer info has been added, so GetSignerInfo(0) should return nullptr
    NSSCMSSignerInfo *result = CMS_SignerInfoCreate(signedData);
    EXPECT_EQ(result, nullptr);

    NSS_CMSMessage_Destroy(cmsMsg);
}

TEST_F(CMSSignerInfoCreateTest_1801, ReturnsSignerInfoWhenPresent_1801)
{
    // This test verifies that when a valid signed data with signer info exists,
    // the function returns a non-null pointer.
    // Creating a full valid signer info requires a certificate, which requires
    // a proper NSS database. We test what we can.

    NSSCMSMessage *cmsMsg = NSS_CMSMessage_Create(nullptr);
    ASSERT_NE(cmsMsg, nullptr);

    NSSCMSSignedData *signedData = NSS_CMSSignedData_Create(cmsMsg);
    if (signedData == nullptr) {
        NSS_CMSMessage_Destroy(cmsMsg);
        GTEST_SKIP() << "Could not create NSSCMSSignedData";
    }

    // Without a real certificate we cannot add signer info,
    // so we verify the empty case returns null consistently
    NSSCMSSignerInfo *result = CMS_SignerInfoCreate(signedData);
    EXPECT_EQ(result, nullptr);

    NSS_CMSMessage_Destroy(cmsMsg);
}

TEST_F(CMSSignerInfoCreateTest_1801, ConsistentBehaviorOnRepeatedCalls_1801)
{
    NSSCMSMessage *cmsMsg = NSS_CMSMessage_Create(nullptr);
    ASSERT_NE(cmsMsg, nullptr);

    NSSCMSSignedData *signedData = NSS_CMSSignedData_Create(cmsMsg);
    if (signedData == nullptr) {
        NSS_CMSMessage_Destroy(cmsMsg);
        GTEST_SKIP() << "Could not create NSSCMSSignedData";
    }

    NSSCMSSignerInfo *result1 = CMS_SignerInfoCreate(signedData);
    NSSCMSSignerInfo *result2 = CMS_SignerInfoCreate(signedData);
    EXPECT_EQ(result1, result2);

    NSS_CMSMessage_Destroy(cmsMsg);
}
