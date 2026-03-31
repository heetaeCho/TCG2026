#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_GetLocalizedText_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr genericLang,
    XMP_StringPtr specificLang,
    XMP_StringPtr * actualLang,
    XMP_StringLen * langSize,
    XMP_StringPtr * itemValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetLocalizedTextTest_2023 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = reinterpret_cast<XMPMetaRef>(meta);
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, NullSchemaNS_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, nullptr, "arrayName", "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, EmptySchemaNS_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "", "arrayName", "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, NullArrayName_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://ns.adobe.com/xap/1.0/", nullptr, "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, EmptyArrayName_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null specificLang should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, NullSpecificLang_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "dc:title", "en", nullptr,
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty specificLang should produce an error
TEST_F(WXMPMetaGetLocalizedTextTest_2023, EmptySpecificLang_ProducesError_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "dc:title", "en", "",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null genericLang should be accepted (defaults to "")
TEST_F(WXMPMetaGetLocalizedTextTest_2023, NullGenericLang_IsAccepted_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://purl.org/dc/elements/1.1/", "title", nullptr, "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    // Should not produce an error from the null genericLang check
    // (may still fail for other reasons like property not found, but errMessage should be null if no exception)
    // The function should complete; if no property exists, int32Result should be 0 (not found)
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Null output parameter pointers should be accepted
TEST_F(WXMPMetaGetLocalizedTextTest_2023, NullOutputParams_AreAccepted_2023) {
    WXMP_Result wResult;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://purl.org/dc/elements/1.1/", "title", "en", "en-US",
                                 nullptr, nullptr, nullptr, nullptr, nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Property not found returns false (0)
TEST_F(WXMPMetaGetLocalizedTextTest_2023, PropertyNotFound_ReturnsFalse_2023) {
    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://purl.org/dc/elements/1.1/", "title", "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Set localized text then get it back successfully
TEST_F(WXMPMetaGetLocalizedTextTest_2023, SetThenGet_ReturnsTrue_2023) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "title";

    // Set a localized text first
    meta->SetLocalizedText(schemaNS, arrayName, "en", "en-US", "Hello World", 0);

    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    EXPECT_NE(itemValue, nullptr);
    EXPECT_STREQ(itemValue, "Hello World");
    EXPECT_GT(valueSize, static_cast<XMP_StringLen>(0));
}

// Test: Get with different specific language that doesn't exist
TEST_F(WXMPMetaGetLocalizedTextTest_2023, DifferentLang_NotFound_2023) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "title";

    meta->SetLocalizedText(schemaNS, arrayName, "en", "en-US", "Hello World", 0);

    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    // Request French - may still find something due to language matching rules
    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, "fr", "fr-FR",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    // The result depends on XMP language matching algorithm; we just verify no error
}

// Test: Multiple localized texts, retrieve specific one
TEST_F(WXMPMetaGetLocalizedTextTest_2023, MultipleLanguages_RetrieveSpecific_2023) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "title";

    meta->SetLocalizedText(schemaNS, arrayName, "en", "en-US", "Hello", 0);
    meta->SetLocalizedText(schemaNS, arrayName, "fr", "fr-FR", "Bonjour", 0);

    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, "fr", "fr-FR",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    EXPECT_STREQ(itemValue, "Bonjour");
}

// Test: WXMP_Result is properly initialized and int32Result is set
TEST_F(WXMPMetaGetLocalizedTextTest_2023, ResultInitialization_2023) {
    WXMP_Result wResult;
    // WXMP_Result() initializes errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://purl.org/dc/elements/1.1/", "title", "", "en-US",
                                 nullptr, nullptr, nullptr, nullptr, nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: genericLang as empty string is valid
TEST_F(WXMPMetaGetLocalizedTextTest_2023, EmptyGenericLang_IsValid_2023) {
    WXMP_Result wResult;

    WXMPMeta_GetLocalizedText_1(xmpRef, "http://purl.org/dc/elements/1.1/", "title", "", "en-US",
                                 nullptr, nullptr, nullptr, nullptr, nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: actualLang is populated when text is found
TEST_F(WXMPMetaGetLocalizedTextTest_2023, ActualLangPopulated_WhenFound_2023) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "title";

    meta->SetLocalizedText(schemaNS, arrayName, "en", "en-US", "Test Value", 0);

    WXMP_Result wResult;
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetLocalizedText_1(xmpRef, schemaNS, arrayName, "en", "en-US",
                                 &actualLang, &langSize, &itemValue, &valueSize, &options, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, static_cast<XMP_Uns32>(0));
    EXPECT_NE(actualLang, nullptr);
    EXPECT_GT(langSize, static_cast<XMP_StringLen>(0));
}
