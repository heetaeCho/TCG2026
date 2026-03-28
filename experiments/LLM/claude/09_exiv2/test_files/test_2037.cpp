#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#include "XMPMeta.hpp"
#include "WXMP_Common.hpp"

// Forward declaration of the wrapper function under test
extern "C" {
void WXMPMeta_Erase_1(XMPMetaRef xmpRef, WXMP_Result* wResult);
}

// Helper to convert XMPMeta* to XMPMetaRef (opaque pointer)
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaEraseTest_2037 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP toolkit is initialized
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test that Erase on a freshly created (empty) XMPMeta succeeds without error
TEST_F(WXMPMetaEraseTest_2037, EraseEmptyMeta_2037) {
    XMPMeta meta;
    WXMP_Result wResult;

    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr)
        << "Erase on empty meta should not produce an error";
}

// Test that Erase clears properties that were previously set
TEST_F(WXMPMetaEraseTest_2037, EraseClearsProperties_2037) {
    XMPMeta meta;

    // Set a property
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);

    // Verify the property exists before erase
    ASSERT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));

    WXMP_Result wResult;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr)
        << "Erase should not produce an error";

    // After erase, the property should no longer exist
    EXPECT_FALSE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"))
        << "Property should not exist after Erase";
}

// Test that Erase clears multiple properties from different namespaces
TEST_F(WXMPMetaEraseTest_2037, EraseClearsMultipleProperties_2037) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "TestTitle", 0);

    ASSERT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));
    ASSERT_TRUE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "title"));

    WXMP_Result wResult;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_FALSE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));
    EXPECT_FALSE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "title"));
}

// Test that calling Erase twice in succession does not cause an error
TEST_F(WXMPMetaEraseTest_2037, EraseCalledTwice_2037) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);

    WXMP_Result wResult1;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    WXMP_Result wResult2;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);

    EXPECT_FALSE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));
}

// Test that Erase clears the object name as well
TEST_F(WXMPMetaEraseTest_2037, EraseClearsObjectName_2037) {
    XMPMeta meta;
    meta.SetObjectName("TestObject");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta.GetObjectName(&namePtr, &nameLen);
    ASSERT_GT(nameLen, 0u);

    WXMP_Result wResult;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    meta.GetObjectName(&namePtr, &nameLen);
    EXPECT_EQ(nameLen, 0u)
        << "Object name should be cleared after Erase";
}

// Test that after Erase, new properties can be set again
TEST_F(WXMPMetaEraseTest_2037, EraseAllowsReuse_2037) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "OldTool", 0);

    WXMP_Result wResult;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // Set a new property after erase
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "NewTool", 0);
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, &valueLen, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "NewTool");
}

// Test that Erase with a null xmpRef sets an error message in the result
TEST_F(WXMPMetaEraseTest_2037, EraseWithNullRef_2037) {
    WXMP_Result wResult;
    WXMPMeta_Erase_1(nullptr, &wResult);

    // When passing a null reference, we expect an error to be reported
    EXPECT_NE(wResult.errMessage, nullptr)
        << "Erase with null ref should report an error";
}

// Test that WXMP_Result is properly initialized and Erase does not corrupt it
TEST_F(WXMPMetaEraseTest_2037, ResultInitialization_2037) {
    WXMP_Result wResult;
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMPMeta meta;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that Erase clears array items
TEST_F(WXMPMetaEraseTest_2037, EraseClearsArrayItems_2037) {
    XMPMeta meta;

    meta.AppendArrayItem("http://purl.org/dc/elements/1.1/", "subject",
                         kXMP_PropArrayIsUnordered, "keyword1", 0);
    meta.AppendArrayItem("http://purl.org/dc/elements/1.1/", "subject",
                         kXMP_PropArrayIsUnordered, "keyword2", 0);

    ASSERT_TRUE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "subject"));
    ASSERT_TRUE(meta.DoesArrayItemExist("http://purl.org/dc/elements/1.1/", "subject", 1));

    WXMP_Result wResult;
    WXMPMeta_Erase_1(MetaToRef(&meta), &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_FALSE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "subject"));
    EXPECT_FALSE(meta.DoesArrayItemExist("http://purl.org/dc/elements/1.1/", "subject", 1));
}
