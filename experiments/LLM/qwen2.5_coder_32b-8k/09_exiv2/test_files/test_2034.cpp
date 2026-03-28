#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Mock class for XMPMeta to verify interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD(void, SetProperty_Date, (XMP_StringPtr schemaNS, XMP_StringPtr propName, const XMP_DateTime & propValue, XMP_OptionBits options), (override));

};



// Test fixture for WXMPMeta_SetProperty_Date_1

class WXMPMeta_SetProperty_Date_Test_2034 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpRef = reinterpret_cast<XMPMetaRef>(new MockXMPMeta());

        wResult = new WXMP_Result();

    }



    void TearDown() override {

        delete wResult;

        delete reinterpret_cast<MockXMPMeta*>(xmpRef);

    }



    XMPMetaRef xmpRef;

    WXMP_Result* wResult;

};



// Test normal operation

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, SetValidDate_2034) {

    MockXMPMeta* mockMeta = reinterpret_cast<MockXMPMeta*>(xmpRef);

    XMP_DateTime dateTime = {2023, 10, 5, 14, 30, 0, 0, 0, 0, 0};

    EXPECT_CALL(*mockMeta, SetProperty_Date("http://example.com/schema", "dateProp", testing::Ref(dateTime), XMP_OptionBits{}));



    WXMPMeta_SetProperty_Date_1(xmpRef, "http://example.com/schema", "dateProp", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_EQ(wResult->errMessage, nullptr);

}



// Test boundary condition with minimum date

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, SetMinDate_2034) {

    MockXMPMeta* mockMeta = reinterpret_cast<MockXMPMeta*>(xmpRef);

    XMP_DateTime dateTime = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};

    EXPECT_CALL(*mockMeta, SetProperty_Date("http://example.com/schema", "dateProp", testing::Ref(dateTime), XMP_OptionBits{}));



    WXMPMeta_SetProperty_Date_1(xmpRef, "http://example.com/schema", "dateProp", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_EQ(wResult->errMessage, nullptr);

}



// Test boundary condition with maximum date

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, SetMaxDate_2034) {

    MockXMPMeta* mockMeta = reinterpret_cast<MockXMPMeta*>(xmpRef);

    XMP_DateTime dateTime = {9999, 12, 31, 23, 59, 59, 0, 0, 0, 999999999};

    EXPECT_CALL(*mockMeta, SetProperty_Date("http://example.com/schema", "dateProp", testing::Ref(dateTime), XMP_OptionBits{}));



    WXMPMeta_SetProperty_Date_1(xmpRef, "http://example.com/schema", "dateProp", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_EQ(wResult->errMessage, nullptr);

}



// Test empty schema namespace URI

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, EmptySchemaNamespaceURI_2034) {

    XMP_DateTime dateTime = {2023, 10, 5, 14, 30, 0, 0, 0, 0, 0};



    WXMPMeta_SetProperty_Date_1(xmpRef, "", "dateProp", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty schema namespace URI");

}



// Test null schema namespace URI

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, NullSchemaNamespaceURI_2034) {

    XMP_DateTime dateTime = {2023, 10, 5, 14, 30, 0, 0, 0, 0, 0};



    WXMPMeta_SetProperty_Date_1(xmpRef, nullptr, "dateProp", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty schema namespace URI");

}



// Test empty property name

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, EmptyPropertyName_2034) {

    XMP_DateTime dateTime = {2023, 10, 5, 14, 30, 0, 0, 0, 0, 0};



    WXMPMeta_SetProperty_Date_1(xmpRef, "http://example.com/schema", "", dateTime, XMP_OptionBits{}, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty property name");

}



// Test null property name

TEST_F(WXMPMeta_SetProperty_Date_Test_2034, NullPropertyName_2034) {

    XMP_DateTime dateTime = {2023, 10, 5, 14, 30, 0, 0, 0, 0, 0};



    WXMPMeta_SetProperty_Date_1(xmpRef, "http://example.com/schema", nullptr, dateTime, XMP_OptionBits{}, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty property name");

}
