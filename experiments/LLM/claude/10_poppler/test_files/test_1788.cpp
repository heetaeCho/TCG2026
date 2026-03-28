#include <gtest/gtest.h>
#include <nss.h>
#include <cms.h>
#include <secoid.h>
#include <seccomon.h>
#include <prtypes.h>
#include <secitem.h>

// Include the .cc file to access the static function
// In practice, this would need build system support or the function made accessible
#include "NSSCryptoSignBackend.cc"

class NSSCMSAttributeArrayFindTest_1788 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        // Initialize NSS for OID lookups
        NSS_NoDB_Init(".");
    }

    static void TearDownTestSuite()
    {
        NSS_Shutdown();
    }

    // Helper to create an attribute with a given OID tag
    NSSCMSAttribute *createAttribute(SECOidTag tag)
    {
        SECOidData *oid = SECOID_FindOIDByTag(tag);
        if (!oid) {
            return nullptr;
        }
        NSSCMSAttribute *attr = (NSSCMSAttribute *)PORT_ZAlloc(sizeof(NSSCMSAttribute));
        if (!attr) {
            return nullptr;
        }
        SECITEM_CopyItem(nullptr, &attr->type, &oid->oid);
        allocatedAttrs.push_back(attr);
        return attr;
    }

    void TearDown() override
    {
        for (auto *attr : allocatedAttrs) {
            if (attr) {
                SECITEM_FreeItem(&attr->type, PR_FALSE);
                PORT_Free(attr);
            }
        }
        allocatedAttrs.clear();
    }

    std::vector<NSSCMSAttribute *> allocatedAttrs;
};

// Test that passing nullptr attrs returns nullptr
TEST_F(NSSCMSAttributeArrayFindTest_1788, NullAttrsReturnsNull_1788)
{
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(nullptr, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test that passing nullptr attrs with only=PR_TRUE returns nullptr
TEST_F(NSSCMSAttributeArrayFindTest_1788, NullAttrsOnlyTrueReturnsNull_1788)
{
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(nullptr, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, nullptr);
}

// Test empty array (only null terminator) returns nullptr
TEST_F(NSSCMSAttributeArrayFindTest_1788, EmptyArrayReturnsNull_1788)
{
    NSSCMSAttribute *attrs[] = { nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test finding a single matching attribute with only=PR_FALSE
TEST_F(NSSCMSAttributeArrayFindTest_1788, FindSingleMatchNotOnly_1788)
{
    NSSCMSAttribute *attr = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr, nullptr);
    NSSCMSAttribute *attrs[] = { attr, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, attr);
}

// Test finding a single matching attribute with only=PR_TRUE
TEST_F(NSSCMSAttributeArrayFindTest_1788, FindSingleMatchOnlyTrue_1788)
{
    NSSCMSAttribute *attr = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr, nullptr);
    NSSCMSAttribute *attrs[] = { attr, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, attr);
}

// Test that duplicate matching attributes with only=PR_TRUE returns nullptr
TEST_F(NSSCMSAttributeArrayFindTest_1788, DuplicateMatchOnlyTrueReturnsNull_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, nullptr);
}

// Test that duplicate matching attributes with only=PR_FALSE returns first match
TEST_F(NSSCMSAttributeArrayFindTest_1788, DuplicateMatchNotOnlyReturnsFirst_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, attr1);
}

// Test no match in array returns nullptr
TEST_F(NSSCMSAttributeArrayFindTest_1788, NoMatchReturnsNull_1788)
{
    NSSCMSAttribute *attr = createAttribute(SEC_OID_PKCS9_SIGNING_TIME);
    ASSERT_NE(attr, nullptr);
    NSSCMSAttribute *attrs[] = { attr, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test mixed attributes, find specific one
TEST_F(NSSCMSAttributeArrayFindTest_1788, MixedAttrsFindsCorrectOne_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_SIGNING_TIME);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    NSSCMSAttribute *attr3 = createAttribute(SEC_OID_PKCS9_MESSAGE_DIGEST);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    ASSERT_NE(attr3, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, attr3, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_FALSE);
    EXPECT_EQ(result, attr2);
}

// Test mixed attributes with only=PR_TRUE and unique match
TEST_F(NSSCMSAttributeArrayFindTest_1788, MixedAttrsOnlyTrueUniqueMatch_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_SIGNING_TIME);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    NSSCMSAttribute *attr3 = createAttribute(SEC_OID_PKCS9_MESSAGE_DIGEST);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    ASSERT_NE(attr3, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, attr3, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, attr2);
}

// Test with duplicate match separated by different attribute, only=PR_TRUE
TEST_F(NSSCMSAttributeArrayFindTest_1788, DuplicateSeparatedOnlyTrueReturnsNull_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_SIGNING_TIME);
    NSSCMSAttribute *attr3 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    ASSERT_NE(attr3, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, attr3, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, nullptr);
}

// Test with an invalid/unknown OID tag
TEST_F(NSSCMSAttributeArrayFindTest_1788, InvalidOidTagReturnsNull_1788)
{
    NSSCMSAttribute *attr = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr, nullptr);
    NSSCMSAttribute *attrs[] = { attr, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_UNKNOWN, PR_FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test match at end of array
TEST_F(NSSCMSAttributeArrayFindTest_1788, MatchAtEndOfArray_1788)
{
    NSSCMSAttribute *attr1 = createAttribute(SEC_OID_PKCS9_SIGNING_TIME);
    NSSCMSAttribute *attr2 = createAttribute(SEC_OID_PKCS9_MESSAGE_DIGEST);
    NSSCMSAttribute *attr3 = createAttribute(SEC_OID_PKCS9_CONTENT_TYPE);
    ASSERT_NE(attr1, nullptr);
    ASSERT_NE(attr2, nullptr);
    ASSERT_NE(attr3, nullptr);
    NSSCMSAttribute *attrs[] = { attr1, attr2, attr3, nullptr };
    NSSCMSAttribute *result = my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, SEC_OID_PKCS9_CONTENT_TYPE, PR_TRUE);
    EXPECT_EQ(result, attr3);
}
