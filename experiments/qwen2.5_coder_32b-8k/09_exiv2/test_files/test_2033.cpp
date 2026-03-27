#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "XMP_Const.h"



// Mock XMPMeta to verify interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD5(SetProperty_Float, void(XMP_StringPtr schemaNS, XMP_StringPtr propName, double propValue, XMP_OptionBits options));

};



TEST_F(WXMPMetaTest_2033, SetPropertyFloat_NormalOperation_2033) {

    WXMP_Result result;

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, SetProperty_Float("http://example.com/schema", "propertyName", 123.456, 0)).Times(1);

    WXMPMeta_SetProperty_Float_1(xmpRef, "http://example.com/schema", "propertyName", 123.456, 0, &result);



    EXPECT_EQ(result.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2033, SetPropertyFloat_EmptySchemaNamespaceURI_2033) {

    WXMP_Result result;

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, SetProperty_Float).Times(0);

    WXMPMeta_SetProperty_Float_1(xmpRef, "", "propertyName", 123.456, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2033, SetPropertyFloat_NullSchemaNamespaceURI_2033) {

    WXMP_Result result;

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, SetProperty_Float).Times(0);

    WXMPMeta_SetProperty_Float_1(xmpRef, nullptr, "propertyName", 123.456, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2033, SetPropertyFloat_EmptyPropertyName_2033) {

    WXMP_Result result;

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, SetProperty_Float).Times(0);

    WXMPMeta_SetProperty_Float_1(xmpRef, "http://example.com/schema", "", 123.456, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty property name");

}



TEST_F(WXMPMetaTest_2033, SetPropertyFloat_NullPropertyName_2033) {

    WXMP_Result result;

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, SetProperty_Float).Times(0);

    WXMPMeta_SetProperty_Float_1(xmpRef, "http://example.com/schema", nullptr, 123.456, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty property name");

}
