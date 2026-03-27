#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if necessary

class MockPLArenaPool {

public:

    MOCK_METHOD(void*, PORT_ArenaMark, (), (const));

    MOCK_METHOD(void, PORT_ArenaUnmark, (void*, void*), (const));

    MOCK_METHOD(void, PORT_ArenaRelease, (void*, void*), (const));

};



class MockNSSCMSAttribute {

public:

    MOCK_METHOD(SECOidTag, my_NSS_CMSAttribute_GetType, (), (const));

};



class MockNSSCMSArray {

public:

    MOCK_METHOD(SECStatus, my_NSS_CMSArray_Add, (PLArenaPool*, void***, void*), (const));

};



class MockNSSCMSAttributeArray {

public:

    MOCK_METHOD(NSSCMSAttribute*, my_NSS_CMSAttributeArray_FindAttrByOidTag, (NSSCMSAttribute***, SECOidTag, PRBool), (const));

};



// Test fixture

class NSSCryptoSignBackendTest_1791 : public ::testing::Test {

protected:

    MockPLArenaPool mockPool;

    MockNSSCMSAttribute mockAttr;

    MockNSSCMSArray mockArray;

    MockNSSCMSAttributeArray mockArrayFinder;



    PLArenaPool* poolp = &mockPool;

    NSSCMSAttribute*** attrs = nullptr;

    NSSCMSAttribute* attr = &mockAttr;



    SECOidTag testOidTag = static_cast<SECOidTag>(1234);

    void* mark = reinterpret_cast<void*>(0x1);



    void SetUp() override {

        EXPECT_CALL(mockAttr, my_NSS_CMSAttribute_GetType()).WillRepeatedly(::testing::Return(testOidTag));

        EXPECT_CALL(mockPool, PORT_ArenaMark()).WillOnce(::testing::Return(mark));

    }

};



// Normal operation

TEST_F(NSSCryptoSignBackendTest_1791, AddAttribute_Success_1791) {

    EXPECT_CALL(mockArrayFinder, my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, testOidTag, PR_FALSE)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockArray, my_NSS_CMSArray_Add(poolp, ::testing::NotNull(), static_cast<void*>(attr))).WillOnce(::testing::Return(SECSuccess));

    EXPECT_CALL(mockPool, PORT_ArenaUnmark(poolp, mark));



    SECStatus result = my_NSS_CMSAttributeArray_AddAttr(poolp, attrs, attr);

    EXPECT_EQ(result, SECSuccess);

}



// Boundary conditions

TEST_F(NSSCryptoSignBackendTest_1791, AddAttribute_NoMark_1791) {

    EXPECT_CALL(mockPool, PORT_ArenaMark()).WillOnce(::testing::Return(nullptr));

    SECStatus result = my_NSS_CMSAttributeArray_AddAttr(poolp, attrs, attr);

    EXPECT_EQ(result, SECFailure);

}



// Exceptional or error cases

TEST_F(NSSCryptoSignBackendTest_1791, AddAttribute_AttrAlreadyExists_1791) {

    EXPECT_CALL(mockArrayFinder, my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, testOidTag, PR_FALSE)).WillOnce(::testing::Return(&mockAttr));

    SECStatus result = my_NSS_CMSAttributeArray_AddAttr(poolp, attrs, attr);

    EXPECT_EQ(result, SECFailure);

}



TEST_F(NSSCryptoSignBackendTest_1791, AddAttribute_ArrayAddFailure_1791) {

    EXPECT_CALL(mockArrayFinder, my_NSS_CMSAttributeArray_FindAttrByOidTag(attrs, testOidTag, PR_FALSE)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockArray, my_NSS_CMSArray_Add(poolp, ::testing::NotNull(), static_cast<void*>(attr))).WillOnce(::testing::Return(SECFailure));

    SECStatus result = my_NSS_CMSAttributeArray_AddAttr(poolp, attrs, attr);

    EXPECT_EQ(result, SECFailure);

}
