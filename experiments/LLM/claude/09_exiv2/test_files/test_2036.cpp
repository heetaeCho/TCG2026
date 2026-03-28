#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" {
void WXMPMeta_Sort_1(XMPMetaRef xmpRef, WXMP_Result* wResult);
}

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaSortTest_2036 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test that Sort on a valid, empty XMPMeta object succeeds without error
TEST_F(WXMPMetaSortTest_2036, SortEmptyMeta_2036) {
    XMPMeta meta;
    WXMP_Result result;

    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test that Sort on a valid XMPMeta with properties succeeds without error
TEST_F(WXMPMetaSortTest_2036, SortMetaWithProperties_2036) {
    XMPMeta meta;

    // Add some properties in non-sorted order
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreateDate", "2023-01-01", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Test Title", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "creator", "Author", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test that Sort does not lose properties
TEST_F(WXMPMetaSortTest_2036, SortPreservesProperties_2036) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Test Title", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Verify properties still exist after sort
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreatorTool"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "title"));
}

// Test that Sort preserves property values
TEST_F(WXMPMetaSortTest_2036, SortPreservesPropertyValues_2036) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "MyTool", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);

    XMP_StringPtr value = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, &valueSize, &options);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "MyTool");
}

// Test that Sort with null xmpRef sets an error in the result
TEST_F(WXMPMetaSortTest_2036, SortNullRef_2036) {
    WXMP_Result result;
    WXMPMeta_Sort_1(nullptr, &result);

    // When passed a null ref, the wrapper should report an error
    EXPECT_NE(result.errMessage, nullptr);
}

// Test that calling Sort multiple times is idempotent
TEST_F(WXMPMetaSortTest_2036, SortIdempotent_2036) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "ZetaProp", "Z", 0);
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "AlphaProp", "A", 0);
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "BetaProp", "B", 0);

    WXMP_Result result1;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result1);
    EXPECT_EQ(result1.errMessage, nullptr);

    // Sort again - should still succeed and produce the same result
    WXMP_Result result2;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result2);
    EXPECT_EQ(result2.errMessage, nullptr);

    // Properties should still be intact
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "ZetaProp"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "AlphaProp"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "BetaProp"));
}

// Test WXMP_Result is properly initialized when sort succeeds
TEST_F(WXMPMetaSortTest_2036, ResultInitialized_2036) {
    XMPMeta meta;
    WXMP_Result result;

    // Verify result starts clean
    EXPECT_EQ(result.errMessage, nullptr);

    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    // After successful call, errMessage should remain null
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test Sort with array items
TEST_F(WXMPMetaSortTest_2036, SortWithArrayItems_2036) {
    XMPMeta meta;

    meta.AppendArrayItem("http://purl.org/dc/elements/1.1/", "subject", kXMP_PropArrayIsUnordered, "Zebra", 0);
    meta.AppendArrayItem("http://purl.org/dc/elements/1.1/", "subject", kXMP_PropArrayIsUnordered, "Apple", 0);
    meta.AppendArrayItem("http://purl.org/dc/elements/1.1/", "subject", kXMP_PropArrayIsUnordered, "Banana", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Array items should still be accessible
    XMP_Index count = meta.CountArrayItems("http://purl.org/dc/elements/1.1/", "subject");
    EXPECT_EQ(count, 3);
}

// Test Sort with struct fields
TEST_F(WXMPMetaSortTest_2036, SortWithStructFields_2036) {
    XMPMeta meta;

    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "MyStruct",
                         "http://ns.adobe.com/xap/1.0/", "FieldZ", "ValueZ", 0);
    meta.SetStructField("http://ns.adobe.com/xap/1.0/", "MyStruct",
                         "http://ns.adobe.com/xap/1.0/", "FieldA", "ValueA", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Struct fields should still exist
    EXPECT_TRUE(meta.DoesStructFieldExist("http://ns.adobe.com/xap/1.0/", "MyStruct",
                                           "http://ns.adobe.com/xap/1.0/", "FieldZ"));
    EXPECT_TRUE(meta.DoesStructFieldExist("http://ns.adobe.com/xap/1.0/", "MyStruct",
                                           "http://ns.adobe.com/xap/1.0/", "FieldA"));
}

// Test Sort after Erase (empty meta)
TEST_F(WXMPMetaSortTest_2036, SortAfterErase_2036) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "SomeProp", "SomeValue", 0);
    meta.Erase();

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test Sort with multiple namespaces
TEST_F(WXMPMetaSortTest_2036, SortMultipleNamespaces_2036) {
    XMPMeta meta;

    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "PropB", "ValB", 0);
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "PropA", "ValA", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "creator", "Auth", 0);
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Title", 0);
    meta.SetProperty("http://ns.adobe.com/photoshop/1.0/", "City", "NYC", 0);

    WXMP_Result result;
    WXMPMeta_Sort_1(MetaToRef(&meta), &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // All properties should still exist
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "PropB"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "PropA"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "creator"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://purl.org/dc/elements/1.1/", "title"));
    EXPECT_TRUE(meta.DoesPropertyExist("http://ns.adobe.com/photoshop/1.0/", "City"));
}
