#include <gtest/gtest.h>

#include "WXMPUtils.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1930 : public ::testing::Test {

protected:

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr arrayName = "exampleArray";

    XMP_Index itemIndex = 1;

    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;

};



TEST_F(WXMPUtilsTest_1930, NormalOperation_1930) {

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1930, EmptySchemaNamespaceURI_1930) {

    schemaNS = "";

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1930, NullSchemaNamespaceURI_1930) {

    schemaNS = nullptr;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1930, EmptyArrayName_1930) {

    arrayName = "";

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1930, NullArrayName_1930) {

    arrayName = nullptr;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1930, NullFullPathPointer_1930) {

    fullPath = nullptr;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1930, NullPathSizePointer_1930) {

    pathSize = 0;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1930, NullWResultPointer_1930) {

    WXMP_Result* wResultPtr = nullptr;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, wResultPtr);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

}



TEST_F(WXMPUtilsTest_1930, BoundaryCondition_ItemIndexZero_1930) {

    itemIndex = 0;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1930, BoundaryCondition_ItemIndexLarge_1930) {

    itemIndex = 99999;

    WXMPUtils_ComposeArrayItemPath_1(schemaNS, arrayName, itemIndex, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_GT(pathSize, 0);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}
