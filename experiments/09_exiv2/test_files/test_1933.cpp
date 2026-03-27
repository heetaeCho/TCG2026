#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "WXMPUtils.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1933 : public ::testing::Test {

protected:

    XMP_StringPtr schemaNS;

    XMP_StringPtr arrayName;

    XMP_StringPtr langName;

    XMP_StringPtr fullPath = nullptr;

    XMP_StringLen pathSize = 0;

    WXMP_Result wResult;



    void SetUp() override {

        schemaNS = "http://example.com/schema";

        arrayName = "exampleArray";

        langName = "en";

        fullPath = nullptr;

        pathSize = 0;

    }



    void TearDown() override {

        if (fullPath != &voidStringPtr) {

            delete[] fullPath;

        }

    }

};



TEST_F(WXMPUtilsTest_1933, NormalOperation_1933) {

    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, nullptr);

    EXPECT_EQ(pathSize, strlen(fullPath));

}



TEST_F(WXMPUtilsTest_1933, SchemaNamespaceEmptyString_1933) {

    schemaNS = "";

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, SchemaNamespaceNullPointer_1933) {

    schemaNS = nullptr;

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, ArrayNameEmptyString_1933) {

    arrayName = "";

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, ArrayNameNullPointer_1933) {

    arrayName = nullptr;

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, LangNameEmptyString_1933) {

    langName = "";

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, LangNameNullPointer_1933) {

    langName = nullptr;

    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1933, FullPathNullPointer_1933) {

    fullPath = nullptr;

    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    EXPECT_NE(fullPath, &voidStringPtr);

}



TEST_F(WXMPUtilsTest_1933, PathSizeNullPointer_1933) {

    pathSize = 0;

    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    EXPECT_EQ(pathSize, strlen(fullPath));

}
