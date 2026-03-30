#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/NSSCryptoSignBackend.cc"  // Include the file containing the function to be tested



using namespace testing;



// Mocking SECOidData and NSSCMSAttribute for testing purposes

struct SECOidData {

    SECItem oid;

};



struct NSSCMSAttribute {

    SECItem type;

};



// Mocking necessary functions

SECOidData* SECOID_FindOIDByTag(SECOidTag) {

    static SECOidData oidData;

    return &oidData;

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, AttrsNull_ReturnsNull_1788) {

    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(nullptr, 0, PR_TRUE), nullptr);

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, OidNotFound_ReturnsNull_1788) {

    SECOidData* oid = SECOID_FindOIDByTag(0);

    oid->oid.len = 5;

    oid->oid.data = reinterpret_cast<unsigned char*>("dummy");



    NSSCMSAttribute attr;

    attr.type.len = 6;

    attr.type.data = reinterpret_cast<unsigned char*>("dummy2");

    

    NSSCMSAttribute* attrs[] = { &attr, nullptr };



    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, 0, PR_TRUE), nullptr);

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, SingleMatch_ReturnsAttr_1788) {

    SECOidData* oid = SECOID_FindOIDByTag(0);

    oid->oid.len = 5;

    oid->oid.data = reinterpret_cast<unsigned char*>("dummy");



    NSSCMSAttribute attr;

    attr.type.len = 5;

    attr.type.data = reinterpret_cast<unsigned char*>("dummy");

    

    NSSCMSAttribute* attrs[] = { &attr, nullptr };



    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, 0, PR_TRUE), &attr);

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, MultipleMatches_ReturnsNull_1788) {

    SECOidData* oid = SECOID_FindOIDByTag(0);

    oid->oid.len = 5;

    oid->oid.data = reinterpret_cast<unsigned char*>("dummy");



    NSSCMSAttribute attr1, attr2;

    attr1.type.len = 5;

    attr1.type.data = reinterpret_cast<unsigned char*>("dummy");

    attr2.type.len = 5;

    attr2.type.data = reinterpret_cast<unsigned char*>("dummy");

    

    NSSCMSAttribute* attrs[] = { &attr1, &attr2, nullptr };



    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, 0, PR_TRUE), nullptr);

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, SingleMatchOnlyFalse_ReturnsAttr_1788) {

    SECOidData* oid = SECOID_FindOIDByTag(0);

    oid->oid.len = 5;

    oid->oid.data = reinterpret_cast<unsigned char*>("dummy");



    NSSCMSAttribute attr;

    attr.type.len = 5;

    attr.type.data = reinterpret_cast<unsigned char*>("dummy");

    

    NSSCMSAttribute* attrs[] = { &attr, nullptr };



    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, 0, PR_FALSE), &attr);

}



TEST(my_NSS_CMSAttributeArray_FindAttrByOidTag_1788, MultipleMatchesOnlyFalse_ReturnsFirstMatch_1788) {

    SECOidData* oid = SECOID_FindOIDByTag(0);

    oid->oid.len = 5;

    oid->oid.data = reinterpret_cast<unsigned char*>("dummy");



    NSSCMSAttribute attr1, attr2;

    attr1.type.len = 5;

    attr1.type.data = reinterpret_cast<unsigned char*>("dummy");

    attr2.type.len = 5;

    attr2.type.data = reinterpret_cast<unsigned char*>("dummy");

    

    NSSCMSAttribute* attrs[] = { &attr1, &attr2, nullptr };



    EXPECT_EQ(my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, 0, PR_FALSE), &attr1);

}
