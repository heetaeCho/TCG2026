#include <gtest/gtest.h>

#include "WXMPUtils.hpp"

#include "client-glue/WXMP_Common.hpp"



class WXMPUtilsTest_1931 : public ::testing::Test {

protected:

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "StructName";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "FieldName";

    XMP_StringPtr fullPath;

    XMP_StringLen pathSize;

    WXMP_Result wResult;



    void SetUp() override {

        fullPath = nullptr;

        pathSize = 0;

    }



    void TearDown() override {

        if (fullPath != &voidStringPtr && fullPath) {

            delete[] fullPath;

        }

    }

};



TEST_F(WXMPUtilsTest_1931, ValidInput_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, fieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(fullPath, "http://example.com/schema/StructName/http://example.com/field=FieldName");

    EXPECT_EQ(pathSize, strlen("http://example.com/schema/StructName/http://example.com/field=FieldName"));

}



TEST_F(WXMPUtilsTest_1931, SchemaNSNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(nullptr, structName, fieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1931, SchemaNSEmpty_1931) {

    XMP_StringPtr emptySchemaNS = "";

    WXMPUtils_ComposeStructFieldPath_1(emptySchemaNS, structName, fieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1931, StructNameNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, nullptr, fieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty struct name");

}



TEST_F(WXMPUtilsTest_1931, StructNameEmpty_1931) {

    XMP_StringPtr emptyStructName = "";

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, emptyStructName, fieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty struct name");

}



TEST_F(WXMPUtilsTest_1931, FieldNSNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, nullptr, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPUtilsTest_1931, FieldNSEmpty_1931) {

    XMP_StringPtr emptyFieldNS = "";

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, emptyFieldNS, fieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPUtilsTest_1931, FieldNameNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, fieldNS, nullptr, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty field name");

}



TEST_F(WXMPUtilsTest_1931, FieldNameEmpty_1931) {

    XMP_StringPtr emptyFieldName = "";

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, fieldNS, emptyFieldName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, "Empty field name");

}



TEST_F(WXMPUtilsTest_1931, FullPathNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, fieldNS, fieldName, nullptr, &pathSize, &wResult);

    EXPECT_STREQ(fullPath, "");

}



TEST_F(WXMPUtilsTest_1931, PathSizeNull_1931) {

    WXMPUtils_ComposeStructFieldPath_1(schemaNS, structName, fieldNS, fieldName, &fullPath, nullptr, &wResult);

    EXPECT_EQ(pathSize, strlen("http://example.com/schema/StructName/http://example.com/field=FieldName"));

}
