#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" {
    typedef XMPMeta* XMPMetaRef;
    void WXMPMeta_Clone_1(XMPMetaRef xmpRef, XMP_OptionBits options, WXMP_Result* wResult);
}

class WXMPMetaCloneTest_2038 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Cloning a default (empty) XMPMeta object succeeds
TEST_F(WXMPMetaCloneTest_2038, CloneEmptyMeta_2038) {
    XMPMeta original;
    WXMP_Result wResult;

    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    // Clean up the cloned object
    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);
    delete clone;
}

// Test: Clone returns a different object than the original
TEST_F(WXMPMetaCloneTest_2038, CloneReturnsDifferentObject_2038) {
    XMPMeta original;
    WXMP_Result wResult;

    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);
    EXPECT_NE(wResult.ptrResult, static_cast<void*>(&original));

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);
    delete clone;
}

// Test: Clone preserves properties set on the original
TEST_F(WXMPMetaCloneTest_2038, ClonePreservesProperties_2038) {
    XMPMeta original;
    original.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);

    WXMP_Result wResult;
    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits propOptions = 0;
    bool found = clone->GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool",
                                     &propValue, &valueSize, &propOptions);

    EXPECT_TRUE(found);
    if (found && propValue != nullptr) {
        EXPECT_STREQ(propValue, "TestTool");
    }

    delete clone;
}

// Test: Clone with zero options produces a valid result
TEST_F(WXMPMetaCloneTest_2038, CloneWithZeroOptions_2038) {
    XMPMeta original;
    WXMP_Result wResult;

    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);
    delete clone;
}

// Test: Clone clientRefs is zero on the newly cloned object
TEST_F(WXMPMetaCloneTest_2038, CloneClientRefsIsZero_2038) {
    XMPMeta original;
    WXMP_Result wResult;

    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);
    // clientRefs is public, so we can check it
    EXPECT_EQ(clone->clientRefs, 0);

    delete clone;
}

// Test: Clone of meta with multiple properties preserves all of them
TEST_F(WXMPMetaCloneTest_2038, ClonePreservesMultipleProperties_2038) {
    XMPMeta original;
    original.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "Tool1", 0);
    original.SetProperty("http://purl.org/dc/elements/1.1/", "title", "MyTitle", 0);

    WXMP_Result wResult;
    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;

    bool found1 = clone->GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool",
                                      &propValue, &valueSize, nullptr);
    EXPECT_TRUE(found1);
    if (found1 && propValue) {
        EXPECT_STREQ(propValue, "Tool1");
    }

    bool found2 = clone->GetProperty("http://purl.org/dc/elements/1.1/", "title",
                                      &propValue, &valueSize, nullptr);
    EXPECT_TRUE(found2);
    if (found2 && propValue) {
        EXPECT_STREQ(propValue, "MyTitle");
    }

    delete clone;
}

// Test: Modifying clone does not affect original
TEST_F(WXMPMetaCloneTest_2038, CloneIsIndependentFromOriginal_2038) {
    XMPMeta original;
    original.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "OriginalTool", 0);

    WXMP_Result wResult;
    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);

    // Modify the clone
    clone->SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "ModifiedTool", 0);

    // Verify original is unchanged
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    bool found = original.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool",
                                       &propValue, &valueSize, nullptr);
    EXPECT_TRUE(found);
    if (found && propValue) {
        EXPECT_STREQ(propValue, "OriginalTool");
    }

    delete clone;
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPMetaCloneTest_2038, ResultInitializedCorrectly_2038) {
    WXMP_Result wResult;

    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.ptrResult, nullptr);
}

// Test: Clone of meta with object name preserves it
TEST_F(WXMPMetaCloneTest_2038, ClonePreservesObjectName_2038) {
    XMPMeta original;
    original.SetObjectName("TestObjectName");

    WXMP_Result wResult;
    WXMPMeta_Clone_1(&original, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(wResult.ptrResult, nullptr);

    XMPMeta* clone = static_cast<XMPMeta*>(wResult.ptrResult);

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    clone->GetObjectName(&namePtr, &nameLen);

    if (namePtr != nullptr) {
        EXPECT_STREQ(namePtr, "TestObjectName");
    }

    delete clone;
}

// Test: Multiple clones from the same original are independent
TEST_F(WXMPMetaCloneTest_2038, MultipleCloneIndependence_2038) {
    XMPMeta original;
    original.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "SharedTool", 0);

    WXMP_Result wResult1;
    WXMPMeta_Clone_1(&original, 0, &wResult1);
    ASSERT_NE(wResult1.ptrResult, nullptr);
    XMPMeta* clone1 = static_cast<XMPMeta*>(wResult1.ptrResult);

    WXMP_Result wResult2;
    WXMPMeta_Clone_1(&original, 0, &wResult2);
    ASSERT_NE(wResult2.ptrResult, nullptr);
    XMPMeta* clone2 = static_cast<XMPMeta*>(wResult2.ptrResult);

    // They should be different objects
    EXPECT_NE(clone1, clone2);

    // Modifying one clone shouldn't affect the other
    clone1->SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "Clone1Tool", 0);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    bool found = clone2->GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool",
                                      &propValue, &valueSize, nullptr);
    EXPECT_TRUE(found);
    if (found && propValue) {
        EXPECT_STREQ(propValue, "SharedTool");
    }

    delete clone1;
    delete clone2;
}
