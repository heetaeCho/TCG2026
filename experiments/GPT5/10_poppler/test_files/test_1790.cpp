#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocking the SECOidData structure and SECOID_FindOID function
struct SECOidData {
    int offset;
};

struct NSSCMSAttribute {
    SECOidData* type;
};

// Mocked function to simulate SECOID_FindOID
SECOidData* SECOID_FindOID(NSSCMSAttribute* attr) {
    return attr->type;
}

// The function under test
static SECOidTag my_NSS_CMSAttribute_GetType(NSSCMSAttribute* attr) {
    SECOidData* typetag;
    typetag = SECOID_FindOID(&(attr->type));
    if (typetag == nullptr) {
        return SEC_OID_UNKNOWN;
    }
    return typetag->offset;
}

class NSSCryptoSignBackendTest_1790 : public testing::Test {};

// Test case for normal operation
TEST_F(NSSCryptoSignBackendTest_1790, TestValidOID_1790) {
    // Prepare a valid NSSCMSAttribute with a valid SECOidData
    SECOidData valid_oid = {10};
    NSSCMSAttribute attr = {&valid_oid};
    
    // Check the return value, expecting the offset value
    EXPECT_EQ(my_NSS_CMSAttribute_GetType(&attr), 10);
}

// Test case for boundary condition: when SECOidData is nullptr
TEST_F(NSSCryptoSignBackendTest_1790, TestNullOID_1790) {
    // Prepare an NSSCMSAttribute with a null SECOidData
    NSSCMSAttribute attr = {nullptr};
    
    // Check the return value, expecting SEC_OID_UNKNOWN
    EXPECT_EQ(my_NSS_CMSAttribute_GetType(&attr), SEC_OID_UNKNOWN);
}

// Test case for exceptional/error case: When SECOid_FindOID returns nullptr
TEST_F(NSSCryptoSignBackendTest_1790, TestInvalidOID_1790) {
    // Simulate SECOid_FindOID returning nullptr (e.g., invalid OID)
    // This can be simulated by having the attribute's type be nullptr.
    NSSCMSAttribute attr = {nullptr};
    
    // The function should return SEC_OID_UNKNOWN in case of error
    EXPECT_EQ(my_NSS_CMSAttribute_GetType(&attr), SEC_OID_UNKNOWN);
}