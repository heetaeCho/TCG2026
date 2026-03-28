#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetLocalizedText_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr genericLang,
    XMP_StringPtr specificLang,
    XMP_StringPtr itemValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPMetaSetLocalizedTextTest_2024 : public ::testing::Test {
protected:
    XMPMeta* meta;
    WXMP_Result wResult;

    void SetUp() override {
        SXMPMeta::Initialize();
        meta = new XMPMeta();
        memset(&wResult, 0, sizeof(wResult));
    }

    void TearDown() override {
        delete meta;
        SXMPMeta::Terminate();
    }

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, NullSchemaNS_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), nullptr, "arrayName", "en", "en-US", "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, EmptySchemaNS_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "", "arrayName", "en", "en-US", "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, NullArrayName_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://ns.adobe.com/xap/1.0/", nullptr, "en", "en-US", "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, EmptyArrayName_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://ns.adobe.com/xap/1.0/", "", "en", "en-US", "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null specificLang should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, NullSpecificLang_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://ns.adobe.com/xap/1.0/", "dc:title", "en", nullptr, "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty specificLang should produce an error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, EmptySpecificLang_SetsError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://ns.adobe.com/xap/1.0/", "dc:title", "en", "", "value", 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null genericLang should not produce an error (defaults to "")
TEST_F(WXMPMetaSetLocalizedTextTest_2024, NullGenericLang_NoError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", nullptr, "en-US", "Test Title", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null itemValue should not produce an error (defaults to "")
TEST_F(WXMPMetaSetLocalizedTextTest_2024, NullItemValue_NoError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", nullptr, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid parameters should succeed without error
TEST_F(WXMPMetaSetLocalizedTextTest_2024, ValidParams_NoError_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "Hello World", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid call sets value that can be retrieved
TEST_F(WXMPMetaSetLocalizedTextTest_2024, ValidCall_ValueRetrievable_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "Test Value", 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetLocalizedText(
        "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US",
        &actualLang, &langSize, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Test Value");
}

// Test: Setting localized text with empty genericLang but valid specificLang
TEST_F(WXMPMetaSetLocalizedTextTest_2024, EmptyGenericLang_ValidSpecificLang_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "", "fr-FR", "Bonjour", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Multiple localized text values for different languages
TEST_F(WXMPMetaSetLocalizedTextTest_2024, MultipleLangs_BothRetrievable_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "Hello", 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMP_Result wResult2;
    memset(&wResult2, 0, sizeof(wResult2));
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "de", "de-DE", "Hallo", 0, &wResult2);
    ASSERT_EQ(wResult2.errMessage, nullptr);

    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;

    bool found = meta->GetLocalizedText(
        "http://purl.org/dc/elements/1.1/", "dc:title", "de", "de-DE",
        &actualLang, &langSize, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Hallo");
}

// Test: Overwriting an existing localized text value
TEST_F(WXMPMetaSetLocalizedTextTest_2024, OverwriteExistingValue_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "Original", 0, &wResult);
    ASSERT_EQ(wResult.errMessage, nullptr);

    WXMP_Result wResult2;
    memset(&wResult2, 0, sizeof(wResult2));
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "Updated", 0, &wResult2);
    ASSERT_EQ(wResult2.errMessage, nullptr);

    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;

    bool found = meta->GetLocalizedText(
        "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US",
        &actualLang, &langSize, &itemValue, &valueSize, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Updated");
}

// Test: Setting with empty item value string
TEST_F(WXMPMetaSetLocalizedTextTest_2024, EmptyItemValue_Succeeds_2024) {
    WXMPMeta_SetLocalizedText_1(
        GetRef(), "http://purl.org/dc/elements/1.1/", "dc:title", "en", "en-US", "", 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}
