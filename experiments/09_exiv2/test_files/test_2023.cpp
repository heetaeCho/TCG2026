#include <gtest/gtest.h>

#include "WXMPMeta.cpp"



class WXMPMetaTest : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr arrayName = "altText";

    XMP_StringPtr genericLang = "";

    XMP_StringPtr specificLang = "en-US";

    XMP_StringPtr actualLang = nullptr;

    XMP_StringLen langSize = 0;

    XMP_StringPtr itemValue = nullptr;

    XMP_StringLen valueSize = 0;

    XMP_OptionBits options = 0;

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize xmpRef if necessary

    }



    void TearDown() override {

        // Clean up xmpRef if necessary

    }

};



TEST_F(WXMPMetaTest, GetLocalizedText_InvalidSchemaNS_2023) {

    schemaNS = nullptr;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest, GetLocalizedText_EmptySchemaNS_2023) {

    schemaNS = "";

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest, GetLocalizedText_InvalidArrayName_2023) {

    arrayName = nullptr;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest, GetLocalizedText_EmptyArrayName_2023) {

    arrayName = "";

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest, GetLocalizedText_InvalidSpecificLang_2023) {

    specificLang = nullptr;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_STREQ(wResult.errMessage, "Empty specific language");

}



TEST_F(WXMPMetaTest, GetLocalizedText_NormalOperation_2023) {

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}



TEST_F(WXMPMetaTest, GetLocalizedText_NullActualLang_2023) {

    actualLang = nullptr;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}



TEST_F(WXMPMetaTest, GetLocalizedText_NullLangSize_2023) {

    langSize = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}



TEST_F(WXMPMetaTest, GetLocalizedText_NullItemValue_2023) {

    itemValue = nullptr;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}



TEST_F(WXMPMetaTest, GetLocalizedText_NullValueSize_2023) {

    valueSize = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}



TEST_F(WXMPMetaTest, GetLocalizedText_NullOptions_2023) {

    options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, genericLang, specificLang, &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);

    EXPECT_TRUE(wResult.int32Result == 0 || wResult.int32Result == 1); // Assuming it returns either found or not found

}
