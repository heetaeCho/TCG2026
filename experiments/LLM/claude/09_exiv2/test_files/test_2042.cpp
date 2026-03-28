#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SetObjectName_1(XMPMetaRef xmpRef, XMP_StringPtr name, WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaSetObjectNameTest_2042 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
};

// Test: Setting a normal object name succeeds without error
TEST_F(WXMPMetaSetObjectNameTest_2042, SetNormalName_2042) {
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), "TestObjectName", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // Verify the name was set by reading it back
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, "TestObjectName");
    EXPECT_EQ(nameLen, std::strlen("TestObjectName"));
}

// Test: Setting a null name defaults to empty string
TEST_F(WXMPMetaSetObjectNameTest_2042, SetNullNameDefaultsToEmpty_2042) {
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, "");
    EXPECT_EQ(nameLen, 0u);
}

// Test: Setting an empty string name
TEST_F(WXMPMetaSetObjectNameTest_2042, SetEmptyName_2042) {
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), "", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, "");
    EXPECT_EQ(nameLen, 0u);
}

// Test: Overwriting an existing name with a new name
TEST_F(WXMPMetaSetObjectNameTest_2042, OverwriteExistingName_2042) {
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), "FirstName", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetObjectName_1(MetaToRef(meta), "SecondName", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, "SecondName");
    EXPECT_EQ(nameLen, std::strlen("SecondName"));
}

// Test: Setting a long name string
TEST_F(WXMPMetaSetObjectNameTest_2042, SetLongName_2042) {
    std::string longName(1000, 'A');
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), longName.c_str(), &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_EQ(std::string(namePtr, nameLen), longName);
}

// Test: Setting name with special characters
TEST_F(WXMPMetaSetObjectNameTest_2042, SetNameWithSpecialChars_2042) {
    WXMP_Result wResult;
    const char* specialName = "Name with spaces & <special> \"chars\"!";
    WXMPMeta_SetObjectName_1(MetaToRef(meta), specialName, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, specialName);
}

// Test: Setting name after setting to null (empty), then setting a real name
TEST_F(WXMPMetaSetObjectNameTest_2042, SetNullThenRealName_2042) {
    WXMP_Result wResult;
    WXMPMeta_SetObjectName_1(MetaToRef(meta), nullptr, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    WXMPMeta_SetObjectName_1(MetaToRef(meta), "RealName", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, "RealName");
}

// Test: WXMP_Result is properly initialized before call (no error)
TEST_F(WXMPMetaSetObjectNameTest_2042, ResultInitializedProperly_2042) {
    WXMP_Result wResult;
    EXPECT_EQ(wResult.errMessage, nullptr);
    WXMPMeta_SetObjectName_1(MetaToRef(meta), "Test", &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Setting name with Unicode/UTF-8 content
TEST_F(WXMPMetaSetObjectNameTest_2042, SetUTF8Name_2042) {
    WXMP_Result wResult;
    const char* utf8Name = u8"Ünïcödé Nàmé";
    WXMPMeta_SetObjectName_1(MetaToRef(meta), utf8Name, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    EXPECT_STREQ(namePtr, utf8Name);
}
