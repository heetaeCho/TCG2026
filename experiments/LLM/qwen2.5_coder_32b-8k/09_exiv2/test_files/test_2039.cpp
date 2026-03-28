#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



class WXMPMetaTest_2039 : public ::testing::Test {

protected:

    XMPMeta meta;

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    virtual void SetUp() {

        xmpRef = &meta;

    }



    virtual void TearDown() {

        // Clean up if necessary

    }

};



TEST_F(WXMPMetaTest_2039, CountArrayItems_NormalOperation_2039) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "array1";



    // Assuming some setup to have items in the array

    meta.AppendArrayItem(schemaNS, arrayName, 0, "item1", 0);

    meta.AppendArrayItem(schemaNS, arrayName, 0, "item2", 0);



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_EQ(wResult.int32Result, 2);

}



TEST_F(WXMPMetaTest_2039, CountArrayItems_EmptySchemaNamespace_2039) {

    const char* schemaNS = "";

    const char* arrayName = "array1";



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2039, CountArrayItems_EmptyArrayName_2039) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "";



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest_2039, CountArrayItems_NullSchemaNamespace_2039) {

    const char* schemaNS = nullptr;

    const char* arrayName = "array1";



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2039, CountArrayItems_NullArrayName_2039) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = nullptr;



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest_2039, CountArrayItems_NoItemsInArray_2039) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "array1";



    WXMPMeta_CountArrayItems_1(xmpRef, schemaNS, arrayName, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

}
