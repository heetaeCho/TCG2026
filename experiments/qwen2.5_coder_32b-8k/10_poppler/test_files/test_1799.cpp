#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking SECItem and NSSCMSMessage for testing purposes

struct SECItem {

    unsigned char *data;

    unsigned int len;

};



struct NSSCMSMessage {};



extern "C" {

    NSSCMSMessage* NSS_CMSMessage_CreateFromDER(SECItem *cms_item, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);

}



// Mocking the external function

class MockNSSCryptoSignBackend {

public:

    MOCK_STATIC_METHOD7(NSS_CMSMessage_CreateFromDER,

                        NSSCMSMessage* (SECItem*, void*, void*, void*, void*, void*, void*));

};



TEST_F(MockNSSCryptoSignBackendTest_1799, CMS_MessageCreate_SuccessfulCreation_1799) {

    SECItem secItem = { reinterpret_cast<unsigned char*>("dummy_data"), 10 };

    

    EXPECT_CALL(MockNSSCryptoSignBackend::get(), NSS_CMSMessage_CreateFromDER(&secItem, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr))

        .WillOnce(testing::Return(reinterpret_cast<NSSCMSMessage*>(0x1)));



    NSSCMSMessage* result = CMS_MessageCreate(&secItem);

    EXPECT_NE(result, nullptr);

}



TEST_F(MockNSSCryptoSignBackendTest_1799, CMS_MessageCreate_NullData_1799) {

    SECItem secItem = { nullptr, 10 };



    EXPECT_CALL(MockNSSCryptoSignBackend::get(), NSS_CMSMessage_CreateFromDER(&secItem, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr))

        .Times(0);



    NSSCMSMessage* result = CMS_MessageCreate(&secItem);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MockNSSCryptoSignBackendTest_1799, CMS_MessageCreate_ZeroLength_1799) {

    SECItem secItem = { reinterpret_cast<unsigned char*>("dummy_data"), 0 };



    EXPECT_CALL(MockNSSCryptoSignBackend::get(), NSS_CMSMessage_CreateFromDER(&secItem, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr))

        .WillOnce(testing::Return(reinterpret_cast<NSSCMSMessage*>(0x1)));



    NSSCMSMessage* result = CMS_MessageCreate(&secItem);

    EXPECT_NE(result, nullptr);

}



TEST_F(MockNSSCryptoSignBackendTest_1799, CMS_MessageCreate_NullSECItem_1799) {

    SECItem* secItem = nullptr;



    EXPECT_CALL(MockNSSCryptoSignBackend::get(), NSS_CMSMessage_CreateFromDER(secItem, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr))

        .Times(0);



    NSSCMSMessage* result = CMS_MessageCreate(secItem);

    EXPECT_EQ(result, nullptr);

}
