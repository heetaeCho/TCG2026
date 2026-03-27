#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMPMeta.hpp"



extern "C" {

    void WXMPMeta_SetProperty_Int64_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_Int64 propValue, XMP_OptionBits options, WXMP_Result * wResult);

}



class WXMPMeta_SetProperty_Int64_Test : public ::testing::Test {

protected:

    XMPMeta* meta;

    XMPMetaRef xmpRef;

    WXMP_Result result;



    void SetUp() override {

        meta = new XMPMeta();

        xmpRef = reinterpret_cast<XMPMetaRef>(meta);

    }



    void TearDown() override {

        delete meta;

    }

};



TEST_F(WXMPMeta_SetProperty_Int64_Test_2032, NormalOperation_2032) {

    WXMPMeta_SetProperty_Int64_1(xmpRef, "http://example.com/schema", "property", 12345, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

}



TEST_F(WXMPMeta_SetProperty_Int64_Test_2032, EmptySchemaNamespaceURI_2032) {

    WXMPMeta_SetProperty_Int64_1(xmpRef, "", "property", 12345, 0, &result);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetProperty_Int64_Test_2032, NullSchemaNamespaceURI_2032) {

    WXMPMeta_SetProperty_Int64_1(xmpRef, nullptr, "property", 12345, 0, &result);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetProperty_Int64_Test_2032, EmptyPropertyName_2032) {

    WXMPMeta_SetProperty_Int64_1(xmpRef, "http://example.com/schema", "", 12345, 0, &result);

    EXPECT_STREQ(result.errMessage, "Empty property name");

}



TEST_F(WXMPMeta_SetProperty_Int64_Test_2032, NullPropertyName_2032) {

    WXMPMeta_SetProperty_Int64_1(xmpRef, "http://example.com/schema", nullptr, 12345, 0, &result);

    EXPECT_STREQ(result.errMessage, "Empty property name");

}
