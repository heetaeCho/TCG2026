#include <gtest/gtest.h>

#include "WXMPUtils.hpp"



TEST(WXMPUtils_ComposeQualifierPath_1932, NormalOperation_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult);



    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullSchemaNS_1932) {

    const char* schemaNS = nullptr;

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, EmptySchemaNS_1932) {

    const char* schemaNS = "";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullPropName_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, EmptyPropName_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullQualNS_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = nullptr;

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, EmptyQualNS_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullQualName_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = nullptr;



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, EmptyQualName_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullFullPath_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, nullptr, &pathSize, &wResult);



    EXPECT_STREQ(fullPath, "");

}



TEST(WXMPUtils_ComposeQualifierPath_1932, NullPathSize_1932) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "property";

    const char* qualNS = "http://example.com/qualifier";

    const char* qualName = "qualifier";



    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, nullptr, &wResult);



    EXPECT_GT(pathSize, 0);

}
