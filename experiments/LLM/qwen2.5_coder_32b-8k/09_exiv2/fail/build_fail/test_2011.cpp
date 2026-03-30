#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



class WXMPMeta_SetArrayItem_2011_Test : public ::testing::Test {

protected:

    XMPMeta* meta;

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    virtual void SetUp() {

        meta = new XMPMeta();

        xmpRef = reinterpret_cast<XMPMetaRef>(meta);

    }



    virtual void TearDown() {

        delete meta;

    }

};



TEST_F(WXMPMeta_SetArrayItem_2011_Test, NormalOperation_2011) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "ExampleArray";

    XMP_Index itemIndex = 1;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    ASSERT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_SetArrayItem_2011_Test, EmptySchemaNamespaceURI_2011) {

    const char* schemaNS = "";

    const char* arrayName = "ExampleArray";

    XMP_Index itemIndex = 1;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetArrayItem_2011_Test, NullSchemaNamespaceURI_2011) {

    const char* schemaNS = nullptr;

    const char* arrayName = "ExampleArray";

    XMP_Index itemIndex = 1;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetArrayItem_2011_Test, EmptyArrayName_2011) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "";

    XMP_Index itemIndex = 1;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMeta_SetArrayItem_2011_Test, NullArrayName_2011) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = nullptr;

    XMP_Index itemIndex = 1;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMeta_SetArrayItem_2011_Test, ZeroItemIndex_2011) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "ExampleArray";

    XMP_Index itemIndex = 0;

    const char* itemValue = "TestValue";

    XMP_OptionBits options = 0;



    WXMPMeta_SetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult);



    // Assuming that zero index is not valid and will throw an error or do nothing

    // Here we are checking if there's no error message indicating a successful operation

    ASSERT_STREQ(wResult.errMessage, nullptr);

}
