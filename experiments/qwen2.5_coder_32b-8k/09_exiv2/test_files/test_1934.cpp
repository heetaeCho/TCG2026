#include <gtest/gtest.h>

#include "WXMPUtils.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1934 : public ::testing::Test {

protected:

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr arrayName = "array";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "field";

    XMP_StringPtr fieldValue = "value";

    XMP_StringPtr fullPath;

    XMP_StringLen pathSize;

    WXMP_Result wResult;



    void SetUp() override {

        fullPath = nullptr;

        pathSize = 0;

        wResult.errMessage = nullptr;

    }



    void TearDown() override {

        if (fullPath != &voidStringPtr && fullPath) {

            delete[] fullPath;

        }

    }

};



TEST_F(WXMPUtilsTest_1934, NormalOperation_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(fullPath, "http://example.com/schema/array[?qualifier=http://example.com/field'field']/value");

    EXPECT_EQ(pathSize, strlen("http://example.com/schema/array[?qualifier=http://example.com/field'field']/value"));

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1934, EmptySchemaNamespaceURI_1934) {

    WXMPUtils_ComposeFieldSelector_1(nullptr, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1934, EmptyArrayName_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, nullptr, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1934, EmptyFieldNamespaceURI_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, nullptr, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPUtilsTest_1934, EmptyFieldName_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, nullptr, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty field name");

}



TEST_F(WXMPUtilsTest_1934, NullFullPathPointer_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, nullptr, &pathSize, &wResult);

    EXPECT_STREQ(fullPath, voidStringPtr);

}



TEST_F(WXMPUtilsTest_1934, NullPathSizePointer_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, nullptr, &wResult);

    EXPECT_EQ(pathSize, voidStringLen);

}



TEST_F(WXMPUtilsTest_1934, NullWResultPointer_1934) {

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, nullptr);

    EXPECT_STREQ(fullPath, "http://example.com/schema/array[?qualifier=http://example.com/field'field']/value");

    EXPECT_EQ(pathSize, strlen("http://example.com/schema/array[?qualifier=http://example.com/field'field']/value"));

}



TEST_F(WXMPUtilsTest_1934, EmptyFieldValue_1934) {

    fieldValue = "";

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(fullPath, "http://example.com/schema/array[?qualifier=http://example.com/field'field']");

}



TEST_F(WXMPUtilsTest_1934, SchemaNamespaceURISpace_1934) {

    schemaNS = " ";

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1934, ArrayNameSpace_1934) {

    arrayName = " ";

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1934, FieldNamespaceURISpace_1934) {

    fieldNS = " ";

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPUtilsTest_1934, FieldNameSpace_1934) {

    fieldName = " ";

    WXMPUtils_ComposeFieldSelector_1(schemaNS, arrayName, fieldNS, fieldName, fieldValue, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty field name");

}
