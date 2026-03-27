#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



extern "C" {

    void WXMPMeta_AppendArrayItem_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr arrayName, XMP_OptionBits arrayOptions, XMP_StringPtr itemValue, XMP_OptionBits options, WXMP_Result * wResult);

}



class WXMPMetaTest_2012 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpRef = new XMPMeta();

        result.errMessage = nullptr;

    }



    void TearDown() override {

        delete xmpRef;

        if (result.errMessage) {

            free(const_cast<char*>(result.errMessage));

        }

    }



    XMPMeta* xmpRef;

    WXMP_Result result;

};



TEST_F(WXMPMetaTest_2012, AppendArrayItem_Successful_2012) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "ExampleArray";

    const char* itemValue = "Item1";



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_EQ(result.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2012, AppendArrayItem_EmptySchemaNamespace_2012) {

    const char* schemaNS = "";

    const char* arrayName = "ExampleArray";

    const char* itemValue = "Item1";



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2012, AppendArrayItem_EmptyArrayName_2012) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "";

    const char* itemValue = "Item1";



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest_2012, AppendArrayItem_NullSchemaNamespace_2012) {

    const char* schemaNS = nullptr;

    const char* arrayName = "ExampleArray";

    const char* itemValue = "Item1";



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2012, AppendArrayItem_NullArrayName_2012) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = nullptr;

    const char* itemValue = "Item1";



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest_2012, AppendArrayItem_NullItemValue_2012) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "ExampleArray";

    const char* itemValue = nullptr;



    WXMPMeta_AppendArrayItem_1(xmpRef, schemaNS, arrayName, 0, itemValue, 0, &result);



    EXPECT_EQ(result.errMessage, nullptr);

}
