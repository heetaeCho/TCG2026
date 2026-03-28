#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp"



class WXMPMeta_SetQualifier_Test : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        // Assuming there's a way to create an XMPMeta object and get its reference

        // For the sake of this test, we'll assume WtoXMPMeta_Ptr is used to convert from ref to pointer

        XMPMeta* meta = new XMPMeta();

        xmpRef = XMPMetaPtrToWXMP_Meta(meta);

    }



    void TearDown() override {

        // Clean up the XMPMeta object

        XMPMeta* meta = WtoXMPMeta_Ptr(xmpRef);

        delete meta;

    }

};



TEST_F(WXMPMeta_SetQualifier_Test, ValidInput_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, nullptr); // No error message expected

}



TEST_F(WXMPMeta_SetQualifier_Test, EmptySchemaNamespaceURI_2014) {

    const char* schemaNS = "";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetQualifier_Test, NullSchemaNamespaceURI_2014) {

    const char* schemaNS = nullptr;

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetQualifier_Test, EmptyPropertyName_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty property name");

}



TEST_F(WXMPMeta_SetQualifier_Test, NullPropertyName_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty property name");

}



TEST_F(WXMPMeta_SetQualifier_Test, EmptyQualifierNamespaceURI_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "";

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty qualifier namespace URI");

}



TEST_F(WXMPMeta_SetQualifier_Test, NullQualifierNamespaceURI_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = nullptr;

    const char* qualName = "qualifier";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty qualifier namespace URI");

}



TEST_F(WXMPMeta_SetQualifier_Test, EmptyQualifierName_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "";

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty qualifier name");

}



TEST_F(WXMPMeta_SetQualifier_Test, NullQualifierName_2014) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = nullptr;

    const char* qualValue = "value";

    XMP_OptionBits options = 0;



    WXMPMeta_SetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult);

    

    EXPECT_STREQ(wResult.errMessage, "Empty qualifier name");

}
