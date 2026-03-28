#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_GetObjectName_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr * namePtr,
    XMP_StringLen * nameLen,
    WXMP_Result * wResult);

// Helper to cast XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaGetObjectNameTest_2041 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        meta = nullptr;
        XMPMeta::Terminate();
    }

    XMPMeta* meta = nullptr;
};

// Test: Getting the default object name (empty by default)
TEST_F(WXMPMetaGetObjectNameTest_2041, DefaultObjectNameIsEmpty_2041) {
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(namePtr, nullptr);
    EXPECT_EQ(nameLen, 0u);
    EXPECT_STREQ(namePtr, "");
}

// Test: Getting object name after setting it
TEST_F(WXMPMetaGetObjectNameTest_2041, ReturnsSetObjectName_2041) {
    meta->SetObjectName("TestObjectName");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(namePtr, nullptr);
    EXPECT_STREQ(namePtr, "TestObjectName");
    EXPECT_EQ(nameLen, static_cast<XMP_StringLen>(std::strlen("TestObjectName")));
}

// Test: Passing null namePtr pointer (should use void default, no crash)
TEST_F(WXMPMetaGetObjectNameTest_2041, NullNamePtrDoesNotCrash_2041) {
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), nullptr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Passing null nameLen pointer (should use void default, no crash)
TEST_F(WXMPMetaGetObjectNameTest_2041, NullNameLenDoesNotCrash_2041) {
    XMP_StringPtr namePtr = nullptr;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(namePtr, nullptr);
}

// Test: Both namePtr and nameLen are null
TEST_F(WXMPMetaGetObjectNameTest_2041, BothNullPointersDoNotCrash_2041) {
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting name, then getting, then changing name and getting again
TEST_F(WXMPMetaGetObjectNameTest_2041, NameUpdatesAfterChange_2041) {
    meta->SetObjectName("FirstName");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_STREQ(namePtr, "FirstName");

    meta->SetObjectName("SecondName");

    namePtr = nullptr;
    nameLen = 0;
    WXMP_Result wResult2;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_STREQ(namePtr, "SecondName");
    EXPECT_EQ(nameLen, static_cast<XMP_StringLen>(std::strlen("SecondName")));
}

// Test: Setting an empty string as object name
TEST_F(WXMPMetaGetObjectNameTest_2041, EmptyObjectName_2041) {
    meta->SetObjectName("");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(namePtr, nullptr);
    EXPECT_STREQ(namePtr, "");
    EXPECT_EQ(nameLen, 0u);
}

// Test: Setting a long object name
TEST_F(WXMPMetaGetObjectNameTest_2041, LongObjectName_2041) {
    std::string longName(1000, 'A');
    meta->SetObjectName(longName.c_str());

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(namePtr, nullptr);
    EXPECT_STREQ(namePtr, longName.c_str());
    EXPECT_EQ(nameLen, static_cast<XMP_StringLen>(longName.size()));
}

// Test: Object name with special characters
TEST_F(WXMPMetaGetObjectNameTest_2041, SpecialCharactersInName_2041) {
    const char* specialName = "Test Name With Spaces & Symbols!@#$%";
    meta->SetObjectName(specialName);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    WXMP_Result wResult;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_STREQ(namePtr, specialName);
    EXPECT_EQ(nameLen, static_cast<XMP_StringLen>(std::strlen(specialName)));
}

// Test: WXMP_Result is properly initialized and no error after normal call
TEST_F(WXMPMetaGetObjectNameTest_2041, ResultInitializedCorrectly_2041) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;

    WXMPMeta_GetObjectName_1(MetaToRef(meta), &namePtr, &nameLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}
