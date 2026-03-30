#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "XMP_Const.h"



// Assuming WXMPMetaRef and XMPMeta are already defined and accessible in the test environment



class WXMPMetaTest_2030 : public ::testing::Test {

protected:

    WXMPMetaTest_2030() {

        // Setup code if needed

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

        wResult = new WXMP_Result();

    }



    ~WXMPMetaTest_2030() override {

        // Cleanup code if needed

        delete wResult;

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }



    XMPMetaRef xmpRef;

    WXMP_Result* wResult;

};



TEST_F(WXMPMetaTest_2030, NormalOperation_2030) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property1";

    bool propValue = true;

    XMP_OptionBits options = 0;



    WXMPMeta_SetProperty_Bool_1(xmpRef, schemaNS, propName, propValue, options, wResult);

    EXPECT_STREQ(wResult->errMessage, nullptr); // Assuming no error message on success

}



TEST_F(WXMPMetaTest_2030, EmptySchemaNamespaceURI_2030) {

    const char* schemaNS = "";

    const char* propName = "property1";

    bool propValue = true;

    XMP_OptionBits options = 0;



    WXMPMeta_SetProperty_Bool_1(xmpRef, schemaNS, propName, propValue, options, wResult);

    EXPECT_STREQ(wResult->errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2030, NullSchemaNamespaceURI_2030) {

    const char* schemaNS = nullptr;

    const char* propName = "property1";

    bool propValue = true;

    XMP_OptionBits options = 0;



    WXMPMeta_SetProperty_Bool_1(xmpRef, schemaNS, propName, propValue, options, wResult);

    EXPECT_STREQ(wResult->errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2030, EmptyPropertyName_2030) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    bool propValue = true;

    XMP_OptionBits options = 0;



    WXMPMeta_SetProperty_Bool_1(xmpRef, schemaNS, propName, propValue, options, wResult);

    EXPECT_STREQ(wResult->errMessage, "Empty property name");

}



TEST_F(WXMPMetaTest_2030, NullPropertyName_2030) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    bool propValue = true;

    XMP_OptionBits options = 0;



    WXMPMeta_SetProperty_Bool_1(xmpRef, schemaNS, propName, propValue, options, wResult);

    EXPECT_STREQ(wResult->errMessage, "Empty property name");

}
