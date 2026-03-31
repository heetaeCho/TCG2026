#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern void WXMPUtils_ComposeLangSelector_1(
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr langName,
    XMP_StringPtr * fullPath,
    XMP_StringLen * pathSize,
    WXMP_Result * wResult
);

class WXMPUtilsComposeLangSelectorTest_1933 : public ::testing::Test {
protected:
    WXMP_Result wResult;

    void SetUp() override {
        wResult = WXMP_Result();
    }
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, NullSchemaNS_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1(nullptr, "arrayName", "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schemaNS should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptySchemaNS_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("", "arrayName", "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null arrayName should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, NullArrayName_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", nullptr, "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty arrayName should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptyArrayName_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "", "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null langName should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, NullLangName_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "arrayName", nullptr, &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty langName should produce an error
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptyLangName_ReturnsError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "arrayName", "", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid inputs should succeed (no error)
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, ValidInputs_NoError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid inputs with non-null fullPath and pathSize should produce a non-empty result
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, ValidInputs_ProducesNonEmptyPath_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// Test: Null fullPath pointer should still work (uses internal void pointer)
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, NullFullPathPointer_NoError_1933) {
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", nullptr, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null pathSize pointer should still work (uses internal void length)
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, NullPathSizePointer_NoError_1933) {
    XMP_StringPtr fullPath = nullptr;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", &fullPath, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Both fullPath and pathSize null should still work
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, BothOutputPointersNull_NoError_1933) {
    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid inputs with different language name
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, ValidInputsDifferentLang_NoError_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "x-default", &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}

// Test: Error message content for empty schema
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptySchemaNS_ErrorMessageContent_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("", "arrayName", "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        // The error message should contain something meaningful
        EXPECT_GT(std::strlen(wResult.errMessage), 0u);
    }
}

// Test: Error message content for empty array name
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptyArrayName_ErrorMessageContent_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "", "en", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        EXPECT_GT(std::strlen(wResult.errMessage), 0u);
    }
}

// Test: Error message content for empty lang name
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, EmptyLangName_ErrorMessageContent_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "arrayName", "", &fullPath, &pathSize, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
    if (wResult.errMessage != nullptr) {
        EXPECT_GT(std::strlen(wResult.errMessage), 0u);
    }
}

// Test: pathSize matches strlen of fullPath on valid input
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, PathSizeMatchesStringLength_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://ns.adobe.com/xap/1.0/", "xap:Description", "en", &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr && fullPath != nullptr) {
        EXPECT_EQ(pathSize, static_cast<XMP_StringLen>(std::strlen(fullPath)));
    }
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, ResultInitializedProperly_1933) {
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Valid call with dc namespace
TEST_F(WXMPUtilsComposeLangSelectorTest_1933, ValidInputsDCNamespace_1933) {
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMPUtils_ComposeLangSelector_1("http://purl.org/dc/elements/1.1/", "dc:title", "fr", &fullPath, &pathSize, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(fullPath, nullptr);
        EXPECT_GT(pathSize, 0u);
    }
}
